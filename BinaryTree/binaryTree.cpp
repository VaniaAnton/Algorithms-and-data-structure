#include <iostream>
#include <string>

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

struct DoubleDeque
{
    TreeNode *data;
    DoubleDeque *next;
    DoubleDeque *prev;
};

struct DoubleStack
{
    TreeNode *data;
    DoubleStack *next;
    DoubleStack *prev;
};

TreeNode *new_item(int data)
{
    TreeNode *node;
    node = new TreeNode;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *insert(TreeNode *tree, int data)
{
    if (tree == NULL)
        return new_item(data);
    else if (data > tree->data)
        tree->right = insert(tree->right, data);
    else if (data < tree->data)
        tree->left = insert(tree->left, data);
    return tree;
}

TreeNode *search(TreeNode *tree, int data)
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

DoubleDeque *pushFront(DoubleDeque *head, TreeNode *data)
{
    DoubleDeque *node = new DoubleDeque;
    node->data = data;
    node->next = head;
    node->prev = NULL;
    if (head != NULL)
        head->prev = node;
    return node;
}

void print(TreeNode *tree)
{
    if (tree != NULL)
    {
        print(tree->left);
        std::cout << tree->data << std::endl;
        print(tree->right);
    }
    else
        return;
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
            std::cout << temp->data->data << " ";
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
            std::cout << temp->data->data << " ";
            temp = temp->next;
        }
    std::cout << std::endl;
}
DoubleStack *push(DoubleStack *head, TreeNode *data)
{
    DoubleStack *node = new DoubleStack;
    node->data = data;
    node->next = head;
    return node;
}

DoubleDeque *insertInIntervalABFromTree(TreeNode *tree, int a, int b, DoubleDeque *&head)
{
    if (tree != NULL)
    {
        insertInIntervalABFromTree(tree->left, a, b, head);
        if (tree->data >= a && tree->data <= b)
            head = pushFront(head, tree);
        insertInIntervalABFromTree(tree->right, a, b, head);
    }
    else
        return NULL;

    return head;
}

DoubleDeque *insertInIntervalZeroToAFromTree(TreeNode *tree, int a, DoubleDeque *&head)
{
    if (tree != NULL)
    {
        insertInIntervalZeroToAFromTree(tree->left, a, head);
        if (tree->data > 0 && tree->data <= a)
            head = pushFront(head, tree);
        insertInIntervalZeroToAFromTree(tree->right, a, head);
    }
    else
        return NULL;

    return head;
}
DoubleStack *insertInIntervalBToCFromTree(TreeNode *tree, int b, int c, DoubleStack *&head1)
{
    if (tree != NULL)
    {
        insertInIntervalBToCFromTree(tree->left, b, c, head1);
        if (tree->data > b && tree->data <= c)
            head1 = push(head1, tree);
        insertInIntervalBToCFromTree(tree->right, b, c, head1);
    }
    else
        return NULL;

    return head1;
}

void deleteByPrint(DoubleDeque *&head, DoubleStack *&head1)
{
    if (head == NULL && head1 == NULL)
        std::cout << "Both deque and stack are empty" << std::endl;
    else if (head == NULL && head1 != NULL)
    {
        while (head1 != NULL)
        {
            DoubleStack *temp1 = head1;
            std::cout << temp1->data->data << " ";
            head1 = head1->next;
            delete temp1;
        }
    }
    else if (head != NULL && head1 == NULL)
    {
        while (head != NULL)
        {
            DoubleDeque *temp = head;
            std::cout << temp->data->data << " ";
            head = head->next;
            delete temp;
        }
    }
    else
    {
        while (head != NULL)
        {
            DoubleDeque *temp = head;
            std::cout << temp->data->data << " ";
            head = head->next;
            delete temp;
        }
        while (head1 != NULL)
        {
            DoubleStack *temp1 = head1;
            std::cout << temp1->data->data << " ";
            head1 = head1->next;
            delete temp1;
        }
    }
}

TreeNode *deleteX(TreeNode *tree, int x)
{
    if (tree == NULL)
        return NULL;
    if (x > tree->data)
        tree->right = deleteX(tree->right, x);
    else if (x < tree->data)
        tree->left = deleteX(tree->left, x);
    else if (tree->left == NULL && tree->right == NULL)
    {
        free(tree);
        return NULL;
    }

    else if (tree->left == NULL || tree->right == NULL)
    {
        TreeNode *temp;
        if (tree->left == NULL)
            temp = tree->right;
        else
            temp = tree->left;
        free(tree);
        return temp;
    }
    else
    {
        TreeNode *temp = tree->right;
        while (temp->left != NULL)
            temp = temp->left;
        tree->data = temp->data;
        tree->right = deleteX(tree->right, temp->data);
    }
    return tree;
}

int main()
{
    TreeNode *tree = NULL;
    TreeNode *temp = NULL;
    DoubleDeque *head = NULL;
    DoubleDeque *temp1 = NULL;
    DoubleStack *head1 = NULL;
    DoubleStack *temp2 = NULL;
    bool inProcess = true;
    int option, data, a, b, c;
    std::string option;
    while (inProcess)
    {
        std::cout << std::endl;
        std::cout << "- - - - - - - - - " << std::endl;
        std::cout << "Choose an option: " << std::endl;
        std::cout << "- - - - - - - - - " << std::endl;
        std::cout << "1. Insert data " << std::endl;
        std::cout << "2. Delete data " << std::endl;
        std::cout << "3. Find data " << std::endl;
        std::cout << "4. Print tree " << std::endl;
        std::cout << "5. insert data with interval [a,b] into the deque " << std::endl;
        std::cout << "6. insert data with interval (0,a] into the deque " << std::endl;
        std::cout << "7. insert data with interval (b,c] into the stack " << std::endl;
        std::cout << "8. Print deque " << std::endl;
        std::cout << "9. Print stack " << std::endl;
        std::cout << "10. Delete deque and stack by printing them on the console" << std::endl;
        std::cout << "11. Exit " << std::endl;
        std::cin >> option;
        switch (option)
        {
        case 1:
            int n;
            std::cout << "How many elements you want to insert: ";
            std::cin >> n;
            std::cout << "Enter data: ";
            for (int i = 0; i < n; i++)
            {
                std::cin >> data;
                tree = insert(tree, data);
            }

            break;
        case 2:
            std::cout << "Enter data to delete: ";
            std::cin >> data;
            tree = deleteX(tree, data);
            break;
        case 3:
            std::cout << "Enter data to find: ";
            std::cin >> data;
            temp = search(tree, data);
            if (temp != NULL)
                std::cout << "Data found" << std::endl;
            else
                std::cout << "Data not found" << std::endl;
            break;
        case 4:
            std::cout << "Tree: " << std::endl;
            print(tree);
            break;
        case 5:
            std::cout << "Enter a: ";
            std::cin >> a;
            std::cout << "Enter b: ";
            std::cin >> b;
            head = insertInIntervalABFromTree(tree, a, b, head);
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
                    std::cout << temp1->data->data << " ";
                    temp1 = temp1->next;
                }
            delete temp1;
            break;
        case 6:
            std::cout << "Enter a: ";
            std::cin >> a;
            head = insertInIntervalZeroToAFromTree(tree, a, head);
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
                    std::cout << temp1->data->data << " ";
                    temp1 = temp1->next;
                }
            delete temp1;
            break;
        case 7:
            std::cout << "Enter b: ";
            std::cin >> b;
            std::cout << "Enter c: ";
            std::cin >> c;
            head1 = insertInIntervalBToCFromTree(tree, b, c, head1);
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
                    std::cout << temp2->data->data << " ";
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
            deleteByPrint(head, head1);
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
