#include "Classes.h"
#include <iostream>
#include <time.h>
#include <random>


template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::addNode(T*& data, Comparator1& comp)
{
	if (root == nullptr)
	{
		Node* newElement = new Node(data);
		root = newElement;
		size++;
	}
	else
	{
		Node* newElement = new Node(data);
		Node* temp = new Node();
		int index = 0;
		temp = root;
		while (temp != nullptr) 
		{
			if (comp(temp->data, newElement->data)) // jeżeli temp wiekszy
			{
				if (temp->left == nullptr)
				{
					temp->left = newElement;
					newElement->parent = temp;
					temp = nullptr;
					size++;
				}
				else
				{
					temp = temp->left;
				}
			}
			else if (comp(temp->data, newElement->data) == false) // temp jest mniejszy lub równy
			{
				if (temp->right == nullptr)
				{
					temp->right = newElement;
					newElement->parent = temp;
					temp = nullptr;
					index++;
					size++;
				}
				else 
				{
					temp = temp->right;
				}
				
			}
		}
			
	}
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1,Comparator2>::Node* Tree<T,Comparator1, Comparator2>::returnNode(T*& data, Comparator1& comp, Comparator2& even)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node* temp = root;
		while (even(temp->data, data) == false) //jeżeli temp różny od data
		{
			if (comp(temp->data, data)) // jeżeli temp wiekszy
			{
				if (even(temp->data, data) == false)
				{
					temp = temp->left;
				}
			}
			else if (comp(temp->data, data) == false) // temp jest mniejszy lub równy
			{
				if (even(temp->data, data) == false)
				{
					temp = temp->right;
				}
			}
			if (temp == nullptr)
			{
				return nullptr;
			}
		}
		return temp;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::findInOrderNew(Node* node)
{
	Node* theNew = node->right;
	while (theNew->left != nullptr)
	{
		theNew = theNew->left;
	}
	return theNew;
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::findInOrderNewRoot(Node* node)
{
	Node* theNew = node->right;
	while (theNew->right != nullptr)
	{
		theNew = theNew->right;
	}
	return theNew;
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::deleteNode(Node*& node)
{
	if (root == nullptr)
	{
		std::cout << "Drzewo jest puste" << std::endl;
		return;
	}
	else
	{
		if (node != root)
		{
			//Jeżeli jest liściem
			if (node->left == nullptr && node->right == nullptr)
			{
				if (node->parent->left == node)
				{
					node->parent->left = nullptr;
				}
				else
				{
					node->parent->right = nullptr;
				}
				delete node;
				size--;

			}
			//Jeżeli ma tylko prawe dziecko
			else if (node->left == nullptr && node->right != nullptr)
			{
				if (node == node->parent->left) // jeżeli jest lewym potomkiem
				{
					node->right->parent = node->parent;
					node->parent->left = node->right; //jeżeli ma prawe dziecko
					delete node;
					size--;
				}
				else // jeżeli jest prawym potomkiem
				{
					node->right->parent = node->parent;
					node->parent->right = node->right; //jeżeli ma prawe dziecko
					delete node;
					size--;
				}

			}
			//Jeżeli ma tylko lewe dziecko
			else if (node->right == nullptr && node->left != nullptr)
			{
				if (node == node->parent->left) //jeżeli jest lewym potomkiem
				{
					node->parent->left = node->left;
					node->left->parent = node->parent;
					delete node;
					size--;
				}
				else //jeżeli jest prawym potomkiem
				{
					node->parent->right = node->left;
					node->left->parent = node->parent;
					delete node;
					size--;
				}
			}
			//Jeżeli ma dwójkę dzieci
			else if (node->right != nullptr && node->left != nullptr)
			{
				Node* New = findInOrderNew(node);
				node->data = New->data;
				deleteNode(New);
				node = nullptr;
				size--;
			}
		}
		else
		{
			//Node* New = findInOrderNewRoot(node); //drzewo czerwono-czarne inspo
			//node->data = New->data;
			//deleteNode(New);
			//node = nullptr;
			//size--;
			root = node->right;

		}
	}
}
template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::deleteA(Node*& node)
{
	if (node != nullptr)
	{
		deleteA(node->left);
		deleteA(node->right);

		delete node;
		node = nullptr;
	}
}


template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::deleteAll()
{
	if (root == nullptr)
	{
		std::cout << "Drzewo jest puste" << std::endl;
		return;
	}
	else
	{
		deleteA(root);
		root = nullptr;
		size = 0;
		height = 0;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
int Tree<T, Comparator1, Comparator2>::HeightCheck(Node*& node)
{
	if (node == nullptr) 
	{
		return 0;
	}

	int heightLeft = HeightCheck(node->left);
	int heightRight = HeightCheck(node->right);

	if (heightLeft > heightRight) 
	{
		return heightLeft + 1;
	}
	else 
	{
		return heightRight + 1;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::displayTree(Node*& node)
{
	if (root == nullptr)
	{
		std::cout << "Drzewo jest puste" << std::endl;
		return;
	}
	else
	{
		if (node != nullptr)
		{
			std::cout << "Rodzic: ";
			if (node->parent != nullptr)
			{
				std::cout << node->parent->data; // << std::endl;
			}
			else
			{
				std::cout << "Brak" << std::endl;
			}
			std::cout << "Dane: " << node->data << "Lewy potomek: ";
			if (node->left != nullptr)
			{
				std::cout << node->left->data;
			}
			else
			{
				std::cout << "Brak" <<std::endl;
			}
			std::cout << "Prawy potomek: ";
			if (node->right != nullptr)
			{
				std::cout << node->right->data;
			}
			else
			{
				std::cout << "Brak" << std::endl;
			}
			std::cout << std::endl;
			displayTree(node->left);
			displayTree(node->right);
		}
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::pre_orderTraversal(Node*& node)
{
	if (node == nullptr)
	{
		return;
	}
	std::cout << node->data << " ";

	pre_orderTraversal(node->left);
	pre_orderTraversal(node->right);
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::in_orderTraversal(Node*& node)
{
	if (node == nullptr)
	{
		return;
	}
	in_orderTraversal(node->left);

	std::cout << node->data << " ";

	in_orderTraversal(node->right);
}

int RandomNumber(long from, long to)
{
	std::random_device rd;
	std::default_random_engine e{ rd() };
	std::uniform_int_distribution <unsigned> u(from, to);
	return u(e);
}

void displayMenu()
{
	bool showMenu = true;
	int choice = 0;
	
	Tree<Data, MyCompare,IfEven> BST;
	MyCompare comparator;
	IfEven even;

	clock_t t1 = clock();
	for (int i = 0; i < 1000; i++)
	{
		int rvalue = RandomNumber(0, 100000);
		char rcharacter = RandomNumber(33, 126);
		Data* newData = new Data(rvalue, rcharacter);
		BST.addNode(newData, comparator);
	}
	clock_t t2 = clock();
	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "\n\n" << time;

	do
	{

		std::cout << "----------Menu----------\n\n";
		std::cout << "1. Dodaj nowy element do drzewa\n"; 
		std::cout << "2. Wyszukaj i zwróć element w drzewie\n"; 
		std::cout << "3. Usuń element drzewa\n"; 
		std::cout << "4. Przejście pre-order drzewa\n"; 
		std::cout << "5. Przejście in-order drzewa\n";
		std::cout << "6. Czyszczenie drzewa\n";
		std::cout << "7. Wyznacz wysokość drzewa\n";
		std::cout << "8. Pokaż drzewo\n";
		std::cout << "9. Wyjście z programu \n";
		std::cout << " \n\n";
		std::cout << "Wybierz opcję: ";
		std::cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
		{
			Data* newData1 = new Data(350, 43);
			BST.addNode(newData1, comparator);
			Data* newData2 = new Data(92, 103);
			BST.addNode(newData2, comparator);
			Data* newData3 = new Data(613, 77);
			BST.addNode(newData3, comparator);
			Data* newData4 = new Data(479, 107);
			BST.addNode(newData4, comparator);
			Data* newData5 = new Data(413, 103);
			BST.addNode(newData5, comparator);
			Data* newData6 = new Data(500, 66);
			BST.addNode(newData6, comparator);
			Data* newData7 = new Data(653, 121);
			BST.addNode(newData7, comparator);
			Data* newData8 = new Data(90, 100);
			BST.addNode(newData8, comparator);
			Data* newData9 = new Data(91, 101);
			BST.addNode(newData9, comparator);
			break;
		}
		case 2:
		{
			int envalue = 0;
			char encharacter;
			std::cout << "Wpisz szukaną wartość: ";
			std::cin >> envalue;
			std::cout << "Wpisz szukany znak: ";
			std::cin >> encharacter;
			Data* enData = new Data(envalue, encharacter);

			clock_t t1 = clock();
			if (BST.returnNode(enData, comparator, even) != nullptr)
			{
				std::cout << BST.returnNode(enData, comparator,even)->data <<std::endl;
			}
			else
			{
				std::cout << "Brak takiego węzła..." << std::endl;
			}
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 3:
		{
			Data* enData = new Data(350, 43);
			Tree<Data, MyCompare, IfEven>::Node* Dnode = new Tree<Data, MyCompare, IfEven>::Node(enData);
			Dnode = BST.returnNode(enData, comparator, even);

			BST.deleteNode(Dnode);
			break;
		}
		case 4:
		{
			clock_t t1 = clock();
			BST.pre_orderTraversal(BST.root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 5:
		{
			clock_t t1 = clock();
			BST.in_orderTraversal(BST.root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 6:
		{
			clock_t t1 = clock();
			BST.deleteAll();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 7:
		{
			clock_t t1 = clock();
			BST.height = BST.HeightCheck(BST.root);
			std::cout << BST.height;
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 8:
		{
			std::cout << "Binary Search Tree" << std::endl;
			BST.displayTree(BST.root);
			break;
		}
		case 9:
			showMenu = false;
			break;
		default:
			std::cout << "Error!\n\n";
		}
	} while (showMenu);
}