/*
 * Board.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */
#include "Board.h"
#include <iostream>
#include "Definitions.h"


Board::Board() {
	// TODO Auto-generated constructor stub
	spacesP = (Space**)malloc(sizeof(Space*) * 32);

	*(spacesP+0) = new Space(GO,0,(char*)"GO");
	*(spacesP+1) = new Space(STREET,1,(char*)"Irving Ave");
	*(spacesP+2) = new Space(CHANCE,2,(char*)"Chance");
	*(spacesP+3) = new Space(STREET,3,(char*)"Dover Street");
	*(spacesP+4) = new Space(STREET,4,(char*)"Orientle Ave");
	*(spacesP+5) = new Space(RAILROAD,5,(char*)"Dallas Station");
	*(spacesP+6) = new Space(STREET,6,(char*)"Liverpool Rd");
	*(spacesP+7) = new Space(STREET,7,(char*)"Irdell Ave");
	*(spacesP+8) = new Space(FREE,8,(char*)"Free");
	*(spacesP+9) = new Space(STREET,9,(char*)"Kiley Court");
	*(spacesP+10) = new Space(CHANCE,10,(char*)"Chance");
	*(spacesP+11) = new Space(STREET,11,(char*)"Enrique Drive");
	*(spacesP+12) = new Space(STREET,12,(char*)"Mangrove Lane");
	*(spacesP+13) = new Space(RAILROAD,13,(char*)"Illinois Station");
	*(spacesP+14) = new Space(STREET,14,(char*)"Annadale Terrace");
	*(spacesP+15) = new Space(STREET,15,(char*)"Sandhill Court");
	*(spacesP+16) = new Space(FREE,16,(char*)"Free");
	*(spacesP+17) = new Space(STREET,17,(char*)"Scotch Pine Way");
	*(spacesP+18) = new Space(CHANCE,18,(char*)"Chance");
	*(spacesP+19) = new Space(STREET,19,(char*)"Iron Wood Lane");
	*(spacesP+20) = new Space(STREET,20,(char*)"Violet Court");
	*(spacesP+21) = new Space(RAILROAD,21,(char*)"California Station");
	*(spacesP+22) = new Space(STREET,22,(char*)"Evans Way");
	*(spacesP+23) = new Space(STREET,23,(char*)"Bosie Run");
	*(spacesP+24) = new Space(FREE,24,(char*)"Free");
	*(spacesP+25) = new Space(STREET,25,(char*)"O'Brien Place");
	*(spacesP+26) = new Space(CHANCE,26,(char*)"Chance");
	*(spacesP+27) = new Space(STREET,27,(char*)"Old Camp Road");
	*(spacesP+28) = new Space(STREET,28,(char*)"Baker Way");
	*(spacesP+29) = new Space(RAILROAD,29,(char*)"Kentucky Station");
	*(spacesP+30) = new Space(STREET,30,(char*)"Albany Avenue");
	*(spacesP+31) = new Space(STREET,31,(char*)"South Shore Lane");


}

Board::~Board() {
	// TODO Auto-generated destructor stub
	for (int i = 0; i < 32; i ++) {
		delete *(spacesP+i);
	}
	delete spacesP;
}

Space* Board::getSpace(int n) {
	return (*(spacesP+n));
}
