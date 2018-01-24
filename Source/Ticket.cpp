#include "Ticket.h"
#include <iostream>

void Ticket::print() const
{
    cout << "Теория: " << endl;
    theory.print();
    cout << endl;
    cout << "Практика: " << endl;
    practice.print();
}
