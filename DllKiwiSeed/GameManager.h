#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#ifdef GAMEMANAGER_EXPORTS
#define GAMEMANAGER_API __declspec(dllexport)
#else
#define GAMEMANAGER_API __declspec(dllimport)
#endif

class GAMEMANAGER_API GameManager {
public:
    GameManager();
    ~GameManager();
    void MyMethod();
};

#endif