// DataStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "BST.h"
#include "RBT.h"
#include "HashTable.h"

using namespace std;

template <class T>
struct hash_struct
{
	size_t operator()(const T &val) { return 0; }
};

void print_hash_table_primes();

int main()
{
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
	rk::HashTable<int, hash_struct<int>> hash(-1, 1000);

	cout << "hi";

	for (auto i = 0; i <= 10000; i++)
		hash.insert(i);


	rk::HashTable<int, hash_struct<int>> hash2;

	hash2 = hash;

	bool fail = false;
	for (auto i = 0; i <= 10000; i++)
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
	*/

	print_hash_table_primes();

    return 0;
}

