#pragma once
#ifndef QUADMAP_H
#define QUADMAP_H

#ifdef QUADMAP_EXPORTS
#define QUADMAP_API __declspec(dllexport)
#else
#define QUADMAP_API __declspec(dllimport)
#endif

class QUADMAP_API QuadMap {
public:
    QuadMap();
    ~QuadMap();
    void MyMethod();
};

#endif