

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;



class Timer
{
public:
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> difer = end - start;
		std::cout << " \nDuratioun - " << difer.count() << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};



class Test
{


public:
	double  y1, y2; //y1 = u y2 = z
	Test difer(double x);
	void print(ofstream *f, double x);
};



Test Test::difer(double x)
{
	Test d;
	d.y1 = y2;
	d.y2 = -exp(x)*y2 + (10 + sin(x))* y1 - 50*((11 + sin(x))*sin(x) - exp(x)*cos(x));
	return d;
}

void Test::print(ofstream *f, double x)
{
	*f<<" x = "<<x<< " u = " << y1 << " z = " << y2<< std::endl;
}


Test operator+(Test a, Test b)
{
	Test c;
	c.y1 = a.y1 + b.y1;
	c.y2 = a.y2 + b.y2;
	/*c.y3 = a.y3 + b.y3;
	c.y4 = a.y4 + b.y4;*/
	return c;
}

Test operator*(Test a, double b)
{
	Test c;
	//c.x = a.x*b;
	c.y1 = a.y1*b;
	c.y2 = a.y2*b;
	/*c.y3 = a.y3*b;
	c.y4 = a.y4*b;*/
	return c;
}







void rynge_kytta()
{
	using namespace std;
	Test p1, p2, p3, p4, pk, k1, k2, k3, k4, kk;

	ofstream file;		file.open("Logs.txt");
	ofstream file_graf;	file_graf.open("Logs_graf.txt");  file_graf << " y = [";

	p1.y1 = 0;
	p1.y2 = 50;


	double h = 0.05;
	double x = 0;
	p1.print(&file, x);
	while (x <= 1)
	{
		
		k1 = p1.difer(x);

		p2 = p1 + k1 * (h / 2);
		k2 = p2.difer(x + h / 2);

		p3 = p1 + k2 * (h / 2);
		k3 = p3.difer(x + h / 2);

		p4 = p1 + k3 * h;
		k4 = p4.difer(x + h);

		kk = (k1 + k2 * 2 + k3 * 2 + k4)*(1.0 / 6.0);
		pk = p1 + kk * (h);
		p1 = pk;
		x += h;
		p1.print(&file, x);
		file_graf << p1.y1 << " ";
	}

	file_graf << "];\n x [= ";
	x = 0;
	while (x <= 1)
	{
		x += h;
		file_graf<<x << " ";
	}
	file_graf << "];\nplot(x,y,'r');\n grid on; hold on;";
	file_graf.close();
	file.close();
}

int main()
{
	Timer time;
	setlocale(LC_ALL, "ru");
	rynge_kytta();

	
}












