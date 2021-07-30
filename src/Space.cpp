/*
 * Space.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#include "Space.h"

Space::Space(int t, int n, char* na) {
	// TODO Auto-generated constructor stub
	type = t;
	spaceNumber = n;
	name = na;
	ownerNum = -1;
	houseCount = 0;
}

Space::~Space() {
	// TODO Auto-generated destructor stub
	delete name;
}

void Space::setHouseCount(int n) {
	houseCount = n;
}
void Space::setOwner(int n) {
	ownerNum = n;
}
int Space::getSpaceNum() {return spaceNumber;}
char* Space::getName() {return name;}
int Space::getType() {return type;}
int Space::getOwner() {return ownerNum;}
int Space::getHouseCount() {return houseCount;}
void Space::buildHouses(int num) {houseCount += num;}
void Space::sellHouses(int num) {houseCount -= num;}
