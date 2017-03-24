#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
//#include <stdexcept>

#define NUM_FACES 6
#define NUM_STICKERS 9

//char _CHAR[6][2] = {"G","R","Y","O","B","W"};	//https://rubiks-cube-solver.com
//char _CHAR[6][2] = {"O","B","W","G","R","Y"};  	//https://ruwix.com/puzzle-scramble-generator/?type=rubiks-cube

char _CHAR[6][2] = {"G","O","W","R","B","Y"};//MY CUBE

char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};
int OPPISITESIDE[6] = {4,3,5,1,0,2};
enum FACES{LEFT,BACK,UP,FRONT,RIGHT,DOWN};
enum COLORS{GREEN, ORANGE, WHITE, RED, BLUE, YELLOW};

int ATMV[6][16] = {		{UP,BACK,DOWN,FRONT,	0,3,6,8,5,2,0,3,6,0,3,6		},//LEFT
						{UP,RIGHT,DOWN,LEFT,	0,1,2,2,5,8,8,7,6,6,3,0		},//BACK
						{LEFT,FRONT,RIGHT,BACK,	0,1,2,0,1,2,0,1,2,0,1,2		},//UP
						{LEFT,DOWN,RIGHT,UP,	2,5,8,0,1,2,6,3,0,8,7,6		},//FRONT
						{UP,FRONT,DOWN,BACK,	2,5,8,2,5,8,2,5,8,6,3,0		},//RIGHT
						{LEFT,BACK,RIGHT,FRONT,	6,7,8,6,7,8,6,7,8,6,7,8		}};//DOWN

int CUBE [NUM_FACES][NUM_STICKERS];

char VALID_TWO_CHAR_COMMANDS[12][3] = {"Li","L2","Bi","B2","Ui","U2","Fi","F2","Ri","R2","Di","D2"};
char VALID_ONE_CHAR_COMMANDS[6][2] = {"L","B","U","F","R","D"};

//METHODS
void initilize();		//INITILIZES THE CUBE
void print(); 			//PRINTS THE CUBE
void move(int SIDE);	//DOES A MOVE CLOCKWISE
void move2(int SIDE);	//DOES A MOVE TWICE
void moveI(int SIDE);	//DOES A MOVE COUNTER CLOCKWISE
void comands(std::string str); 
void rotateSingleFace(int SIDE);
void rotation(int _int);
void rotation(std::string _str);

void rotationI(int SIDE);
void rotation2(int SIDE);
void rotationI(std::string SIDE);
void rotation2(std::string SIDE);

std::string replaceText(std::string str);

void rotationX();
void rotationY();
void rotationZ();

bool checkFaceAllSame();
bool doesSideHaveCross(int SIDE);
//std::tuple<int,int> targetEdgeCube();
int targetEdgeCubeX();
int targetEdgeCubeY();

bool checkCross(int SIDE);
void makeCross();


int main(){
	initilize();
	//makeCross();
	//comands("L2 R U"); 
	//rotation("x");
	//rotation("y");
	//rotation("z");	

	//I need to pick a side to work on 
	//For now my target will be the top
	//STEP ONE: MAKE A CROSS 			//This will probably be the most difficult to solve
	//A USEFULL METHOD THAT I CAN HAVE IS A TARGETING SYSTEM
	//I CAN HAVE ONE FOR EDGE PIECES AND ONE FOR CORNER PIECES
	//I am going to actually start out will the easiest one which is the last algoritm
	//The only problem since I made the algorithm I will have to recreate it

	//checkState();


	comands("R2 D' U L D U2 L R' D' R2");
	print();


	makeCross();
	//print();
	
	return 0;
}







//When I am going to check a valid cross I will have to check the edge pieces



/* 		EDGE PIECES
CUBE[UP][1] and CUBE[BACK][1]
CUBE[UP][3] and CUBE[LEFT][1]
CUBE[UP][5] and CUBE[FRONT][1]
CUBE[UP][7] and CUBE[RIGHT][1]

CUBE[BACK][1] and CUBE[BACK][7]
CUBE[BACK][3] and CUBE[LEFT][7]
CUBE[BACK][5] and CUBE[FRONT][7]
CUBE[BACK][7] and CUBE[RIGHT][7]

CUBE[FRONT][5] and CUBE[RIGHT][3]
CUBE[RIGHT][5] and CUBE[BACK][3]
CUBE[BACK][5]  and CUBE[LEFT][3]
CUBE[LEFT][5]  and CUBE[FRONT][3]
*/



void makeCross(){
//Well the first, instead of checking for a cross, I should just make the cross for the UP face.
	//to do that I should make a temp of the top side
	//while(not doesSideHaveCross(UP)){//If the up side isn't solved yet then keep trying

	

	//for (int loops = 0; (loops<=200) and (not doesSideHaveCross(UP)) ; loops++){
	while(not doesSideHaveCross(UP)){ //this prevents infinit loops 		I am not sure how many loops it needs to be definite though

		//[0,1,2]
		//[3,4,5]
		//[6,7,8]

		/*
						to make a cross is quite simple
			check 		first you need to check that you don't have a cross on the face that you are working on
									if you do have a check then you can end the function
						else continue


						then next thing that you need to work on is targeting a cubelet that you need
									you need to have a cubelet that is the same color as UP's middle position
									You will target what side it is on, and what position it is at

						the next thing that you will need to work on is bringing the cublets to the space that they need
									rotate the side so that it is in the 5th position


		*/



		

		int targetSide 		= targetEdgeCubeX(); //I would like to make this a tuple when I can figure that out other wise this will have to do
		int targetPosition 	= targetEdgeCubeY();
		std::cout<<"PRINT TARGET"<<FACE_NAME[targetSide]<<"\t"<<targetPosition<<std::endl;



		//while(CUBE[targetSide][5]!=CUBE[UP][4])//This says if cube position 5 is equal to white then 
		//	move(targetSide); //move the target side

		for (int i = 0; (i<4 and (CUBE[targetSide][5]!=CUBE[UP][4])); i++)
			move(targetSide);			
		

		if(targetSide==LEFT){//THIS RELIES ON THE ASSUMPTION THAT THE PREVIOUS WHILE WORKED AND THE POSITION OF THE TARGET IS IN THE TARGETS SIDE AND IN THE 5TH POSITION
			rotation(1);
			rotation(1);
			rotation(1);
			move(UP);
			move(RIGHT);
		}
		else if (targetSide == FRONT){
			move(RIGHT);
		}
		else if (targetSide == RIGHT){
			rotation(1);
			moveI(UP);
			move(RIGHT);
		}
		else if (targetSide == BACK){
			rotation(1);
			rotation(1);
			move2(UP);
			move(RIGHT);
		}
		else if (targetSide==DOWN){
			move(RIGHT);
			move(RIGHT);
		}
		moveI(UP);

		//so when I target a cube since I want to have the target be up things will behave nicely
		//I want it so that the pice I target goes into the 5th postion this will be done by rotating the x side
		//move(x) until target is in 5th
	}
}










void rotationI(int SIDE){
	rotation2(SIDE);
	rotation(SIDE);
}
void rotation2(int SIDE){
	rotation(SIDE);
	rotation(SIDE);
}

void rotationI(std::string SIDE){
	rotation2(SIDE);
	rotation(SIDE);
}
void rotation2(std::string SIDE){
	rotation(SIDE);
	rotation(SIDE);
}







int targetEdgeCubeY(){
	//I want to target a piece that I want on the cube
	//To do this 
	for (int x = 0; x<NUM_FACES; x++){
		for (int y=1; y <NUM_STICKERS; y+=2){
			if(x != UP){
				//Look for it as long as it isn't looking at the UP face
				if(CUBE[x][y]==CUBE[UP][4]){
					//This is the target
					//return (x and y);
					//return std::make_tuple(x, y);
					return y;
				}
			}
		}
	}
	return -1;
}
int targetEdgeCubeX(){
	//I want to target a piece that I want on the cube
	//To do this 
	for (int x = 0; x<NUM_FACES; x++){
		for (int y=1; y <NUM_STICKERS; y+=2){
			if(x != UP){
				//Look for it as long as it isn't looking at the UP face
				if(CUBE[x][y]==CUBE[UP][4]){
					//This is the target
					//return (x and y);
					//return std::make_tuple(x, y);
					return x;
				}
			}
		}
	}
	return -1;
}






bool doesSideHaveCross(int SIDE){
	for (int y = 1; y<NUM_STICKERS-2; y+=2){
		if(CUBE[SIDE][0+y]!=CUBE[SIDE][2+y]){
			return false;
		}
	}	
	return true;	
}


/*
bool checkFaceAllSame(){
	for(int x = 0;x<NUM_FACES;x++){
		bool allSame = true;
		for (int y = 0; y<NUM_STICKERS; y++){
			if(CUBE[x][0+y]==CUBE[x][1+y]){
				allSame=false;
			}
		}
		if(allSame){
			return true;//x is the face that is all  the same
		}

	}
	return false;
}*/


void move(int SIDE){//Clockwise Turn
	int temp = 	   CUBE[ATMV[SIDE][0]][ATMV[SIDE][4]];
	int temp0 =    CUBE[ATMV[SIDE][0]][ATMV[SIDE][5]];
	int temp1 =    CUBE[ATMV[SIDE][0]][ATMV[SIDE][6]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][4]] 	= CUBE[ATMV[SIDE][1]][ATMV[SIDE][7]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][5]] 	= CUBE[ATMV[SIDE][1]][ATMV[SIDE][8]];
	CUBE[ATMV[SIDE][0]][ATMV[SIDE][6]] 	= CUBE[ATMV[SIDE][1]][ATMV[SIDE][9]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][7]] 	= CUBE[ATMV[SIDE][2]][ATMV[SIDE][10]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][8]] 	= CUBE[ATMV[SIDE][2]][ATMV[SIDE][11]];
	CUBE[ATMV[SIDE][1]][ATMV[SIDE][9]] 	= CUBE[ATMV[SIDE][2]][ATMV[SIDE][12]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][10]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][13]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][11]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][14]];
	CUBE[ATMV[SIDE][2]][ATMV[SIDE][12]] = CUBE[ATMV[SIDE][3]][ATMV[SIDE][15]];
	CUBE[ATMV[SIDE][3]][ATMV[SIDE][13]] = temp;
	CUBE[ATMV[SIDE][3]][ATMV[SIDE][14]] = temp0;
	CUBE[ATMV[SIDE][3]][ATMV[SIDE][15]] = temp1;
	std::cout<<std::endl<<FACE_NAME[SIDE]<<std::endl;
	rotateSingleFace(SIDE);
	print();
}

void rotation(std::string _str){//These rotation functions are now what I want but they will work for now
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	if(_str=="x")
		rotationX();
	else if(_str=="y")
		rotationY();
	else if(_str=="z")
		rotationZ();
	else
		std::cout<<"ROTATION CALLED BUT NOT APPLIED"<<std::endl;
}
void rotation(int _int){
	if(_int == 0)
		rotationX();
	else if(_int==1)
		rotationY();
	else if(_int==2)
		rotationZ();
	else
		std::cout<<"ROTATION CALLED BUT NOT APPLIED"<<std::endl;
}

void rotationX(){//GOOD
	int temp[9];
	for(int i = 0; i<NUM_STICKERS; i++){
		temp[i]=CUBE[FRONT][i];

		CUBE[FRONT][i]=CUBE[DOWN][i];
		CUBE[DOWN][i]=CUBE[BACK][i];
		CUBE[BACK][i]=CUBE[UP][i];
		CUBE[UP][i]=temp[i];
	}
	rotateSingleFace(BACK);
	rotateSingleFace(BACK);
	rotateSingleFace(RIGHT);
	rotateSingleFace(OPPISITESIDE[RIGHT]);//TO ROTATE IT CLOCKWISE
	rotateSingleFace(OPPISITESIDE[RIGHT]);
	rotateSingleFace(OPPISITESIDE[RIGHT]);
	std::cout<<std::endl<<"Rotation X"<<std::endl;
	print();
}
void rotationY(){//GOOD
	int temp[9];
	for(int i = 0; i<NUM_STICKERS; i++){
		temp[i]=CUBE[FRONT][i];
		CUBE[FRONT][i]=CUBE[RIGHT][i];
		CUBE[RIGHT][i]=CUBE[BACK][i];
		CUBE[BACK][i]=CUBE[LEFT][i];
		CUBE[LEFT][i]=temp[i];
	}
	//rotateSingleFace(DOWN);
	//rotateSingleFace(DOWN);
	rotateSingleFace(UP);
	rotateSingleFace(OPPISITESIDE[UP]);//TO ROTATE IT CLOCKWISE
	//rotateSingleFace(OPPISITESIDE[UP]);
	//rotateSingleFace(OPPISITESIDE[UP]);//I am going to figure out why this dosn't need a second one
	std::cout<<std::endl<<"Rotation Y"<<std::endl;
	print();
}
void rotationZ(){//GOOD
	int temp[9];
	for(int i = 0; i<NUM_STICKERS; i++){
		temp[i]=CUBE[UP][i];
		CUBE[UP][i]=CUBE[LEFT][i];
		CUBE[LEFT][i]=CUBE[DOWN][i];
		CUBE[DOWN][i]=CUBE[RIGHT][i];
		CUBE[RIGHT][i]=temp[i];
	}
	rotateSingleFace(UP);
	rotateSingleFace(LEFT);
	rotateSingleFace(DOWN);
	rotateSingleFace(RIGHT);

	rotateSingleFace(FRONT); //This is the original side I am rotating
	rotateSingleFace(OPPISITESIDE[FRONT]);
	rotateSingleFace(OPPISITESIDE[FRONT]);
	rotateSingleFace(OPPISITESIDE[FRONT]);
	std::cout<<std::endl<<"Rotation Z"<<std::endl;
	print();
}

void moveI(int SIDE){//Counter Clockwise Trun
	move(SIDE);
 	move(SIDE);
 	move(SIDE);
}

void move2(int SIDE){//2 Turns
 	move(SIDE);
 	move(SIDE);
}

void rotateSingleFace(int SIDE){ //I am seperating this out because rotating the cube will need this
	int temp = CUBE[SIDE][0]; 
	CUBE[SIDE][0] = CUBE[SIDE][6];
	CUBE[SIDE][6] = CUBE[SIDE][8];
	CUBE[SIDE][8] = CUBE[SIDE][2];
	CUBE[SIDE][2] = temp;
	temp = CUBE[SIDE][1];
	CUBE[SIDE][1] = CUBE[SIDE][3];
	CUBE[SIDE][3] = CUBE[SIDE][7];
	CUBE[SIDE][7] = CUBE[SIDE][5];
	CUBE[SIDE][5] = temp;
}

void comands(std::string str){ //This preforms all moves sent to the cube 
	str = replaceText(str);
	int strLen = 0; //have this outside so it dosn't get reset
	while(strLen<=str.length()-1){	
		std::string strBeta;
		std::string strAlpha;
		bool isValidChar = true;
		strAlpha = str.substr(strLen,2);
		strBeta = str.substr(strLen,1);
		for (int i = 0; i <6*2; i++){
			if(strAlpha == VALID_TWO_CHAR_COMMANDS[i]){
				if(i%2==0){
					moveI(i/2);
					strLen++;
				}
				else{
					move2((i-1)/2);
					strLen++;
				}
			}
		}
		strAlpha = str.substr(strLen,2); 
		strBeta = str.substr(strLen,1);
		for (int i = 0; i<6; i++){
			if (strBeta == VALID_ONE_CHAR_COMMANDS[i]){
				move(i); 
			}
		}
		strLen++;
	}
}

std::string replaceText(std::string str){
	str.erase(remove(str.begin(),str.end(),' '),str.end());
	std::replace( str.begin(), str.end(), '\'', 'i');
	return str;
}//This gets rid of spaces and replaces ' with i (this stands of prime)

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
	for (int x = 0; x<NUM_FACES; x++)
		for (int y = 0; y<NUM_STICKERS; y++)
			CUBE[x][y] = x;
}
