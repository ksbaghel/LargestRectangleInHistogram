// LargestRectangleInHistogram.cpp : Defines the entry point for the console application.
//
/*
Given n non-negative integers representing the histogram’s bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.

Solution:

Method 1: O(N^2) : Check every rectangle
	1. Maintain the min height for each rectangle and calculate the area
	2. Use double ended queue for maintaining min height.
	3. While entering new element in the Queue..remove all the heights greater than this so that the min height for sliding window always stays in the front


Method 2: O(N):  Use stack



*/


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

int max(int a, int b) { return a > b ? a : b;  }

int max_rectangle_method_1(vector<int>& Ht)
{
	int res = 0;

	int n = Ht.size();
	deque<int> minHeight;
	for (int i = 0; i < n; i++)
	{
		//minHeight.push_back(Ht[i]);
		for(int j=i; j<n; j++)
		{	
			//Now remove all the greater elements than this new elements
			while (!minHeight.empty() && minHeight.back() > Ht[j])
			{
				minHeight.pop_back();
			}
			minHeight.push_back(Ht[j]);
			int curr_area = (j - i + 1)*minHeight.front();
			res = max(res, curr_area);
		}
		minHeight.clear();
	}

	return res;
}

int max_rectangle_method_2(vector<int>& Ht)
{
	int res = 0;
	int currArea = 0;

	stack<int> S;
	for (int i = 0; i < Ht.size(); i++)
	{
		if (S.empty() || Ht[S.top()] <= Ht[i])
		{
			S.push(i);
		}
		else {
			while (!S.empty() && Ht[S.top()] > Ht[i])
			{
				int h = Ht[S.top()];
				int L = S.top();
				S.pop();
				int R = i;
				currArea = (R - L)*h;
				res = max(res, currArea);
			}
		}
	}

	//Now if S is non-empty..it will have all the elements in increasing order
	int R = S.empty() ? -1 : S.top();
	while (!S.empty())
	{
		currArea = (R - S.top() + 1)*Ht[S.top()];
		S.pop();
		res = max(res, currArea);
	}
	return res;
}

int main()
{
	int n;
	cin >> n;

	vector<int> Ht(n, 0);

	for (int i = 0; i < n; i++)
	{
		cin >> Ht[i];
	}

	cout << max_rectangle_method_1(Ht) << endl;
	cout << max_rectangle_method_2(Ht) << endl;
    return 0;
}

