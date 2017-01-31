// DataStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "BST.h"
#include "RBT.h"
#include "HashTable.h"
#include "vector.h"

using namespace std;

template <class T>
struct hash_struct
{
	size_t operator()(const T &val) { return 0; }
};

void print_hash_table_primes();

int main()
{
	rk::vector<int> v(30,-1);
	rk::vector<int> v2(20);
	rk::vector<int> v3(v2);
	v2 = v;

	for (auto i = 0; i < 30; i++)
		v[i] = i * 10;

	bool b = false;
	for (auto i = 0; i < 30; i++)
		if (v.at(i) != i * 10)
			b = true;

	cout << b<<endl;

	cout << v2.size() << v2.empty() << v2.capacity()<<endl;

	v2.push_back(1000);
	v2.push_back(1000);
	v2.push_back(1000);
	v2.pop_back();
	cout << v2.capacity()<<endl;

	cout << v2.front() << " " << v2.back() << endl;
	v2.clear();
	v2.resize(10);
	v2.resize(30, -100);
	v2.resize(5);
	v2.shrink_to_fit();
	//v.at(100);

	rk::vector<int> v5 = { 10,20, 30, 40, 50, 60, 70 };



	v2.reserve(10000);

	cout << "hi";



	/*
	//{
	//	//, Less<string>
	//	rk::RBT<string> bst("NOT FOUND");
	//	if (bst.isEmpty())
	//		cout << "empty\n";
	//	else
	//		cout << "not empty\n";


	//	bst.insert("o");
	//	bst.insert("r");
	//	bst.insert("p");
	//	bst.insert("ro");
	//	bst.insert("n");
	//	bst.insert("m");
	//	bst.insert("no");
	//	bst.insert("nc");
	//	bst.insert("noo");
	//	bst.insert("l");
	//	bst.insert("mo");
	//	bst.insert("mm");
	//	bst.insert("ml");
	//	bst.insert("mmo");
	//	//bst.insert("");

	//	cout << endl;
	//	if (bst.isEmpty())
	//		cout << "empty\n";
	//	else
	//		cout << "not empty\n";

	//	cout << "\nfound:\n";
	//	cout << bst.find("mmo") << endl;
	//	cout << bst.find("mmoo") << endl;
	//	cout << bst.find("noo") << endl;
	//	cout << bst.find("mn") << endl;
	//	cout << bst.find("l") << endl;
	//	cout << bst.find("p") << endl;
	//	cout << bst.find("r") << endl;


	//	if (bst.find("pa") == "")
	//		cout << "\nsucess\n";


	//	cout << "max: " << bst.find_Max() << endl;

	//	cout << "\n\n hi\n";

	//	bst.erase("mmo");
	//	bst.erase("n");
	//	bst.erase("o");
	//	bst.erase("mmo");
	//	bst.erase("mmo");

	//	cout << "min: " << bst.find_Min() << endl;

	//	cout << "\n\n hi\n";

	//	bst.clear();

	//	cout << bst.find("no") << endl;

	//	bst.insert("o");
	//	bst.insert("r");
	//	bst.insert("p");
	//	bst.insert("ro");
	//	bst.insert("n");
	//	bst.insert("m");

	//	rk::RBT<string> bst2("");
	//	bst2 = bst;
	//	bst.clear();

	//	bst2.get_Not_Found_value() = "KKKKK";

	//	cout << "bst2: " << bst2.find("lklkdw") << endl;

	//	cout << "\n\n hi\n";
	//}
	//
	*/

	
	/*
	rk::HashTable<int> hash(-1, 40);

	cout << "hi";

	for (auto i = 0; i <= 10000000; i++)
		hash.insert(i);


	rk::HashTable<int> hash2;

	hash2 = hash;

	bool fail = false;
	for (auto i = 0; i <= 10000000; i++)
		if (hash2.find(i) == -1)
		{
			fail = true;
		}

	
	cout << " fail: " << fail;

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

