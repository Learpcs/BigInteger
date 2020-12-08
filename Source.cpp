#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

	
template <class type> 
class BigInteger
{
private:
	const size_t base = 1000000000;
	const unsigned short max_digits = 5;//ceil(log10(sqrt(base)));
	vector<type> digits;

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
		size_t size = another.digits.size();                //addition in two steps:
		for (size_t i = 0; i < size; i++)					
		{
			this->digits[i] += another.digits[i];			//1 simple addition, ignoring overflow of digits
		}
		for (size_t i = 0; ; i++)
		{
			if (this->digits[i] >= base)					//2 take into account the remainders				
			{
				this->digits[i] -= base;
				digits[i + 1]++;
			}
			else if (i >= size)
				break;
		}
		while (this->digits.back() == 0 && this->digits.size() != 1) 
			this->digits.pop_back();
		return *this;
	}

	BigInteger operator +(const BigInteger& another)
	{
		BigInteger copy = *this;
		return copy += another;
	}

	template <class type>
	friend istream& operator >>(istream& in, BigInteger<type>& object);

	template <class type>
	friend ostream& operator <<(ostream& out, const BigInteger<type>& object);
};

template <class type>
istream& operator >>(istream& in, BigInteger<type>& object)
{
	string input;
	in >> input;
	//мне нужно уходить в отрицательные числа поэтому long long, а size_t - самый большой тип после long long
	for (long long i = static_cast<long long>(input.size()) - object.max_digits; ; i -= object.max_digits)
	{
		if (i >= 0)
		{
			object.digits.push_back(stoull(input.substr(i, object.max_digits)));
		}
		else 
		{
			if (object.max_digits + i != 0)
				object.digits.push_back(stoull(input.substr(0, object.max_digits + i)));
			break;
		}
	}

	return in;
}

template <class type>
ostream& operator <<(ostream& out, const BigInteger<type>& object)
{

	return out;
}

typedef BigInteger<size_t> BigInt;

int main()
{
	BigInt a, b;
	cin >> a >> b;
	cout << a + b;
}
