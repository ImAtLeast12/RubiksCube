#include <iostream>
#include <string>
#include <algorithm>

#define NUM_FACES 6
#define NUM_STICKERS 9

char _CHAR[6][2] = {"G","R","Y","O","B","W"}; 
char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};
enum FACES{LEFT,BACK,UP,FRONT,RIGHT,DOWN};
enum COLORS{GREEN, ORANGE, WHITE, RED, BLUE, YELLOW};

int ATMV[6][17] = {{UP,BACK,DOWN,FRONT,	0,3,6,8,5,2,0,3,6,0,3,6,true},
						{UP,RIGHT,DOWN,LEFT,	0,1,2,2,5,8,6,7,8,0,3,6,false},
						{LEFT,FRONT,RIGHT,BACK,	0,1,2,0,1,2,0,1,2,0,1,2,false},
						{LEFT,DOWN,RIGHT,UP,	2,5,8,0,1,2,6,3,0,8,7,6,false},
						{UP,FRONT,DOWN,BACK,	2,5,8,2,5,8,2,5,8,6,3,0,true},
						{LEFT,BACK,RIGHT,FRONT,	6,7,8,6,7,8,6,7,8,6,7,8,false}}; //THIS IS WHERE THE MAGIC HAPPEND

int CUBE [NUM_FACES][NUM_STICKERS];

char validChar[3*6][3] = {"L","Li","L2","B","Bi","B2","U","Ui","U2","F","Fi","F2","R","Ri","R2","D","Di","D2"};


//METHODS
void initilize();		//INITILIZES THE CUBE
void print(); 			//PRINTS THE CUBE
void move(int SIDE);	//DOES A MOVE CLOCKWISE
void move2(int SIDE);	//DOES A MOVE TWICE
void moveI(int SIDE);	//DOES A MOVE COUNTER CLOCKWISE
void comands(std::string str); 
std::string replaceText(std::string str);


int main(){
	//int CUBE [NUM_FACES][NUM_STICKERS];  //MY GOAL IS TO HAVE THIS BE AS FLEXIBLE AS POSSIBLE
	initilize();
	comands("L2 D' R2 D R' B U F' L' F' R D' L F2 U' F' R' F2 R2 F L F2 D2 B L2'");
	
	return 0;
}



char strAlphas[12][3] = {"Li","L2","Bi","B2","Ui","U2","Fi","F2","Ri","R2","Di","D2"};
char strBetas[6][2] = {"L","B","U","F","D"};



void comands(std::string str){ 

	str = replaceText(str);

	std::cout<<"ORIGINAL TEXT:\t";//<<std::endl;
	std::cout<<str<<std::endl;

	int strLen = 0;
	while(strLen<=str.length()-1){
		bool isValidChar = false;
		for (int i = 0; i < 3*6; i++)
			if(str.substr(strLen,2) == validChar[i]){ //This looks for single characters
				isValidChar = true;
				//std::cout<<str.substr(strLen,2)<<std::endl;
				strLen++;
				std::string strAlpha = str.substr(strLen,2);

				for (int i = 0; i<6*2; i++){
					if(i%2 == true){
						if(strAlpha==strAlphas[i]){
							move2(i);
						}
					}
				 	else if (i%2 == false){
						if(strAlpha==strAlphas[i]){
							moveI(i);
						}
					}
				}//This is what I want to work on*/

				if(strAlpha=="L2")
					move2(LEFT);			
				else if(strAlpha=="B2")
					move2(BACK);
				else if(strAlpha=="U2")
					move2(UP);
				else if(strAlpha=="F2")
					move2(FRONT);
				else if(strAlpha=="R2")
					move2(RIGHT);
				else if(strAlpha=="D2")
					move2(DOWN);
				else if(strAlpha=="Li")
					moveI(LEFT);			
				else if(strAlpha=="Bi")
					moveI(BACK);
				else if(strAlpha=="Ui")
					moveI(UP);
				else if(strAlpha=="Fi")
					moveI(FRONT);
				else if(strAlpha=="Ri")
					moveI(RIGHT);
				else if(strAlpha=="Di")
					moveI(DOWN);
				else{
					std::cout<<"FAILA"<<std::endl;
				}
			}
		if(isValidChar == false){ //This looks for double characters
			std::string strBeta = str.substr(strLen,1);
			//std::cout<<str.substr(strLen,1)<<std::endl;

			if(strBeta=="L")
				move(LEFT);			
			else if(strBeta=="B")
				move(BACK);
			else if(strBeta=="U")
				move(UP);
			else if(strBeta=="F")
				move(FRONT);
			else if(strBeta=="R")
				move(RIGHT);
			else if(strBeta=="D")
				move(DOWN);
			else{
				std::cout<<"FAILB"<<std::endl;
			}

		}
			//std::string x = str.substr(strLen,1);
			//std::cout<<x<<"\tXXX"<<std::endl;

		strLen++;
	}


	//OK so now I need to do a switch statemnt to see what the letters where
}

std::string replaceText(std::string str){
	str.erase(remove(str.begin(),str.end(),' '),str.end());
	std::replace( str.begin(), str.end(), '\'', 'i');
	return str;
}//This gets rid of spaces and replaces ' with i (this stands of prime)



void moveI(int SIDE){
	move(SIDE);
 	move(SIDE);
 	move(SIDE);
}

void move2(int SIDE){
 	move(SIDE);
 	move(SIDE);
 }

void move(int SIDE){
	std::cout<<FACE_NAME[SIDE]<<std::endl;
	int temp = CUBE[ATMV[SIDE][0]][ATMV[SIDE][4]];
	int temp0 = CUBE[ATMV[SIDE][0]][ATMV[SIDE][5]];
	int temp1 = CUBE[ATMV[SIDE][0]][ATMV[SIDE][6]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][4]] = CUBE[ATMV[SIDE][1]][ATMV[SIDE][7]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][5]] = CUBE[ATMV[SIDE][1]][ATMV[SIDE][8]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][6]] = CUBE[ATMV[SIDE][1]][ATMV[SIDE][9]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][7]] = CUBE[ATMV[SIDE][2]][ATMV[SIDE][10]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][8]] = CUBE[ATMV[SIDE][2]][ATMV[SIDE][11]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][9]] = CUBE[ATMV[SIDE][2]][ATMV[SIDE][12]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][10]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][13]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][11]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][14]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][12]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][15]];

	if (ATMV[SIDE][16]){//I need to add this because LEFT and RIGHT are not congruent
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][13]] = temp;
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][14]] = temp0;
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][15]] = temp1;
	}
	else{
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][13]] = temp1;
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][14]] = temp0;
		CUBE[ATMV[SIDE][3]][ATMV[SIDE][15]] = temp;	
	}

	temp = CUBE[SIDE][0]; //This rotates the side it's self
	CUBE[SIDE][0] = CUBE[SIDE][6];
	CUBE[SIDE][6] = CUBE[SIDE][8];
	CUBE[SIDE][8] = CUBE[SIDE][2];
	CUBE[SIDE][2] = temp;
	temp = CUBE[SIDE][1];
	CUBE[SIDE][1] = CUBE[SIDE][3];
	CUBE[SIDE][3] = CUBE[SIDE][7];
	CUBE[SIDE][7] = CUBE[SIDE][5];
	CUBE[SIDE][5] = temp;
	print();
	std::cout<<std::endl;
}

void print(){


		std::cout<<"\t"<<_CHAR[CUBE[UP][0]] << _CHAR[CUBE[UP][1]] << _CHAR[CUBE[UP][2]]<<std::endl;
		std::cout<<"\t"<<_CHAR[CUBE[UP][3]] << _CHAR[CUBE[UP][4]] << _CHAR[CUBE[UP][5]]<<std::endl;
		std::cout<<"\t"<<_CHAR[CUBE[UP][6]] << _CHAR[CUBE[UP][7]] << _CHAR[CUBE[UP][8]]<<std::endl<<std::endl;

		std::cout<<_CHAR[CUBE[LEFT][0]] << _CHAR[CUBE[LEFT][1]] << _CHAR[CUBE[LEFT][2]] <<"\t";
		std::cout<<_CHAR[CUBE[FRONT][0]] << _CHAR[CUBE[FRONT][1]] << _CHAR[CUBE[FRONT][2]] <<"\t";
		std::cout<<_CHAR[CUBE[RIGHT][0]] << _CHAR[CUBE[RIGHT][1]] << _CHAR[CUBE[RIGHT][2]] <<"\t";
		std::cout<<_CHAR[CUBE[BACK][0]] << _CHAR[CUBE[BACK][1]] << _CHAR[CUBE[BACK][2]]<<std::endl;

		std::cout<<_CHAR[CUBE[LEFT][3]] << _CHAR[CUBE[LEFT][4]] << _CHAR[CUBE[LEFT][5]] <<"\t";
		std::cout<<_CHAR[CUBE[FRONT][3]] << _CHAR[CUBE[FRONT][4]] << _CHAR[CUBE[FRONT][5]] <<"\t";
		std::cout<<_CHAR[CUBE[RIGHT][3]] << _CHAR[CUBE[RIGHT][4]] << _CHAR[CUBE[RIGHT][5]] <<"\t";
		std::cout<<_CHAR[CUBE[BACK][3]] << _CHAR[CUBE[BACK][4]] << _CHAR[CUBE[BACK][5]]<<std::endl;

		std::cout<<_CHAR[CUBE[LEFT][6]] << _CHAR[CUBE[LEFT][7]] << _CHAR[CUBE[LEFT][8]] <<"\t";
		std::cout<<_CHAR[CUBE[FRONT][6]] << _CHAR[CUBE[FRONT][7]] << _CHAR[CUBE[FRONT][8]] <<"\t";
		std::cout<<_CHAR[CUBE[RIGHT][6]] << _CHAR[CUBE[RIGHT][7]] << _CHAR[CUBE[RIGHT][8]] <<"\t";
		std::cout<<_CHAR[CUBE[BACK][6]] << _CHAR[CUBE[BACK][7]] << _CHAR[CUBE[BACK][8]]<<std::endl<<std::endl;

		std::cout<<"\t"<<_CHAR[CUBE[DOWN][0]] << _CHAR[CUBE[DOWN][1]] << _CHAR[CUBE[DOWN][2]]<<std::endl;
		std::cout<<"\t"<<_CHAR[CUBE[DOWN][3]] << _CHAR[CUBE[DOWN][4]] << _CHAR[CUBE[DOWN][5]]<<std::endl;
		std::cout<<"\t"<<_CHAR[CUBE[DOWN][6]] << _CHAR[CUBE[DOWN][7]] << _CHAR[CUBE[DOWN][8]]<<std::endl;
}

void initilize(){
	for (int x = 0; x<NUM_FACES; x++){
		for (int y = 0; y<NUM_STICKERS; y++){
			CUBE[x][y] = x;
		}
	}//This is a solved CUBE at this point this initializes the CUBE
}
