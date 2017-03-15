#include <iostream>
#define NUM_FACES 6
#define NUM_STICKERS 9
//OK so I know that a rubiks cube has 6 faces
//And Each Face has 9 Cubes
/*
enum Faces(){
	Front,
	Back,
	Up,
	Down,
	Left,
	Right
};
*/


//Some Ideas is to make this cube an object so that I can do extra stuff on it
//I can also make a .h file so I won't have to see all of these void statements up in here
char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};

enum FACES{LEFT,BACK,UP,FRONT,RIGHT,DOWN};
enum COLORS{GREEN, ORANGE, WHITE, RED, BLUE, YELLOW};
void spinX(int (&cube)[NUM_FACES][NUM_STICKERS]);

void print(int (&cube)[NUM_FACES][NUM_STICKERS]); //This prints out the cube for me in the order of Front,Back,Up,Down,Left,Right ~ it dosn't really matter what it is mapped to 
void initilize(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveRIGHT(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveLEFT(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveUP(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveDOWN(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveFRONT(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveBACK(int (&cube)[NUM_FACES][NUM_STICKERS]);
int main(){

	int cube [NUM_FACES][NUM_STICKERS];  //MY GOAL IS TO HAVE THIS BE AS FLEXIBLE AS POSSIBLE
	initilize(cube);
	print(cube); 

	spinX(cube);
}

void moveBACK(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][0];
	int temp0 = cube[UP][1];
	int temp1 = cube[UP][2];
	cube[UP][0] = cube[RIGHT][2];
	cube[UP][1] = cube[RIGHT][5];
	cube[UP][2] = cube[RIGHT][8];
	cube[RIGHT][2] = cube[DOWN][2];
	cube[RIGHT][5] = cube[DOWN][5];
	cube[RIGHT][8] = cube[DOWN][8];
	cube[DOWN][2] = cube[LEFT][6];
	cube[DOWN][5] = cube[LEFT][3];
	cube[DOWN][8] = cube[LEFT][0];
	cube[LEFT][6] = temp;
	cube[LEFT][3] = temp0;
	cube[LEFT][0] = temp1;

	temp = cube[BACK][0]; //I will also have to switch the roatation of the face it's self
	cube[BACK][0] = cube[BACK][6];
	cube[BACK][6] = cube[BACK][8];
	cube[BACK][8] = cube[BACK][2];
	cube[BACK][2] = temp;
	temp = cube[BACK][1];
	cube[BACK][1] = cube[BACK][3];
	cube[BACK][3] = cube[BACK][7];
	cube[BACK][7] = cube[BACK][5];
	cube[BACK][5] = temp;
}

void moveFRONT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[LEFT][2];
	int temp0 = cube[LEFT][5];
	int temp1 = cube[LEFT][8];
	cube[LEFT][2] = cube[DOWN][6];
	cube[LEFT][5] = cube[DOWN][3];
	cube[LEFT][8] = cube[DOWN][0];
	cube[DOWN][6] = cube[RIGHT][6];
	cube[DOWN][3] = cube[RIGHT][3];
	cube[DOWN][0] = cube[RIGHT][0];
	cube[RIGHT][6] = cube[UP][8];
	cube[RIGHT][3] = cube[UP][7];
	cube[RIGHT][0] = cube[UP][6];
	cube[UP][8] = temp;
	cube[UP][7] = temp0;
	cube[UP][6] = temp1;
	
	temp = cube[FRONT][0]; //I will also have to switch the roatation of the face it's self
	cube[FRONT][0] = cube[FRONT][6];
	cube[FRONT][6] = cube[FRONT][8];
	cube[FRONT][8] = cube[FRONT][2];
	cube[FRONT][2] = temp;
	temp = cube[FRONT][1];
	cube[FRONT][1] = cube[FRONT][3];
	cube[FRONT][3] = cube[FRONT][7];
	cube[FRONT][7] = cube[FRONT][5];
	cube[FRONT][5] = temp;
	//preferabley I would like to make only 1 function that you will input  a number and it will do everything on it's own
}

void moveDOWN(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[LEFT][6];
	int temp0 = cube[LEFT][7];
	int temp1 = cube[LEFT][8];
	cube[LEFT][6] = cube[BACK][6];
	cube[LEFT][7] = cube[BACK][7];
	cube[LEFT][8] = cube[BACK][8];
	cube[BACK][6] = cube[RIGHT][6];
	cube[BACK][7] = cube[RIGHT][7];
	cube[BACK][8] = cube[RIGHT][8];
	cube[RIGHT][6] = cube[FRONT][6];
	cube[RIGHT][7] = cube[FRONT][7];
	cube[RIGHT][8] = cube[FRONT][8];
	cube[FRONT][6] = temp;
	cube[FRONT][7] = temp0;
	cube[FRONT][8] = temp1;
	
	temp = cube[DOWN][0]; //I will also have to switch the roatation of the face it's self
	cube[DOWN][0] = cube[DOWN][6];
	cube[DOWN][6] = cube[DOWN][8];
	cube[DOWN][8] = cube[DOWN][2];
	cube[DOWN][2] = temp;
	temp = cube[DOWN][1];
	cube[DOWN][1] = cube[DOWN][3];
	cube[DOWN][3] = cube[DOWN][7];
	cube[DOWN][7] = cube[DOWN][5];
	cube[DOWN][5] = temp;
}

void moveUP(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[LEFT][0];
	int temp0 = cube[LEFT][1];
	int temp1 = cube[LEFT][2];
	cube[LEFT][0] = cube[FRONT][0];
	cube[LEFT][1] = cube[FRONT][1];
	cube[LEFT][2] = cube[FRONT][2];
	cube[FRONT][0] = cube[RIGHT][0];
	cube[FRONT][1] = cube[RIGHT][1];
	cube[FRONT][2] = cube[RIGHT][2];
	cube[RIGHT][0] = cube[BACK][0];
	cube[RIGHT][1] = cube[BACK][1];
	cube[RIGHT][2] = cube[BACK][2];
	cube[BACK][0] = temp;
	cube[BACK][1] = temp0;
	cube[BACK][2] = temp1;
	
	temp = cube[UP][0];//I will also have to switch the roatation of the face it's self
	cube[UP][0] = cube[UP][6];
	cube[UP][6] = cube[UP][8];
	cube[UP][8] = cube[UP][2];
	cube[UP][2] = temp;
	temp = cube[UP][1];
	cube[UP][1] = cube[UP][3];
	cube[UP][3] = cube[UP][7];
	cube[UP][7] = cube[UP][5];
	cube[UP][5] = temp;
}

void moveRIGHT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][8];
	int temp0 = cube[UP][5];
	int temp1 = cube[UP][2];
	cube[UP][2] = cube[FRONT][2];
	cube[UP][5] = cube[FRONT][5];
	cube[UP][8] = cube[FRONT][8];
	cube[FRONT][2] = cube[DOWN][0];
	cube[FRONT][5] = cube[DOWN][1];
	cube[FRONT][8] = cube[DOWN][2];
	cube[DOWN][0] = cube[BACK][6];
	cube[DOWN][1] = cube[BACK][3];
	cube[DOWN][2] = cube[BACK][0];
	cube[BACK][0] = temp;
	cube[BACK][3] = temp0;
	cube[BACK][6] = temp1;

	temp = cube[RIGHT][0]; //I will also have to switch the roatation of the face it's self
	cube[RIGHT][0] = cube[RIGHT][6];
	cube[RIGHT][6] = cube[RIGHT][8];
	cube[RIGHT][8] = cube[RIGHT][2];
	cube[RIGHT][2] = temp;
	temp = cube[RIGHT][1];
	cube[RIGHT][1] = cube[RIGHT][3];
	cube[RIGHT][3] = cube[RIGHT][7];
	cube[RIGHT][7] = cube[RIGHT][5];
	cube[RIGHT][5] = temp;
}

void moveLEFT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][0];
	int temp0 = cube[UP][3];
	int temp1 = cube[UP][6];
	cube[UP][6] = cube[BACK][2];
	cube[UP][3] = cube[BACK][5];
	cube[UP][0] = cube[BACK][8];
	cube[BACK][2] = cube[DOWN][8];
	cube[BACK][5] = cube[DOWN][7];
	cube[BACK][8] = cube[DOWN][6];
	cube[DOWN][8] = cube[FRONT][6];
	cube[DOWN][7] = cube[FRONT][3];
	cube[DOWN][6] = cube[FRONT][0];
	cube[FRONT][0] = temp;
	cube[FRONT][3] = temp0;
	cube[FRONT][6] = temp1;
	
	
	temp = cube[LEFT][0]; //I will also have to switch the roatation of the face it's self
	cube[LEFT][0] = cube[LEFT][6];
	cube[LEFT][6] = cube[LEFT][8];
	cube[LEFT][8] = cube[LEFT][2];
	cube[LEFT][2] = temp;
	temp = cube[LEFT][1];
	cube[LEFT][1] = cube[LEFT][3];
	cube[LEFT][3] = cube[LEFT][7];
	cube[LEFT][7] = cube[LEFT][5];
	cube[LEFT][5] = temp;
}

void initilize(int (&cube)[NUM_FACES][NUM_STICKERS]){
	for (int x = 0; x<NUM_FACES; x++){
		for (int y = 0; y<NUM_STICKERS; y++){
			cube[x][y] = x;
		}
	}//This is a solved cube at this point this initilizes the cube
}

void print(int (&cube)[NUM_FACES][NUM_STICKERS]){
	for (int x = 0; x<NUM_FACES; x++){
		for (int y = 0; y<NUM_STICKERS; y++){
			std::cout<<cube[x][y];
		}
		std::cout<<"\t"<<FACE_NAME[x]<<std::endl;
	}
	std::cout<<std::endl;
}//This lets me print out all of the information I need for the cube
