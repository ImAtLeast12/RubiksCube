//https://www.youtube.com/watch?v=1t1OL2zN0LQ		//THIS IS THE VIDEO THAT I AM USING FOR THE ALGORITHMS

#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
//Hyristics

#define NUM_FACES 6
#define NUM_STICKERS 9

char _CHAR[6][2] = {"O","B","W","G","R","Y"};  	//https://ruwix.com/puzzle-scramble-generator/?type=rubiks-cube
//char _CHAR[6][2] = {"G","R","Y","O","B","W"};	//https://rubiks-cube-solver.com
//char _CHAR[6][2] = {"G","O","W","R","B","Y"};//MY CUBE

int tempCorner[2] = {0,0};
char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};

enum FACES{LEFT, BACK, UP, FRONT, RIGHT, DOWN};
int OPPISITESIDE[6] = {RIGHT,FRONT,DOWN,BACK,LEFT,UP};
enum COLORS{GREEN, ORANGE, WHITE, RED, BLUE, YELLOW};
enum CUBELETS{	TOP_LEFT, 	 TOP_CENTER, 	TOP_RIGHT,
				CENTER_LEFT, CENTER, 		CENTER_RIGHT,
				BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT,}; //WHEN I WANT TO CALL A CUBELET OF A CUBE I WILL USE THESE

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

//ALL OF THESE ARE FOR A MOVEMENT FOR A SIDE GIVEN
void move(int SIDE);	//DOES A MOVE CLOCKWISE
void move2(int SIDE);	//DOES A MOVE TWICE
void moveI(int SIDE);	//DOES A MOVE COUNTER CLOCKWISE

//ALL OF THESE ARE FOR THE COMANDS
void comands(std::string str); 
std::string replaceText(std::string str);

//ALL OF THESE ARE FOR ROTATIONS
void rotateSingleFace(int SIDE);
void rotateSingleFace2(int SIDE);
void rotateSingleFaceI(int SIDE);
void rotation(int _int);
void rotation(std::string _str);
void rotationX();
void rotationY();
void rotationZ();
void rotationI(int SIDE);
void rotation2(int SIDE);
void rotationI(std::string SIDE);
void rotation2(std::string SIDE);

//ALL OF THESE ARE FOR THE AI
bool checkFaceAllSame();
bool doesSideHaveCross(int SIDE);
int targetEdgeCubeX();//I WANT THIS TO BE A TUPLE INSTEAD OF 2 FUNCTIONS 
int targetEdgeCubeY();//BUT IT STILL WORKS 
bool checkCross(int SIDE);
void makeCross();
void solveCross();
void solveFirstLayerCorners();
void makeDaisy();

/*
int xCorner(int position);
int yCorner(int position);
int zCorner(int position);*/

int CORNERS[8][3];
void updateCorners();
int Corner(int position, int xyz);


void topPieceLeft();
void topPieceRight();
void secondLayer();

bool isSecondLayerDone();
bool doesEdgeHaveYellow();

void leftyAlg();
void rightyAlg();

//This is to make yellowCross

void yellowCross();
void theLine();
void theAngle();
void theDot();
void orientateCornersUp();

void rotateCorner();

void edgeFlip();

bool printMode = false;

int NUM_MOVES = 0;
int NUM_ROTATIONS = 0;
void switchCorners();
void whichSwitch();
void positionEdges();
bool completeEdgeSolved();
void M();
bool isCornerEqualToPiece(int corner,int SIDE, int position);
bool edgesInverted();
bool edgesAskew();

void M(){
	rotation(0);
	comands("L R'");
}

int main(){
	initilize();
	comands("R D2 F U L2 U B' U2 L U' F L2 R' B' F2 D R D2 F B' U' F U2 F2 B"); //this just generates a random cube
	makeCross();
	solveCross();
	makeDaisy();
	solveFirstLayerCorners();
	secondLayer();
	yellowCross();
	whichSwitch();
	positionEdges();



	std::cout<<std::endl<<"NUM MOVES: "<<NUM_MOVES<<std::endl;
	std::cout<<"NUM_ROTATIONS: "<<NUM_ROTATIONS<<std::endl;
	std::cout<<"TOTAL MOVES: "<<NUM_MOVES + NUM_ROTATIONS<<std::endl;
	if (!printMode) print();
	return 0;
}



bool cube_flipFloped(){
	for(int side = 0; side<NUM_FACES; side++){
		if(side == UP || side == DOWN){

		}
		else if ( CUBE[side][1] == CUBE[OPPISITESIDE[side]][0] &&
				CUBE[side][1] == CUBE[OPPISITESIDE[side]][2]){
			//then I need to do the flip thing
		}
		else
			return false;
	}
	return true;
}

void switchCorners(){
	comands("R' D' R2 D2 R' D R' D' R D");
	move(UP);
	comands("R' D' R D R' D' R D");	
	comands("R' D' R D R' D' R D");	
	moveI(UP);
}

bool edgesAskew(){
	for(int i = 0; i<3; i++){
		if (CUBE[FRONT][0] == CUBE[RIGHT][1] && CUBE[FRONT][2] == CUBE[RIGHT][1]) 
			if (CUBE[BACK][0] == CUBE[LEFT][1] && CUBE[BACK][2] == CUBE[LEFT][1]) 
				return true;
		move(UP);
	}
	return false;

}

bool edgesInverted(){
	for(int i = 0; i<3; i++){
			if(CUBE[FRONT][1] == CUBE[BACK][0] && CUBE[RIGHT][1]==CUBE[LEFT][0])
				return true;
			move(UP);
		}
		return false;
}
bool justEdgesSolved(){
	if (CUBE[FRONT][0] == CUBE[FRONT][1] && CUBE[FRONT][1]==CUBE[FRONT][2])
		if (CUBE[RIGHT][0] == CUBE[RIGHT][1] && CUBE[RIGHT][1]==CUBE[RIGHT][2])
			if (CUBE[BACK][0] == CUBE[BACK][1] && CUBE[BACK][1]==CUBE[BACK][2])
				if (CUBE[LEFT][0] == CUBE[LEFT][1] && CUBE[LEFT][1]==CUBE[LEFT][2])
					return true;
	return false;
}

void positionEdges(){
	//I am going to move the up layer until front upcenter == front center

	//case 2

	/*M2 D2 M2 U
	M2 D2 M2 U'

	spin the cube

	M2 D2 M2 U
	M2 D2 M2 U'
	*/

	if (edgesAskew()){
		print();
		edgeFlip();
		while(CUBE[FRONT][0]!= CUBE[FRONT][1] && CUBE[FRONT][2]!= CUBE[FRONT][1])
			move(UP);
		while(!justEdgesSolved()) //case 4 and case 1
			edgeFlip();
		std::cout<<"\n\ncase askew";
		return;
	}
	else if(edgesInverted()){ //case 3
		print();
		edgeFlip();
		while(CUBE[FRONT][0]!= CUBE[FRONT][1] && CUBE[FRONT][2]!= CUBE[FRONT][1])
			move(UP);
		while(!justEdgesSolved()) //case 4 and case 1
			edgeFlip();
		std::cout<<"\n\ncase INVERTED";
		return;
	}
	else{
		print();
		while(CUBE[FRONT][0]!= CUBE[FRONT][1] && CUBE[FRONT][2]!= CUBE[FRONT][1])	//same as in the bottom of edges askew
			move(UP);
		while(!justEdgesSolved()) //case 4 and case 1
			edgeFlip();
		std::cout<<"\n\nthree in a row";
		return;
	}
}

void edgeFlip(){
	rightyAlg();
	leftyAlg();
	for(int i = 0; i<5;i++){
		rightyAlg();
	}
	for(int i = 0; i<5; i++){
		leftyAlg();
	}
}


bool completeEdgeSolved(){
	for (int x = 0; x<4; x++){
		for(int y = 0; y<2; y++){
			if (CUBE[FRONT][0+y]!=CUBE[FRONT][1+y]){
				return false;
			}
		}
	}
	return true;
}
void whichSwitch(){
	//This one i am going to have to decide which switch to do
	//First is the cube solved already
	orientateCornersUp();
	for(int i = 0; i<4; i++){
		if (CUBE[FRONT][0]==CUBE[FRONT][2] &&
			CUBE[RIGHT][0]==CUBE[RIGHT][2] &&
			CUBE[BACK][0]==CUBE[BACK][2] &&
			CUBE[LEFT][0]==CUBE[LEFT][2]){
			std::cout<<"case0\n\n\n\n";
			return;
		}
		else if (CUBE[FRONT][0]==CUBE[BACK][2] &&
				CUBE[RIGHT][0]==CUBE[LEFT][2] &&
				CUBE[BACK][0]==CUBE[FRONT][2] &&
				CUBE[LEFT][0]==CUBE[RIGHT][2]){//CASE 2
			std::cout<<"\n\n\n";
			std::cout<<"case1\n\n\n\n";
			switchCorners();
			move2(UP);
			switchCorners();
			return;
		}
		else if(CUBE[FRONT][0]==CUBE[RIGHT][2] &&
				CUBE[RIGHT][0]==CUBE[LEFT][2] &&
				CUBE[BACK][0]==CUBE[BACK][2] &&
				CUBE[LEFT][0]==CUBE[FRONT][2]){//So this is case 1
				switchCorners();
				move(UP);
				switchCorners();
				std::cout<<"case2\n\n\n\n";
				return;
			}
		else if(CUBE[FRONT][0]==CUBE[BACK][2]&&
				CUBE[RIGHT][0]==CUBE[RIGHT][2]&&
				CUBE[BACK][0]==CUBE[LEFT][2]&&
				CUBE[LEFT][0]==CUBE[FRONT][2]){
				move(UP);
				switchCorners();
				moveI(UP);
				switchCorners();
				std::cout<<"case3\n\n\n\n";
				return;
		}
		move(UP);
	}
}


void rotateCorner(){
	comands("R' D' R D");
}//I could probably do this with the righty algoritm but I just need to change the position of corner I am working with is


void orientateCornersUp(){	
	for(int x = 0; x<4; x++){
		//I need to find which one is yellow
		if (Corner(4,0) == CUBE[UP][CENTER])
			for(int i = 0; i<2; i++)
				rotateCorner();
		else if(Corner(4,1) == CUBE[UP][CENTER])
			for(int i = 0; i<4; i++)
				rotateCorner();
		move(UP);//spin the cube for the next one 
		}
}

void yellowCross(){
	//to solve the yellow cross is pretty easy
	//I need to first see if it is solved already
	if( CUBE[UP][1]==CUBE[UP][3] &&
		CUBE[UP][3]==CUBE[UP][5]&&
		CUBE[UP][5]==CUBE[UP][7]&&
		CUBE[UP][7]==CUBE[UP][CENTER] ){
		return;
	}
	//then the cube is already yellow cross is already done
	else if (CUBE[UP][1]!=CUBE[UP][CENTER] &&
		CUBE[UP][3]!=CUBE[UP][CENTER]&&
		CUBE[UP][5]!=CUBE[UP][CENTER]&&
		CUBE[UP][7]!=CUBE[UP][CENTER]){
		theDot();
		return;
	}
	//then the cube is in the "dot" position

	if (CUBE[UP][1]==CUBE[UP][7] || CUBE[UP][3]==CUBE[UP][5]){
		if (CUBE[UP][3]!=CUBE[UP][5]){
			rotation(1);
		}
		theLine();
		return;
	}
	else{
		while(CUBE[UP][7]!= CUBE[UP][5])
			rotation(1);
		theAngle();
		return;
	}
}
void theDot(){
	theLine();
	theAngle();
}
void theAngle(){
	rotation("Z");
	move(BACK);
	rightyAlg();
	rotationI("Z");
	moveI(BACK);
}
void theLine(){
	move(FRONT);
	rightyAlg();
	moveI(FRONT);
}

void rightyAlg(){
	comands("R U R' U'");
}

void leftyAlg(){
	comands("L' U' L U");
}

void secondLayer(){
	//the first thing that I need to do is turn the cube around
	rotation2(0);
	//I need to see if the edge piece has a yellow on it 
	//If all of the pieces have yellow then I need to trade for one of the pieces that are not solved yet
	//I have to solve for the respective colors

	//comands("R U R' U'");	//Righty Alg
	//comands("L' U' L U"); //Lefty Alg

	//If you want it to go right
	//U righty algo U Lefty alg
	//comands("U R U R' U' L' U' L U");



	//So now I have 2 algorithms that can either go left or right
	//Now I just have to decide when to do that and how many times I need it to be done

	int counter= 0;
	while(not isSecondLayerDone()){
		if (counter > 5){
			//then I need to swap an edge with another to free it up
			//Just make sure that it dosn't free a cubelet that is in the correct spot already
			while(CUBE[FRONT][5]==CUBE[FRONT][CENTER]){ 		//THIS IS A MAJOR PROBLEM THAT I WILL HAVE TO LOOK INTO LATER
				rotation(1);
			}
			topPieceRight();
			counter = 0;
		}
	//for(int i = 0; i<20; i++){
		if(not doesEdgeHaveYellow()){
			//IF THE CUBELET DOSN'T HAVE YELLOW THEN
				//SPIN UNTIL FRONT[CENTER] == FRONT[2]
				while(CUBE[FRONT][1] != CUBE[FRONT][CENTER]){
					moveI(UP);
					rotation(1);
				}//Do that until it is fine
				//Then I am either going to go left or go right
				if(CUBE[UP][7] == CUBE[LEFT][CENTER])
					topPieceLeft();
				
				else
					topPieceRight();
				
		}
		move(UP);
		counter++;
	}
}

bool doesEdgeHaveYellow(){
	if(CUBE[FRONT][1] == CUBE[UP][CENTER] || CUBE[UP][7] == CUBE[UP][CENTER]){
		return true;
	}
	return false;
}

bool isSecondLayerDone(){
	if(	CUBE[FRONT][3]== CUBE[FRONT][CENTER] && CUBE[FRONT][CENTER] == CUBE[FRONT][5] &&
		CUBE[RIGHT][3]== CUBE[RIGHT][CENTER] && CUBE[RIGHT][CENTER] == CUBE[RIGHT][5] &&
		CUBE[BACK][3]== CUBE[BACK][CENTER] && CUBE[BACK][CENTER] == CUBE[BACK][5] &&
		CUBE[LEFT][3]== CUBE[LEFT][CENTER] && CUBE[LEFT][CENTER] == CUBE[LEFT][5]){
		return true;
	}
	return false;
}

void topPieceLeft(){
	moveI(UP);
	leftyAlg();
	rotationI(1);
	rightyAlg();
	rotation(1);
}

void topPieceRight(){
	move(UP);
	rightyAlg();
	rotation(1);
	leftyAlg();
	rotationI(1);
}

int Corner(int position, int xyz){ //this update the corners
	CORNERS [0][0] = CUBE[LEFT][2]; 	CORNERS [0][1] = CUBE[FRONT][0]; 	CORNERS [0][2] = CUBE[UP][6];
	CORNERS [1][0] = CUBE[LEFT][8]; 	CORNERS [1][1] = CUBE[FRONT][6]; 	CORNERS [1][2] = CUBE[DOWN][0];
	CORNERS [2][0] = CUBE[LEFT][0]; 	CORNERS [2][1] = CUBE[BACK][2];  	CORNERS [2][2] = CUBE[UP][0];
	CORNERS [3][0] = CUBE[LEFT][6]; 	CORNERS [3][1] = CUBE[BACK][8];  	CORNERS [3][2] = CUBE[DOWN][6];
	CORNERS [4][0] = CUBE[RIGHT][0];	CORNERS [4][1] = CUBE[FRONT][2]; 	CORNERS [4][2] = CUBE[UP][8];
	CORNERS [5][0] = CUBE[RIGHT][6]; 	CORNERS [5][1] = CUBE[FRONT][8]; 	CORNERS [5][2] = CUBE[DOWN][2];
	CORNERS [6][0] = CUBE[RIGHT][2]; 	CORNERS [6][1] = CUBE[BACK][0]; 	CORNERS [6][2] = CUBE[UP][2];
	CORNERS [7][0] = CUBE[RIGHT][8]; 	CORNERS [7][1] = CUBE[BACK][6]; 	CORNERS [7][2] = CUBE[DOWN][8];
	return CORNERS[position][xyz];
}

void solveFirstLayerCorners(){
	for(int x = 0; x<5; x++){
		for(int y = 0; y<5; y++){
			if (isCornerEqualToPiece(5,FRONT,1) && 
				isCornerEqualToPiece(5,RIGHT,1) && 
				isCornerEqualToPiece(5,UP,CENTER)){
				rotateCorner();
				while(CUBE[UP][CENTER]!=CUBE[UP][8]){
					rotateCorner();
					rotateCorner();
				}
				rotation(1);
			}
			move(DOWN);
		}
	}
}

bool isCornerEqualToPiece(int corner,int SIDE, int position){
	if (CUBE[SIDE][position]==Corner(corner,0))
		return true;
	if (CUBE[SIDE][position]==Corner(corner,1))
		return true;
	if (CUBE[SIDE][position]==Corner(corner,2))
		return true;
	return false;
}
		












void makeDaisy(){
	for (int i = 0; i<4; i++){
		if (Corner(4,0) == CUBE[UP][CENTER] || Corner(4,1) == CUBE[UP][CENTER] || Corner(4,2) == CUBE[UP][CENTER]){ //if any of these cublets are white
			//then check if down 2 has a white piece
			do
				move(DOWN);
			while(Corner(5,0) == CUBE[UP][CENTER] || Corner(5,1) == CUBE[UP][CENTER] || Corner(5,2) == CUBE[UP][CENTER]); //keep going until white is freed
			comands("R' D' R D");
		}
		move(UP);
	}
}

void solveCross(){
	for(int i = 0; i<4; i++){
		move2(FRONT);
		rotation(1);
	}//THIS MAKES DAISY

	for(int i = 0; i<4; i++){//I NEED TO PULL 4 PEICES UP
		while(CUBE[FRONT][7]!=CUBE[FRONT][CENTER]){ //IF THEY MATCH THE MIDDLE AND THE BOTTOM
			move(DOWN);
			rotation(1);
		}
		move2(FRONT);//IF THE BOTTOM MIDDLE PIECE IS THE SAME AS THE MIDDLE PIECE THEN I AM GOING TO 
		rotation(1);
	}
}

void makeCross(){
	//Well the first, instead of checking for a cross, I should just make the cross for the UP face.
	//to do that I should make a temp of the top side
	//while(not doesSideHaveCross(UP)){//If the up side isn't solved yet then keep trying
	//for (int loops = 0; (loops<=200) and (not doesSideHaveCross(UP)) ; loops++){
	while(not doesSideHaveCross(UP)){ //this prevents infinit loops 		I am not sure how many loops it needs to be definite though
		int targetSide 		= targetEdgeCubeX(); //I would like to make this a tuple when I can figure that out other wise this will have to do
		int targetPosition 	= targetEdgeCubeY();
		for (int i = 0; (i<4 and (CUBE[targetSide][5]!=CUBE[UP][CENTER])); i++)
			move(targetSide);			
		
		if(targetSide==LEFT){ //Depending on what the target side was I need to put it in the CUBE[UP][5] position
			rotationI(1);
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
			rotation2(1);
			move2(UP);
			move(RIGHT);
		}
		else if (targetSide==DOWN){
			move2(RIGHT);
		}
		moveI(UP);
		//so when I target a cube since I want to have the target be up things will behave nicely
		//I want it so that the pice I target goes into the 5th postion this will be done by rotating the x side
		//move(x) until target is in 5th
	}
}

int targetEdgeCubeY(){
	//I want to target a piece that I want on the cube
	//To do this 
	for (int x = 0; x<NUM_FACES; x++){
		for (int y=1; y <NUM_STICKERS; y+=2){
			if(x != UP){
				//Look for it as long as it isn't looking at the UP face
				if(CUBE[x][y]==CUBE[UP][CENTER]){
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
				if(CUBE[x][y]==CUBE[UP][CENTER]){
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
}

/*THIS ONE IS FOR LETTERS PUT STAR HERE*/
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

void moveI(int SIDE){//Counter Clockwise Trun
	move(SIDE);
 	move(SIDE);
 	move(SIDE);
}

void move2(int SIDE){//2 Turns
 	move(SIDE);
 	move(SIDE);
}

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
	std::cout<<std::endl<<FACE_NAME[SIDE];
	rotateSingleFace(SIDE);
	if (printMode) print();
	NUM_MOVES++;
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

void rotation(std::string _str){//These rotation functions are now what I want but they will work for now
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	if(_str=="x")
		rotationX();
	else if(_str=="y")
		rotationY();
	else if(_str=="z")
		rotationZ();
	if (printMode) print();
	NUM_ROTATIONS++;
}
void rotation(int _int){
	if(_int == 0)
		rotationX();
	else if(_int==1)
		rotationY();
	else if(_int==2)
		rotationZ();
	if (printMode) print();
	NUM_ROTATIONS++;
}

void rotateSingleFaceI(int SIDE){
	rotateSingleFace2(SIDE);
	rotateSingleFace(SIDE);
}
void rotateSingleFace2(int SIDE){
	rotateSingleFace(SIDE);
	rotateSingleFace(SIDE);
}

void rotationX(){
	int temp[NUM_STICKERS];
	for(int i = 0; i<NUM_STICKERS; i++){
		temp[i]=CUBE[FRONT][i];
		CUBE[FRONT][i] = CUBE[DOWN][i];
		CUBE[DOWN][i] = CUBE[BACK][i];
		CUBE[BACK][i] = CUBE[UP][i];
		CUBE[UP][i] = temp[i];
	}
	rotateSingleFace2(BACK);
	rotateSingleFace2(DOWN);
	rotateSingleFace(RIGHT);
	rotateSingleFaceI(OPPISITESIDE[RIGHT]);//TO ROTATE IT CLOCKWISE
	std::cout<<std::endl<<"Rotation X";
	//print();
}
void rotationY(){
	int temp[NUM_STICKERS];
	for(int i = 0; i<NUM_STICKERS; i++){
		temp[i]=CUBE[FRONT][i];
		CUBE[FRONT][i]=CUBE[RIGHT][i];
		CUBE[RIGHT][i]=CUBE[BACK][i];
		CUBE[BACK][i]=CUBE[LEFT][i];
		CUBE[LEFT][i]=temp[i];
	}
	rotateSingleFace(UP);
	rotateSingleFaceI(OPPISITESIDE[UP]);//TO ROTATE IT CLOCKWISE
	std::cout<<std::endl<<"Rotation Y";
	//print();
}
void rotationZ(){
	int temp[NUM_STICKERS];
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
	rotateSingleFaceI(OPPISITESIDE[FRONT]);
	std::cout<<std::endl<<"Rotation Z";
	//print();
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

void initilize(){
	for (int x = 0; x<NUM_FACES; x++)
		for (int y = 0; y<NUM_STICKERS; y++)
			CUBE[x][y] = x;
}
