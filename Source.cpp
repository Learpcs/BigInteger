#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class BigInteger
{
private:
	size_t base = 10;//65536; //беру такую систему счисления потому, что это крайнее число для того, чтобы при перемножении числа уместились в size_t (если выделяется 4 байта)
	vector<size_t> digits;
	bool is_positive = true;	

public:
	BigInteger()
	{

	}

	BigInteger& operator= (const BigInteger& another)
	{
		this->digits = another.digits;
		return *this;
	}

	BigInteger& operator +=(const BigInteger& another) 
	{
		while (this->digits.size() < another.digits.size())
			this->digits.push_back(0);
		this->digits.push_back(0); //999 <=> 0999
		size_t size = another.digits.size();                //в два прохода
		for (size_t i = 0; i < size; i++)                     
		{
			this->digits[i] += another.digits[i];			//1 проход - просто складывает
		}
		for (size_t i = 0; ; i++)
		{
			if (this->digits[i] >= base)					//2 проход - учитывает остатки				
			{
				this->digits[i] -= base;
				digits[i + 1]++;
			}
			else if (i >= size)
				break;
		}
		while (this->digits.back() == 0 && this->digits.size() != 1) //1 условие - убрать ведущие нули, 2 условие - случай 0 + 0
			this->digits.pop_back();
		return *this;
		
	}
	BigInteger operator +(const BigInteger& another)
	{
		*this += another;
		return *this;
	}
	BigInteger& operator -=(const BigInteger& another)
	{

	}
	BigInteger& operator -(const BigInteger& another)
	{
		*this -= another;
		return *this;
	}
	BigInteger& operator *=(const BigInteger& another)
	{

	}
	BigInteger& operator *(const BigInteger& another)
	{
		*this *= another;
		return *this;
	}
	BigInteger& operator /=(const BigInteger& another)
	{

	}
	BigInteger& operator /(const BigInteger& another)
	{
		*this /= another;
		return *this;
	}


	

	friend ostream& operator << (ostream& out, const BigInteger& object);
	friend istream& operator >> (istream& in, BigInteger& object);
};

ostream& operator << (ostream& out, const BigInteger& object)
{
	for (vector<size_t>::const_reverse_iterator i = object.digits.rbegin(); i != object.digits.rend(); i++)
		out << *i;
	return out;
}

istream& operator >> (istream& in, BigInteger& object)
{
	string input;
	in >> input;
	//в случае если экземпляр BigInteger уже имеет в себе числа, чтобы они не вводились "поверх" остальных - clear(), т.к. используется push_back()
	object.digits.clear(); 

	for (string::reverse_iterator i = input.rbegin(); i != input.rend(); i++)
	{
		object.digits.push_back(*i - '0');
	}
	return in;
}

int main()
{

	BigInteger a, b;
	cin >> a >> b;
	cout << a + b;
}