#include <iostream>

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

struct SingleDeque
{
    TreeNode *data;
    SingleDeque *next;
};

struct SingleStack
{
    TreeNode *data;
    SingleStack *next;
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

void print(TreeNode *tree)
{
    if (tree != NULL)
    {
        print(tree->left);
        std::cout << tree->data << " ";
        print(tree->right);
    }
    else
        return;
}

void print(SingleDeque *head)
{
    if (head == NULL)
    {
        std::cout << "Deque is empty" << std::endl;
        return;
    }
    SingleDeque *node = head;
    while (node != NULL)
    {
        std::cout << node->data->data << " ";
        node = node->next;
    }
}

void print(SingleStack *head)
{
    if (head == NULL)
    {
        std::cout << "Stack is empty" << std::endl;
        return;
    }

    SingleStack *node = head;
    while (node != NULL)
    {
        std::cout << node->data->data << " ";
        node = node->next;
    }
}

SingleDeque *pushFront(SingleDeque *head, TreeNode *data)
{
    SingleDeque *node = new SingleDeque;
    node->data = data;
    node->next = head;
    return node;
}

SingleStack *push(SingleStack *head, TreeNode *data)
{
    SingleStack *node = new SingleStack;
    node->data = data;
    node->next = head;
    return node;
}

SingleDeque *insertInIntervalABFromTree(TreeNode *tree, int a, int b, SingleDeque *&head)
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

SingleDeque *insertInIntervalZeroToAFromTree(TreeNode *tree, int a, SingleDeque *&head)
{
    if (tree != NULL)
    {
        insertInIntervalZeroToAFromTree(tree->left, a, head);
        if (tree->data >= 0 && tree->data < a)
            head = pushFront(head, tree);
        insertInIntervalZeroToAFromTree(tree->right, a, head);
    }
    else
        return NULL;
    return head;
}

SingleStack *insertInIntervalBToCFromTree(TreeNode *tree, int b, int c, SingleStack *&head1)
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

void deleteByPrint(SingleDeque *&head, SingleStack *&head1)
{
    if (head == NULL && head1 == NULL)
        std::cout << "Both deque and stack are empty" << std::endl;
    else if (head == NULL && head1 != NULL)
    {
        while (head1 != NULL)
        {
            std::cout << "Stack: ";
            SingleStack *temp1 = head1;
            std::cout << temp1->data->data << " ";
            head1 = head1->next;
            delete temp1;
        }
    }
    else if (head != NULL && head1 == NULL)
    {
        std::cout << "Deque: ";
        while (head != NULL)
        {
            SingleDeque *temp = head;
            std::cout << temp->data->data << " ";
            head = head->next;
            delete temp;
        }
    }
    else
    {
        std::cout << "Deque: ";
        while (head != NULL)
        {
            SingleDeque *temp = head;
            std::cout << temp->data->data << " ";
            head = head->next;
            delete temp;
        }
        std::cout << std::endl;
        std::cout << "Stack: ";
        while (head1 != NULL)
        {
            SingleStack *temp1 = head1;
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
    else if (x > tree->data)
        tree->right = deleteX(tree->right, x);
    else if (x < tree->data)
        tree->left = deleteX(tree->left, x);
    else
    {
        if (tree->left == NULL && tree->right == NULL)
        {
            delete tree;
            return NULL;
        }
        else if (tree->left == NULL)
        {
            TreeNode *temp = tree->right;
            delete tree;
            return temp;
        }
        else if (tree->right == NULL)
        {
            TreeNode *temp = tree->left;
            delete tree;
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
    }
    return tree;
}

int main()
{
    TreeNode *tree = NULL;
    TreeNode *temp = NULL;
    SingleDeque *head = NULL;
    SingleDeque *temp1 = NULL;
    SingleStack *head1 = NULL;
    SingleStack *temp2 = NULL;
    bool inProcess = true;
    int option, data, a, b, c;
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
        std::cout << "6. insert data with interval [0,a) into the deque " << std::endl;
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