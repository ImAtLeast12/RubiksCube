//https://www.youtube.com/watch?v=1t1OL2zN0LQ		//THIS IS THE VIDEO THAT I AM USING FOR THE ALGORITHMS

#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

#define NUM_FACES 6
#define NUM_STICKERS 9


//char _CHAR[6][2] = {"G","R","Y","O","B","W"};	//https://rubiks-cube-solver.com
char _CHAR[6][2] = {"O","B","W","G","R","Y"};  	//https://ruwix.com/puzzle-scramble-generator/?type=rubiks-cube

//char _CHAR[6][2] = {"G","O","W","R","B","Y"};//MY CUBE

char FACE_NAME [6][20] = {"A","B","C","D","E","F"};
						// ?   x	x	?	?	?					


//char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};

int OPPISITESIDE[6] = {4,3,5,1,0,2};
enum FACES{LEFT, BACK, UP, FRONT, RIGHT, DOWN};
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


int xCorner(int position);
int yCorner(int position);
int zCorner(int position);

int CORNERS[8][3] = {{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0}};

void updateCorners();


int main(){
	initilize();
	comands("L U' D' F B' L2 B2 L' U2 R U2 B R B' F' D B L D' R L F R D' B");
	makeCross();
	//std::cout<<std::endl;
	//print();

	solveCross();
	solveFirstLayerCorners();

	//The next thing I need to do is solve the second layer doing this involves a couple algoritms that can be placed easily
	//I am also going to have to put the yellow side face up



	//I need to pick a side to work on 
	//For now my target will be the top
	//STEP ONE: MAKE A CROSS 			//This will probably be the most difficult to solve
	//A USEFULL METHOD THAT I CAN HAVE IS A TARGETING SYSTEM
	//I CAN HAVE ONE FOR EDGE PIECES AND ONE FOR CORNER PIECES
	//I am going to actually start out will the easiest one which is the last algoritm
	//The only problem since I made the algorithm I will have to recreate it	




	return 0;
}





int xCorner(int position){//I WOULD LIKE TO CHANGE THIS TO A TUPLE LATER
	int CORNERS [8][3] = {{CUBE[LEFT][2],		CUBE[FRONT][0],		CUBE[UP][6]},
							{CUBE[LEFT][8],		CUBE[FRONT][6],		CUBE[DOWN][0]},
							{CUBE[LEFT][0],		CUBE[BACK][2],		CUBE[UP][0]},
							{CUBE[LEFT][6],		CUBE[BACK][8],		CUBE[DOWN][6]},
							{CUBE[RIGHT][0],	CUBE[FRONT][2],		CUBE[UP][8]},
							{CUBE[RIGHT][6],	CUBE[FRONT][8],		CUBE[DOWN][2]},
							{CUBE[RIGHT][2],	CUBE[BACK][0],		CUBE[UP][2]},
							{CUBE[RIGHT][8],	CUBE[BACK][6],		CUBE[DOWN][8]}};
	return CORNERS[position][0];
}


int yCorner(int position){
	int CORNERS [8][3] = {{CUBE[LEFT][2],		CUBE[FRONT][0],		CUBE[UP][6]},
							{CUBE[LEFT][8],		CUBE[FRONT][6],		CUBE[DOWN][0]},
							{CUBE[LEFT][0],		CUBE[BACK][2],		CUBE[UP][0]},
							{CUBE[LEFT][6],		CUBE[BACK][8],		CUBE[DOWN][6]},
							{CUBE[RIGHT][0],	CUBE[FRONT][2],		CUBE[UP][8]},
							{CUBE[RIGHT][6],	CUBE[FRONT][8],		CUBE[DOWN][2]},
							{CUBE[RIGHT][2],	CUBE[BACK][0],		CUBE[UP][2]},
							{CUBE[RIGHT][8],	CUBE[BACK][6],		CUBE[DOWN][8]}};
	return CORNERS[position][1];
}

int zCorner(int position){
	int CORNERS [8][3] = {{CUBE[LEFT][2],		CUBE[FRONT][0],		CUBE[UP][6]},
							{CUBE[LEFT][8],		CUBE[FRONT][6],		CUBE[DOWN][0]},
							{CUBE[LEFT][0],		CUBE[BACK][2],		CUBE[UP][0]},
							{CUBE[LEFT][6],		CUBE[BACK][8],		CUBE[DOWN][6]},
							{CUBE[RIGHT][0],	CUBE[FRONT][2],		CUBE[UP][8]},
							{CUBE[RIGHT][6],	CUBE[FRONT][8],		CUBE[DOWN][2]},
							{CUBE[RIGHT][2],	CUBE[BACK][0],		CUBE[UP][2]},
							{CUBE[RIGHT][8],	CUBE[BACK][6],		CUBE[DOWN][8]}};
	return CORNERS[position][2];
}//I would also like to make these a tuple so it does everything all at once

void solveFirstLayerCorners(){//I ONLY WANT TO PUT THE CORNERS IN THE CORRECT POSITIONS I DON'T CARE ABOUT ORIENTATION
	std::cout<<"FIRST CORNERS"<<std::endl;



	//So the first thing that I am going to do is look for a white corner piece in the top row
	int tempX,tempY, tempZ;
	
	for (int i = 0; i < 8; i++){ //This will only check for the UP pieces
			tempX = xCorner(i);
			tempY = yCorner(i);
			tempZ = zCorner(i);
			if(tempX == CUBE[UP][4] || tempY == CUBE[UP][4] || tempZ == CUBE[UP][4]) //IF ONE OF THESE PIECES ARE WHITE THEN THIS WILL TRIGGER		
				std::cout<<"FOUND WHITE PIECE AT "<<std::endl << FACE_NAME[tempX] <<std::endl <<FACE_NAME[tempY]<<std::endl<<FACE_NAME[tempZ]<<std::endl<<std::endl;
				//XX, YY, ZZ
	}

	//SO IF Z





	//comands("R' D' R D");//THIS IS WHAT I USE
	//FIRST THING I AM GOING TO DO IS CHECK TO SEE IF THERE ARE ANY WHITE PIECES ON THE TOP OR NOT
	//I WANT TO PUT ALL OF THE WHITE PIECES FROM THE TOP TO THE BOTTOM 
	//THIS IS JUST SO THAT I DON'T HAVE PARODY ERRORS MAKING IT EASIER FOR MY SELF







	//This puts the [UP][8] to [DOWN][2] 
	//6 repititions will put the cube in the original state







	//to do this I will have to pull all of the white corners up
	//I will then have to orientate them using the corner flip method

	//mabey have a check corner function 
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
		std::cout<<"PRINT TARGET"<<FACE_NAME[targetSide]<<"\t"<<targetPosition<<std::endl;

		for (int i = 0; (i<4 and (CUBE[targetSide][5]!=CUBE[UP][4])); i++)
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
	std::cout<<std::endl<<FACE_NAME[SIDE]<<std::endl;
	rotateSingleFace(SIDE);
	print();
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

void rotateSingleFaceI(int SIDE){
	rotateSingleFace2(SIDE);
	rotateSingleFace(SIDE);
}
void rotateSingleFace2(int SIDE){
	rotateSingleFace(SIDE);
	rotateSingleFace(SIDE);
}

void rotationX(){ //GOOD
	int temp[9];
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
	rotateSingleFace(UP);
	rotateSingleFaceI(OPPISITESIDE[UP]);//TO ROTATE IT CLOCKWISE
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
	rotateSingleFaceI(OPPISITESIDE[FRONT]);
	std::cout<<std::endl<<"Rotation Z"<<std::endl;
	print();
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



/*STAR/int CUBE[NUM_FACES][NUM_STICKERS] =  {{0,1,2,3,4,5,6,7,8},
									{9,10,11,12,13,14,15,16,17},
									{18,19,20,21,22,23,24,25,26},
									{27,28,29,30,31,32,33,34,35},
									{36,37,38,39,40,41,42,43,44},
									{45,46,47,48,49,50,51,52,53}};
//PUT THIS ONE IN THE HEADER/**/

/*THIS GOES IN THE MAIN STAR/
print();
rotationX();/**/
/*PUT STAR HERE*/

/* THIS ONE IS FOR NUMBERS PUT STAR/
void print(){
		std::cout<<"\t\t\t"<<CUBE[UP][0] << " "<< CUBE[UP][1]     << " "<< CUBE[UP][2]<<std::endl;
		std::cout<<"\t\t\t"<<CUBE[UP][3] << " "<< CUBE[UP][4] 	<< " "<< CUBE[UP][5]<<std::endl;
		std::cout<<"\t\t\t"<<CUBE[UP][6] << " "<< CUBE[UP][7] 	<< " "<< CUBE[UP][8]<<std::endl<<std::endl;

		std::cout<<CUBE[LEFT][0] 	<< " "<< CUBE[LEFT][1] 	<< " "<< CUBE[LEFT][2] <<"\t";
		std::cout<<CUBE[FRONT][0] 	<< " "<< CUBE[FRONT][1] 	<< " "<< CUBE[FRONT][2] <<"\t";
		std::cout<<CUBE[RIGHT][0] 	<< " "<< CUBE[RIGHT][1] 	<< " "<< CUBE[RIGHT][2] <<"\t";
		std::cout<<"   "<<CUBE[BACK][0] 	<< " "<< CUBE[BACK][1] 	<< " "<< CUBE[BACK][2]<<std::endl;

		std::cout<<CUBE[LEFT][3] 	<< " "<< CUBE[LEFT][4] 	<< " "<< CUBE[LEFT][5] <<"\t";
		std::cout<<CUBE[FRONT][3] 	<< " "<< CUBE[FRONT][4] 	<< " "<< CUBE[FRONT][5] <<"\t";
		std::cout<<CUBE[RIGHT][3] 	<< " "<< CUBE[RIGHT][4] 	<< " "<< CUBE[RIGHT][5] <<"\t";
		std::cout<<CUBE[BACK][3] 	<< " "<< CUBE[BACK][4] 	<< " "<< CUBE[BACK][5]<<"\t"<<std::endl;

		std::cout<<CUBE[LEFT][6] 	<< " "<< CUBE[LEFT][7] 	<< " "<< CUBE[LEFT][8] <<"\t";
		std::cout<<CUBE[FRONT][6] 	<< " "<< CUBE[FRONT][7] 	<< " "<< CUBE[FRONT][8] <<"\t";
		std::cout<<CUBE[RIGHT][6] 	<< " "<< CUBE[RIGHT][7] 	<< " "<< CUBE[RIGHT][8] <<"\t";
		std::cout<<CUBE[BACK][6] 	<< " "<< CUBE[BACK][7] 	<< " "<< CUBE[BACK][8]<<std::endl<<std::endl;

		std::cout<<"\t\t\t"<<CUBE[DOWN][0] << " "<< CUBE[DOWN][1] << " "<< CUBE[DOWN][2]<<std::endl;
		std::cout<<"\t\t\t"<<CUBE[DOWN][3] << " "<< CUBE[DOWN][4] << " "<< CUBE[DOWN][5]<<std::endl;
		std::cout<<"\t\t\t"<<CUBE[DOWN][6] << " "<< CUBE[DOWN][7] << " "<< CUBE[DOWN][8]<<std::endl;
}/**/


/*void updateCorners(){
	CORNERS = {{CUBE[LEFT][2],		CUBE[FRONT][0],		CUBE[UP][6]},
				{CUBE[LEFT][8],		CUBE[FRONT][6],		CUBE[DOWN][0]},
				{CUBE[LEFT][0],		CUBE[BACK][2],		CUBE[UP][0]},
				{CUBE[LEFT][6],		CUBE[BACK][8],		CUBE[DOWN][6]},
				{CUBE[RIGHT][0],	CUBE[FRONT][2],		CUBE[UP][8]},
				{CUBE[RIGHT][6],	CUBE[FRONT][8],		CUBE[DOWN][2]},
				{CUBE[RIGHT][2],	CUBE[BACK][0],		CUBE[UP][2]},
				{CUBE[RIGHT][8],	CUBE[BACK][6],		CUBE[DOWN][0]}};
}*/ //this keeps on saying unexpected identifyer I think it is beacuse cube is not initilized yet


