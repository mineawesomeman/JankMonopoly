/*
 * Board.h
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Space.h"

class Board {
public:
	Board();
	virtual ~Board();
	Space* getSpace(int);
private:
	Space** spacesP;
};

#endif /* BOARD_H_ */
