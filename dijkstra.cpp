#pragma optimize( "", off )
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VERTEXES = 10;
const int MAX = 10e+6;

int dist[MAX_VERTEXES], predcessor[MAX_VERTEXES], weight_matrix[MAX_VERTEXES][MAX_VERTEXES];

set<int> get_F(int n)
{
	set<int> F;
	for (int i = 0; i < n; i++)
	{
		F.insert(i);
	}
	return F;
}

int Min(set<int> F)
{
	int min = MAX;
	int min_v = -1;
	for (auto v : F)
	{
		if (dist[v] < min)
		{
			min = dist[v];
			min_v = v;
		}
	}
	return min_v;
}

void init(int start, int n)
{
	for (int i = 0; i < n; i++)
	{
		dist[i] = weight_matrix[start][i];
		predcessor[i] = start;
	}
}

void print_path(int end)
{
	vector<int> path;
	if (dist[end - 1] == 0)
		cout << "N";
	else
	{
		cout << "Y" << endl;
		int current = end - 1;
		path.push_back(current + 1);
		while (current != 0)
		{
			current = predcessor[current];
			path.push_back(current + 1);
		}
		reverse(path.begin(), path.end());
		for (auto vertex : path)
			cout << vertex << " ";
		cout << endl << dist[end - 1];
	}
}

void Dijkstra(int start, int n)
{
	dist[start] = 0;
	predcessor[start] = 0;
	set<int> F = get_F(n);
	F.erase(start);		// F = V \ s
	init(start, n);
	for (int i = 0; i < n; i++)
	{
		int w = Min(F);
		F.erase(w); // F = F \ w
		for (auto v : F)
		{
			if (dist[w] + weight_matrix[w][v] < dist[v])
			{
				dist[v] = dist[w] + weight_matrix[w][v];
				predcessor[v] = w;
			}
		}
	}
}

int main()
{
	int n, predcessor_vertex, edge_weight;
	
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				weight_matrix[i][j] = 0;
			else
				weight_matrix[i][j] = MAX;
		}
	}

	for (int i = 0; i < n; i++)
	{
		cin >> predcessor_vertex;
		while (predcessor_vertex != 0)
		{
			cin >> edge_weight;
			weight_matrix[predcessor_vertex - 1][i] = edge_weight;
			cin >> predcessor_vertex;
		}
	}

	int start, end;
	cin >> start >> end;

	Dijkstra(start - 1, n);

	print_path(end);
	return 0;
}
