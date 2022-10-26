#include<cstdio>
#include<iostream>
#include<conio.h>
#include<windows.h>
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
		double rez = 0;
		if (count < 2) return rez;
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
	broken_line a(5);
	broken_line b(5);
	b[0].x = 4;
	b[3].y = 6;
	point f;
	f.x = 4;
	f.y = 5;
	while (true)
	{
		system("cls");
		cout << "1 - Enter value by index" << endl;
		cout << "2 - Obj broken_list + obj broken_list" << endl;
		cout << "3 - Obj broken_list + obj point" << endl;
		cout << "4 - Obj point + obj broken_list" << endl;
		cout << "5 - Calculate" << endl;
		cout << "6 - Tack" << endl;
		cout << "7 - Exit" << endl;
		char z = getch();
		if (z == '1')
		{
			int index, value_x, value_y;
			cout << "Enter index" << endl;
			cin >> index;
			cout << "Enter value for x" << endl;
			cin >> value_x;
			cout << "Enter value for y" << endl;
			cin >> value_y;
			try
			{
				a[index].x = value_x;
				a[index].y = value_y;
			}
			catch (const char* msg)
			{
				cout << msg << endl;
				getch();
			}
			system("cls");
		}
		if (z == '2')
		{
			cout << "line a" << endl;
			a.print();
			cout << "line b" << endl;
			b.print();
			broken_line d = a + b;
			cout << "line a + line b" << endl;
			d.print();
			getch();
		}
		if (z == '3')
		{
			cout << "line a" << endl;
			a.print();
			cout << "point f" << endl << f.x << " " << f.y <<endl;
			broken_line d = a + f;
			cout << "line a + point f" << endl;
			d.print();
			getch();
		}
		if (z == '4')
		{
			cout << "line a" << endl;
			a.print();
			cout << "point f" << endl << f.x << " " << f.y << endl;
			broken_line d = f + a;
			cout << "point f + line a" << endl;
			d.print();
			getch();
		}
		if (z == '5')
		{
			cout << "line a" << endl;
			a.print();
			cout << "lengh line a: " << a.calculate();
			getch();
		}
		if (z == '6')
		{
			broken_line t(4);
			t[0].x = 150;
			t[0].y = 30;
			t[1].x = 100;
			t[1].y = 30;
			t[2].x = 100;
			t[2].y = 100;
			t[3].x = 150;
			t[3].y = 100;
			t.print_graf();
			getch();
		}
		if (z == '7') return 0;
	}
}