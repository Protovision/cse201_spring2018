/* g++ -std=c++11 list.cpp */
#include <iostream>
#include <list>
using namespace std;

list<int>::const_iterator nth(const list<int>& t, int index, int& steps) 
{
	list<int>::const_iterator it = t.begin();
	while (index > 0) { ++it; --index; ++steps; }
	return it;
}

int binary_search(int x, const list<int>& vec, int& steps)
{
	int low = 0;
	int high = vec.size() - 1;

	steps = 0;
	while (low <= high) {
		int mid = (low + high) / 2;
		list<int>::const_iterator mid_it = nth(vec, mid, steps);
		if (*mid_it < x)
			low = mid + 1;
		else if (*mid_it > x)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int steps = 0;
	list<int> t{{ 1, 5, 20, 40, 100, 103, 120, 205, 300, 500 }};
	cout << "205 found at index: " << binary_search(205, t, steps) << " in " << steps << " steps.\n";
}
