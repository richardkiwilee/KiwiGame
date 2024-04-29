#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#ifdef EQUIPMENT_EXPORTS
#define EQUIPMENT_API __declspec(dllexport)
#else
#define EQUIPMENT_API __declspec(dllimport)
#endif

class EQUIPMENT_API Equipment {
public:
    Equipment();
    ~Equipment();
    void MyMethod();
};

#endif
