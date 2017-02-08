// DataStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "BST.h"
#include "RBT.h"
#include "HashTable.h"
#include "vector.h"
#include "Heap.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <vector>
#include <queue>

using namespace std;

template <class T>
struct hash_struct
{
	size_t operator()(const T &val) { return 0; }
};

void print_hash_table_primes();

int main()
{
	//cout << (size_t(-1) >> 1);
	struct g
	{
		bool operator ()(const int& s1, const int& s2)
		{
			return s1 > s2;
		}
	};
	rk::Heap<int, rk::vector<int>, g> h;
	rk::Heap<int, std::vector<int>, g> h2;
	cout << "empty: " << h.empty()<<endl;
	h.push(10);
	cout << "empty: " << h.empty() << endl;
	h.push(0);
	h.push(5);
	h.push(15);
	h.push(10);
	h.push(11);
	h.push(0);
	h.push(7);
	h.push(9);
	h.push(100);
	h.push(56);
	h.push(110);
	
	cout << "top: "<< h.top() << endl;
	cout << "size: "<<h.size() << endl;

	h.pop();
	h.pop();
	h.pop();
	h.pop();

	h.pop();
	h.pop();
	srand(time(NULL));
	
	h2.push(2);
	h2.pop();
	try {
		h2.pop();
	}
	catch (...)
	{ }
	/*

	rk::vector<int> v5 = { 10,20, 30, 40, 50, 60, 70 };
	for (auto x : v5)
	{
		cout << x << " ";
	}
	cout << endl;
	
	v5.insert(v5.begin() + 1, 100);
	v5.insert(v5.begin() + 3, 100);
	v5.insert(v5.end() , 100);
	for (auto x : v5)
	{
		cout << x << " ";
	}

	v5.erase(v5.begin());
	v5.erase(v5.begin() + 1);
	v5.erase(v5.end() - 1);
	v5.erase(v5.end() - 3);
	cout << endl<< "j";
	for (auto x : v5)
	{
		cout << x << " ";
	}

	cout << "hi";
	*/
	
	/*rk::vector<int> v5 = { 10,20, 30, 40, 50, 60, 70 };

	rk::vector_Iterator<int> itr= v5.begin();

	


	for (; itr != v5.end(); )
	{
		cout << *itr << " ";
		*itr = *itr * 10;
		itr = itr + 1;
	}
	cout << "\n\n";
	v5.push_back(-1);
	v5.push_back(-2);

	for (itr = v5.end(); itr != v5.begin(); )
	{
		itr--;
		cout << *itr << " ";
		*/
	

	
	/*
	rk::vector<int> v;
	for (auto i = 0; i < 10; i++)
	{
		v.push_back(rand() % 100);
	}

	for (rk::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
	{
		cout << " " << *itr;
	}
	cout << endl ;
	cout << v.end() - v.begin();

	//rk::vector<int>::iterator itr = v.cbegin();

	sort(v.begin(), v.end());

	cout << endl;
	cout << endl;
	for (rk::vector<int>::const_iterator itr = v.cbegin(); itr != v.cend(); itr++)
	{
		cout << " " << *itr;
	}

	struct A {
		int a;
		int b;

	};

	rk::vector<A> vA;
	A s = { 10,10 };
	vA.push_back(s);
	cout << s.a<<" ";
	auto itr2 = vA.begin();
	itr2->a = 1000;

	cout << (*itr2).a;
	//cout << "\n\n sort:\n" << is_sorted(v.rbegin(), v.rend());

	*/

	//
	//{
	//	//, Less<string>
	//	rk::BST<string> bst("NOT FROUND");
	//	if (bst.empty())
	//		cout << "empty\n";
	//	else
	//		cout << "not empty\n";


	//		bst.insert("o");
	//		bst.insert("n");
	//		bst.insert("m");
	//		bst.insert("r");
	//		bst.insert("m");
	//		bst.insert("no");
	//		bst.insert("p");
	//		bst.insert("ro");
	//		bst.insert("l");
	//		bst.insert("nc");
	//		bst.insert("noo");
	//		bst.insert("mo");
	//		bst.insert("mm");
	//		bst.insert("ml");
	//		bst.insert("mmo");

	//	rk::BST<string>::const_iterator itr;
	//	for ( itr = bst.begin(); itr != bst.end(); ++itr)
	//	{
	//		cout << *itr << " ";
	//	}
	//	cout << endl;

	//	rk::BST<string>::const_reverse_iterator itr2;
	//	//itr = itr2;
	//	for (itr2 = bst.rbegin(); itr2 != bst.rend(); ++itr2)
	//	{
	//		cout << *itr2 << " ";
	//	}

	//	cout << endl;

	//	for (itr2 = bst.rbegin(); itr2 != bst.rend(); bst.erase(itr2))
	//	{
	//		cout << *itr2 << " ";
	//	}
	//	cout << endl << bst.empty();


	//	cout << "\n\n hi\n";
	//}
	//
	

	
	/*
	rk::HashTable<int> hash(-1);

	cout << "hi\n";

	for (int i = 1; i < 20; i++)
		hash.insert(i);

	for (auto itr = hash.cbegin() ; itr != hash.cend(); itr++)
		cout << *itr << " ";

	cout << endl;

	for (auto itr = hash.cbegin(); itr != hash.cend(); hash.erase(itr))
		cout << *itr << " ";

	cout << "emp: " << hash.empty();
	*/
/*
	rk::HashTable<int> hash2;

	hash2 = hash;

	bool fail = false;
	for (auto i = 0; i <= 10000000; i++)
		if (hash2.find(i) == -1)
		{
			fail = true;
		}

	/*int i = 0;
	for (rk::HashTable<int>::const_iterator itr = hash.cbegin(); itr != hash.cend(); ++itr)
	{
		cout << *itr << " "; 
		i++;
	}
	cout << endl;
	for (auto itr = hash.cbegin(); itr != hash.cend(); itr++)
	{
		cout << *itr << " ";
		i++;

	}
	cout << endl << is_sorted(hash.cbegin(), hash.cend());
	cout << "\n n: " << i;

	cout << "\nend";
	
	*/

	/*
	
	cout << hash.empty();

	cout << "\n cont size: " << hash.table_size();

	hash.insert(0);
	hash.insert(1);
	hash.insert(2);
	hash.insert(3);
	hash.insert(4);
	hash.insert(5);
	hash.insert(6);
	hash.insert(7);

	cout << hash.empty();

	cout << "\nx: " << hash.find(3);
	cout << "\nx: " << hash.find(0);
	cout << "\nx: " << hash.find(7);
	cout << "\nx: " << hash.find(-10);
	cout << "\nx: " << hash.find(10);
	cout << endl;

	hash.erase(5);
	hash.erase(4);

	cout << "\nnum: " << hash.size();

	hash.insert(6);

	cout << "\nx: " << hash.find(6);

	cout << "\n\nhi";


	hash.insert(8);
	hash.insert(9);
	hash.insert(10);

	cout << "\n\nhi";

	hash.clear();

	cout << "\nnum: " << hash.size();

	cout << "\n\nhi";
	

	print_hash_table_primes();

	*/

    return 0;
}

