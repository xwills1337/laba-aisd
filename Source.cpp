#include<cstdio>
#include<iostream>
#include"Graphics.h"
using namespace std;

Graphics g;

struct point
{
	double x, y;
};

class broken_line
{
	point* line = NULL;
	int size, count, grow;
public:
	broken_line(int _size = 0, int _grow = 5) : size(_size), grow(_grow)
	{
		if (_size < 0) throw "Error! Array size cannot be negative";
		if (_grow < 0) throw "Error! grow cannot be negative";
		line = (point*)malloc(sizeof(point) * size);
		count = size;
		for (int i = 0; i < count; i++)
		{
			line[i].x = 0;
			line[i].y = 0;
		}
	}
	broken_line(const broken_line& v)
	{
		size = v.size;
		count = v.count;
		grow = v.grow;
		line = (point*)malloc(sizeof(point) * size);
		for (int i = 0; i < count; i++)
		{
			line[i].x = v.line[i].x;
			line[i].y = v.line[i].y;
		}

	}
};











int main()
{
	
}