/**********|**********|**********|
Program: team.cpp
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#include "../header/team.h"
#include "../header/shiptype.h"
Node *Team::getLinkedListHead() const
{
    return ships.getHead();
}
Node *Team::getLinkedListTail() const
{
    return ships.getTail();
}
void Team::pushbackShips(Ship *ship)
{
    ships.pushback(ship);
}
Ship *Team::searchShip(int index)
{
    return ships.search(index);
}
void Team::replaceShip(Ship *oriShip, Ship *newShip)
{
    ships.replace(oriShip, newShip);
}
LinkedList &Team::getShip()
{
    return ships;
}