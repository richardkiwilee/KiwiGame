#pragma once
#ifndef UNIT_H
#define UNIT_H

#ifdef UNIT_EXPORTS
#define UNIT_API __declspec(dllexport)
#else
#define UNIT_API __declspec(dllimport)
#endif

class UNIT_API Unit {
public:
    Unit();
    ~Unit();
    void MyMethod();
};

#endif
