



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <thread>
const bool print = 0;
#define FABS ||
class Timer			/* Это класс для замера времене вычисления. На ход решения не влияет*/
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
		std::cout << " \nComputation time - " << difer.count() << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};

#define EPS 1e-3



class Test /*Данный класс описывает систему диффуров */
{
private:
	double  x, y, z;
public:
	
	Test difer();
	void print();
	
	
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setZ(double z) { this->z = z; }

	Test operator+(const Test &other){	Test c;		/*Перегрузка различных операторов */
		c.x = this->x + other.x;
		c.y = this->y + other.y;
		c.z = this->z + other.z;
		return c;
	}

	Test operator-(const Test  &other) { Test c;
	c.x = this->x - other.x;
	c.y = this->y - other.y;
	c.z = this->z - other.z;
	return c;
	}

	Test operator*(double value) {	Test c;
	c.x = value * this->x;
	c.y = value * this->y;
	c.z = value * this->z;
	return c;
	}

	bool operator>(double epsilon)	{	return this->y > epsilon && this->z >epsilon;}



	Test operator /(const Test &other) {
		Test b;
		b.y = this->y / other.y;
		b.x = this->x / other.x;
		b.z = this->z / other.z;

		return b;
	}

	void  FAB() {
		this->x = fabs(this->x);
		this->y = fabs(this->y);
		this->z = fabs(this->z);

	}

	bool Any()	{	return this->y > EPS && this->z > EPS;}

	bool ALL()	{	return this->y < EPS / 32.0 && this->z < EPS / 32.0;}
};



Test Test::difer()		/*Система диффуров. */
{
	Test d;
	
	d.z = 2 * x*z / (x*x + 1);
	d.y = z;



	d.x = 1;
	return d;
}

void Test::print()		/*Вывод в консоль */
{
	std::cout <<"x = "<<x<< " y= " << y << " z= " << z << std::endl;
}







void Rynge_Kyt()
{
	setlocale(LC_ALL, "ru");

	using namespace std;
	Test p1, p2, p3, p4, pk, k1, k2, k2k, k3, k3k, k4, kk, p5, pkKontrol;

	double h = 0.001; //начальный шаг

	p1.setX(0);		p1.setY(1);		p1.setZ(3);
	
	double x = 0;

	Test e, mu;
	double right_board	= 1.0; //граница интервала
	
	double h_min		= 0.000001;
	double h_max		= 0.1;

	int count = 0;


	
	do
	{
		
		p1.print();

		
		k1 = p1.difer();

		p2 = p1 + k1 * (h / 2.0);	
		k2 = p2.difer();

		p3 = p1 + k2 * (h / 2.0);		
		k3 = p3.difer();

		p4 = p1 + k3 * h;			
		k4 = p4.difer();

		kk = (k1 + k2 * 2 + k3 * 2 + k4)*(1.0 / 6.0);	
		pk = p1 + kk * h;

		p1 = pk;


		
		count++;

		x += h;

		if (right_board - x < h)
			h = right_board - x;
		
		pkKontrol = p1 + kk * h; //Вычисление для опредления меры погрешности 

		
		
		std::cout << " \n";


		e = (((k1 - k2 - k3 + k4)*(2. / 3.)));// контрольный член
		e.FAB();
		

		pkKontrol.FAB();

		if (pkKontrol > 0.001)
			mu = e / pkKontrol;
		else
			mu = e;

		bool ex = mu.Any();		bool ex2 = mu.ALL();

		if (mu.Any() && h > 2 * h_min)	//Изменение шага
		{
			h = h / 2;
		}
		else if (mu.ALL() && h < 0.5*h_max)
		{
			h = h * 2;
		}
		
		
	} while (x < right_board);
	

	p1.print();
	std::cout << "Количество итераций= " << count << std::endl;
}



int main()
{
	Timer clock;
	Rynge_Kyt();
	
}


