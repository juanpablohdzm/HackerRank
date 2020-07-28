#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include <vector>

using namespace  std;

const int FromAirport[] = { 0,1,1,0 };
const int ToAirport[] = { 0,-1,-1,0 };

enum class Direction { FROM_AIRPORT, TO_AIRPORT };

struct Node
{
	int amount;
	Node* parent;
	int x, y;


	friend bool operator==(const Node& lhs, const Node& rhs)
	{
		return lhs.x == rhs.x
			&& lhs.y == rhs.y;
	}

	friend bool operator!=(const Node& lhs, const Node& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const Node& lhs, const Node& rhs)
	{
		return lhs.amount < rhs.amount;
	}

	friend bool operator<=(const Node& lhs, const Node& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const Node& lhs, const Node& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const Node& lhs, const Node& rhs)
	{
		return !(lhs < rhs);
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& obj)
	{
		return os
			<< "amount: " << obj.amount
			<< " x: " << obj.x
			<< " y: " << obj.y << endl;
	}
};

Node* CreateNode(int amount, Node* parent, int X, int Y)
{
	return new Node{ amount, parent,X,Y };
}

vector<Node*> CheckAdjacency(const vector<vector<int>>& mat, Node* current, Direction direction)
{
	const int* coordiantes;
	vector<Node*> adj;
	switch (direction)
	{
	case Direction::TO_AIRPORT:
		coordiantes = ToAirport;
		break;
	case Direction::FROM_AIRPORT:
	default:
		coordiantes = FromAirport;
		break;
	}

	int n = mat.size();
	for (int i = 0; i < 4; i += 2)
	{
		int x = current->x + *(coordiantes + i);
		int y = current->y + *(coordiantes + i + 1);

		if (x < 0 || y < 0 || x >= n || y >= n)
			continue;

		int value = mat[x][y];
		if (value == -1)
			continue;

		Node* node = CreateNode(current->amount + value, current, x, y);
		adj.push_back(node);
	}
	return adj;
}

vector<Node> Travel(const vector<vector<int>>& mat, int n, int startX, int startY, int finishX, int finishY, Direction direction)
{
	deque<Node*> possibleFinishNodes;
	list<Node*> queue;

	Node* node = CreateNode(mat[startX][startY], nullptr, startY, startY);
	queue.push_back(node);
	list<Node*>::iterator it = queue.begin();

	do
	{
		node = *it;
		if (node->x == finishX && node->y == finishY)
		{
			possibleFinishNodes.push_back(node);
		}

		vector<Node*> adj = CheckAdjacency(mat, node, direction);
		for (Node* neighbor : adj)
		{
			queue.push_back(neighbor);
		}

		it++;
	} while (it != queue.end());

	vector<Node> path;
	if (possibleFinishNodes.empty())
		return path;

	Node* bestNode = possibleFinishNodes[0];
	for (int i = 1; i < possibleFinishNodes.size(); ++i)
	{
		if (*possibleFinishNodes[i] > * bestNode)
			bestNode = possibleFinishNodes[i];
	}

	while (bestNode)
	{
		path.push_back(*bestNode);
		if (direction == Direction::TO_AIRPORT)
			break;
		bestNode = bestNode->parent;
	}

	for (list<Node*>::reverse_iterator it = queue.rbegin(); it != queue.rend(); ++it)
	{
		delete* it;
	}

	return path;

}

void ResetRecollectedTiles(vector<vector<int>>& mat, const vector<Node> path)
{
	for (const Node& node : path)
	{
		mat[node.x][node.y] = 0;
	}
}


int collectMax(vector<vector<int>> mat)
{
	if (mat[mat.size() - 1][mat.size() - 1] == -1) return 0;

	int total = 0;
	vector<Node> path = Travel(mat, mat.size(), 0, 0, mat.size() - 1, mat.size() - 1, Direction::FROM_AIRPORT);
	if (path.empty()) return 0;
	ResetRecollectedTiles(mat, path);
	total = path[0].amount;
	total += Travel(mat, mat.size(), mat.size() - 1, mat.size() - 1, 0, 0, Direction::TO_AIRPORT)[0].amount;
	return total;
}

int main(int argc, char* argv[])
{

	return 0;
}
