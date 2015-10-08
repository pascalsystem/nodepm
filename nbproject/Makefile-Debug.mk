#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/app/ConfigLoader.o \
	${OBJECTDIR}/app/HelpMe.o \
	${OBJECTDIR}/app/Manager.o \
	${OBJECTDIR}/lib/Command/CommandAbstract.o \
	${OBJECTDIR}/lib/Command/CommandStdIn.o \
	${OBJECTDIR}/lib/Command/CommandUnixSock.o \
	${OBJECTDIR}/lib/Logger/LoggerAbstract.o \
	${OBJECTDIR}/lib/Logger/LoggerConsole.o \
	${OBJECTDIR}/lib/Logger/LoggerFileOut.o \
	${OBJECTDIR}/lib/Process/ConfigAbstract.o \
	${OBJECTDIR}/lib/Process/ConfigNodeJS.o \
	${OBJECTDIR}/lib/Process/Item.o \
	${OBJECTDIR}/lib/Settings/SettingsAbstract.o \
	${OBJECTDIR}/lib/Settings/SettingsIni.o \
	${OBJECTDIR}/lib/Socket/SocketServerAbstract.o \
	${OBJECTDIR}/lib/Socket/SocketServerPort.o \
	${OBJECTDIR}/lib/Socket/SocketServerUnix.o \
	${OBJECTDIR}/lib/Utils/Directory.o \
	${OBJECTDIR}/lib/Utils/FileWriter.o \
	${OBJECTDIR}/lib/Utils/ProcSingleton.o \
	${OBJECTDIR}/lib/Utils/User.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nodepm

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nodepm: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nodepm ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/app/ConfigLoader.o: app/ConfigLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/app
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app/ConfigLoader.o app/ConfigLoader.cpp

${OBJECTDIR}/app/HelpMe.o: app/HelpMe.cpp 
	${MKDIR} -p ${OBJECTDIR}/app
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app/HelpMe.o app/HelpMe.cpp

${OBJECTDIR}/app/Manager.o: app/Manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/app
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app/Manager.o app/Manager.cpp

${OBJECTDIR}/lib/Command/CommandAbstract.o: lib/Command/CommandAbstract.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Command
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Command/CommandAbstract.o lib/Command/CommandAbstract.cpp

${OBJECTDIR}/lib/Command/CommandStdIn.o: lib/Command/CommandStdIn.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Command
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Command/CommandStdIn.o lib/Command/CommandStdIn.cpp

${OBJECTDIR}/lib/Command/CommandUnixSock.o: lib/Command/CommandUnixSock.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Command
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Command/CommandUnixSock.o lib/Command/CommandUnixSock.cpp

${OBJECTDIR}/lib/Logger/LoggerAbstract.o: lib/Logger/LoggerAbstract.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Logger
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Logger/LoggerAbstract.o lib/Logger/LoggerAbstract.cpp

${OBJECTDIR}/lib/Logger/LoggerConsole.o: lib/Logger/LoggerConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Logger
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Logger/LoggerConsole.o lib/Logger/LoggerConsole.cpp

${OBJECTDIR}/lib/Logger/LoggerFileOut.o: lib/Logger/LoggerFileOut.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Logger
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Logger/LoggerFileOut.o lib/Logger/LoggerFileOut.cpp

${OBJECTDIR}/lib/Process/ConfigAbstract.o: lib/Process/ConfigAbstract.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Process
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Process/ConfigAbstract.o lib/Process/ConfigAbstract.cpp

${OBJECTDIR}/lib/Process/ConfigNodeJS.o: lib/Process/ConfigNodeJS.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Process
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Process/ConfigNodeJS.o lib/Process/ConfigNodeJS.cpp

${OBJECTDIR}/lib/Process/Item.o: lib/Process/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Process
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Process/Item.o lib/Process/Item.cpp

${OBJECTDIR}/lib/Settings/SettingsAbstract.o: lib/Settings/SettingsAbstract.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Settings
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Settings/SettingsAbstract.o lib/Settings/SettingsAbstract.cpp

${OBJECTDIR}/lib/Settings/SettingsIni.o: lib/Settings/SettingsIni.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Settings
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Settings/SettingsIni.o lib/Settings/SettingsIni.cpp

${OBJECTDIR}/lib/Socket/SocketServerAbstract.o: lib/Socket/SocketServerAbstract.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Socket
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Socket/SocketServerAbstract.o lib/Socket/SocketServerAbstract.cpp

${OBJECTDIR}/lib/Socket/SocketServerPort.o: lib/Socket/SocketServerPort.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Socket
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Socket/SocketServerPort.o lib/Socket/SocketServerPort.cpp

${OBJECTDIR}/lib/Socket/SocketServerUnix.o: lib/Socket/SocketServerUnix.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Socket
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Socket/SocketServerUnix.o lib/Socket/SocketServerUnix.cpp

${OBJECTDIR}/lib/Utils/Directory.o: lib/Utils/Directory.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Utils/Directory.o lib/Utils/Directory.cpp

${OBJECTDIR}/lib/Utils/FileWriter.o: lib/Utils/FileWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Utils/FileWriter.o lib/Utils/FileWriter.cpp

${OBJECTDIR}/lib/Utils/ProcSingleton.o: lib/Utils/ProcSingleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Utils/ProcSingleton.o lib/Utils/ProcSingleton.cpp

${OBJECTDIR}/lib/Utils/User.o: lib/Utils/User.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/Utils/User.o lib/Utils/User.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nodepm

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
