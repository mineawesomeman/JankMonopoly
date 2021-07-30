/*
 * Production.h
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "Board.h"
#include "Player.h"
#include <iostream>

class Production {
public:
	Production();
	virtual ~Production();
	void prod(int,char*[]);
private:
	void landOnStreet(Player*,Space*,Player**,FILE*);
	void landOnRailroad(Player*,Space*,Player**,FILE*);
	void landOnChance(Player*,FILE*);
	void buyHouses(Player*,Board*,FILE*);
	void sellHouses(Player*,Board*,FILE*);
	void sellProperties(Player*,Board*,FILE*);
	void printPropertyList(Player*,Board*);
};

#endif /* PRODUCTION_H_ */
