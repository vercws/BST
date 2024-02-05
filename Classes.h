#pragma once
#include <iostream>

template<typename T, typename Comparator1, typename Comparator2>
class Tree
{
public:
	class Node
	{
		public:
			Node(T*& newData) //root
			{
				data = newData;
				left = nullptr;
				right = nullptr;
				parent = nullptr;
			}
			Node()
			{
				data = nullptr;
				left = nullptr;
				right = nullptr;
				parent = nullptr;

			}
			Node* parent;
			Node* left;
			Node* right;
			T* data;
	};
	Node* root = nullptr;
	int size = 0;
	int height = 0;


	void addNode(T*& data, Comparator1& comp); // Arguemty: dane i komparator 
	Node* returnNode(T*& data, Comparator1& comp, Comparator2& even); // Argumenty: dane i komparator i wynik ewentualnie null
	void deleteNode(Node*& node); // Argumenty: wskaŸnik na wêze³ do usuniêcia
	// stworzenie dodatkowej metody znajduj¹cej w³aœciwego kandydata do zast¹pienia
	void pre_orderTraversal(Node*& node);
	void in_orderTraversal(Node*& node);
	void deleteAll();
	void deleteA(Node*& node);
	int HeightCheck(Node*& node);
	void displayTree(Node*& node);
	Node* findInOrderNew(Node* node);
	Node* findInOrderNewRoot(Node* node);
};

class Data
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Data* data)
	{
		os << data->value << ", ";
		os << data->character << "\n";
		return os;
	}
	//Data(int& v, char& c)
	//{
	//	value = v;
	//	character = c;
	//};
	Data(int val, char ch)
	{
		value = val;
		character = ch;
	};
	int value;
	char character;
};


class MyCompare //czy pierwsze jest wiêksze od drugiego
{
public:
	bool operator()(const Data* d1, const Data* d2) const
	{
		if (d1->value > d2->value)
		{
			return true;
		}
		else if (d1->value == d2->value && d1->character > d2->character)
		{
			return true;
		}
		else {
			return false;
		}

	}
};

class IfEven
{
public:
	bool operator()(const Data* d1, const Data* d2) const
	{
		if (d1->value == d2->value && d1->character == d2->character)
		{
			return true;
		}
		else
			return false;
	}
};