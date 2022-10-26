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
	~broken_line()
	{
		clear();
	}
	void clear()
	{
		free(line);
		size = 0;
		count = 0;
	}
	broken_line& operator = (const broken_line& v)
	{
		clear();
		size = v.size;
		count = v.count;
		grow = v.grow;
		line = (point*)malloc(sizeof(point) * size);

		for (int i = 0; i < count; i++)
		{
			line[i].x = v.line[i].x;
			line[i].y = v.line[i].y;
		}
		return *this;
	}
	broken_line& operator += (const broken_line& v)
	{
		while (size < count + v.count) size += grow;

		point* tmp = (point*)realloc(line, sizeof(point) * size);
		if (tmp != NULL) line = tmp;

		for (int i = 0; i < v.count; i++)
		{
			line[i + count].x = v.line[i].x;
			line[i + count].y = v.line[i].y;
		}
		count += v.count;
		return *this;
	}
	broken_line operator + (const broken_line& v)
	{
		broken_line temp(*this);
		temp += v;
		return temp;
	}
	broken_line& operator += (const point& v)
	{
		if (count + 1 > size) size += grow;
		point* tmp = (point*)realloc(line, sizeof(point) * size);
		if (tmp != NULL) line = tmp;
		line[count].x = v.x;
		line[count++].y = v.y;
		return *this;
	}
	broken_line operator + (const point& v)
	{
		broken_line temp(*this);
		temp += v;
		return temp;
	}
	point& operator[] (const int index)
	{
		if (index < count && count != 0) return line[index];
		else throw "Error! Element with this index does not exist.";
	}

	double calculate()
	{
		if (count == 0) throw "Error! Line has no vertices";
		double rez = 0;
		for (int i = 0; i < count - 1; i++) rez += sqrt(pow((line[i + 1].x - line[i].x), 2) + pow((line[i + 1].y - line[i].y), 2));
		return rez;
	}
};











int main()
{
	
}