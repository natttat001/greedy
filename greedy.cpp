#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <limits>
using namespace std;

typedef struct space
{
	string destination = " ";
	int load = 0;
	vector<int> distance = { 0, 0, 0, 0, 0 };
	bool visit = false;
} p;

int FindShortestRoute(vector<p>& ships, p ship, vector<int>& location, int i, int& currload);

void makeship(vector<p>& ship)
{
	string planet[5] = { "Alpha  ", "Beta   " , "Gamma  ", "Delta  ", "Epsilon" };
	vector<int> planetload = {20, 40, 70, 10, 30};
	int distances[5][5] =
	{
		{0, 10, 15, 12, 20},
		{10, 0,	12,	25,	14},
		{15, 12, 0, 16,	28},
		{12, 25, 16, 0, 17},
		{20, 14, 28, 17, 0},
	};
	for (int i = 0; i < 5; i++)
	{
		p temp;
		temp.destination = planet[i];
		cout << temp.destination << "    ";
		temp.load = planetload[i];
		cout << temp.load << "    ";
		for (int ii = 0; ii < 5; ii++)
		{
			temp.distance[ii] = distances[i][ii];
			cout << temp.distance[ii] << "  ";
		}
		ship.push_back(temp);
		cout << endl;
		ship[i].visit = false;
	}
	ship.shrink_to_fit();
}
void Greedy(vector<p>& ship, vector<int>& location, int& loadcost)
{
	int totalload = 170;
	int currload = 0;
	string planet[5] = { "Alpha  ", "Beta   " , "Gamma  ", "Delta  ", "Epsilon" };
	vector<int> planetload = { 20, 40, 70, 10, 30 };
	for (int i = 0; i < planetload.size(); ++i)
	{
		if (currload <= planetload[i])
		{
			currload = planetload[i];
			location[0] = i;
		}
	}
	ship[location[0]].visit = true;
	for (int i = 0; i < location.size()-1; ++i)
	{
		totalload -= currload;
		loadcost += totalload * FindShortestRoute(ship, ship[location[i]], location, i, currload) * 25;
	}
}
int FindShortestRoute(vector<p>& ships, p ship, vector<int>& location, int i, int& currload)
{
	int temp = INT_MAX;
	for (int ii = 0; ii < ship.distance.size(); ++ii)
	{
		if (!ships[ii].visit && temp >= ship.distance[ii] && ship.distance[ii] != 0)
		{
			temp = ship.distance[ii];
			location[i+1] = ii;
		}
	}
	currload = ships[location[i + 1]].load;
	ships[location[i+1]].visit = true;
	return temp;
}
int main()
{
	vector<p> ship;
	makeship(ship);
	vector<int> location; //store the current location in another vector to point to distance in ship.distance[]
	int loadcost = 0;
	for (int i = 0; i < 5; i++)
	{
		location.push_back(i);
	}
	Greedy(ship, location, loadcost);
	for (int i = 0; i < location.size(); ++i)
	{
		cout << ship[location[i]].destination << " ";
	}
	cout << loadcost;
}
