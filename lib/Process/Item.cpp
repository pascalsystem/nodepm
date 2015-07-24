/* 
 * File:   Item.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 12 maj 2015, 21:59
 */

#include "Item.h"

void *PascalSystem::Process::Item::threadTransmitOutputData(void* This) {
    ThreadProcessTransmitOutput* data = ((ThreadProcessTransmitOutput*)This);
    data->output->writeFromHandler(data->handler, data->type);
}

void *PascalSystem::Process::Item::threadPermissionUnixDomain(void* This) {
    PascalSystem::Process::Item* item = ((PascalSystem::Process::Item*)This);
    sleep(1);
    if (item->isEnvUnixDomain()) {
        std::string envPortValue = item->getConfig()->getEnvironment("PORT");
        int maxTryNum = 30;
        int current = 0;
        do {
            current++;
            char mode[] = "0777";
            int mask = strtol(mode, 0, 8);
            usleep(250000);
            if (chmod(envPortValue.c_str(), mask) == 0) {
                break;
            }
        } while (current < maxTryNum);
    }
    item->envPortStarted = true;
}

void PascalSystem::Process::Item::run() {
    pid = -1;
    envPortStarted = false;
    
    int pipeOut[2];
    int pipeErr[2];
    int init[2];
    pipe(pipeOut);
    pipe(pipeErr);
    pipe(init);
    
    //kill defunct process
    signal(SIGCHLD, SIG_IGN);
    
    pid_t cpid = fork();
    if (cpid == 0) {
        //kill chid when parent die
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        
        dup2(pipeOut[1], STDOUT_FILENO);
        dup2(pipeErr[1], STDERR_FILENO);
        close(pipeOut[0]);
        close(pipeErr[0]);
        
        std::ostringstream pidSS;
        pidSS << getpid();
        if (write(init[1], pidSS.str().c_str(), pidSS.str().length()) != pidSS.str().length()) {
            char buf[2];
            read(init[0], &buf, 2);
            if (buf != "ok") {
                throw std::runtime_error("Problem with get child pid");
            }
        }
        close(init[0]);
        close(init[1]);
        
        std::list<std::string> commandArgs = config->getCommand();
        if (commandArgs.size() == 0) {
            throw std::runtime_error("Required minimum one command parameters");
        }
        
        int commandIndex = 0;
        const char* args[commandArgs.size() + 1];
        for (std::list<std::string>::iterator it = commandArgs.begin(); it != commandArgs.end(); it++) {
            args[commandIndex++] = it->c_str();
        }
        args[commandIndex] = 0;
        
        int execRes;
        if (config->hasEnvironments()) {
            if (this->isEnvUnixDomain()) {
                unlink(config->getEnvironment("PORT").c_str());
            }
            std::list<std::string> environments = config->getEnvironments();
            int envIndex = 0;
            const char* envArgs[environments.size() + 1];
            for (std::list<std::string>::iterator it = environments.begin(); it != environments.end(); it++) {
                envArgs[envIndex++] = it->c_str();
            }
            envArgs[envIndex] = 0;
            execRes = execve(args[0], const_cast<char**>(args), const_cast<char**>(envArgs));
        } else {
            execRes = execv(args[0], const_cast<char**>(args));
        }
        
        if (execRes != 0) {
            std::ostringstream ss;
            ss << "Error start process: ";
            for (int i=0;commandArgs.size();i++) {
                if (i > 0) {
                    ss << " ";
                }
                ss << args[i];
            }
            std::cerr << ss.str() << std::endl;
            exit(EXIT_FAILURE);
        }
        
        close(pipeOut[1]);
        close(pipeErr[1]);
        close(init[1]);
        
        exit(EXIT_SUCCESS);
    } else if (cpid < 0) {
        return;
    }
    
    close(pipeOut[1]);
    close(pipeErr[1]);
    
    pthread_t tP;
    pthread_create(&tP, NULL, &threadPermissionUnixDomain, this);
    pthread_detach(tP);
    
    char bufPid[11];
    int bufPidBytes = read(init[0], &bufPid, 11);
    std::stringstream bufPidSS;
    bufPidSS << bufPid;
    pid = atoi(bufPidSS.str().substr(0, bufPidBytes).c_str());
    write(init[1], "OK", 2);
    close(init[0]);
    close(init[1]);
    
    ThreadProcessTransmitOutput* data = new ThreadProcessTransmitOutput();
    data->handler = pipeOut[0];
    data->output = logger;
    data->type = PascalSystem::Logger::LoggerAbstract::LOG_TYPE_INFO;
    pthread_create(&threadOutputLogger, NULL, &threadTransmitOutputData, data);
    pthread_detach(threadOutputLogger);
    
    logger->writeFromHandler(pipeErr[0], PascalSystem::Logger::LoggerAbstract::LOG_TYPE_ERR);
    
    close(pipeOut[0]);
    close(pipeErr[0]);
    pid = -1;
}

void PascalSystem::Process::Item::runPermanently() {
    running = true;
    int counter = 0;
    time_t lastTimeRestart = 0;
    time_t startTime = time(0);
    
    MultiErrorOption* errorOptions = config->getErrorOptions();
    
    while (running) {
        if ((lastTimeRestart != 0) && (lastTimeRestart <= startTime + errorOptions->tryIntervalSecond)) {
            counter++;
            if (counter > errorOptions->maxTryInInterval) {
                counter = 0;
                sleep(errorOptions->sleepTimeOnError);
                startTime = time(0);
            }
        }
        
        run();
        lastTimeRestart = time(0);
        counter++;
    }
}

void PascalSystem::Process::Item::hardStop() {
    running = false;
    kill(pid, SIGKILL);
    while ((pid > 0) && (kill(pid, 0) == 0)) {
        usleep(50000);
    }
    pid = -1;
}

void PascalSystem::Process::Item::stop() {
    running = false;
    int counterSigTerm = 0;
    while ((pid > 0) && (kill(pid, 0) == 0) && (counterSigTerm < 5)) {
        usleep(50000);
        counterSigTerm++;
    }
    if (pid > 0) {
        hardStop();
    }
    pid = -1;
}

int PascalSystem::Process::Item::getPid() {
    return pid;
}

bool PascalSystem::Process::Item::isEnvUnixDomain() {
    std::string envPort = config->getEnvironment("PORT");
    if ((envPort.length() > 1) && (envPort.find("/") == 0)) {
        return true;
    }
    return false;
}