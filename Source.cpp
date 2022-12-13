#include<cstdio>
#include<iostream>
#include<conio.h>
#include"Graphics.h"
#include"complex"
#include<vector>
#include<iterator>
Graphics g;

template <class Type>
struct point
{
	Type x, y;
	point(Type _x = 0, Type _y = 0) : x(_x), y(_y) {}
	point(const point& v)
	{
		x = v.x;
		y = v.y;
	}
};

const double accuracy = 1.0E-38;


template <class Type>
class broken_line;

template <class Type>
double calculate(const broken_line<Type>& v);

template <class Type>
void print_graf(const broken_line<Type>& v);

template <class Type>
class broken_line
{
	std::vector<point<Type>> line;
public:
	broken_line(int _size = 0)
	{
		if (_size < 0) throw "Error! Array size cannot be negative";

		for (int i = 0; i < _size; i++) line.push_back(point<Type>(0, 0));
	}

	broken_line(const broken_line&) = default;

	~broken_line() = default;

	broken_line& operator = (const broken_line&) = default;

	broken_line& operator += (const broken_line& v)
	{
		int x = line.size();
		for (int i = 0; i < v.line.size(); i++) line.push_back(point<Type>(v.line[i].x, v.line[i].y));
		return *this;
	}

	broken_line operator + (const broken_line& v)
	{
		broken_line temp(*this);
		temp += v;
		return temp;
	}

	broken_line<Type>& operator += (const point<Type>& v)
	{
		line.push_back(point<Type>(v.x, v.y));
		return *this;
	}

	broken_line<Type> operator + (const point<Type>& v)
	{
		broken_line temp(*this);
		temp += v;
		return temp;
	}

	const point<Type>& operator[] (int index) const
	{
		if (index < line.size() || line.size() == 0) return line[index];
		else throw "Error! Element with this index does not exist.";
	}

	point<Type>& operator[] (int index)
	{
		if (index < line.size() || line.size() == 0) return line[index];
		else throw "Error! Element with this index does not exist.";
	}

	bool operator == (const broken_line& v)
	{
		if (line.size() != v.line.size()) return false;
		for (int i = 0; i < line.size(); i++) if (accuracy < abs(line[i].x != v.line[i].x) || accuracy < abs(line[i].y != v.line[i].y)) return false;
		return true;
	}
	bool operator != (const broken_line& v)
	{
		return !(*this == v);
	}

	friend double calculate<>(const broken_line<Type>& v);

	friend void print_graf<>(const broken_line<Type>& v);

	auto begin()
	{
		return line.begin();

	}

	auto end()
	{
		return line.end();
	}

	int get_size() const { return line.size(); }

	friend broken_line<Type> operator + (const point<Type>& p, const broken_line<Type>& v)
	{
		broken_line temp(0);
		temp += p;
		temp += v;
		return temp;
	}

	friend std::ostream& operator << (std::ostream& os, const broken_line<Type>& v)
	{
		os << "size: " << v.get_size() << std::endl;
		for (const auto i : v.line)
		{
			os << i.x << " " << i.y << std::endl;
		}
		os << std::endl;
		return os;
	}
};

template <class Type>
double calculate(const broken_line<Type>& v)
{
	double rez = 0;
	if (v.get_size() < 2) return rez;
	for (int i = 0; i < v.get_size() - 1; i++) rez += sqrt(pow((v.line[i + 1].x - v.line[i].x), 2) + pow((v.line[i + 1].y - v.line[i].y), 2));
	return rez;
}
template <>
double calculate(const broken_line<std::complex<double>>& v)
{
	double rez = 0;
	if (v.get_size() < 2) return rez;
	for (int i = 0; i < v.get_size() - 1; i++) rez += sqrt(pow((v.line[i + 1].x.real() - v.line[i].x.real()), 2) + pow((v.line[i + 1].y.real() - v.line[i].y.real()), 2));
	return rez;
}
template <>
double calculate(const broken_line<std::complex<float>>& v)
{
	double rez = 0;
	if (v.get_size() < 2) return rez;
	for (int i = 0; i < v.get_size() - 1; i++) rez += sqrt(pow((v.line[i + 1].x.real() - v.line[i].x.real()), 2) + pow((v.line[i + 1].y.real() - v.line[i].y.real()), 2));
	return rez;
}

template <class Type>
void print_graf(const broken_line<Type>& v)
{
	for (int i = 0; i < v.get_size() - 1; i++) g.DrawLine(float(v.line[i].x), float(v.line[i].y), float(v.line[i + 1].x), float(v.line[i + 1].y));
}
template <>
void print_graf(const broken_line<std::complex<double>>& v)
{
	for (int i = 0; i < v.get_size() - 1; i++) g.DrawLine(float(v.line[i].x.real()), float(v.line[i].y.real()), float(v.line[i + 1].x.real()), float(v.line[i + 1].y.real()));
}
template <>
void print_graf(const broken_line<std::complex<float>>& v)
{
	for (int i = 0; i < v.get_size() - 1; i++) g.DrawLine(float(v.line[i].x.real()), float(v.line[i].y.real()), float(v.line[i + 1].x.real()), float(v.line[i + 1].y.real()));
}
///////////////////////////////////////
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
	if (*b == 0 || *b == '.') return false;
	if (*b == '0' && (*(b + 1) != 0 && *(b + 1) != '.')) return false;
	while (*b != 0 && *b != '.')
	{
		if (*b < '0' || *b > '9') return false;
		b++;
	}
	if (*b == '.')
	{
		b++;
		if (*b == 0) return false;
		while (*b)
		{
			if (*b < '0' || *b > '9') return false;
			b++;
		}
	}
	return true;
}

bool test_complex(char* b)
{
	if (*b == '-') b++;
	if (*b == 0 || *b == '.' || *b == ' ') return false;
	if (*b == '0' && (*(b + 1) != ' ' && *(b + 1) != '.')) return false;
	while (*b != 0 && *b != '.' && *b != ' ')
	{
		if (*b < '0' || *b > '9') return false;
		b++;
	}
	if (*b == '.')
	{
		b++;
		if (*b == 0) return false;
		while (*b != 0 && *b != ' ')
		{
			if (*b < '0' || *b > '9') return false;
			b++;
		}
	}
	if (*b == 0) return false;
	b++;
	return test_double(b);
}

template <class Type>
Type scan()
{
	bool i = false;
	while (true)
	{
		char* str = new char[256];
		std::cin.getline(str, 256);
		if (typeid(Type) == typeid(int)) i = test_int(str);
		if (typeid(Type) == typeid(double) || typeid(Type) == typeid(float)) i = test_double(str);
		if (i)
		{
			Type x = 0;
			if (typeid(Type) == typeid(int)) x = atoi(str);
			if (typeid(Type) == typeid(double) || typeid(Type) == typeid(float)) x = atof(str);
			delete[] str;
			return x;
		}
		else puts("Wrong data");
		delete[]str;
	}
}
template<>
std::complex<double> scan()
{
	while (true)
	{
		char* str = new char[256];
		std::cin.getline(str, 256);
		if (test_complex(str))
		{
			char* tmp = str;
			while (*tmp != ' ') tmp++;
			tmp++;
			std::complex<double> y(atof(str), atof(tmp));
			delete[] str;
			return y;
		}
		else puts("Wrong data");
		delete[]str;
	}
}
std::complex<float> scan()
{
	while (true)
	{
		char* str = new char[256];
		std::cin.getline(str, 256);
		if (test_complex(str))
		{
			char* tmp = str;
			while (*tmp != ' ') tmp++;
			tmp++;
			std::complex<float> y(atof(str), atof(tmp));
			delete[] str;
			return y;
		}
		else puts("Wrong data");
		delete[]str;
	}
}

int main()
{
	std::cout << "1 - Work with int data\n";
	std::cout << "2 - Work with double data\n";
	std::cout << "3 - Work with complex<double> data\n";
	while (true)
	{
		int zl = getch();
		if (zl == '1')
		{
			broken_line<int> a(5);
			broken_line<int> b(5);
			point<int> f(4, 5);
			while (true)
			{
				system("cls");
				std::cout << a;
				std::cout << b;
				std::cout << "1 - Enter value by index" << std::endl;
				std::cout << "2 - Obj broken_line + obj broken_line" << std::endl;
				std::cout << "3 - Obj broken_line + obj point" << std::endl;
				std::cout << "4 - Obj point + obj broken_line" << std::endl;
				std::cout << "5 - Calculate" << std::endl;
				std::cout << "6 - Task" << std::endl;
				std::cout << "7 - Compare obj a and obj b" << std::endl;
				std::cout << "8 - Exit" << std::endl;
				std::cout << "9 - Create new broken_line" << std::endl;
				int z = getch();
				system("cls");
				if (z == '1')
				{
					int index;
					int value_x, value_y; // 1
					int l = '3';
					std::cout << "Enter index" << std::endl;
					index = scan<int>();
					std::cout << "Enter value for x" << std::endl;
					value_x = scan<int>();
					std::cout << "Enter value for y" << std::endl;
					value_y = scan<int>();
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
						if (getch()) z = '0';
					}
					system("cls");
				}
				if (z == '2')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "line b" << std::endl;
					std::cout << b;
					try
					{
						a = a + b;
						std::cout << "line a + line b" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '3')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = a + f;
						std::cout << "line a + point f" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '4')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = f + a;
						std::cout << "point f + line a" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '5')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "lengh line a: " << calculate<int>(a);
					if (getch()) z = '0';
				}
				if (z == '6')
				{
					broken_line<int> t(4);
					t[0].x = 150;
					t[0].y = 30;
					t[1].x = 100;
					t[1].y = 30;
					t[2].x = 100;
					t[2].y = 100;
					t[3].x = 150;
					t[3].y = 100;
					print_graf<int>(t);
				}
				if (z == '7')
				{
					if (a == b) std::cout << "Objects are the same";
					if (a != b) std::cout << "Objects are different";
					if (getch()) z = '0';
				}
				if (z == '8') return 0;
				if (z == '9')
				{
					int size = 0;
					std::cout << "Enter new size" << std::endl;
					while (size <= 0) size = scan<int>();
					broken_line<int> v(size);
					a = v;
				}
			}
		}
		if (zl == '2')
		{
			broken_line<double> a(5);
			broken_line<double> b(5);
			point<double> f(4.0, 5.0);
			while (true)
			{
				system("cls");
				std::cout << a;
				std::cout << b;
				std::cout << "1 - Enter value by index" << std::endl;
				std::cout << "2 - Obj broken_line + obj broken_line" << std::endl;
				std::cout << "3 - Obj broken_line + obj point" << std::endl;
				std::cout << "4 - Obj point + obj broken_line" << std::endl;
				std::cout << "5 - Calculate" << std::endl;
				std::cout << "6 - Task" << std::endl;
				std::cout << "7 - Compare obj a and obj b" << std::endl;
				std::cout << "8 - Exit" << std::endl;
				std::cout << "9 - Create new broken_line" << std::endl;
				int z = getch();
				system("cls");
				if (z == '1')
				{
					int index;
					double value_x, value_y; // 1
					int l = '3';
					std::cout << "Enter index" << std::endl;
					index = scan<int>();
					std::cout << "Enter value for x" << std::endl;
					value_x = scan<double>();
					std::cout << "Enter value for y" << std::endl;
					value_y = scan<double>();
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
						if (getch()) z = '0';
					}
					system("cls");
				}
				if (z == '2')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "line b" << std::endl;
					std::cout << b;
					try
					{
						a = a + b;
						std::cout << "line a + line b" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '3')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = a + f;
						std::cout << "line a + point f" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '4')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = f + a;
						std::cout << "point f + line a" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '5')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "lengh line a: " << calculate<double>(a);
					if (getch()) z = '0';
				}
				if (z == '6')
				{
					broken_line<double> t(4);
					t[0].x = 150;
					t[0].y = 30;
					t[1].x = 100;
					t[1].y = 30;
					t[2].x = 100;
					t[2].y = 100;
					t[3].x = 150;
					t[3].y = 100;
					print_graf<double>(t);
				}
				if (z == '7')
				{
					if (a == b) std::cout << "Objects are the same";
					if (a != b) std::cout << "Objects are different";
					if (getch()) z = '0';
				}
				if (z == '8') return 0;
				if (z == '9')
				{
					int size = 0;
					std::cout << "Enter new size" << std::endl;
					while (size <= 0) size = scan<int>();
					broken_line<double> v(size);
					a = v;
				}
			}
		}
		if (zl == '3')
		{
			broken_line<std::complex<double>> a(5);
			broken_line<std::complex<double>> b(5);
			point<std::complex<double>> f(4.0, 5.0);
			while (true)
			{
				system("cls");
				std::cout << a;
				std::cout << b;
				std::cout << "1 - Enter value by index" << std::endl;
				std::cout << "2 - Obj broken_line + obj broken_line" << std::endl;
				std::cout << "3 - Obj broken_line + obj point" << std::endl;
				std::cout << "4 - Obj point + obj broken_line" << std::endl;
				std::cout << "5 - Calculate" << std::endl;
				std::cout << "6 - Task" << std::endl;
				std::cout << "7 - Compare obj a and obj b" << std::endl;
				std::cout << "8 - Exit" << std::endl;
				std::cout << "9 - Create new broken_line" << std::endl;
				int z = getch();
				system("cls");
				if (z == '1')
				{
					int index;
					std::complex<double> value_x, value_y; // 1
					std::cout << "Enter index" << std::endl;
					index = scan<int>();
					std::cout << "Enter value for x" << std::endl;
					value_x = scan<std::complex<double>>();
					std::cout << "Enter value for y" << std::endl;
					value_y = scan<std::complex<double>>();
					int l = '3';
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
						if (getch()) z = '0';
					}
					system("cls");
				}
				if (z == '2')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "line b" << std::endl;
					std::cout << b;
					try
					{
						a = a + b;
						std::cout << "line a + line b" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '3')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = a + f;
						std::cout << "line a + point f" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '4')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "point f" << std::endl << f.x << " " << f.y << std::endl << std::endl;
					try
					{
						a = f + a;
						std::cout << "point f + line a" << std::endl;
						std::cout << a;
					}
					catch (const char* msg)
					{
						std::cout << msg << std::endl;
					}
					if (getch()) z = '0';
				}
				if (z == '5')
				{
					std::cout << "line a" << std::endl;
					std::cout << a;
					std::cout << "lengh line a: " << calculate<std::complex<double>>(a);
					if (getch()) z = '0';
				}
				if (z == '6')
				{
					broken_line<std::complex<double>> t(4);
					t[0].x = 150;
					t[0].y = 30;
					t[1].x = 100;
					t[1].y = 30;
					t[2].x = 100;
					t[2].y = 100;
					t[3].x = 150;
					t[3].y = 100;
					print_graf<std::complex<double>>(t);
				}
				if (z == '7')
				{
					if (a == b) std::cout << "Objects are the same";
					if (a != b) std::cout << "Objects are different";
					if (getch()) z = '0';
				}
				if (z == '8') return 0;

				if (z == '9')
				{
					int size = 0;
					std::cout << "Enter new size" << std::endl;
					while (size <= 0) size = scan<int>();
					broken_line<std::complex<double>> v(size);
					a = v;
				}
			}
		}
	}

}