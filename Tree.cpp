#include <iostream>

using namespace std;

struct tree
{
	int data;
	tree* left;
	tree* right;
};

tree* add(int x, tree* t)
{
	if (t == NULL)
	{
		t = new tree;
		t->data = x;
		t->left = NULL;
		t->right = NULL;
	}
	else if (x > t->data)
	{
		t->left = add(x, t->left);
	}
	else if (x < t->data)
	{
		t->right = add(x, t->right);
	}
	return t;
}

void print(tree* t)
{
	if (t != NULL)
	{
		cout << t->data << " ";
		print(t->left);
		cout << endl;
		print(t->right);
	}
}

int main()
{
	int n,x;
	tree* root = NULL;
	while (cin >> x)
	{
		root = add(x, root);
	}
	print(root);
	return 0;
}
