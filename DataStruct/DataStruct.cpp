// DataStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "BST.h"
#include "RBT.h"

using namespace std;



int main()
{
	{
		//, Less<string>
		rk::RBT<string> bst("NOT FOUND");
		if (bst.isEmpty())
			cout << "empty\n";
		else
			cout << "not empty\n";


		bst.insert("o");
		bst.insert("r");
		bst.insert("p");
		bst.insert("ro");
		bst.insert("n");
		bst.insert("m");
		bst.insert("no");
		bst.insert("nc");
		bst.insert("noo");
		bst.insert("l");
		bst.insert("mo");
		bst.insert("mm");
		bst.insert("ml");
		bst.insert("mmo");
		//bst.insert("");

		cout << endl;
		if (bst.isEmpty())
			cout << "empty\n";
		else
			cout << "not empty\n";

		cout << "\nfound:\n";
		cout << bst.find("mmo") << endl;
		cout << bst.find("mmoo") << endl;
		cout << bst.find("noo") << endl;
		cout << bst.find("mn") << endl;
		cout << bst.find("l") << endl;
		cout << bst.find("p") << endl;
		cout << bst.find("r") << endl;


		if (bst.find("pa") == "")
			cout << "\nsucess\n";


		cout << "max: " << bst.find_Max() << endl;

		cout << "\n\n hi\n";

		bst.erase("mmo");
		bst.erase("n");
		bst.erase("o");
		bst.erase("mmo");
		bst.erase("mmo");

		cout << "min: " << bst.find_Min() << endl;

		cout << "\n\n hi\n";

		bst.clear();

		cout << bst.find("no") << endl;

		bst.insert("o");
		bst.insert("r");
		bst.insert("p");
		bst.insert("ro");
		bst.insert("n");
		bst.insert("m");

		rk::RBT<string> bst2("");
		bst2 = bst;
		bst.clear();

		bst2.get_Not_Found_value() = "KKKKK";

		cout << "bst2: " << bst2.find("lklkdw") << endl;

		cout << "\n\n hi\n";
	}
	

    return 0;
}

