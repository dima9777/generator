#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <windows.h>
#include <iostream>;
#include <cstdlib>;

#include "Ticket.h"
#include "Question.h"

using namespace std;

#define THEORY          0
#define PRACTICE        1
#define FILE_NAME       "questions.txt"

#define Q_VECTOR        vector<vector<Question>>
#define T_VECTOR        vector<Ticket>

#define DELIMITER       "-------------"

int stringToInt(string str)
{
    return atoi(str.c_str());
}

void insertInMax(vector<Question> &v, Question q)
{
    size_t i;
    const size_t value = q.getLevel();

    for (i = 0; i < v.size() && value < v[i].getLevel(); i++);

    v.insert(v.begin() + i, q);
}

void insertInMin(vector<Question> &v, Question q)
{
    size_t i;
    const size_t value = q.getLevel();

    for (i = 0; i < v.size() && value > v[i].getLevel(); i++);

    v.insert(v.begin() + i, q);
}

void print(const Q_VECTOR questions)
{
    cout << "Теория:" << endl;
    for (size_t i = 0, size = questions[THEORY].size(); i < size; i++)
    {
        cout << "Вопрос: " << questions[THEORY][i].getQuestion() << endl;
        cout << "Сложность: " << questions[THEORY][i].getLevel() << endl;
    }
    cout << endl;

    cout << "Практика:" << endl;
    for (size_t i = 0, size = questions[PRACTICE].size(); i < size; i++)
    {
        cout << "Вопрос: " << questions[PRACTICE][i].getQuestion() << endl;
        cout << "Сложность: " << questions[PRACTICE][i].getLevel() << endl;
    }
    cout << endl;
}

void print(const T_VECTOR tickets)
{
    cout << "Список билетов:" << endl << endl;
    for (size_t i = 0, size = tickets.size(); i < size; i++)
    {
        cout << DELIMITER << endl;
        cout << "Билет №" << i + 1 << endl;
        cout << DELIMITER << endl;
        tickets[i].print();
        cout << endl << "Общая сложность: " << tickets[i].getLevel() << endl;
        cout << DELIMITER << endl << endl;
    }
}

void checkQuestionsSize(const Q_VECTOR questions)
{
    if (questions[THEORY].size() != questions[PRACTICE].size() && questions[THEORY].size() < 2)
    {
        cout << "Invalid questions size!" << endl;
        system("pause");
        exit(1);
    }
}

Q_VECTOR initQuestions(const string fileName)
{
    ifstream file(fileName);

    Q_VECTOR questions(2);

    string str;                 // string from file
    size_t type = THEORY;       // question type
    string question;
    size_t linePosition = 1;

    while (getline(file, str))
    {
        switch (linePosition)
        {
            case 1:    // question name
                question = str;
                break;
            case 2:    // type
                type = str == "Практика" ? PRACTICE : THEORY;
                break;
            case 3:    // level
                const size_t level = stringToInt(str);

                Question q(question, type, level);
                
                type == PRACTICE
                    ? insertInMax(questions[PRACTICE], q)
                    : insertInMin(questions[THEORY], q);

                linePosition = 0;
                break;
        }
    
        linePosition++;
    }

    file.close();

    return questions;
}

T_VECTOR createTickets(Q_VECTOR questions)
{
    T_VECTOR tickets;

    for (size_t i = 0, size = questions[0].size(); i < size; i++)
    {
        tickets.push_back(Ticket(questions[THEORY][i], questions[PRACTICE][i]));
    }

    return tickets;
}

void showMenu()
{
    cout << "1. Посмотреть все билеты." << endl;
    cout << "2. Заменить вопрос из билета." << endl;
    cout << "3. Поменять вопросы в билетах." << endl;
}

Question createNewQuestionByConsole()
{
    size_t level;
    size_t type;
    string question;

    string str;

    cin.get();

    cout << "Введите вопрос: ";
    getline(cin, question);
    cout << endl;

    cout << "Проставьте тип вопроса (0 - теория, остальное - практика): ";
    getline(cin, str);
    type = stringToInt(str) == 0 ? THEORY : PRACTICE;
    cout << endl;

    cout << "Установите уровень сложности: ";
    getline(cin, str);
    level = stringToInt(str);
    cout << endl;

    return Question(question, type, level);
}

void setQuestionInTicketByConsole(const Question q, T_VECTOR &tickets)
{
    size_t ticketId;

    cout << "Введите номер билета, в котором хотите заменить вопрос: ";
    cin >> ticketId;
    cout << endl;

    if (ticketId <= tickets.size() && ticketId >= 0)
    {
        ticketId--;
        q.getType() == PRACTICE
            ? tickets[ticketId].setPractice(q)
            : tickets[ticketId].setTheory(q);
        cout << "OK" << endl << endl;
    }
    else
    {
        cout << "Билет с номером " << ticketId << " не найден. " << endl << endl;
    }    
}

void swap(T_VECTOR &tickets)
{
    size_t firstTicketId, secondTicketId, type;

    cout << "Введите номер билета первого билета: ";
    cin >> firstTicketId;

    cout << "Введите номер второго билета: ";
    cin >> secondTicketId;

    if (firstTicketId > tickets.size() || firstTicketId < 0)
    {
        cout << "Билет с номером " << firstTicketId << " не найден. " << endl << endl;
    }

    if (secondTicketId > tickets.size() || secondTicketId < 0)
    {
        cout << "Билет с номером " << secondTicketId << " не найден. " << endl << endl;
    }

    firstTicketId--; secondTicketId--;

    cout << "Проставьте тип вопроса (0 - теория, остальное - практика): ";
    cin >> type;
    type = type == 0 ? THEORY : PRACTICE;

    if (type == THEORY)
    {
        const Question q = tickets[firstTicketId].getTheory();

        tickets[firstTicketId].setTheory(tickets[secondTicketId].getTheory());
        tickets[secondTicketId].setTheory(q);
    }
    else
    {
        const Question q = tickets[firstTicketId].getPractice();

        tickets[firstTicketId].setPractice(tickets[secondTicketId].getPractice());
        tickets[secondTicketId].setPractice(q);
    }

    cout << "OK" << endl << endl;
}

void setRussianLocale()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);    
}

void destroy(Q_VECTOR q)
{
    for (size_t i = 0, size = q.size(); i < size; i++)
    {
        q[i].clear();
    }
    q.clear();
}

int main(int argc, char* argv[])
{
    setRussianLocale();

    // upload question from file
    const Q_VECTOR questions = initQuestions(FILE_NAME);

    // checking question size
    checkQuestionsSize(questions);

    // create tickets vector
    T_VECTOR tickets = createTickets(questions);
    destroy(questions);

    cout << "Билеты сгинерированы. " << endl << endl;

    size_t status = 1;
    do
    {
        showMenu();

        cout << "Выберите пункт меню: ";
        cin >> status;
        cout << endl;

        switch (status)
        {
            case 1:
                print(tickets);
                break;
            case 2:
            {
                // read question by console
                const Question q = createNewQuestionByConsole();
                // set new question in tickets list
                setQuestionInTicketByConsole(q, tickets);
                break;
            }
            case 3:
                swap(tickets);
                break;
            case 0:
                cout << "Выход." << endl;
                break;
        }

    } while (status);

    system("pause");
    return 0;
}
