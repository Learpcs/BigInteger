#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

	
template <class type> 
class BigInteger
{
private:
	const type base = 1 << sizeof(type) * 4;
	const type max = base - 1;
	vector<type> digits;

public:
	BigInteger()
	{
		this->digits.push_back(0);
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
		return copy;
	}

	template <class type>
	friend istream& operator >>(istream& in, BigInteger<type>& object);

	template <class type>
	friend ostream& operator <<(ostream& out, const BigInteger<type>& object);
};

template <class type>
istream& operator >>(istream& in, BigInteger<type>& object)
{
	object.digits.clear();
	for (char ch = in.get(); ch != '\n'; ch = in.get())
	{
		object.digits.push_back(ch - '0');
	}
	size_t size = object.digits.size();
	//i was doing it at 4 am and i suspect i wanted to do conversion from decimal to my base numerical system 
	for (size_t i = 1; i < size; i++) //what is this?
	{
		for (size_t j = i; j > 0 && object.digits[j - 1] < object.max; j--)
		{
			if (object.max - object.digits[j - 1] >= object.digits[j])
			{
				object.digits[j - 1] += object.digits[j];
				object.digits[j] = 0;
			}
			else
			{
				object.digits[j - 1] += min(object.max - object.digits[j - 1], object.digits[j]);
				object.digits[j] -= min(object.max - object.digits[j - 1], object.digits[j]);
			}
		}
	}
	return in;
}

template <class type>
ostream& operator <<(ostream& out, const BigInteger<type>& object)
{
	for (vector<type>::const_reverse_iterator i = object.digits.rbegin(); i != object.digits.rend(); i++)
		out << *i;
	return out;
}

typedef BigInteger<size_t> BigInt;

int main()
{
	BigInt a, b;
	cin >> a >> b;
	cout << a + b;
}
