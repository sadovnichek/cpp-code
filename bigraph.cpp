#include <iostream>
#include <vector>

using namespace std;

const int MAX_VERTEXES = 100;

vector<vector<int>> graph;
bool used[MAX_VERTEXES];
char colors[MAX_VERTEXES];

char invertor(char ch)
{
	return (ch == 'r') ? 'g' : 'r';
}

void dfs(int vertex, char color)
{
	//cout << "Current vertex: " << vertex << " color: " << color << endl;
	used[vertex] = true;
	colors[vertex] = color;
	for (auto u : graph[vertex])
	{
		if (!used[u])
			dfs(u, invertor(color));
		else if (color == colors[u])
		{
			cout << "N";
			exit(0);
		}
	}
}

void print(int n, char color)
{
	for (int i = 0; i < n; i++)
	{
		if (colors[i] == color)
			cout << i + 1 << " ";
	}
	cout << endl;
}

int main()
{
	int n, t;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		graph.push_back(vector<int>());
		for (int j = 0; j < n; j++)
		{
			cin >> t;
			if(t != 0)
				graph[i].push_back(j);
		}
	}
	dfs(0, 'r');
	cout << "Y" << endl;
	print(n, 'r');
	print(n, 'g');
	return 0;
}
