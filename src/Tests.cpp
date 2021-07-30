/*
 * Tests.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#include "Tests.h"
#include "Player.h"
#include "Board.h"
#include "Production.h"
#include "Definitions.h"
#include <iostream>

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::test() {
	printf("Testing Space Functions\n"); fflush(stdout);
	bool ok1 = testSpace();
	printf("Testing Board Functions\n"); fflush(stdout);
	bool ok2 = testBoard();
	printf("Testing Player Functions\n"); fflush(stdout);
	bool ok3 = testPlayer();
	fflush(stdout);

	return ok1 && ok2 && ok3;
}

bool Tests::testSpace() {
	Space* sp = new Space(STREET,-1,(char*)"test");

	if (sp->getHouseCount() != 0 || sp->getOwner() != -1) return false;

	sp->setOwner(0);
	sp->buildHouses(3);

	if (sp->getHouseCount() != 3 || sp->getOwner() != 0) return false;

	sp->sellHouses(2);

	if (sp->getHouseCount() != 1 || sp->getOwner() != 0) return false;

	printf("testSpace passed\n");
	return true;
}

bool Tests::testBoard() {
	Board* bd = new Board();
	Space* sp = bd->getSpace(0);

	if (sp->getType() != GO || sp->getSpaceNum() != 0 || sp->getHouseCount() != 0 || sp->getOwner() != -1) return false;

	printf("testBoard passed\n");
	return true;
}

bool Tests::testPlayer() {
	Player* p = new Player (-1);
	Space* sp = new Space (STREET,6,(char*)"test");
	Space* sp2 = new Space (RAILROAD,5,(char*)"test choo choo");

	if (p->hasProperty(6) || p->hasProperty(5)) return false;

	p->buyProperty(sp);
	p->buyProperty(sp2);

	if (!p->hasProperty(6) || !p->hasProperty(5)) return false;
	if (p->getMoney() != 800-120) return false;
	if (p->getPosition() != 0) return false;

	p->move(6);
	p->gainMoney(69);

	if (p->getPosition() != 6) return false;
	if (p->getMoney() != 800-120+69) return false;

	p->loseMoney(420);

	if (p->getMoney() != 800-120+69-420) return false;

	p->sellProperty(sp2);

	if (p->getMoney() != 800-120+69-420+50) return false;
	if (p->hasProperty(5)) return false;

	printf("testPlayer passed\n");
	return true;
}
