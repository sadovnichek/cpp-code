#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <map>
#include <queue>
#include <stack>

using namespace std;

map<pair<int, int>, vector<pair<int, int>>> graph;
vector<pair<int, int>> free_points;
vector<pair<int, int>> used;
map<pair<int, int>, pair<int, int>> predcessor; // child - parent


int calculate_distance(pair<int, int> a, pair<int, int> b)
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void print_pair(pair<int, int> a)
{
	cout << a.first << " " << a.second;
}

void print_graph()
{
	for (auto p : graph)
	{
		print_pair(p.first);
		cout << ": ";
		for (auto point : p.second)
		{
			print_pair(point);
			cout << " ";
		}
		cout << endl;
	}
}

void print_path(pair<int, int> start, pair<int, int> end)
{
	stack<pair<int, int>> s;
	auto current = end;
	while (current != start)
	{
		s.push(current);
		current = predcessor[current];
	}
	s.push(current);
	while (!s.empty())
	{
		print_pair(s.top());
		s.pop();
		cout << endl;
	}
}

void bfs(pair<int, int> start, pair<int, int> end)
{
	queue<pair<int, int>> q;
	q.push(start);
	predcessor.insert(make_pair(start, start));
	used.push_back(start);
	while (!q.empty())
	{
		auto current = q.front();
		q.pop();
		for (auto neighbor : graph[current])
		{
			if (neighbor == end)
			{
				predcessor.insert(make_pair(neighbor, current));
				cout << "Y" << endl;
				print_path(start, end);
				exit(0);
			}
			if (find(used.begin(), used.end(), neighbor) == used.end())
			{
				q.push(neighbor);
				used.push_back(neighbor);
				predcessor.insert(make_pair(neighbor, current));
			}
		}
	}
}

int main()
{
	int n, m, t;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> t;
			if (t == 0)
				free_points.push_back(make_pair(i + 1, j + 1));
		}
	}
	int x_start, y_start, x_end, y_end;
	cin >> y_start >> x_start;
	cin >> y_end >> x_end;

	for(int i = 0; i < free_points.size(); i++)
	{
		vector<pair<int, int>> neighbours;
		auto vertex_a = free_points[i];
		for (int j = 0; j < free_points.size(); j++)
		{
			auto vertex_b = free_points[j];
			int distance = calculate_distance(vertex_a, vertex_b);
			if (distance == 1)
				neighbours.push_back(vertex_b);
		}
		graph.insert(make_pair(vertex_a, neighbours));
	}

	bfs(make_pair(y_start, x_start), make_pair(y_end, x_end));
	cout << "N";
	return 0;
}
