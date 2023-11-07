#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
} *head;

class SingleLinkedList
{
public:
    void createList(Node *&head, int data);
    void displayList(const Node *head);
    void clearList(Node *&head);
    void removeAllEvenElementwithOddIndex();
    SingleLinkedList(){}; // default constructor
    ~SingleLinkedList()
    {
        clearList(head);
    }
};

void SingleLinkedList::createList(Node *&head, int data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void SingleLinkedList::displayList(const Node *head)
{
    const Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void SingleLinkedList::clearList(Node *&head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void SingleLinkedList::removeAllEvenElementwithOddIndex()
{
    Node *temp = head;
    Node *prev = NULL;
    int index = 0;
    while (temp != NULL)
    {
        if (index != 0 && index % 2 == 1 && temp->data % 2 == 0)
        {
            if (prev == NULL)
            {
                head = temp->next;
                delete temp;
                temp = head;
            }
            else
            {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
        index++;
    }
}

int main()
{
    int option, data;
    SingleLinkedList List;
    bool inProcess = true;
    head = nullptr;
    while (inProcess)
    {
        cout << endl
             << "---------------------------------" << endl;
        cout << endl
             << "Operations on singly linked list" << endl;
        cout << endl
             << "---------------------------------" << endl;
        cout << "1. Create List" << endl;
        cout << "2. Display List" << endl;
        cout << "3. Remove all even element with odd index" << endl;
        cout << "4. Clear list" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your option : ";
        cin >> option;
        cout << endl;
        switch (option)
        {
        case 1:
            cout << "Enter the size of list: ";
            int size;
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                cin >> data;
                List.createList(head, data);
            }
            break;
        case 2:
            List.displayList(head);
            break;
        case 3:
            List.removeAllEvenElementwithOddIndex();
            List.displayList(head);
            break;
        case 4:
            List.clearList(head);
            break;
        case 5:
            inProcess = false;
            break;
        default:
            cout << "Wrong choice" << endl;
        }
    }
}
