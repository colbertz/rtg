//Theoretically the matrix way to calcaulate Fib series is
//fast as O(logn). Due to the max Fib number can be represented
//by 64 bit integer is F93. This algothrim is slower than the
//DP one in this input level based on my test.
//The reason is O(log100) = 7, but each of it requires at least
//8 times of multiplication, as well as calling and returning cost.
//DP algorithm is accurate O(n) = 100

//If we consider to use string to represent the very large integer,
//I guess this Fast way is still slower than the DP way because
//it requires mutiplication while DP only uses add.

#include <iostream>

class Matrix
{

public:
	Matrix(unsigned long long a, unsigned long long b, 
    unsigned long long c, unsigned long long d)
		:a11(a), a12(b), a21(c), a22(d)
	{

	}

	unsigned long long a11;
	unsigned long long a12;
	unsigned long long a21;
	unsigned long long a22;

	Matrix operator *(const Matrix& m1)
	{
		return Matrix(this->a11*m1.a11 + this->a12*m1.a21,
			this->a11*m1.a12 + this->a12*m1.a22,
			this->a21*m1.a11 + this->a22*m1.a21,
			this->a21*m1.a12 + this->a22*m1.a22);
	}
};

Matrix Power(Matrix m, unsigned long long power)
{
	if (power == 1)
	{
		return m;
	}

	if (power % 2 == 0)
	{
		m = Power(m, power / 2);
		m = m*m;
		return m;
	}
	else
	{
		m = Power(m, power / 2);
		m = m*m;
		m = m*Matrix(1, 1, 1, 0);
		return m;
	}
}
//The Theoretical fast way to calculate Fib series
unsigned long long FastFib(unsigned long long n)
{
	if (n < 2) return n;

	return Power(Matrix(1, 1, 1, 0), n - 1).a11;
}
//DP method to calculate Fib series
unsigned long long DPFib(unsigned long long n)
{
	if (n < 2) return n;

	unsigned long long num1 = 0;
	unsigned long long num2 = 1;

	while (n-- >= 2)
	{
		unsigned long long temp = num2;
		num2 = num1 + num2;
		num1 = temp;
	}

	return num2;
}

int main()
{
	int n = 0;
	do
	{
		std::cout << n << ": " << FastFib(n) << std::endl;
		n++;
	} while (n <= 93);
}

