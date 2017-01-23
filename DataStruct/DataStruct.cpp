// DataStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "BST.h"

using namespace std;



int main()
{
	//, Less<string>
	rk::BST<string> bst("");
	bst.insert("g");
	bst.insert("a");
	bst.insert("p");
	bst.insert("a");
	bst.insert("r");

	cout << bst.find("p");
	cout << bst.find("r");
	cout << bst.find("a");

	if(bst.find("pa") == "")
		cout << "sucess";

	cout << "\n\n hi\n";
    return 0;
}

