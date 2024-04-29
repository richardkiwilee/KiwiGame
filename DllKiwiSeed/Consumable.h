#pragma once
#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#ifdef CONSUMABLE_EXPORTS
#define CONSUMABLE_API __declspec(dllexport)
#else
#define CONSUMABLE_API __declspec(dllimport)
#endif

class CONSUMABLE_API Consumable {
public:
    Consumable();
    ~Consumable();
    void MyMethod();
};

#endif
