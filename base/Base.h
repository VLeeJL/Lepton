//
// Created by user on 18-12-17.
//

#ifndef LEPTON_BASE_H
#define LEPTON_BASE_H
#define NOCOPYABLE(ClassType)\
    ClassType(const ClassType&) = delete;\
    ClassType& operator=(const ClassType&) = delete;

#endif //LEPTON_BASE_H
