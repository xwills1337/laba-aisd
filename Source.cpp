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
	void print()
	{
		cout << size << endl << count << endl;
		for (int i = 0; i < count; i++) cout << line[i].x << " " << line[i].y << endl;
		cout << endl;
	}

	void print_graf()
	{
		for (int i = 0; i < count - 1; i++) g.DrawLine(line[i].x, line[i].y, line[i + 1].x, line[i + 1].y);
	}

	int get_size() { return size; }
	int get_count() { return count; }
	int get_grow() { return grow; }
};

broken_line operator + (const point& p, const broken_line& v)
{
	broken_line temp(0);
	temp += p;
	temp += v;
	return temp;
}



int main()
{
	broken_line a(4);
	a[0].x = 150;
	a[0].y = 30;
	a[1].x = 100;
	a[1].y = 30;
	a[2].x = 100;
	a[2].y = 100;
	a[3].x = 150;
	a[3].y = 100;
	a.print();
	broken_line b(4);
	b[1].y = 7;
	b.print();
	broken_line c(4);
	c[3].x = 2;
	c.print();
	broken_line d = a + b;
	d.print();
	point f;
	f.x = 4;
	f.y = 4;
	d = a + f;
	d.print();
	d = f + a;
	d.print();
	cout << d.calculate();

	a.print_graf();
	system("pause");
}