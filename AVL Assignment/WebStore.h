#pragma once
#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Product.h"

using namespace std;

// Class to test the functionality of Associative Maps using Binary Search Tree

class WebStore
{
private:
	AVLTree<int, Product> ProductMap; // Stock of items in Store
public:
	void Load();
	inline void ShowLine();
	void ShowMenu();
	void PrintItems(); // Print Items in Sorted Order using Inorder traversal of BST
	void AddNewItem();
	void DeleteItem();
	void SearchAnItem();
	void ChoiceMaker(char choice);
	void UserInput();
	void PrintTreeDiagram();	// Print the keys in a Tree Diagram
};

void WebStore::Load()
{
	ifstream input("Data.txt");
	string buffer;
	getline(input, buffer);
	while (getline(input, buffer))
	{
		int ID;
		string name;
		int quantity;
		stringstream s(buffer);
		s >> ID;
		s.ignore();
		getline(s, name, '\t');
		s >> quantity;
		Product *p= new Product(name, quantity);
		ProductMap.Insert(ID,p);
	}
}

void WebStore::ShowLine()
{
	for (int i = 0; i < 50; i++)
	{
		cout << '-';
	}
	cout << endl;
}

void WebStore::ShowMenu()
{
	ShowLine();
	cout << "\t\t\tMENU\n";
	ShowLine();
	cout << "1- Load items from file\n"
		<< "2- Print items with sorted keys\n"
		<< "3- Add new item\n"
		<< "4- Delete an item\n"
		<< "5- Search an Item\n"
		<< "6- Print tree diagram\n"
		<< "E- EXIT \n";
}

void WebStore::ChoiceMaker(char choice)
{
	switch (choice)
	{
	case '1':
		Load();
		break;
	case '2':
		PrintItems();
		break;
	case '3':
		AddNewItem();
		break;
	case '4':
		DeleteItem();
		break;
	case '5':
		SearchAnItem();
		break;
	case '6':
		PrintTreeDiagram();
		break;
	default:
		break;
	}
}

void WebStore::PrintItems()
{
	ShowLine();
	cout.setf(ios::left);
	cout.width(10);
	cout << "ID";
	cout.width(25);
	cout << "Name";
	cout.width(10);
	cout << "Quantity";
	cout << endl;
	ShowLine();
	ProductMap.printInorder();
}

void WebStore::AddNewItem()
{
	string name;
	int id, quantity;

	cout << "Enter the ID of Item: ";
	cin >> id;
	cin.ignore();
	cout << "Enter the Name of Item: ";
	getline(cin, name);
	cout << "Enter the Quantity of Item: ";
	cin >> quantity;

	Product * newProduct = new Product(name, quantity);
	ProductMap.Insert(id, newProduct);
}

void WebStore::DeleteItem()
{
	int id;
	cout << "Enter the ID of Item to be deleted: ";
	cin >> id;
	if (ProductMap.deleteNode(id))
	{
		cout << "\n\nItem deleted successfully.\n\n";
	}
	else
	{
		cout << "\n\nItem with ID " << id << " does not exist.\n\n";
	}
	PrintTreeDiagram();
}

void WebStore::SearchAnItem()
{
	int id;
	cout << "Enter the ID of the Product: ";
	cin >> id;
	if (ProductMap.lookUp(id))
	{
		cout << "\n\nItem with ID " << id << " exists.\n\n";
	}
	else
	{
		cout << "\n\nItem with ID " << id << " does not exists.\n\n";
	}
}

void WebStore::PrintTreeDiagram()
{
	ProductMap.printTree();
	for (int i = 0; i < ProductMap.height(); i++)
	{
		cout << endl;
	}
}

void WebStore::UserInput()
{
	char choice = '0';
	while (choice != 'E')
	{
		ShowMenu();
		cout << "Please make a choice: ";
		cin >> choice;
		cout << endl;
		ChoiceMaker(choice);
		ShowLine();
	}
}