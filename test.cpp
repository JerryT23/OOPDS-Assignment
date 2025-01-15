// this file is for testing certain function only:)))
#include <iostream>

using namespace std;

class LinkedList
{
    struct Node
    {
        int value;
        Node *next;
    };
    Node *head;
    Node *tail;
    int size;

public:
    void pushFirst(int value);
    LinkedList() : head(nullptr), tail(nullptr), size(0)
    {
    }
    void pushback(int value);
    bool empty() { return tail == nullptr; }
    void deleteNode(int index)
    {
        if (index >= size)
        {
            std::cout << "invalid access\n " << __LINE__ << " lines";
            exit(-1);
        }
        if (index == 0)
        {
            if (head == tail)
                tail = nullptr;
            Node *ptr = head;
            head = head->next;
            delete ptr;
        }
        else
        {
            Node *indexNode = head;
            Node *prev;
            for (int i = 0; i < index; i++)
            {
                prev = indexNode;
                indexNode = indexNode->next;
            }
            if (index == (size - 1))
            {
                tail = prev;
                prev->next = nullptr;
            }
            else
                prev->next = indexNode->next;
            delete indexNode;
        }
        size--;
    }
    void display()
    {
        Node *ptr = head;
        for (int i = 0; i < size; i++)
        {
            cout << ptr->value;
            ptr = ptr->next;
        }
    }
};
void LinkedList::pushFirst(int value)
{
    for (int gridY = 2 - 1; gridY <= 2 + 1; gridY++)
    { // get the grid of nine-square area centered on (x,y)
        if (gridY < 0)
            continue; // if outside of grid
        for (int gridX = 5 - 1; gridX <= 5 + 1; 5++)
        {
            if (gridX < 0)
                continue;
            std::cout << gridY << ',' << gridX << std::endl;
            // if(gridX == shipPositionX && gridY==shipPositionY) continue; //ignore self;
            // if(grid[gridY][gridX].getship()) {
            //     if(grid[gridY][gridX].getship()->getTeamName() == this->getTeamName()) {
            //         std::cout << "Friendly ship found at -> Y:" <<gridY << " X:" << gridX << std::endl;
            //     }
            // }
        }
    }
}

void LinkedList::pushback(int value)
{
    if (!head)
    {
        pushFirst(value);
    }
    else
    {
        Node *newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
        size++;
    }
}
int main()
{
    LinkedList *list = new LinkedList;
    list->pushback(3);
    list->pushback(5);
    list->pushback(8);
    list->deleteNode(0);
    list->deleteNode(0);
    list->deleteNode(0);
    if (list->empty())
    {
        cout << "empty";
    }
    else
    {
        cout << "not Empty";
    }
    list->display();
    delete list;
    return 0;
}