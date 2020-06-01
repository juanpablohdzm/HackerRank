// #include <map>
// /*
//  * Complete the 'droppedRequests' function below.
//  *
//  * The function is expected to return an INTEGER.
//  * The function accepts INTEGER_ARRAY requestTime as parameter.
//  */
// 
// void PopulateMapSeconds(map<int, int>& seconds, vector<int> time)
// {
// 	unique(time.begin(), time.end());
// 	for (vector<int>::iterator it = time.begin(); it != time.end(); ++it)
// 	{
// 		seconds[*it] = 0;
// 	}
// }
// 
// int droppedRequests(vector<int> requestTime)
// {
// 	int lastSecond = 0;
// 	int deniedRequests = 0;
// 
// 	int temp10 = 0;
// 	int temp60 = 0;
// 
// 	vector<int> uniqueVector = requestTime;
// 	unique(uniqueVector.begin(), uniqueVector.end());
// 
// 	vector<int>::iterator lastIndex10 = uniqueVector.begin();
// 	vector<int>::iterator lastIndex60 = uniqueVector.begin();
// 
// 
// 	map<int, int> seconds;
// 	PopulateMapSeconds(seconds, requestTime);
// 
// 	for (vector<int>::iterator it = requestTime.begin(); it != requestTime.end(); ++it)
// 	{
// 		int& totalRequestSecond = seconds[*it];
// 
// 		temp10++;
// 		temp60++;
// 
// 		totalRequestSecond++;
// 
// 
// 		if (lastSecond != *it)
// 		{
// 			int desireNumber = *it - 9;
// 			for (; lastIndex10 != uniqueVector.end(); ++lastIndex10)
// 			{
// 				if (*lastIndex10 >= desireNumber)
// 					break;
// 				temp10 -= seconds[*lastIndex10];
// 			}
// 		}
// 		if (lastSecond != *it)
// 		{
// 			int desireNumber = *it - 59;
// 			for (; lastIndex60 != uniqueVector.end(); ++lastIndex60)
// 			{
// 				if (*lastIndex60 >= desireNumber)
// 					break;
// 				temp60 -= seconds[*lastIndex60];
// 			}
// 		}
// 		lastSecond = *it;
// 
// 
// 		bool ShouldDeniedRequest = (totalRequestSecond > 3) ||
// 			(temp10 > 20) ||
// 			(temp60 > 60);
// 
// 
// 		if (ShouldDeniedRequest)
// 		{
// 			deniedRequests++;
// 		}
// 
// 
// 
// 	}
// 
// 	return deniedRequests;
// }