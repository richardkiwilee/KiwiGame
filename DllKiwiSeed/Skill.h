#pragma once
#ifndef SKILL_H
#define SKILL_H

#ifdef SKILL_EXPORTS
#define SKILL_API __declspec(dllexport)
#else
#define SKILL_API __declspec(dllimport)
#endif

class SKILL_API Skill {
public:
    Skill();
    ~Skill();
    void MyMethod();
};

#endif
