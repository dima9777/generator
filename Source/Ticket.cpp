#include "Ticket.h"
#include <iostream>

void Ticket::print() const
{
    cout << "������: " << endl;
    theory.print();
    cout << endl;
    cout << "��������: " << endl;
    practice.print();
}
