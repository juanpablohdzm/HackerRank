#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>

using namespace std;
enum class Direction { FROM_AIRPORT = 1, TO_AIRPORT = -1 };

struct Node
{
public:
	Node() {};
	Node(int X, int Y, int Cost) : x(X), y(Y), cost(Cost), accumulateCost(Cost)
	{
		dist = sqrt(x * x + y * y);
	}

	int x, y, cost, accumulateCost;
	float dist;
	bool operator<(const Node& rhs) const
	{
		return dist < rhs.dist;
	}
};


void GetPossibleCoordinates(Direction direction, const Node& currentCoordinate, vector<Node>& possibleNeighbors)
{
	switch (direction)
	{
	case Direction::FROM_AIRPORT:
		possibleNeighbors = vector<Node>{ Node(currentCoordinate.x,currentCoordinate.y + 1,0),
							 Node(currentCoordinate.x + 1,currentCoordinate.y,0) };
		break;
	case Direction::TO_AIRPORT:
		possibleNeighbors = vector<Node>{ Node(currentCoordinate.x,currentCoordinate.y - 1,0),
							 Node(currentCoordinate.x - 1,currentCoordinate.y,0) };
		break;
	}
}


void CheckAdjacency(Direction direction, const vector<vector<int>>& mat, const Node& currentCoordinate, vector<Node>& possibleCoordinates)
{
	vector<Node> possibleNeighbors;
	GetPossibleCoordinates(direction, currentCoordinate, possibleNeighbors);

	for (Node& node : possibleNeighbors)
	{
		int x = node.x;
		int y = node.y;
		if (x >= mat.size() || y >= mat.size() || x < 0 || y < 0) continue;
		node.cost = mat[x][y];
		if (x + (int)direction < mat.size() && y < mat.size() && x + (int)direction >= 0 && y >= 0)
			node.accumulateCost += mat[x + (int)direction][y];
		if (x < mat.size() && y + (int)direction < mat.size() && x >= 0 && y + (int)direction >= 0)
			node.accumulateCost += mat[x][y + (int)direction];

		node.accumulateCost = node.cost + currentCoordinate.cost;

		if (node.cost >= 0)
		{
			possibleCoordinates.push_back(node);
		}
	}
}

bool SortVector(const Node& lh, const Node& rh)
{
	return lh.cost + lh.accumulateCost > rh.cost + rh.accumulateCost;
}

bool TravelPath(Direction direction, map<Node, Node>& path, Node& currentCoordinate, const int& n, vector<vector<int>>& mat2, int xGoal, int yGoal, int xStart, int yStart)
{
	deque<Node> coordinates;
	coordinates.push_front(Node(xStart, yStart, mat2[xStart][yStart]));
	bool pathFound = false;

	while (coordinates.size() != 0)
	{
		currentCoordinate = coordinates.front();
		coordinates.pop_front();

		if (currentCoordinate.x == xGoal && currentCoordinate.y == yGoal)
		{
			return true;
		}

		vector<Node> possibleCoordinates;
		CheckAdjacency(direction, mat2, currentCoordinate, possibleCoordinates);

		for (const Node& node : possibleCoordinates)
		{
			coordinates.push_front(node);
			path[node] = currentCoordinate;
		}
		if (coordinates.size())
		{
			sort(coordinates.begin(), coordinates.end(), SortVector);
		}

	}
	return false;
}


int collectMax(vector<vector<int>> mat)
{
	vector<vector<int>> mat2 = mat;
	int n = mat2.size();
	int passengers = 0;

	map<Node, Node> path;
	Node currentCoordinate;
	if (TravelPath(Direction::FROM_AIRPORT, path, currentCoordinate, n, mat2, n - 1, n - 1, 0, 0))
	{
		while (!(currentCoordinate.x == 0 && currentCoordinate.y == 0))
		{
			passengers += mat2[currentCoordinate.x][currentCoordinate.y];
			mat2[currentCoordinate.x][currentCoordinate.y] = 0;
			currentCoordinate = path[currentCoordinate];
		}
		path.clear();
		if (TravelPath(Direction::TO_AIRPORT, path, currentCoordinate, n, mat2, 0, 0, n - 1, n - 1))
		{
			while (!(currentCoordinate.x == n - 1 && currentCoordinate.y == n - 1))
			{
				passengers += mat2[currentCoordinate.x][currentCoordinate.y];
				mat2[currentCoordinate.x][currentCoordinate.y] = 0;
				currentCoordinate = path[currentCoordinate];
			}
		}
	}



	return passengers;

}



int main()
{
	vector<vector<int>> mat{ vector<int>{0,1,-1}, vector<int>{1,0,-1}, vector<int>{1,1,1} };
	int x = collectMax(mat);
	cout << x << endl;
}