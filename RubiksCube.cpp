#include <iostream>
#define NUM_FACES 6
#define NUM_STICKERS 9

char PRINT_COLOR[6][2] = {"G","R","Y","O","B","W"};
char FACE_NAME [6][20] = {"LEFT","BACK","UP","FRONT","RIGHT","DOWN"};
enum FACES{LEFT,BACK,UP,FRONT,RIGHT,DOWN};
enum COLORS{GREEN, ORANGE, WHITE, RED, BLUE, YELLOW};


int AUTO_MOVE[6][18] = {{LEFT,UP,BACK,DOWN,FRONT,0,3,6,8,5,2,0,3,6,0,3,6,true},
						{BACK,UP,RIGHT,DOWN,LEFT,0,1,2,2,5,8,6,7,8,0,3,6,false},
						{UP,LEFT,FRONT,RIGHT,BACK,0,1,2,0,1,2,0,1,2,0,1,2,false},
						{FRONT,LEFT,DOWN,RIGHT,UP,2,5,8,0,1,2,6,3,0,8,7,6,false},
						{RIGHT,UP,FRONT,DOWN,BACK,2,5,8,2,5,8,2,5,8,6,3,0,true},
						{DOWN,LEFT,BACK,RIGHT,FRONT,6,7,8,6,7,8,6,7,8,6,7,8,false}};



void spinX(int (&cube)[NUM_FACES][NUM_STICKERS]);

void print(int (&cube)[NUM_FACES][NUM_STICKERS]); //This prints out the cube for me in the order of Front,Back,Up,Down,Left,Right ~ it dosn't really matter what it is mapped to 
void initilize(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveRIGHT(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveLEFT(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveUP(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveDOWN(int (&cube)[NUM_FACES][NUM_STICKERS]);

void moveFRONT(int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveBACK(int (&cube)[NUM_FACES][NUM_STICKERS]);
void move(	int S0,
			int S1, int S1V0, int S1V1, int S1V2,
			int S2, int S2V0, int S2V1, int S2V2,
			int S3, int S3V0, int S3V1, int S3V2,
			int S4, int S4V0, int S4V1, int S4V2,
			int (&cube)[NUM_FACES][NUM_STICKERS]);

void move(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]);
void move2(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]);
void moveI(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]);

int main(){

	int cube [NUM_FACES][NUM_STICKERS];  //MY GOAL IS TO HAVE THIS BE AS FLEXIBLE AS POSSIBLE
	initilize(cube);

	

	
	move(FRONT,cube);
	moveI(LEFT,cube);
	//move2(LEFT,cube);

	//move(FRONT,cube);
	//move2(LEFT,cube);


	print(cube); 
	std::cout<<std::endl;
	print(cube);
}

void moveI(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]){
	move(SIDE,cube);
 	move(SIDE,cube);
 	move(SIDE,cube);
}

void move2(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]){
 	move(SIDE,cube);
 	move(SIDE,cube);
 }

void move(int SIDE,int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][5]];
	int temp0 = cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][6]];
	int temp1 = cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][7]];
	cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][5]] = cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][8]];
	cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][6]] = cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][9]];
	cube[AUTO_MOVE[SIDE][1]][AUTO_MOVE[SIDE][7]] = cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][10]];
	cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][8]] = cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][11]];
	cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][9]] = cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][12]];
	cube[AUTO_MOVE[SIDE][2]][AUTO_MOVE[SIDE][10]] = cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][13]];
	cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][11]] = cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][14]];
	cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][12]] = cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][15]];
	cube[AUTO_MOVE[SIDE][3]][AUTO_MOVE[SIDE][13]] = cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][16]];

	if (AUTO_MOVE[SIDE][17]){
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][14]] = temp;
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][15]] = temp0;
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][16]] = temp1;
	}
	else{
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][14]] = temp1;
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][15]] = temp0;
		cube[AUTO_MOVE[SIDE][4]][AUTO_MOVE[SIDE][16]] = temp;	
	}

	temp = cube[AUTO_MOVE[SIDE][0]][0]; //I will also have to switch the roatation of the face it's self
	cube[AUTO_MOVE[SIDE][0]][0] = cube[AUTO_MOVE[SIDE][0]][6];
	cube[AUTO_MOVE[SIDE][0]][6] = cube[AUTO_MOVE[SIDE][0]][8];
	cube[AUTO_MOVE[SIDE][0]][8] = cube[AUTO_MOVE[SIDE][0]][2];
	cube[AUTO_MOVE[SIDE][0]][2] = temp;
	temp = cube[AUTO_MOVE[SIDE][0]][1];
	cube[AUTO_MOVE[SIDE][0]][1] = cube[AUTO_MOVE[SIDE][0]][3];
	cube[AUTO_MOVE[SIDE][0]][3] = cube[AUTO_MOVE[SIDE][0]][7];
	cube[AUTO_MOVE[SIDE][0]][7] = cube[AUTO_MOVE[SIDE][0]][5];
	cube[AUTO_MOVE[SIDE][0]][5] = temp;
}

void moveLEFT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][0];
	int temp0 = cube[UP][3];
	int temp1 = cube[UP][6];
	cube[UP][0] = cube[BACK][8];
	cube[UP][3] = cube[BACK][5];
	cube[UP][6] = cube[BACK][2];
	cube[BACK][8] = cube[DOWN][0];
	cube[BACK][5] = cube[DOWN][3];
	cube[BACK][2] = cube[DOWN][6];
	cube[DOWN][0] = cube[FRONT][0];
	cube[DOWN][3] = cube[FRONT][3];
	cube[DOWN][6] = cube[FRONT][6];

	cube[FRONT][0] = temp1;//0
	cube[FRONT][3] = temp0;//3
	cube[FRONT][6] = temp;//6

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


void moveBACK(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][0];
	int temp0 = cube[UP][1];
	int temp1 = cube[UP][2];
	cube[UP][0] = cube[RIGHT][2];
	cube[UP][1] = cube[RIGHT][5];
	cube[UP][2] = cube[RIGHT][8];
	cube[RIGHT][2] = cube[DOWN][6];
	cube[RIGHT][5] = cube[DOWN][7];
	cube[RIGHT][8] = cube[DOWN][8];
	cube[DOWN][6] = cube[LEFT][0];
	cube[DOWN][7] = cube[LEFT][3];
	cube[DOWN][8] = cube[LEFT][6];

	cube[LEFT][0] = temp;
	cube[LEFT][3] = temp0;
	cube[LEFT][6] = temp1;

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

void moveFRONT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[LEFT][2];
	int temp0 = cube[LEFT][5];
	int temp1 = cube[LEFT][8];
	cube[LEFT][2] = cube[DOWN][0];
	cube[LEFT][5] = cube[DOWN][1];
	cube[LEFT][8] = cube[DOWN][2];
	cube[DOWN][0] = cube[RIGHT][6];
	cube[DOWN][1] = cube[RIGHT][3];
	cube[DOWN][2] = cube[RIGHT][0];
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
}

void moveRIGHT(int (&cube)[NUM_FACES][NUM_STICKERS]){
	int temp = cube[UP][2];
	int temp0 = cube[UP][5];
	int temp1 = cube[UP][8];
	cube[UP][2] = cube[FRONT][2];
	cube[UP][5] = cube[FRONT][5];
	cube[UP][8] = cube[FRONT][8];
	cube[FRONT][2] = cube[DOWN][2];
	cube[FRONT][5] = cube[DOWN][5];
	cube[FRONT][8] = cube[DOWN][8];
	cube[DOWN][2] = cube[BACK][6];
	cube[DOWN][5] = cube[BACK][3];
	cube[DOWN][8] = cube[BACK][0];

	cube[BACK][6] = temp1;
	cube[BACK][3] = temp0;
	cube[BACK][0] = temp;

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

void initilize(int (&cube)[NUM_FACES][NUM_STICKERS]){
	for (int x = 0; x<NUM_FACES; x++){
		for (int y = 0; y<NUM_STICKERS; y++){
			cube[x][y] = x;
		}
	}//This is a solved cube at this point this initilizes the cube
}

void print(int (&cube)[NUM_FACES][NUM_STICKERS]){

	std::cout<<"CUBE"<<std::endl;

		std::cout<<"\t"<<PRINT_COLOR[cube[UP][0]] << PRINT_COLOR[cube[UP][1]] << PRINT_COLOR[cube[UP][2]]<<std::endl;
		std::cout<<"\t"<<PRINT_COLOR[cube[UP][3]] << PRINT_COLOR[cube[UP][4]] << PRINT_COLOR[cube[UP][5]]<<std::endl;
		std::cout<<"\t"<<PRINT_COLOR[cube[UP][6]] << PRINT_COLOR[cube[UP][7]] << PRINT_COLOR[cube[UP][8]]<<std::endl<<std::endl;

		std::cout<<PRINT_COLOR[cube[LEFT][0]] << PRINT_COLOR[cube[LEFT][1]] << PRINT_COLOR[cube[LEFT][2]] <<"\t";
		std::cout<<PRINT_COLOR[cube[FRONT][0]] << PRINT_COLOR[cube[FRONT][1]] << PRINT_COLOR[cube[FRONT][2]] <<"\t";
		std::cout<<PRINT_COLOR[cube[RIGHT][0]] << PRINT_COLOR[cube[RIGHT][1]] << PRINT_COLOR[cube[RIGHT][2]] <<"\t";
		std::cout<<PRINT_COLOR[cube[BACK][0]] << PRINT_COLOR[cube[BACK][1]] << PRINT_COLOR[cube[BACK][2]]<<std::endl;

		std::cout<<PRINT_COLOR[cube[LEFT][3]] << PRINT_COLOR[cube[LEFT][4]] << PRINT_COLOR[cube[LEFT][5]] <<"\t";
		std::cout<<PRINT_COLOR[cube[FRONT][3]] << PRINT_COLOR[cube[FRONT][4]] << PRINT_COLOR[cube[FRONT][5]] <<"\t";
		std::cout<<PRINT_COLOR[cube[RIGHT][3]] << PRINT_COLOR[cube[RIGHT][4]] << PRINT_COLOR[cube[RIGHT][5]] <<"\t";
		std::cout<<PRINT_COLOR[cube[BACK][3]] << PRINT_COLOR[cube[BACK][4]] << PRINT_COLOR[cube[BACK][5]]<<std::endl;

		std::cout<<PRINT_COLOR[cube[LEFT][6]] << PRINT_COLOR[cube[LEFT][7]] << PRINT_COLOR[cube[LEFT][8]] <<"\t";
		std::cout<<PRINT_COLOR[cube[FRONT][6]] << PRINT_COLOR[cube[FRONT][7]] << PRINT_COLOR[cube[FRONT][8]] <<"\t";
		std::cout<<PRINT_COLOR[cube[RIGHT][6]] << PRINT_COLOR[cube[RIGHT][7]] << PRINT_COLOR[cube[RIGHT][8]] <<"\t";
		std::cout<<PRINT_COLOR[cube[BACK][6]] << PRINT_COLOR[cube[BACK][7]] << PRINT_COLOR[cube[BACK][8]]<<std::endl<<std::endl;

		std::cout<<"\t"<<PRINT_COLOR[cube[DOWN][0]] << PRINT_COLOR[cube[DOWN][1]] << PRINT_COLOR[cube[DOWN][2]]<<std::endl;
		std::cout<<"\t"<<PRINT_COLOR[cube[DOWN][3]] << PRINT_COLOR[cube[DOWN][4]] << PRINT_COLOR[cube[DOWN][5]]<<std::endl;
		std::cout<<"\t"<<PRINT_COLOR[cube[DOWN][6]] << PRINT_COLOR[cube[DOWN][7]] << PRINT_COLOR[cube[DOWN][8]]<<std::endl;
/*	for (int x = 0; x<NUM_FACES; x++){
		for (int y = 0; y<NUM_STICKERS; y++){
			if(y%3 == 0){
				std::cout<<std::endl;
			}
			std::cout<<cube[x][y];
		}
		std::cout<<"\t"<<FACE_NAME[x]<<std::endl;
	}
	std::cout<<std::endl;
*/


/*
		UUU
		UUU
		UUU

LLL		FFF		RRR		BBB
LLL		FFF		RRR		BBB
LLL		FFF		RRR		BBB

		DDD
		DDD
		DDD
*/

}//This lets me print out all of the information I need for the cube
