#include<cstdio>
#include<iostream>
#include<conio.h>
#include<windows.h>
#include"Graphics.h"

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
		line = new point[size];
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
		line = new point[size];
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
		delete[] line;
		size = 0;
		count = 0;
	}

	broken_line& operator = (const broken_line& v)
	{
		if (size < v.count || count > v.count) throw "Right object data cannot be passed to left object";
		for (int i = 0; i < count; i++)
		{
			line[i].x = v.line[i].x;
			line[i].y = v.line[i].y;
		}
		return *this;
	}

	broken_line& operator += (const broken_line& v)
	{
		if (size - (count + v.count) > grow) size = count + v.count;
		else size += grow;
		point* tmp = new point[size];
		for (int i = 0; i < count; i++)
		{
			tmp[i].x = line[i].x;
			tmp[i].y = line[i].y;
		}
		for (int i = 0; i < v.count; i++)
		{
			tmp[i + count].x = v.line[i].x;
			tmp[i + count].y = v.line[i].y;
		}
		delete[] line;
		line = tmp;
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
		point* tmp = new point[size];
		for (int i = 0; i < count; i++)
		{
			tmp[i].x = line[i].x;
			tmp[i].y = line[i].y;
		}
		tmp[count].x = v.x;
		tmp[count++].y = v.y;
		delete[] line;
		line = tmp;
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
		std::cout << "size: " << size << std::endl << "count: " << count << std::endl;
		for (int i = 0; i < count; i++) std::cout << line[i].x << " " << line[i].y << std::endl;
		std::cout << std::endl;
	}

	void print_graf()
	{
		for (int i = 0; i < count - 1; i++) g.DrawLine(float(line[i].x), float(line[i].y), float(line[i + 1].x), float(line[i + 1].y));
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

bool test_int(char* b)
{
	
	if (*b == '-') b++;
	if (*b == 0) return false;
	if (*b == '0' && *(b + 1) != 0) return false;
	while (*b)
	{
		if (*b < '0' || *b>'9') return false;
		b++;
	}
	return true;
}

bool test_double(char* b)
{
	if (*b == '-') b++;
	if (*b == 0) return false;
	if (*b == '0' && (*(b + 1) != 0 && *(b + 1) != '.')) return false;
	while (*b != 0 && *b != '.')
	{
		if (*b < '0' || *b>'9') return false;
		b++;
	}
	if (*b == '.')
	{
		b++;
		if (*b == 0) return false;
		while (*b)
		{
			if (*b < '0' || *b>'9') return false;
			b++;
		}
	}
	return true;
}


double scan(bool n) 
{
	bool i = false; 
	while (true)
	{
		char* str = new char[256];
		std::cin.getline(str, 256);
		if (n == true) i = test_int(str);
		else i = test_double(str);
		if (i)
		{
			double x = atof(str);
			delete[] str;
			return x;
		}
		else puts("Wrong data");
		delete []str;
	}
}

int main()
{
	broken_line a(5);
	broken_line b(5);
	point f;
	f.x = 4;
	f.y = 5;
	while (true)
	{
		system("cls");
		std::cout << "1 - Enter value by index" << std::endl;
		std::cout << "2 - Obj broken_list + obj broken_list" << std::endl;
		std::cout << "3 - Obj broken_list + obj point" << std::endl;
		std::cout << "4 - Obj point + obj broken_list" << std::endl;
		std::cout << "5 - Calculate" << std::endl;
		std::cout << "6 - Tack" << std::endl;
		std::cout << "7 - Exit" << std::endl;
		int z = getch();
		system("cls");
		if (z == '1')
		{
			int index;
			double value_x, value_y;
			int l = '3';
			std::cout << "Enter index" << std::endl;
			index = int(scan(true));
			std::cout << "Enter value for x" << std::endl;
			value_x = scan(false);
			std::cout << "Enter value for y" << std::endl;
			value_y = scan(false);
			std::cout << "1 - add to line a\n2 - add to line b" << std::endl;
			while (l != '1' && l != '2') l = getch();
			try
			{
				if (l == '1')
				{
					a[index].x = value_x;
					a[index].y = value_y;
				}
				else
				{
					b[index].x = value_x;
					b[index].y = value_y;
				}	
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				getch();
			}
			system("cls");
		}
		if (z == '2')
		{
			std::cout << "line a" << std::endl;
			a.print();
			std::cout << "line b" << std::endl;
			b.print();
			try
			{
				broken_line d(10);
				d = a + b;
				std::cout << "line a + line b" << std::endl;
				d.print();
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
			}
			getch();
		}
		if (z == '3')
		{
			std::cout << "line a" << std::endl;
			a.print();
			std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
			try
			{
				broken_line d(6);
				d = a + f;
				std::cout << "line a + point f" << std::endl;
				d.print();
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
			}
			getch();
		}
		if (z == '4')
		{
			std::cout << "line a" << std::endl;
			a.print();
			std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
			try
			{
				broken_line d(6);
				d = f + a;
				std::cout << "point f + line a" << std::endl;
				d.print();
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
			}
			getch();
		}
		if (z == '5')
		{
			std::cout << "line a" << std::endl;
			a.print();
			std::cout << "lengh line a: " << a.calculate();
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