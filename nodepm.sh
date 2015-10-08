#!/bin/bash

NODEPMAPP="`dirname $0`/dist/Debug/GNU-Linux-x86/nodepm"

if [ "$1" = "" ]
then
    echo "NodePM bash script: required parameters."
    exit
fi

if [ "$1" == "start" ]
then
    if [ "$2" != "" ]
    then
        echo "NodePM bash script: start allowed only without any parameters"
        exit
    fi
    
    ${NODEPMAPP} start
    exit
fi

if [ "$1" == "stop" ]
then
    if [ "$2" != "" ]
    then
        echo "NodePM bash script: stop allowed only without any parameters"
        exit
    fi
    
    ${NODEPMAPP} stop
    exit
fi

if [ "$1" == "restart" ] && [ "$2" == "" ]
then
    ${NODEPMAPP} stop
    ${NODEPMAPP} start
    exit
fi

if [ "$1" == "restart" ] && [ "$2" != "" ]
then
    ${NODEPMAPP} restart $2
    exit
fi

if [ "$1" == "reload" ] && [ "$2" == "" ]
then
    ${NODEPMAPP} reload
    exit
fi

if [ "$1" == "reload" ] && [ "$2" != "" ]
then
    ${NODEPMAPP} reload $2
    exit
fi

${NODEPMAPP} $1
