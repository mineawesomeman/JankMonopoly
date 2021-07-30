/*
 * Player.h
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Space.h"

class Player {
public:
	Player(int);
	Player(int,bool[32],int,int);
	virtual ~Player();
	void setPosition(int);
	int getPosition();
	void buyProperty(Space*);
	void sellProperty(Space*);
	void move(int);
	int getPlayerNum();
	void loseMoney(int);
	void gainMoney(int);
	bool hasProperty(int);
	int getMoney();
	void setMoney(int);
private:
	int playerNum;
	bool* properties;
	int position;
	int money;
};

#endif /* PLAYER_H_ */
