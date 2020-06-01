// enum class Direction { FROM_AIRPORT = 1, TO_AIRPORT = -1 };
// 
// 
// void GetPossibleCoordinates(Direction direction, const tuple<int, int, int>& currentCoordinate, vector<tuple<int, int>>& possibleNeighbors)
// {
// 	switch (direction)
// 	{
// 	case Direction::FROM_AIRPORT:
// 		possibleNeighbors = vector<tuple<int, int>>{ make_pair(get<0>(currentCoordinate),get<1>(currentCoordinate) + 1),
// 							 make_pair(get<0>(currentCoordinate) + 1,get<1>(currentCoordinate)) };
// 		break;
// 	case Direction::TO_AIRPORT:
// 		possibleNeighbors = vector<tuple<int, int>>{ make_pair(get<0>(currentCoordinate),get<1>(currentCoordinate) - 1),
// 							 make_pair(get<0>(currentCoordinate) - 1,get<1>(currentCoordinate)) };
// 		break;
// 	}
// }
// 
// 
// void CheckAdjacency(Direction direction, const vector<vector<int>>& mat, const tuple<int, int, int>& currentCoordinate, vector<tuple<int, int, int>>& possibleCoordinates)
// {
// 	vector<tuple<int, int>> possibleNeighbors;
// 	GetPossibleCoordinates(direction, currentCoordinate, possibleNeighbors);
// 
// 	for (const tuple<int, int>& node : possibleNeighbors)
// 	{
// 		int x = get<0>(node);
// 		int y = get<1>(node);
// 		if (x >= mat.size() || y >= mat.size() || x < 0 || y < 0) continue;
// 		int result = mat[x][y];
// 		if (x + (int)direction < mat.size() && x + (int)direction >= 0)
// 			result += mat[x + (int)direction][y];
// 		if (y + (int)direction < mat.size() && y + (int)direction >= 0)
// 			result += mat[x][y + (int)direction];
// 
// 		if (mat[x][y] >= 0)
// 		{
// 			possibleCoordinates.push_back(tuple<int, int, int>(x, y, result));
// 		}
// 	}
// }
// 
// bool SortVector(const tuple<int, int, int>& lh, const tuple<int, int, int>& rh)
// {
// 	return get<2>(lh) > get<2>(rh);
// }
// 
// void TravelPath(Direction direction, int& passengers, const int& n, vector<vector<int>>& mat2, int xGoal, int yGoal, int xStart, int yStart)
// {
// 	deque<tuple<int, int, int>> coordinates;
// 	coordinates.push_front(tuple<int, int, int>(xStart, yStart, mat2[xStart][yStart]));
// 	bool pathFound = false;
// 
// 	while (coordinates.size() != 0)
// 	{
// 		tuple<int, int, int> currentCoordinate = coordinates.front();
// 		passengers += mat2[get<0>(currentCoordinate)][get<1>(currentCoordinate)];
// 		mat2[get<0>(currentCoordinate)][get<1>(currentCoordinate)] = 0;
// 		coordinates.pop_front();
// 
// 		if (currentCoordinate == tuple<int, int, int>(xGoal, yGoal, get<2>(currentCoordinate)))
// 		{
// 			pathFound = true;
// 			break;
// 		}
// 
// 		vector<tuple<int, int, int>> possibleCoordinates;
// 		CheckAdjacency(direction, mat2, currentCoordinate, possibleCoordinates);
// 
// 		for (const tuple<int, int, int>& node : possibleCoordinates)
// 		{
// 			int x = get<0>(node);
// 			int y = get<1>(node);
// 
// 			coordinates.push_front(node);
// 
// 
// 		}
// 		if (coordinates.size())
// 		{
// 			sort(coordinates.begin(), coordinates.end(), SortVector);
// 			coordinates.resize(1);
// 
// 		}
// 
// 	}
// 	if (!pathFound)
// 		passengers = 0;
// }
// 
// 
// int collectMax(vector<vector<int>> mat)
// {
// 	vector<vector<int>> mat2 = mat;
// 	int n = mat2.size();
// 	int passengers = 0;
// 
// 	TravelPath(Direction::FROM_AIRPORT, passengers, n, mat2, n - 1, n - 1, 0, 0);
// 
// 	TravelPath(Direction::TO_AIRPORT, passengers, n, mat2, 0, 0, n - 1, n - 1);
// 
// 
// 
// 	return passengers;
// 
// }