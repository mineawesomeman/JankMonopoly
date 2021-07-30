/*
 * Tests.h
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#ifndef TESTS_H_
#define TESTS_H_

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool test();
private:
	bool testSpace();
	bool testBoard();
	bool testPlayer();
};

#endif /* TESTS_H_ */
