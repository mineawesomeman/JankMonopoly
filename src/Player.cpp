/*
 * Player.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#include "Player.h"
#include "Definitions.h"
#include <iostream>

Player::Player(int n) {
	// TODO Auto-generated constructor stub
	playerNum = n;
	properties = (bool*)malloc(sizeof(bool) * 32);
	for (int i = 0; i < 32; i ++) {
		*(properties+i) = false;
	}
	position = 0;
	money = 800;
}

Player::Player(int n, bool* p, int pos, int mon) {
	// TODO Auto-generated constructor stub
	playerNum = n;
	properties = p;
	position = pos;
	money = mon;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
	delete properties;
}

void Player::setPosition(int pos) {
	position = pos;
}

int Player::getPosition() {return position;}

void Player::buyProperty(Space* sp) {
	int pNum = sp->getSpaceNum();
	*(properties+pNum) = true;

	if (sp->getType() == RAILROAD) {
		money -= 100;
	} else if (pNum <= 7) {
		money -= 20;
	} else if (pNum <= 15) {
		money -= 40;
	} else if (pNum <= 23) {
		money -= 50;
	} else {
		money -= 70;
	}

	sp->setOwner(playerNum);
	printf("Sucessfully bought %s\n",sp->getName());
}

void Player::sellProperty(Space* sp) {
	int pNum = sp->getSpaceNum();
	properties[pNum] = false;
	if (sp->getType() == RAILROAD) {
		money += 50;
	} else if (pNum <= 7) {
		money += 10;
	} else if (pNum <= 15) {
		money += 20;
	} else if (pNum <= 23) {
		money += 25;
	} else {
		money += 35;
	}

	sp->setOwner(-1);
	printf("Sucessfully sold %s\n",sp->getName());
}

void Player::move(int spaces) {
	position += spaces;
	if (position > 31) {
		position -= 32;
		money += 200;
		printf("You passed GO! You got $200!\n"); fflush(stdout);
	}
}

int Player::getPlayerNum() {return playerNum;}
void Player::gainMoney(int mon) {money += mon;}
void Player::loseMoney(int mon) {money -= mon;}
bool Player::hasProperty(int num) {return *(properties+num);}
int Player::getMoney() {return money;}
void Player::setMoney(int mon) {money = mon;}
