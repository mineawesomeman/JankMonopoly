//============================================================================
// Name        : Monopoly.cpp
// Author      : David Rosenstein
// Version     :
// Copyright   : checkersssss i forgot to change this from hw5 haha
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Production.h"
#include "Tests.h"
using namespace std;


//there is one argument and its the name of the input file
//the output file will always be output.txt
int main(int argc, char* argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	srand (time(NULL));

	Tests* t = new Tests();


	if (t->test()) {
		cout << "Tests Passes!!" << endl;
		Production* production = new Production();

		production->prod(argc, argv);
	} else {
		cout << "Tests Failed!!" << endl;
	}

	return 0;
}
