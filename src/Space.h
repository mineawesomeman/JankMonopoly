/*
 * Space.h
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#ifndef SPACE_H_
#define SPACE_H_

class Space {
public:
	Space(int,int,char*);
	virtual ~Space();
	void setHouseCount(int);
	void setOwner(int);
	int getSpaceNum();
	char* getName();
	int getType();
	int getOwner();
	int getHouseCount();
	void buildHouses(int num);
	void sellHouses(int num);
private:
	int type;
	int spaceNumber;
	char* name;
	int ownerNum;
	int houseCount;
};


#endif /* SPACE_H_ */
