#pragma once

#include <string>

using namespace std;

class Question
{
protected:
    size_t type;
    size_t level;
    string question;

public:
    Question()
    {
        type = 0;
        level = 0;
        question = "";
    }

    Question(const string _question, const size_t _type, const size_t _level)
    {
        type = _type;
        level = _level;
        question = _question;
    }

    ~Question()
    {
        
    }

    string getQuestion(void) const
    {
        return question;
    }

    size_t getLevel(void) const
    {
        return level;
    }

    size_t getType(void) const
    {
        return type;
    }

    void setQuestion(const string _question)
    {
        question = _question;
    }

    void setLevel(const size_t _level)
    {
        level = _level;
    }

    void setType(const size_t _type)
    {
        type = _type;
    }

    void print() const;

};
