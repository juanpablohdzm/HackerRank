// 
// void ProcessInputFile(ifstream& file, map<string, bool>& dates)
// {
// 	string line;
// 	while (getline(file, line))
// 	{
// 		int startIndex = line.find("[");
// 		string date = line.substr(startIndex + 1, 20);
// 
// 		if (!dates.empty())
// 		{
// 			map<string, bool>::iterator it = dates.find(date);
// 			if (it != dates.end())
// 			{
// 				it->second = true;
// 			}
// 			else
// 			{
// 				dates[date] = false;
// 			}
// 		}
// 		else
// 		{
// 			dates[date] = false;
// 		}
// 
// 
// 
// 	}
// 
// }
// 
// void ProcessOutputFile(ofstream& file, const map<string, bool>& dates)
// {
// 	for_each(dates.begin(), dates.end(), [&](pair<string, bool> date)
// 		{
// 			if (date.second)
// 			{
// 				file << date.first << endl;
// 			}
// 		});
// }
// 
// int not_main()
// {
// 	// read the string filename
// 	string filename;
// 	cin >> filename;
// 
// 	//Open the file read mode 
// 	ifstream file;
// 	file.open(filename);
// 	map<string, bool> dates;
// 	if (file.is_open())
// 	{
// 		ProcessInputFile(file, dates);
// 	}
// 	else
// 	{
// 		cout << "File: " << filename << "could not be opened" << endl;
// 	}
// 	file.close();
// 
// 	//Create the output file
// 	string outFileName = "req_" + filename;
// 	ofstream outFile;
// 	outFile.open(outFileName);
// 	if (outFile.is_open())
// 	{
// 		ProcessOutputFile(outFile, dates);
// 	}
// 	else
// 	{
// 		cout << "File: " << outFileName << "could not be opened" << endl;
// 	}
// 	outFile.close();
// 
// 
// 	return 0;
// }
// 
