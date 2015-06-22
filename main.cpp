/*
 * File:   main.cpp
 * Author: info@pascalsystem.pl
 *
 * Created on 12 maj 2015, 20:49
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "./app/Manager.h"
#include "./app/HelpMe.h"
#include "./app/ConfigLoader.h"
#include "./lib/Settings/SettingsAbstract.h"
#include "./lib/Command/CommandStdIn.h"
#include "./lib/Logger/LoggerFileOut.h"
#include "./lib/Utils/ProcSingleton.h"
#include "./lib/Command/CommandUnixSock.h"

using namespace NodePM;
using namespace PascalSystem::Settings;
using namespace PascalSystem::Utils;

/**
 * Manager instance
 * 
 * @var NodePM::Manager*
 */
Manager* manager = NULL;

/**
 * Bool command mode
 * 
 * @var bool
 */
bool commandMode = false;

/**
 * Process command on manager
 * 
 * @param std::string msg
 * @return std::string
 */
std::string procCommand(std::string msg) {
    try {
        if (msg == "start") {
            manager->start();
        } else if (msg == "stop") {
            manager->stop(commandMode);
        } else if (msg == "restart") {
            if (commandMode) {
                manager->stop(commandMode);
                manager->start();
            } else {
                std::runtime_error("command restart allow only on console mode in command");
            }
        } else if (msg == "reload") {
            manager->reload();
        } else if (msg.find("reload ") == 0) {
            manager->reload(msg.substr(strlen("reload ")));
        } else if (msg.find("restart ") == 0) {
            manager->restart(msg.substr(strlen("restart ")));
        } else {
            std::string err = "unknown command: ";
            err.append(msg);
            throw std::runtime_error(err.c_str());
        }
        std::string res = "Success command: ";
        res.append(msg);
        return res;
    } catch (std::runtime_error &ex) {
        std::string res = "Error[runtime_error]: ";
        res.append(ex.what());
        return res;
    } catch (std::exception &ex) {
        std::string res = "Error[exception]: ";
        res.append(ex.what());
        return res;
    }
    return "Error: UNKNOWN ERROR.";
}

/**
 * Redirect console out data and error to logger
 * 
 * @param PascalSystem::Logger::LoggerFileOut* log
 */
void redirectConsoleOutToFile(PascalSystem::Logger::LoggerFileOut* log) {
    int stdOut[2];
    int stdErr[2];
    pipe(stdOut);
    pipe(stdErr);
    dup2(stdOut[1], STDOUT_FILENO);
    dup2(stdErr[1], STDERR_FILENO);
    
    log->asyncWriteFromHandler(stdOut[0], PascalSystem::Logger::LoggerAbstract::LOG_TYPE_INFO);
    log->asyncWriteFromHandler(stdErr[0], PascalSystem::Logger::LoggerAbstract::LOG_TYPE_ERR);
}

/*
 * Main function
 *
 * @param int argc
 * @param char** argv
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Application required parameters, see --help" << std::endl;
        return EXIT_FAILURE;
    }
    
    SettingsAbstract* config = ConfigLoader::getConfig();
    config->load();
    
    std::string appCommand = "";
    for (int i=1; i<argc;i++) {
        if (strcmp(argv[i], "--console=command") == 0) {
            commandMode = true;
            manager = new Manager(config);
            PascalSystem::Command::CommandStdIn* cmd = new PascalSystem::Command::CommandStdIn();
            cmd->setHandler(procCommand);
            cmd->run();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "--help") == 0) {
            std::cout << NodePM::HelpMe::getData();
            return EXIT_SUCCESS;
        }
        
        if (i > 1) {
            appCommand.append(" ");
        }
        appCommand.append(argv[i]);
    }
    
    std::string managerSocket = config->getStringValue("managerSocket");
    std::string pidFileName = config->getStringValue("managerPid");
    
    std::string unixPath = managerSocket;
    ProcSingleton* procPid = new ProcSingleton(pidFileName, true);
    bool dameonLive = procPid->createPid(getpid()) ? false : true;
    
    if (dameonLive) {
        std::cout << "Send message command: " << appCommand << " to NodePM:" << std::endl;
        std::string result = PascalSystem::Command::CommandUnixSock::sendMessageToServer(unixPath, appCommand);
        std::cout << "Result:" << result << std::endl;
        return EXIT_SUCCESS;
    }
    
    if (appCommand != "start") {
        std::cerr << std::endl;
        std::cerr << "Incorrect command, see --help." << std::endl;
        std::cerr << std::endl;
        return EXIT_FAILURE;
    }
    
    manager = new Manager(config);
    if (!config->exists("nodepmErrorFilePath") || !config->exists("nodepmDebugFilePath")) {
        std::cerr << std::endl;
        std::cerr << "Not found in settings nodepmErrorFilePath or nodepmDebugFilePath properties.";
        std::cerr << std::endl;
        return EXIT_FAILURE;
    }
    std::string nodepmErrorFilePath = config->getStringValue("nodepmErrorFilePath");
    std::string nodepmDebugFilePath = config->getStringValue("nodepmDebugFilePath");

    pid_t dameonPid = fork();
    if (dameonPid < 0) {
        std::cerr << std::endl;
        std::cerr << "can`t start NodePM dameon" << std::endl;
        std::cerr << std::endl;
        return EXIT_FAILURE;
    } else if (dameonPid == 0) {
        PascalSystem::Logger::LoggerFileOut* logger = new PascalSystem::Logger::LoggerFileOut(nodepmErrorFilePath, nodepmDebugFilePath);
        redirectConsoleOutToFile(logger);
        
        PascalSystem::Command::CommandUnixSock::reqisterInstance(unixPath);
        PascalSystem::Command::CommandUnixSock* cmd = PascalSystem::Command::CommandUnixSock::getInstance();
        cmd->setHandler(&procCommand);
        cmd->executeCommand("start");
        cmd->run();
        procPid->destroyPid();
        exit(EXIT_SUCCESS);
    }
    
    sleep(1);
    std::cout << std::endl;
    std::cout << "Dameon running." << std::endl;
    std::cout << "Dameon log file: " << nodepmDebugFilePath << std::endl;
    std::cout << "Dameon err file: " << nodepmErrorFilePath << std::endl;
    return EXIT_SUCCESS;
}
