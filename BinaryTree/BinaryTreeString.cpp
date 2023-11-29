// Made by Miras Kamatay, EIRfuc-22, HW2 by Algorithms and Data Structures
#include <iostream>
#include <string>

struct BinaryTreeString
{
    std::string data;
    BinaryTreeString *left;
    BinaryTreeString *right;
};

struct DoubleDeque
{
    std::string data;
    DoubleDeque *next;
    DoubleDeque *prev;
};

struct DoubleStack
{
    std::string data;
    DoubleStack *next;
    DoubleStack *prev;
};

BinaryTreeString *new_item(std::string data)
{
    BinaryTreeString *node;
    node = new BinaryTreeString;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BinaryTreeString *insert(BinaryTreeString *tree, std::string data)
{
    if (tree == NULL)
        return new_item(data);
    else if (data > tree->data)
        tree->right = insert(tree->right, data);
    else if (data < tree->data)
        tree->left = insert(tree->left, data);
    return tree;
}

BinaryTreeString *search(BinaryTreeString *tree, std::string data)
{
    if (tree == NULL)
        return NULL;
    else if (data == tree->data)
    {
        return tree;
    }
    else if (data > tree->data)
        return search(tree->right, data);
    else if (data < tree->data)
        return search(tree->left, data);
    return tree;
}

DoubleDeque *insertFront(DoubleDeque *head, std::string data)
{
    DoubleDeque *node = new DoubleDeque;
    node->data = data;
    node->next = head;
    node->prev = NULL;
    if (head != NULL)
        head->prev = node;
    return node;
}

void print(BinaryTreeString *tree)
{
    if (tree == NULL)
    {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    else
    {
        if (tree->left != NULL)
            print(tree->left);
        std::cout << tree->data << " ";
        if (tree->right != NULL)
            print(tree->right);
    }
}
void print(DoubleDeque *head)
{
    DoubleDeque *temp = head;
    if (temp == NULL)
    {
        std::cout << "Deque is empty" << std::endl;
        return;
    }
    else
        while (temp != NULL)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    std::cout << std::endl;
}

void print(DoubleStack *head)
{
    DoubleStack *temp = head;
    if (temp == NULL)
    {
        std::cout << "Stack is empty" << std::endl;
        return;
    }
    else
        while (temp != NULL)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    std::cout << std::endl;
}

BinaryTreeString *deleteX(BinaryTreeString *tree, std::string x)
{
    BinaryTreeString *temp = tree;
    if (tree == NULL)
        return NULL;
    if (x > tree->data)
        tree->right = deleteX(tree->right, x);
    else if (x < tree->data)
        tree->left = deleteX(tree->left, x);
    else if (tree->left == NULL && tree->right == NULL)
    {
        delete temp;
        return tree = NULL;
    }

    else if (tree->left == NULL || tree->right == NULL)
    {
        if (tree->left == NULL)
            temp = tree->right;
        else
            temp = tree->left;
        tree->data = temp->data;
        tree->left = temp->left;
        tree->right = temp->right;
        tree = temp;
        delete temp;
        return tree;
    }
    else
    {
        BinaryTreeString *temp1 = tree->right;
        while (temp1->left != NULL)
            temp1 = temp1->left;
        tree->data = temp1->data;
        tree->right = deleteX(tree->right, temp1->data);
    }
    return tree;
}

DoubleDeque *pushFront(DoubleDeque *head, std::string data)
{
    DoubleDeque *node = new DoubleDeque;
    node->data = data;
    node->next = head;
    node->prev = NULL;
    if (head != NULL)
        head->prev = node;
    return node;
}
DoubleDeque *pushBack(DoubleDeque *head, std::string data)
{
    DoubleDeque *node = new DoubleDeque;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    if (head == NULL)
        return node;
    DoubleDeque *temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = node;
    node->prev = temp;
    return head;
}

DoubleStack *push(DoubleStack *head, std::string data)
{
    DoubleStack *node = new DoubleStack;
    node->data = data;
    node->next = head;
    node->prev = NULL;
    if (head != NULL)
        head->prev = node;
    return node;
}

DoubleDeque *insertGreaterThan5AtTheBeginning(DoubleDeque *&head, BinaryTreeString *tree)
{
    if (tree != NULL)
    {
        if (tree->data.length() > 5)
            head = insertFront(head, tree->data);
        insertGreaterThan5AtTheBeginning(head, tree->left);
        insertGreaterThan5AtTheBeginning(head, tree->right);
    }
    else
        return NULL;

    return head;
}

DoubleDeque *insertGreaterThan5AndLessThan11AtTheEnd(DoubleDeque *&head, BinaryTreeString *tree)
{
    if (tree != NULL)
    {
        if (tree->data.length() > 5 && tree->data.length() < 11)
            head = insertFront(head, tree->data);
        insertGreaterThan5AndLessThan11AtTheEnd(head, tree->left);
        insertGreaterThan5AndLessThan11AtTheEnd(head, tree->right);
    }
    else
        return NULL;

    return head;
}

DoubleStack *removeGreaterThan10FromTheTreeAndInputToTheStack(DoubleStack *head, BinaryTreeString *tree)
{
    if (tree != NULL)
    {
        if (tree->data.length() > 10)
        {
            head = push(head, tree->data);
            tree = deleteX(tree, tree->data);
        }
        if (tree->left != NULL)
            removeGreaterThan10FromTheTreeAndInputToTheStack(head, tree->left);
        if (tree->right != NULL)
            removeGreaterThan10FromTheTreeAndInputToTheStack(head, tree->right);
    }
    else
        return nullptr;
    return head;
}
void removeByPrinting(DoubleDeque *&head, DoubleStack *&head1)

{
    if (head == NULL && head1 == NULL)
        std::cout << "Both deque and stack are empty" << std::endl;
    else if (head == NULL && head1 != NULL)
    {
        std::cout << "Stack: " << std::endl;
        while (head1 != NULL)
        {
            DoubleStack *temp1 = head1;
            std::cout << temp1->data << " ";
            head1 = head1->next;
            delete temp1;
        }
    }
    else if (head != NULL && head1 == NULL)
    {
        std::cout << "Deque: " << std::endl;
        while (head != NULL)
        {
            DoubleDeque *temp = head;
            std::cout << temp->data << " ";
            head = head->next;
            delete temp;
        }
    }
    else
    {
        std::cout << "Deque: " << std::endl;
        while (head != NULL)
        {
            DoubleDeque *temp = head;
            std::cout << temp->data << " ";
            head = head->next;
            delete temp;
        }
        std::cout << std::endl;
        std::cout << "Stack: " << std::endl;
        while (head1 != NULL)
        {
            DoubleStack *temp1 = head1;
            std::cout << temp1->data << " ";
            head1 = head1->next;
            delete temp1;
        }
    }
}

int main()
{
    BinaryTreeString *tree = NULL;
    BinaryTreeString *temp = NULL;
    DoubleDeque *head = NULL;
    DoubleDeque *temp1 = NULL;
    DoubleStack *head1 = NULL;
    DoubleStack *temp2 = NULL;
    bool inProcess = true;
    int option;
    std::string data;
    while (inProcess)
    {
        std::cout << std::endl;
        std::cout << "- - - - - - - - - " << std::endl;
        std::cout << "Choose an option: " << std::endl;
        std::cout << "- - - - - - - - - " << std::endl;
        std::cout << "1. Insert surnames " << std::endl;
        std::cout << "2. Delete surname from the tree " << std::endl;
        std::cout << "3. Find surname in the tree " << std::endl;
        std::cout << "4. Print the tree " << std::endl;
        std::cout << "5. Insert all surnames from the tree with a length greater than 5 at the beginning of the deque " << std::endl;
        std::cout << "6. Insert all surnames from the tree with length greater than 5 but less than 11 in the same deque at the end. " << std::endl;
        std::cout << "7. Remove all surnames greater than 10 from the tree and input then to the stack " << std::endl;
        std::cout << "8. Print deque " << std::endl;
        std::cout << "9. Print stack " << std::endl;
        std::cout << "10. Remove all items from the deque and the stack by printing them on the screen" << std::endl;
        std::cout << "11. Exit " << std::endl;
        std::cin >> option;
        switch (option)
        {
        case 1:
            int n;
            std::cout << "How many elements you want to insert? ";
            std::cin >> n;
            std::cout << "Enter elements here: ";
            for (int i = 0; i < n; i++)
            {
                std::cin >> data;
                tree = insert(tree, data);
            }
            break;
        case 2:
            std::cout << "Which surname do you want to delete? ";
            std::cin >> data;
            tree = deleteX(tree, data);
            break;
        case 3:
            std::cout << "Which surname are you looking for? ";
            std::cin >> data;
            temp = search(tree, data);
            if (temp != NULL)
                std::cout << "Surname is found in tree" << std::endl;
            else
                std::cout << "Surname is not found in tree" << std::endl;
            break;
        case 4:
            std::cout << "Tree: " << std::endl;
            if (temp == NULL)
            {
                std::cout << "Tree is empty" << std::endl;
            }
            else
                print(tree);
            break;
        case 5:
            head = insertGreaterThan5AtTheBeginning(head, tree);
            temp1 = head;
            std::cout << "Deque: " << std::endl;
            if (temp1 == NULL)
            {
                std::cout << "Deque is empty" << std::endl;
                break;
            }
            else
                while (temp1 != NULL)
                {
                    std::cout << temp1->data << " ";
                    temp1 = temp1->next;
                }
            delete temp1;
            break;
        case 6:
            head = insertGreaterThan5AndLessThan11AtTheEnd(head, temp);
            temp1 = head;
            std::cout << "Deque: " << std::endl;
            if (temp1 == NULL)
            {
                std::cout << "Deque is empty" << std::endl;
                break;
            }
            else
                while (temp1 != NULL)
                {
                    std::cout << temp1->data << " ";
                    temp1 = temp1->next;
                }
            delete temp1;
            break;
        case 7:
            head1 = removeGreaterThan10FromTheTreeAndInputToTheStack(head1, tree);
            temp2 = head1;
            std::cout << "Stack: " << std::endl;
            if (temp2 == NULL)
            {
                std::cout << "Stack is empty" << std::endl;
                break;
            }
            else
                while (temp2 != NULL)
                {
                    std::cout << temp2->data << " ";
                    temp2 = temp2->next;
                }
            delete temp2;
            break;
        case 8:
            std::cout << "Deque: " << std::endl;
            print(head);
            break;
        case 9:
            std::cout << "Stack: " << std::endl;
            print(head1);
            break;
        case 10:
            removeByPrinting(head, head1);
            break;
        case 11:
            inProcess = false;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
    return 0;
}
