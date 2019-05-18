#pragma once
#include <string>

using namespace std;


class Product
{
private:
	string name;
	int quantity;

public:
	Product(const string &_name = "", const int &_quantity = 0);
	friend ostream& operator<<(ostream& cout, const Product& p);
};

Product::Product(const string &_name, const int &_quantity)
{
	name = _name;
	quantity = _quantity;
}

ostream& operator<<(ostream& cout, const Product& p)
{
	cout.setf(ios::left);
	cout.width(25);
	cout << p.name;
	cout.width(30);
	cout << p.quantity;
	cout << endl;
	return cout;
}