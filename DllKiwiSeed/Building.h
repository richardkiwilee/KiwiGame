#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#ifdef BUILDING_EXPORTS
#define BUILDING_API __declspec(dllexport)
#else
#define BUILDING_API __declspec(dllimport)
#endif

class BUILDING_API Building {
public:
    Building();
    ~Building();
    void MyMethod();
};

#endif