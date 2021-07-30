/*
 * Production.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: daraw
 */

#include "Production.h"
#include "Definitions.h"
#include <iostream>

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

void Production::prod(int argc, char* argv[]) {
	printf("Starting Production!\n"); fflush(stdout);

	if (argc <= 1) {
		printf("No file name found, uh oh!\n"); fflush(stdout);
		return;
	}

	char* fileName;
	printf("Found File %s\n",argv[1]);
	fileName = argv[1];

	FILE* f;
	FILE* output = fopen("output.txt","w");

	printf("Would you like to read the file and continue that game (1), or start a new game (2)?\n"); fflush(stdout);

	Player** playersP;
	Board* board = new Board();
	int choice, playerCount;
	bool running = true;

	scanf("%i",&choice);

	if (choice == 1) {
		f = fopen(fileName, "r");
		fscanf(f,"%i",&playerCount);

		playersP = (Player**)malloc(sizeof(Player*) * playerCount);

		for (int i = 0; i < playerCount; i ++) {
			int money, position;
			bool* properties = (bool*) malloc(sizeof(bool) * 32);
			fscanf(f,"%i %i",&money,&position);

			for (int j = 0; j < 32; j ++) {
				int res;
				fscanf(f,"%i",&res);
				if (res == 1) {
					*(properties+j) = true;
					board->getSpace(j)->setOwner(i);
				} else {
					*(properties+j) = false;
				}
			}
			*(playersP+i) = new Player (i,properties,position,money);

		}

		for (int i = 0; i < 32; i ++) {
			int house;
			fscanf(f,"%i",&house);
			board->getSpace(i)->setHouseCount(house);
		}
		fclose(f);
		fprintf(output,"Started Game From File\n");

	} else {
		printf("How many players do you have?\n"); fflush(stdout);
		scanf("%i",&playerCount);

		playersP = (Player**)malloc(sizeof(Player*) * playerCount);
		for (int i = 0; i < playerCount; i++) {
			*(playersP+i) = new Player(i);
		}

		fprintf(output,"Started Fresh Game\n");
	}

	while (running) {

		for (int currentPlayerNum = 0; currentPlayerNum < playerCount && running; currentPlayerNum++) {
			printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			fprintf(output,"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			if ((*(playersP+currentPlayerNum))->getMoney() >= 0) {

				printf("Player %i's turn!!!\n",currentPlayerNum);
				printf("Rolling the Dice!\n"); fflush(stdout);

				Player* currentPlayer = *(playersP + currentPlayerNum);
				int roll = rand() % 8 + 1;

				printf("You rolled a %i!\n",roll); fflush(stdout);
				fprintf(output,"Player %i rolled a %i\n",currentPlayerNum,roll);

				currentPlayer->move(roll);

				int spaceNum = currentPlayer->getPosition();
				Space* space = board->getSpace(spaceNum);
				int type = space->getType();

				printf("You landed on %s (Space number %i)\n",space->getName(),spaceNum); fflush(stdout);
				fprintf(output,"Player %i landed on %s (space number %i)\n",currentPlayerNum,space->getName(),spaceNum);

				switch (type) {
				case STREET:
					landOnStreet(currentPlayer,space,playersP,output);
					break;
				case RAILROAD:
					landOnRailroad(currentPlayer,space,playersP,output);
					break;
				case CHANCE:
					landOnChance(currentPlayer,output);
					break;
				default:
					printf("You landed on %s, how boring!\n",space->getName()); fflush(stdout);
				}
				fflush(stdout);

				bool endTurnLoop = true;

				while (endTurnLoop) {
					printf("You currently have $%i! What would you like to do?\n",currentPlayer->getMoney());
					printf("Note: if you end your turn with less than $0, then you will be bankrupted and will lose!\n");
					printf("1) Buy houses\n");
					printf("2) Sell Houses\n");
					printf("3) Sell Properties\n");
					printf("4) See Which Properties You Own!\n");
					printf("0) End Your Turn\n");
					printf("(Type the number of your choice!)\n");
					fflush(stdout);
					int c;

					scanf("%i",&c);

					switch (c) {
					case 1:
						buyHouses(currentPlayer,board,output);
						break;
					case 2:
						sellHouses(currentPlayer,board,output);
						break;
					case 3:
						sellProperties(currentPlayer,board,output);
						break;
					case 4:
						printPropertyList(currentPlayer,board);
						break;
					default:
						endTurnLoop = false;
					}

				}

				if (currentPlayer->getMoney() < 0) {

					for (int i = 0; i < 32; i ++) {
						if (currentPlayer->hasProperty(i)) {
							currentPlayer->sellProperty(board->getSpace(i));
							board->getSpace(i)->setHouseCount(0);
						}
					}

					currentPlayer->setMoney(-1);

					printf("Player %i is bankrupt!!!",currentPlayerNum); fflush(stdout);
					fprintf(output,"Player %i went Bankrupt!\n",currentPlayerNum);
				} else {
					fprintf(output,"Turn Ended! Player %i has $%i\n",currentPlayerNum,currentPlayer->getMoney());
				}

				printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
		}

		if (running) {
			int what, how;
			printf("Another Round is Over! Would you like to quit or play another round? (1 to quit, 2 for another round)\n"); fflush(stdout);
			scanf("%i",&what);

			if (what == 1) {
				running = false;
				printf("Would you like to save the game? (1 for yes, 2 for no)\n"); fflush(stdout);
				scanf("%i",&how);
				if (how == 1) {
					f = fopen(fileName,"w");
					fprintf(f,"%i\n",playerCount);
					for (int i = 0; i < playerCount; i ++) {
						fprintf(f,"%i %i ",(*(playersP+i))->getMoney(),(*(playersP+i))->getPosition());
						for (int j = 0; j < 32; j ++) {
							if ((*(playersP+i))->hasProperty(j)) {
								fprintf(f,"1 ");
							} else {
								fprintf(f,"0 ");
							}
						}
						fprintf(f,"\n");
					}

					for (int i = 0; i < 32; i ++) {
						Space* sp = board->getSpace(i);

						fprintf(f,"%i ",sp->getHouseCount());
					}

					fclose(f);

				}
			}
		}

	}


}

void Production::landOnStreet(Player* p, Space* s,Player** pP,FILE* f) {
	int owner = s->getOwner();

	if (owner == -1) {
		int choice;
		printf("Would you like to buy %s? (You currently have %i dollars)\n",s->getName(),p->getMoney());
		printf("(Type 1 for yes, type 2 for no)\n"); fflush(stdout);
		scanf("%i",&choice);

		if (choice == 1) {
			p->buyProperty(s);
			fprintf(f,"Player %i bought %s (Space number %i)\n",p->getPlayerNum(),s->getName(),s->getSpaceNum());
		}
	} else if (owner == p->getPlayerNum()) {
		printf("You already own %s! Enjoy your stay!\n",s->getName());
	} else {
		int amountOwed;

		if (s->getHouseCount() == 4) amountOwed = 60;
		else amountOwed = 10 + (10 * s->getHouseCount());

		printf("Player %i owns this property! You owe them %i dollars!\n",s->getOwner(),amountOwed);
		fprintf(f,"Player %i paid Player %i $%i for landing on %s!\n",p->getPlayerNum(),s->getOwner(),amountOwed,s->getName());
		p->loseMoney(amountOwed);
		(*(pP+s->getOwner()))->gainMoney(amountOwed);
	}
}

void Production::landOnRailroad(Player* p, Space* s,Player** pP,FILE* f) {
	int owner = s->getOwner();

	if (owner == -1) {
		int choice;
		printf("Would you like to buy %s? (You currently have $%i)\n",s->getName(),p->getMoney());
		printf("(Type 1 for yes, type 2 for no)\n"); fflush(stdout);
		scanf("%i",&choice);

		if (choice == 1) {
			p->buyProperty(s);
			fprintf(f,"Player %i bought %s (Space number %i)\n",p->getPlayerNum(),s->getName(),s->getSpaceNum());
		}
	} else if (owner == p->getPlayerNum()) {
		printf("You already own %s! Enjoy your stay!\n",s->getName());
	} else {
		int amountOwed, railRoadNum;
		//5 13 21 29
		Player* p2 = *(pP+s->getOwner());

		for (int i = 5; i <= 29; i += 8) {
			if (p2->hasProperty(i)) railRoadNum++;
		}

		amountOwed = 25 * railRoadNum;

		printf("Player %i owns this property! You owe them %i dollars!\n",s->getOwner(),amountOwed);
		fprintf(f,"Player %i paid Player %i $%i for landing on %s!\n",p->getPlayerNum(),s->getOwner(),amountOwed,s->getName());
		p->loseMoney(amountOwed);
		(*(pP+s->getOwner()))->gainMoney(amountOwed);
	}
}

void Production::landOnChance(Player* p,FILE* f) {
	int chance1 = rand() % 2;
	int chance2 = (rand() % 6) + 1;
	printf("Take a chance!\n");
	if (chance1 == 0) {
		printf("You will pay $%i! That sucks!\n",chance2*10);
		fprintf(f,"Player %i took a chance and lost $%i!\n",p->getPlayerNum(),chance2*10);
		p->loseMoney(chance2*10);
	} else {
		printf("You got $%i! Wooooo!\n",chance2*10);
		fprintf(f,"Player %i took a chance and won $%i!\n",p->getPlayerNum(),chance2*10);
		p->gainMoney(chance2*10);
	}
}

void Production::buyHouses(Player* p,Board* b,FILE* f) {
	int propertyNum, houseNum;
	printf("Here are the properties you own:\n");
	printPropertyList(p,b);
	printf("Which property would you like to build houses on? (type the number of the property)\n"); fflush(stdout);
	scanf("%i",&propertyNum);

	if (!p->hasProperty(propertyNum)) {
		printf("You don't own that property! You can only build houses on properties you own!\n");
		return;
	} else if (b->getSpace(propertyNum)->getType() != STREET) {
		printf("You can only build houses on streets!\n");
		return;
	} else if (b->getSpace(propertyNum)->getHouseCount() == 4) {
		printf("You already build the max number of houses here!\n");
		return;
	}

	Space* sp = b->getSpace(propertyNum);

	printf("%s currently has %i houses. How many more would you like to build? (there is a max of 4, they cost $30 each)\n",sp->getName(),sp->getHouseCount());
	fflush(stdout);
	scanf("%i",&houseNum);

	if (sp->getHouseCount() + houseNum > 4) {
		printf("Thats too many houses!\n");
		return;
	} else if (houseNum < 0) {
		printf("You can't build negative numbers of houses...\n");
		return;
	}

	fprintf(f,"Player %i built %i houses on %s (space number %i)\n",p->getPlayerNum(),houseNum,sp->getName(),sp->getSpaceNum());
	sp->buildHouses(houseNum);
	p->loseMoney(houseNum*30);

}

void Production::sellHouses(Player* p,Board* b,FILE* f) {
	int propertyNum, houseNum;
	printf("Here are the properties you own:\n");
	printPropertyList(p,b);
	printf("Which property would you like to sell houses on? (type the number of the property)\n"); fflush(stdout);
	scanf("%i",&propertyNum);

	if (!p->hasProperty(propertyNum)) {
		printf("You don't own that property! You can only sell houses on properties you own!\n");
		return;
	} else if (b->getSpace(propertyNum)->getType() != STREET) {
		printf("You can only sell houses on streets!\n");
		return;
	} else if (b->getSpace(propertyNum)->getHouseCount() == 0) {
		printf("There are no houses here to sell!\n");
		return;
	}

	Space* sp = b->getSpace(propertyNum);

	printf("%s currently has %i houses. How many more would you like to sell? (there is a max of 4, they sell for $15 each)\n",sp->getName(),sp->getHouseCount());
	fflush(stdout);
	scanf("%i",&houseNum);

	if (sp->getHouseCount() + houseNum < 0) {
		printf("Thats too many houses!\n");
		return;
	} else if (houseNum < 0) {
		printf("You can't sell negative numbers of houses...\n");
		return;
	}

	fprintf(f,"Player %i sold %i houses on %s (space number %i)\n",p->getPlayerNum(),houseNum,sp->getName(),sp->getSpaceNum());
	sp->sellHouses(houseNum);
	p->gainMoney(houseNum*15);
}

void Production::sellProperties(Player* p,Board* b,FILE* f) {
	int propertyNum;
	printf("Here are the properties you own:\n");
	printPropertyList(p,b);
	printf("Which property would you like to sell? (type the number of the property)\n"); fflush(stdout);
	scanf("%i",&propertyNum);

	if (!p->hasProperty(propertyNum)) {
		printf("You don't own that property! You can only sell properties you own!\n");
		return;
	}

	Space* sp = b->getSpace(propertyNum);

	fprintf(f,"Player %i sold their property %s (space num %i)!\n",p->getPlayerNum(),sp->getName(),sp->getSpaceNum());
	p->sellProperty(sp);
}

void Production::printPropertyList(Player* p,Board* bd) {
	for (int i = 0; i < 32; i ++) {
		if (p->hasProperty(i)) {
			printf("You own propery number %i: %s\n",i,bd->getSpace(i)->getName());
		}
	}
	fflush(stdout);
}
