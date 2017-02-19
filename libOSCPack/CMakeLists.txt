cmake_minimum_required(VERSION 2.8)
PROJECT(LIBOSCPACK)

ADD_LIBRARY(OSCPack
            OscTypes.cpp 
            OscReceivedElements.cpp
            OscPrintReceivedElements.cpp
            OscOutboundPacketStream.cpp
)


