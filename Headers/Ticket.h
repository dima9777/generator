#pragma once

#include <string>
#include "Question.h"

using namespace std;

class Ticket
{
protected:
    Question theory;
    Question practice;

public:
    Ticket()
    {
        theory = Question();
        practice = Question();
    }

    Ticket(const Question t, const Question p)
    {
        theory = t;
        practice = p;
    }

    ~Ticket()
    {
        theory.~Question();
        practice.~Question();
    }

    Question getTheory(void) const
    {
        return theory;
    }

    Question getPractice(void) const
    {
        return practice;
    }

    size_t getLevel(void) const
    {
        return theory.getLevel() + practice.getLevel();
    }

    void setTheory(const Question q)
    {
        theory = q;
    }

    void setPractice(const Question q)
    {
        practice = q;
    }

    void print() const;

};
