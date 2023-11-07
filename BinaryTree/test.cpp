#include <iostream>

struct BayerTree
{
    int data;
    BayerTree *left;
    BayerTree *right;
    BayerTree(int x) : data(x), left(NULL), right(NULL) {}
};

void newItem(BayerTree *root, int x)
{
    if (root->data > x)
    {
        if (root->left == NULL)
        {
            root->left = new BayerTree(x);
        }
        else
        {
            newItem(root->left, x);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = new BayerTree(x);
        }
        else
        {
            newItem(root->right, x);
        }
    }
}

void printTree(BayerTree *root)
{
    if (root == NULL)
    {
        return;
    }
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
}

int main()
{
    int n;
    std::cin >> n;
    int x;
    std::cin >> x;
    BayerTree *root = new BayerTree(x);
    for (int i = 1; i < n; i++)
    {
        std::cin >> x;
        newItem(root, x);
    }
    printTree(root);
    return 0;
}