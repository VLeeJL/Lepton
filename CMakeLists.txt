cmake_minimum_required(VERSION 3.13)
project(Lepton)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lepton main.cpp base/ObserverList.h base/Base.h base/ObserverList.cpp base/Utils.h TestObserver.h)