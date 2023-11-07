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
    void insertAfterLastEvenElement(int data);
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

void SingleLinkedList::insertAfterLastEvenElement(int x)
{
    int neededIndex = 0;
    int counter = 0;
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data % 2 == 0 && current->next == nullptr)
        {

            neededIndex = counter;
            Node *newNode = new Node;
            newNode->data = x;
            newNode->next = nullptr;
            break;
        }
        else if (current->data % 2 == 0)
        {
            neededIndex = counter;
        }
        current = current->next;
        counter++;
    }
    if (neededIndex == 0)
    {
        // if we didn't find even number we push X at the front of the list
        Node *newNode = new Node;
        newNode->data = x;
        newNode->next = head;
        head = newNode;
    }
    else
    {
        // if we found even number we push X after the last even number
        Node *temp = head;
        int counter = 0;
        while (temp != nullptr)
        {
            if (counter == neededIndex)
            {
                Node *newNode = new Node;
                newNode->data = x;
                newNode->next = temp->next;
                temp->next = newNode;
                break;
            }
            temp = temp->next;
            counter++;
        }
    }
}

int main()
{
    int option, data, x;
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
        cout << "3. Insert number after last even element" << endl;
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
            cout << "Enter the x: ";
            cin >> x;
            List.insertAfterLastEvenElement(x);
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
