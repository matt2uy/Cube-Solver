// main file = initializes movement variables and integrates all of them together
// cube_data.h = gets cube data from user and sends it to solver
// solver.h = gets cube data from cube_data.h and tells movement.h what algorithm to use
// movement.h = gets algorithm from solver.h and moves the servos
//-------------------------------------------------------------------------
// fixes: maybe make proxy or pointer/reference variables in order to move all movement functions to a header file
//Cube Solver: solves rubiks cube with 2 servos
// pictures: <URL>
// files and instructables: <URL>

#include <Servo.h>
//#include <Solver.h>

// servo objects
Servo rotate_servo;
Servo push_servo;

int move_speed = 5;
int buffer_time = 200;
int rotate_pos = 90;
int push_pos = 140;
int hold_progress = 3;
int offset_degrees = 10;

//////// cube move variables:
bool sim_only = false;

// test function:
bool test_ongoing = true;

char yellow_side[9] = {'y', 'y', 'y',
                       'y', 'y', 'y',
                       'y', 'y', 'y'};

char white_side[9] =  {'w', 'w', 'w',
                       'w', 'w', 'w',
                       'w', 'w', 'w'};

char blue_side[9] =   {'b', 'b', 'b',
                       'b', 'b', 'b',
                       'b', 'b', 'b'};

char red_side[9] =    {'r', 'r', 'r',
                       'r', 'r', 'r',
                       'r', 'r', 'r'};

char green_side[9] =  {'g', 'g', 'g',
                       'g', 'g', 'g',
                       'g', 'g', 'g'};

char orange_side[9] = {'o', 'o', 'o',
                       'o', 'o', 'o',
                       'o', 'o', 'o'};

String raw_cube_string = "";

// prints one side of a cube (used for diagnostic purposes)
void print_cube(char cube_side[])
{
	// make a for loop for this
	for (int i = 0; i < 3; i++)
	{
		Serial.println('\r');
	}

	Serial.print("Face: ");
	Serial.println(cube_side[4]);

	for(int i = 0; i < 9; i = i+3)
	{
		Serial.print("|");
		Serial.print(cube_side[i]);
		Serial.print("|");
		Serial.print(cube_side[i+1]);
		Serial.print("|");
		Serial.print(cube_side[i+2]);
		Serial.println("|");
	}
}

// prints all six sides of the cube
void print_whole_cube()
{
	print_cube(yellow_side);
	print_cube(white_side);
	print_cube(blue_side);
	print_cube(red_side);
	print_cube(green_side);
	print_cube(orange_side);
}

////////////////////// Serial Communication (receive arrays from .py script)


void accept_string()
{
	char ready_signal = 'ready';
	char received_signal = 'recieved';
	
	for (int piece_num = 0; piece_num <10; piece_num++)
	{	
		// send ready signal
		Serial.println(ready_signal);
		delay(1000);
	}
	// receive string
	while(raw_cube_string == "")
	{
		char character;
		while(Serial.available()) 
		{
		    character = Serial.read();
		   	raw_cube_string.concat(character);
		}
	}
	delay(10);
	Serial.print("String Accepted: ");
	//Serial.print(raw_cube_string);

	// send color confirmed signal
	Serial.println(received_signal);
	delay(10);
}

void parse_raw_cube() // need an input of 54 char length string
{	
	// convert to char array
	Serial.print("Parsing... ");
	raw_cube_string.toCharArray(yellow_side, sizeof(yellow_side));
	
	// assign to cube sides:
	Serial.println("yellow...");
	for(int x = 0; x < 9; x++)
	{
		yellow_side[x] = raw_cube_string[x];
	}
	
	Serial.println("white...");
	for(int x = 9; x < 18; x++)
	{
		white_side[x-9] = raw_cube_string[x];
	}

	Serial.println("red...");
	for(int x = 18; x < 27; x++)
	{
		red_side[x-18] = raw_cube_string[x];
	}

	Serial.println("blue...");
	for(int x = 27; x < 36; x++)
	{
		blue_side[x-27] = raw_cube_string[x];
	}

	Serial.println("green...");
	for(int x = 36; x < 45; x++)
	{
		green_side[x-36] = raw_cube_string[x];
	}

	Serial.println("orange...");
	for(int x = 45; x < 54; x++)
	{
		orange_side[x-45] = raw_cube_string[x];
	}
}

// imports cube colors from .py file through serial
void import_cube_colors()
{
	accept_string();

	parse_raw_cube();
	print_whole_cube();
	while(true){}
}
///////////////////// Physical Movement Functions ///////////////////////////

////////// Servo movement function: ///////////
int move_servo(int start, int finish, int servo_pin)
{
	int pos;
	if (start - finish < 0)
	{
		for(pos = start; pos <= finish; pos += 1)
		{
			if (servo_pin == 6)
			{
				push_servo.write(pos);
				delay(move_speed);
			}
			else if (servo_pin == 9)
			{
				rotate_servo.write(pos);
				delay(move_speed);
			}
		}
	}
	else
	{
		for(pos = start; pos >= finish; pos -= 1)
		{
			if (servo_pin == 6)
			{
				push_servo.write(pos);
				delay(move_speed);
			}
			else if (servo_pin == 9)
			{
				rotate_servo.write(pos);
				delay(move_speed);
			}
		}
	}
	// use a swich case next time
	if (servo_pin == 9)
	{
		rotate_pos = pos;
	}
	if (servo_pin == 6)
	{
		push_pos = pos;
	}
	delay(buffer_time);
}
///////// Cube movement functions: ////////////
void push_cube()
{
	move_servo(140, 72, 6);
	delay(buffer_time);
	move_servo(72, 140, 6);
}
void hold_cube()
{
	move_servo(push_pos, 115, 6);
	hold_progress = 1;
}
void release_cube()
{
	move_servo(push_pos, 140, 6);
	hold_progress = 3;
}
void rotate_one()
{
	int rotate_finish = 12;
	if (hold_progress == 1) // hold progress 1 = hold
	{
		move_servo(rotate_pos, rotate_finish-8, 9);
		move_servo(rotate_pos, rotate_finish+5, 9);
		hold_progress = 2;
	}
	else if (hold_progress == 2) // hold progress 2 = release, but offset still there
	{
		hold_progress = 3;
	}
	else if (hold_progress == 3) // hold progress 3 = release, offsets reconciled
	{
		// do nothing
	}

	move_servo(rotate_pos, rotate_finish, 9);
}
void rotate_two()
{
	int rotate_finish = 90;
	if (hold_progress == 1) // hold progress 1 = hold
	{
		// rotate from rotate_one
		if (rotate_pos < 50) 
		{
			move_servo(rotate_pos, rotate_finish+12, 9);
			move_servo(rotate_pos, rotate_finish-5, 9);
		}
		// rotate from rotate_three
		else if (rotate_pos > 150) 
		{
			move_servo(rotate_pos, rotate_finish-5, 9);
			move_servo(rotate_pos, rotate_finish+5, 9);
		}
		hold_progress = 2;
	}
	else if (hold_progress == 2) // hold progress 2 = release, but offset still there
	{
		hold_progress = 3;
		move_servo(rotate_pos, rotate_finish, 9);
	}
	else if (hold_progress == 3) // hold progress 3 = release, offsets reconciled
	{
		// do nothing
		move_servo(rotate_pos, rotate_finish, 9);
	}
}
void rotate_three()
{
	int rotate_finish = 175;
	if (hold_progress == 1) // hold progress 1 = hold
	{
		move_servo(rotate_pos, rotate_finish+5, 9);
		move_servo(rotate_pos, rotate_finish-10, 9); // prevent pulling

		// fix: cube not fully turned
		release_cube();
		move_servo(rotate_pos, 80, 9);
		hold_cube();
		move_servo(rotate_pos, 100, 9);
		move_servo(rotate_pos, 90, 9); // prevent pulling
		release_cube();
		move_servo(rotate_pos, 175, 9);
		hold_progress = 2;
	}
	else if (hold_progress == 2) // hold progress 2 = release, but offset still there
	{
		hold_progress = 3;
		move_servo(rotate_pos, rotate_finish, 9);
	}
	else if (hold_progress == 3) // hold progress 3 = release, offsets reconciled
	{
		// do nothing
		move_servo(rotate_pos, rotate_finish, 9);
	}
}

///////////////////// Cube Move Notation ///////////////////////////
// They print, simulate and call the physical functions

void left()
{
	Serial.print("L, ");

	if (sim_only == false)
	{
		rotate_three();
		push_cube();
		hold_cube();
		rotate_two();
		release_cube();
		rotate_one();
		push_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_blue_side[9];
	char r_white_side[9];
	char r_green_side[9];
	char r_red_side[9];

	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}

	yellow_side[0] = r_blue_side[0];
	yellow_side[3] = r_blue_side[3];
	yellow_side[6] = r_blue_side[6];

	blue_side[0] = r_white_side[0];
	blue_side[3] = r_white_side[3];
	blue_side[6] = r_white_side[6];

	white_side[0] = r_green_side[8];
	white_side[3] = r_green_side[5];
	white_side[6] = r_green_side[2];

	green_side[8] = r_yellow_side[0];
	green_side[5] = r_yellow_side[3];
	green_side[2] = r_yellow_side[6];

	for(int x = 0; x < 9; x++)
	{
		r_red_side[x] = red_side[x];
	}

	red_side[0] = r_red_side[6];
	red_side[1] = r_red_side[3];
	red_side[2] = r_red_side[0];
	red_side[3] = r_red_side[7];
	red_side[4] = r_red_side[4];
	red_side[5] = r_red_side[1];
	red_side[6] = r_red_side[8];
	red_side[7] = r_red_side[5];
	red_side[8] = r_red_side[2];
}
void left_inverted()
{
	Serial.print("L', ");

	if (sim_only == false)
	{
		rotate_three();
		push_cube();
		rotate_two();
		hold_cube();
		rotate_three();
		release_cube();
		rotate_one();
		push_cube();
		rotate_two();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_blue_side[9];
	char r_white_side[9];
	char r_green_side[9];
	char r_red_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}

	yellow_side[0] = r_green_side[8];
	yellow_side[3] = r_green_side[5];
	yellow_side[6] = r_green_side[2];

	blue_side[0] = r_yellow_side[0];
	blue_side[3] = r_yellow_side[3];
	blue_side[6] = r_yellow_side[6];

	white_side[0] = r_blue_side[0];
	white_side[3] = r_blue_side[3];
	white_side[6] = r_blue_side[6];

	green_side[8] = r_white_side[0];
	green_side[5] = r_white_side[3];
	green_side[2] = r_white_side[6];

	for(int x = 0; x < 9; x++)
	{
		r_red_side[x] = red_side[x];
	}

	red_side[0] = r_red_side[2];
	red_side[1] = r_red_side[5];
	red_side[2] = r_red_side[8];
	red_side[3] = r_red_side[1];
	red_side[4] = r_red_side[4];
	red_side[5] = r_red_side[7];
	red_side[6] = r_red_side[0];
	red_side[7] = r_red_side[3];
	red_side[8] = r_red_side[6];
}
void right()
{
	Serial.print("R, ");

	if (sim_only == false)
	{
		rotate_one();
		push_cube();
		rotate_two();
		hold_cube();
		rotate_one();
		release_cube();
		rotate_three();
		push_cube();
		rotate_two();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_blue_side[9];
	char r_white_side[9];
	char r_green_side[9];
	char r_orange_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}

	yellow_side[2] = r_green_side[6];
	yellow_side[5] = r_green_side[3];
	yellow_side[8] = r_green_side[0];

	blue_side[2] = r_yellow_side[2];
	blue_side[5] = r_yellow_side[5];
	blue_side[8] = r_yellow_side[8];

	white_side[2] = r_blue_side[2];
	white_side[5] = r_blue_side[5];
	white_side[8] = r_blue_side[8];

	green_side[6] = r_white_side[2];
	green_side[3] = r_white_side[5];
	green_side[0] = r_white_side[8];

	for(int x = 0; x < 9; x++)
	{
		r_orange_side[x] = orange_side[x];
	}

	orange_side[0] = r_orange_side[6];
	orange_side[1] = r_orange_side[3];
	orange_side[2] = r_orange_side[0];
	orange_side[3] = r_orange_side[7];
	orange_side[4] = r_orange_side[4];
	orange_side[5] = r_orange_side[1];
	orange_side[6] = r_orange_side[8];
	orange_side[7] = r_orange_side[5];
	orange_side[8] = r_orange_side[2];
}
void right_inverted()
{
	Serial.print("R', ");

	if(sim_only == false)
	{
		rotate_one();
		push_cube();
		hold_cube();
		rotate_two();
		release_cube();
		rotate_three();
		push_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_blue_side[9];
	char r_white_side[9];
	char r_green_side[9];
	char r_orange_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}

	yellow_side[2] = r_blue_side[2];
	yellow_side[5] = r_blue_side[5];
	yellow_side[8] = r_blue_side[8];

	blue_side[2] = r_white_side[2];
	blue_side[5] = r_white_side[5];
	blue_side[8] = r_white_side[8];

	white_side[2] = r_green_side[6];
	white_side[5] = r_green_side[3];
	white_side[8] = r_green_side[0];

	green_side[6] = r_yellow_side[2];
	green_side[3] = r_yellow_side[5];
	green_side[0] = r_yellow_side[8];

	for(int x = 0; x < 9; x++)
	{
		r_orange_side[x] = orange_side[x];
	}

	orange_side[0] = r_orange_side[2];
	orange_side[1] = r_orange_side[5];
	orange_side[2] = r_orange_side[8];
	orange_side[3] = r_orange_side[1];
	orange_side[4] = r_orange_side[4];
	orange_side[5] = r_orange_side[7];
	orange_side[6] = r_orange_side[0];
	orange_side[7] = r_orange_side[3];
	orange_side[8] = r_orange_side[6];
}
void down()
{
	Serial.print("D, ");
	
	if (sim_only == false)
	{
		hold_cube();
		rotate_one();
		release_cube();
		rotate_two();
		push_cube();
		rotate_one();
		push_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_white_side[9];
	char r_orange_side[9];
	char r_red_side[9];
	char r_green_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	orange_side[8] = r_yellow_side[6];
	orange_side[5] = r_yellow_side[7];
	orange_side[2] = r_yellow_side[8];

	yellow_side[6] = r_red_side[0];
	yellow_side[7] = r_red_side[3];
	yellow_side[8] = r_red_side[6];

	red_side[0] = r_white_side[2];
	red_side[3] = r_white_side[1];
	red_side[6] = r_white_side[0];

	white_side[0] = r_orange_side[2];
	white_side[1] = r_orange_side[5];
	white_side[2] = r_orange_side[8];

	for(int x = 0; x < 9; x++)
	{
		r_green_side[x] = green_side[x];
	}
	// reassign colours on face
	green_side[0] = r_green_side[6];
	green_side[1] = r_green_side[3];
	green_side[2] = r_green_side[0];
	green_side[3] = r_green_side[7];
	green_side[4] = r_green_side[4];
	green_side[5] = r_green_side[1];
	green_side[6] = r_green_side[8];
	green_side[7] = r_green_side[5];
	green_side[8] = r_green_side[2];
}
void down_inverted()
{
	Serial.print("D', ");
	
	if (sim_only == false)
	{
		hold_cube();
		rotate_three();
		release_cube();
		rotate_two();
		push_cube();
		rotate_three();
		push_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_white_side[9];
	char r_orange_side[9];
	char r_red_side[9];
	char r_green_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	yellow_side[6] = r_orange_side[8];
	yellow_side[7] = r_orange_side[5];
	yellow_side[8] = r_orange_side[2];

	red_side[0] = r_yellow_side[6];
	red_side[3] = r_yellow_side[7];
	red_side[6] = r_yellow_side[8];

	white_side[0] = r_red_side[6];
	white_side[1] = r_red_side[3];
	white_side[2] = r_red_side[0];

	orange_side[2] = r_white_side[0];
	orange_side[5] = r_white_side[1];
	orange_side[8] = r_white_side[2];

	for(int x = 0; x < 9; x++)
	{
		r_green_side[x] = green_side[x];
	}

	green_side[0] = r_green_side[2];
	green_side[1] = r_green_side[5];
	green_side[2] = r_green_side[8];
	green_side[3] = r_green_side[1];
	green_side[4] = r_green_side[4];
	green_side[5] = r_green_side[7];
	green_side[6] = r_green_side[0];
	green_side[7] = r_green_side[3];
	green_side[8] = r_green_side[6];
}
void up()
{
	Serial.print("U, ");
	
	if (sim_only == false)
	{
		push_cube();
		push_cube();
		hold_cube();
		rotate_one();
		release_cube();
		rotate_two();
		push_cube();
		rotate_one();
		push_cube();
		rotate_two();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_white_side[9];
	char r_orange_side[9];
	char r_red_side[9];
	char r_blue_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	yellow_side[0] = r_orange_side[6];
	yellow_side[1] = r_orange_side[3];
	yellow_side[2] = r_orange_side[0];

	red_side[2] = r_yellow_side[0];
	red_side[5] = r_yellow_side[1];
	red_side[8] = r_yellow_side[2];

	white_side[6] = r_red_side[8];
	white_side[7] = r_red_side[5];
	white_side[8] = r_red_side[2];

	orange_side[0] = r_white_side[6];
	orange_side[3] = r_white_side[7];
	orange_side[6] = r_white_side[8];

	for(int x = 0; x < 9; x++)
	{
		r_blue_side[x] = blue_side[x];
	}

	blue_side[0] = r_blue_side[6];
	blue_side[1] = r_blue_side[3];
	blue_side[2] = r_blue_side[0];
	blue_side[3] = r_blue_side[7];
	blue_side[4] = r_blue_side[4];
	blue_side[5] = r_blue_side[1];
	blue_side[6] = r_blue_side[8];
	blue_side[7] = r_blue_side[5];
	blue_side[8] = r_blue_side[2];
}
void up_inverted()
{
	Serial.print("U', ");
	
	if (sim_only == false)
	{
		push_cube();
		push_cube();
		hold_cube();
		rotate_three();
		release_cube();
		rotate_two();
		push_cube();
		rotate_three();
		push_cube();
		rotate_two();
		push_cube();
	}

	// Cube simulation
	char r_yellow_side[9];
	char r_white_side[9];
	char r_orange_side[9];
	char r_red_side[9];
	char r_blue_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_yellow_side[i] = yellow_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_white_side[i] = white_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	orange_side[6] = r_yellow_side[0];
	orange_side[3] = r_yellow_side[1];
	orange_side[0] = r_yellow_side[2];

	yellow_side[0] = r_red_side[2];
	yellow_side[1] = r_red_side[5];
	yellow_side[2] = r_red_side[8];

	red_side[2] = r_white_side[8];
	red_side[5] = r_white_side[7];
	red_side[8] = r_white_side[6];

	white_side[8] = r_orange_side[6];
	white_side[7] = r_orange_side[3];
	white_side[6] = r_orange_side[0];

	for(int x = 0; x < 9; x++)
	{
		r_blue_side[x] = blue_side[x];
	}

	blue_side[0] = r_blue_side[2];
	blue_side[1] = r_blue_side[5];
	blue_side[2] = r_blue_side[8];
	blue_side[3] = r_blue_side[1];
	blue_side[4] = r_blue_side[4];
	blue_side[5] = r_blue_side[7];
	blue_side[6] = r_blue_side[0];
	blue_side[7] = r_blue_side[3];
	blue_side[8] = r_blue_side[6];
}
void front()
{
	Serial.print("F, ");
	
	if (sim_only == false)
	{
	push_cube();
	push_cube();
	push_cube();
	hold_cube();
	rotate_one();
	release_cube();
	rotate_two();
	push_cube();
	rotate_one();
	push_cube();
	rotate_two();
	}

	// Cube simulation
	char r_blue_side[9];
	char r_orange_side[9];
	char r_green_side[9];
	char r_red_side[9];
	char r_yellow_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	blue_side[6] = r_red_side[6];
	blue_side[7] = r_red_side[7];
	blue_side[8] = r_red_side[8];

	red_side[6] = r_green_side[6];
	red_side[7] = r_green_side[7];
	red_side[8] = r_green_side[8];

	green_side[6] = r_orange_side[6];
	green_side[7] = r_orange_side[7];
	green_side[8] = r_orange_side[8];

	orange_side[6] = r_blue_side[6];
	orange_side[7] = r_blue_side[7];
	orange_side[8] = r_blue_side[8];


	for(int x = 0; x < 9; x++)
	{
		r_yellow_side[x] = yellow_side[x];
	}

	yellow_side[0] = r_yellow_side[6];
	yellow_side[1] = r_yellow_side[3];
	yellow_side[2] = r_yellow_side[0];
	yellow_side[3] = r_yellow_side[7];
	yellow_side[4] = r_yellow_side[4];
	yellow_side[5] = r_yellow_side[1];
	yellow_side[6] = r_yellow_side[8];
	yellow_side[7] = r_yellow_side[5];
	yellow_side[8] = r_yellow_side[2];
}
void front_inverted()
{
	Serial.print("F', ");

	if (sim_only == false)
	{
		push_cube();
		push_cube();
		push_cube();
		hold_cube();
		rotate_three();
		release_cube();
		rotate_two();
		push_cube();
		rotate_three();
		push_cube();
		rotate_two();
	}

	// Cube simulation
	char r_blue_side[9];
	char r_orange_side[9];
	char r_green_side[9];
	char r_red_side[9];
	char r_yellow_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	blue_side[6] = r_orange_side[6];
	blue_side[7] = r_orange_side[7];
	blue_side[8] = r_orange_side[8];

	red_side[6] = r_blue_side[6];
	red_side[7] = r_blue_side[7];
	red_side[8] = r_blue_side[8];

	green_side[6] = r_red_side[6];
	green_side[7] = r_red_side[7];
	green_side[8] = r_red_side[8];

	orange_side[6] = r_green_side[6];
	orange_side[7] = r_green_side[7];
	orange_side[8] = r_green_side[8];

	for(int x = 0; x < 9; x++)
	{
		r_yellow_side[x] = yellow_side[x];
	}

	yellow_side[0] = r_yellow_side[2];
	yellow_side[1] = r_yellow_side[5];
	yellow_side[2] = r_yellow_side[8];
	yellow_side[3] = r_yellow_side[1];
	yellow_side[4] = r_yellow_side[4];
	yellow_side[5] = r_yellow_side[7];
	yellow_side[6] = r_yellow_side[0];
	yellow_side[7] = r_yellow_side[3];
	yellow_side[8] = r_yellow_side[6];
}
void back()
{
	Serial.print("B, ");
	if (sim_only == false)
	{
		push_cube();
		hold_cube();
		rotate_one(); // ccw
		release_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
		rotate_three(); //cw
		push_cube();
		rotate_two();
	}

	// Cube simulation
	char r_blue_side[9];
	char r_orange_side[9];
	char r_green_side[9];
	char r_red_side[9];
	char r_white_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	blue_side[0] = r_orange_side[0];
	blue_side[1] = r_orange_side[1];
	blue_side[2] = r_orange_side[2];

	red_side[0] = r_blue_side[0];
	red_side[1] = r_blue_side[1];
	red_side[2] = r_blue_side[2];

	green_side[0] = r_red_side[0];
	green_side[1] = r_red_side[1];
	green_side[2] = r_red_side[2];

	orange_side[0] = r_green_side[0];
	orange_side[1] = r_green_side[1];
	orange_side[2] = r_green_side[2];

	for(int x = 0; x < 9; x++)
	{
		r_white_side[x] = white_side[x];
	}

	white_side[0] = r_white_side[6];
	white_side[1] = r_white_side[3];
	white_side[2] = r_white_side[0];
	white_side[3] = r_white_side[7];
	white_side[4] = r_white_side[4];
	white_side[5] = r_white_side[1];
	white_side[6] = r_white_side[8];
	white_side[7] = r_white_side[5];
	white_side[8] = r_white_side[2];
}
void back_inverted()
{
	Serial.print("B', ");

	if (sim_only == false)
	{
		push_cube();
		hold_cube();
		rotate_three();
		release_cube();
		rotate_two();
		push_cube();
		push_cube();
		push_cube();
		rotate_one();
		push_cube();
		rotate_two();
	}

	// Cube simulation
	char r_blue_side[9];
	char r_orange_side[9];
	char r_green_side[9];
	char r_red_side[9];
	char r_white_side[9];
	for(int i = 0; i < 9; i++)
	{
		r_blue_side[i] = blue_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_orange_side[i] = orange_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_green_side[i] = green_side[i];
	}
	for(int i = 0; i < 9; i++)
	{
		r_red_side[i] = red_side[i];
	}

	blue_side[0] = r_red_side[0];
	blue_side[1] = r_red_side[1];
	blue_side[2] = r_red_side[2];

	red_side[0] = r_green_side[0];
	red_side[1] = r_green_side[1];
	red_side[2] = r_green_side[2];

	green_side[0] = r_orange_side[0];
	green_side[1] = r_orange_side[1];
	green_side[2] = r_orange_side[2];

	orange_side[0] = r_blue_side[0];
	orange_side[1] = r_blue_side[1];
	orange_side[2] = r_blue_side[2];

	for(int x = 0; x < 9; x++)
	{
		r_white_side[x] = white_side[x];
	}

	white_side[0] = r_white_side[2];
	white_side[1] = r_white_side[5];
	white_side[2] = r_white_side[8];
	white_side[3] = r_white_side[1];
	white_side[4] = r_white_side[4];
	white_side[5] = r_white_side[7];
	white_side[6] = r_white_side[0];
	white_side[7] = r_white_side[3];
	white_side[8] = r_white_side[6];
}
void flip_cube(char cube_rotation)	// flips the cube on the F or U axis
{
	switch(cube_rotation)
	{
		char r_blue_side[9];
		char r_orange_side[9];
		char r_green_side[9];
		char r_red_side[9];
		char r_white_side[9];
		char r_yellow_side[9];
		case 'F': // CW on F
			Serial.print("[Cube Flip: CW on F], ");
			// physical movements
			rotate_one();
			push_cube();
			rotate_two();
			
			// cube simulation
			for(int i = 0; i < 9; i++)	
			{
				r_blue_side[i] = blue_side[i];
			}
			for(int i = 0; i < 9; i++)	
			{
				r_orange_side[i] = orange_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_green_side[i] = green_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_red_side[i] = red_side[i];
			}
		
			for(int x = 0; x < 9; x++)
			{
				r_white_side[x] = white_side[x];
			}
			for(int x = 0; x < 9; x++)
			{
				r_yellow_side[x] = yellow_side[x];
			}

			// assign copies to real faces
			for(int i = 0; i < 9; i++)
			{
				orange_side[i] = r_blue_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				green_side[i] = r_orange_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				red_side[i] = r_green_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				blue_side[i] = r_red_side[i];
			}
		
			white_side[0] = r_white_side[2];
			white_side[1] = r_white_side[5];
			white_side[2] = r_white_side[8];
			white_side[3] = r_white_side[1];
			white_side[4] = r_white_side[4];
			white_side[5] = r_white_side[7];
			white_side[6] = r_white_side[0];
			white_side[7] = r_white_side[3];
			white_side[8] = r_white_side[6];
			
			yellow_side[0] = r_yellow_side[6];
			yellow_side[1] = r_yellow_side[3];
			yellow_side[2] = r_yellow_side[0];
			yellow_side[3] = r_yellow_side[7];
			yellow_side[4] = r_yellow_side[4];
			yellow_side[5] = r_yellow_side[1];
			yellow_side[6] = r_yellow_side[8];
			yellow_side[7] = r_yellow_side[5];
			yellow_side[8] = r_yellow_side[2];
			break;
		case 'f': // CCW on F
			Serial.print("[Cube Flip: CCW on F], ");
			
			rotate_three();
			push_cube();
			rotate_two();
			
			// assign colors to a copy of the face
			for(int i = 0; i < 9; i++)
			{
				r_blue_side[i] = blue_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_orange_side[i] = orange_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_green_side[i] = green_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_red_side[i] = red_side[i];
			}
		
			for(int x = 0; x < 9; x++)
			{
				r_white_side[x] = white_side[x];
			}
			for(int x = 0; x < 9; x++)
			{
				r_yellow_side[x] = yellow_side[x];
			}

			// assign copies to real faces
			for(int i = 0; i < 9; i++)
			{
				red_side[i] = r_blue_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				blue_side[i] = r_orange_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				orange_side[i] = r_green_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				green_side[i] = r_red_side[i];
			}

			yellow_side[0] = r_yellow_side[2];
			yellow_side[1] = r_yellow_side[5];
			yellow_side[2] = r_yellow_side[8];
			yellow_side[3] = r_yellow_side[1];
			yellow_side[4] = r_yellow_side[4];
			yellow_side[5] = r_yellow_side[7];
			yellow_side[6] = r_yellow_side[0];
			yellow_side[7] = r_yellow_side[3];
			yellow_side[8] = r_yellow_side[6];
			
			white_side[0] = r_white_side[6];
			white_side[1] = r_white_side[3];
			white_side[2] = r_white_side[0];
			white_side[3] = r_white_side[7];
			white_side[4] = r_white_side[4];
			white_side[5] = r_white_side[1];
			white_side[6] = r_white_side[8];
			white_side[7] = r_white_side[5];
			white_side[8] = r_white_side[2];
			
			break;
		case 'U': // CW on U
			
			Serial.print("[Cube Flip: CW on U], ");

			push_cube();
			rotate_one();
			push_cube();
			rotate_two();
			push_cube();
			push_cube();
			push_cube();
			
			
			for(int i = 0; i < 9; i++)
			{
				r_white_side[i] = white_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_orange_side[i] = orange_side[i];
				
			}
			for(int i = 0; i < 9; i++)
			{
				r_yellow_side[i] = yellow_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_red_side[i] = red_side[i];
			}
		
			for(int x = 0; x < 9; x++)
			{
				r_blue_side[x] = blue_side[x];
			}
			for(int x = 0; x < 9; x++)
			{
				r_green_side[x] = green_side[x];
			}
			
			orange_side[0] = r_white_side[8];
			orange_side[1] = r_white_side[7];
			orange_side[2] = r_white_side[6];
			orange_side[3] = r_white_side[5];
			orange_side[4] = r_white_side[4];
			orange_side[5] = r_white_side[3];
			orange_side[6] = r_white_side[2];
			orange_side[7] = r_white_side[1];
			orange_side[8] = r_white_side[0];
			
			
			yellow_side[0] = r_orange_side[6];
			yellow_side[1] = r_orange_side[3];
			yellow_side[2] = r_orange_side[0];
			yellow_side[3] = r_orange_side[7];
			yellow_side[4] = r_orange_side[4];
			yellow_side[5] = r_orange_side[1];
			yellow_side[6] = r_orange_side[8];
			yellow_side[7] = r_orange_side[5];
			yellow_side[8] = r_orange_side[2];
			
			white_side[8] = r_red_side[6];
			white_side[7] = r_red_side[3];
			white_side[6] = r_red_side[0];
			white_side[5] = r_red_side[7];
			white_side[4] = r_red_side[4];
			white_side[3] = r_red_side[1];
			white_side[2] = r_red_side[8];
			white_side[1] = r_red_side[5];
			white_side[0] = r_red_side[2];
			
			red_side[6] = r_yellow_side[0];
			red_side[3] = r_yellow_side[1];
			red_side[0] = r_yellow_side[2];
			red_side[7] = r_yellow_side[3];
			red_side[4] = r_yellow_side[4];
			red_side[1] = r_yellow_side[5];
			red_side[8] = r_yellow_side[6];
			red_side[5] = r_yellow_side[7];
			red_side[2] = r_yellow_side[8];
		
			green_side[0] = r_green_side[2];
			green_side[1] = r_green_side[5];
			green_side[2] = r_green_side[8];
			green_side[3] = r_green_side[1];
			green_side[4] = r_green_side[4];
			green_side[5] = r_green_side[7];
			green_side[6] = r_green_side[0];
			green_side[7] = r_green_side[3];
			green_side[8] = r_green_side[6];
			
			blue_side[0] = r_blue_side[6];
			blue_side[1] = r_blue_side[3];
			blue_side[2] = r_blue_side[0];
			blue_side[3] = r_blue_side[7];
			blue_side[4] = r_blue_side[4];
			blue_side[5] = r_blue_side[1];
			blue_side[6] = r_blue_side[8];
			blue_side[7] = r_blue_side[5];
			blue_side[8] = r_blue_side[2];
		case 'u':
			Serial.print("[Cube Flip: CCW on U], ");

			push_cube();
			rotate_three();
			push_cube();
			rotate_two();
			push_cube();
			push_cube();
			push_cube();
			
			for(int i = 0; i < 9; i++)
			{
				r_white_side[i] = white_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_orange_side[i] = orange_side[i];
				
			}
			for(int i = 0; i < 9; i++)
			{
				r_yellow_side[i] = yellow_side[i];
			}
			for(int i = 0; i < 9; i++)
			{
				r_red_side[i] = red_side[i];
			}
		
			for(int x = 0; x < 9; x++)
			{
				r_blue_side[x] = blue_side[x];
			}
			for(int x = 0; x < 9; x++)
			{
				r_green_side[x] = green_side[x];
			}
			
			red_side[6] = r_white_side[0];
			red_side[3] = r_white_side[1];
			red_side[0] = r_white_side[2];
			red_side[7] = r_white_side[3];
			red_side[4] = r_white_side[4];
			red_side[1] = r_white_side[5];
			red_side[8] = r_white_side[6];
			red_side[5] = r_white_side[7];
			red_side[2] = r_white_side[8];
			
			
			white_side[0] = r_orange_side[6];
			white_side[1] = r_orange_side[3];
			white_side[2] = r_orange_side[0];
			white_side[3] = r_orange_side[7];
			white_side[4] = r_orange_side[4];
			white_side[5] = r_orange_side[1];
			white_side[6] = r_orange_side[8];
			white_side[7] = r_orange_side[5];
			white_side[8] = r_orange_side[2];
			
			yellow_side[0] = r_red_side[6];
			yellow_side[1] = r_red_side[3];
			yellow_side[2] = r_red_side[0];
			yellow_side[3] = r_red_side[7];
			yellow_side[4] = r_red_side[4];
			yellow_side[5] = r_red_side[1];
			yellow_side[6] = r_red_side[8];
			yellow_side[7] = r_red_side[5];
			yellow_side[8] = r_red_side[2];
		
			orange_side[6] = r_yellow_side[0];
			orange_side[3] = r_yellow_side[1];
			orange_side[0] = r_yellow_side[2];
			orange_side[7] = r_yellow_side[3];
			orange_side[4] = r_yellow_side[4];
			orange_side[1] = r_yellow_side[5];
			orange_side[8] = r_yellow_side[6];
			orange_side[5] = r_yellow_side[7];
			orange_side[2] = r_yellow_side[8];
		
			blue_side[0] = r_blue_side[2];
			blue_side[1] = r_blue_side[5];
			blue_side[2] = r_blue_side[8];
			blue_side[3] = r_blue_side[1];
			blue_side[4] = r_blue_side[4];
			blue_side[5] = r_blue_side[7];
			blue_side[6] = r_blue_side[0];
			blue_side[7] = r_blue_side[3];
			blue_side[8] = r_blue_side[6];
			
			green_side[0] = green_side[6];
			green_side[1] = green_side[3];
			green_side[2] = green_side[0];
			green_side[3] = green_side[7];
			green_side[4] = green_side[4];
			green_side[5] = green_side[1];
			green_side[6] = green_side[8];
			green_side[7] = green_side[5];
			green_side[8] = green_side[2];
			
		default:
			Serial.println("INVALID CUBE ROTATION: SEE < void flip_cube() >");
	}
}

///////////////////// Cube Algorithms ///////////////////////////
void fix_cross_instance_1() // bad pieces up and right
{
	Serial.println();
	Serial.print("	Fix Cross Instance 1: ");

	// only does the sim movements because we aren't using the moves in the function, since they are inefficient (due to higher abstraction)
	sim_only = true;
	right();
	right();
	back();
	up();
	up();
	back_inverted();
	right();
	right();
	sim_only = false;	// bring it back, to avoid problems when using it in the future.

	// The actual, "lower level" movements:
	// R
	rotate_one();
	push_cube();
	rotate_two();
	hold_cube();
	rotate_one();
	release_cube();

	// R
	rotate_two();
	hold_cube();
	rotate_one();
	release_cube();

	// B
	rotate_two();
	push_cube();
	push_cube();
	push_cube();
	hold_cube();
	rotate_one();
	release_cube();

	// U
	rotate_two();
	push_cube();
	push_cube();
	push_cube();
	hold_cube();
	rotate_one();
	release_cube();

	// U
	rotate_two();
	hold_cube();
	rotate_one();
	release_cube();
	//ornage on top
	//green in front

	// B'
	//white
	rotate_two();
	push_cube();
	push_cube();
	push_cube();
	hold_cube();
	rotate_three();
	release_cube();

	// R
	//green
	rotate_two();
	push_cube();
	push_cube();
	push_cube();
	hold_cube();
	rotate_one();
	release_cube();

	// R
	rotate_two();
	hold_cube();
	rotate_one();
	release_cube();




}
void fix_cross_instance_2() // bad pieces up and down
{
	Serial.println();
	Serial.print("	Fix Cross Instance 2: ");
	up();
	up();
	back();
	back();
	down();
	down();
	back();
	back();
	up();
	up();
}
void fix_corners_instance_1() // top left
{
	Serial.println();
	Serial.print("	Fix Corners Instance 1: ");
	up();
	back();
	up_inverted();
}
void fix_corners_instance_2() // top right
{
	Serial.println();
	Serial.print("	Fix Corners Instance 2: ");
	up_inverted();
	back_inverted();
	up();
}
void fix_corners_instance_3()
{
	Serial.println();
	Serial.print("	Fix Corners Instance 3 (bring yellow piece up): ");
	left_inverted();
	back();
	left();
}
void add_edges_instance_1() // 2 left
{
	Serial.println();
	Serial.print("	Add Edges Instance 1: ");
	back_inverted();
	left_inverted();
	back();
	left();
	back();
	up();
	back_inverted();
	up_inverted();
}
void add_edges_instance_2() // 2 right
{
	Serial.println();
	Serial.print("	Add edges Instance 2: ");
	back();
	right();
	back_inverted();
	right_inverted();
	back_inverted();
	up_inverted();
	back();
	up();
}
void add_edges_instance_3()
{
	Serial.println();
	Serial.print("	Add edges Instance 3: " );
	back_inverted();
	up_inverted();
	back();
	up();
	back();
	right();
	back_inverted();
	right_inverted();
}
void white_cross_on_top()
{
	Serial.println();
	Serial.print("	White Cross On Top: ");
	right_inverted();
	back_inverted();
	up_inverted();
	back();
	up();
	right();
}
void finish_white_face_instance_1()
{
	Serial.println();
	Serial.print("	Finish White Face Instance 1: ");
	right();
	back();
	right_inverted();
	back();
	right();
	back();
	back();
	right_inverted();
}
void finish_white_face_instance_2()
{
	Serial.println();
	Serial.print("	Finish White Face Instance 2: ");
	left_inverted();
	back_inverted();
	left();
	back_inverted();
	left_inverted();
	back_inverted();
	back_inverted();
	left();
}
// insert top layer corners
void green_on_right()
{
	Serial.println();
	Serial.print("	Green On Right: ");
	right_inverted();
	up();
	right_inverted();
	down();
	down();
	right();
	up_inverted();
	right_inverted();
	down();
	down();
	right();
	right();
}
void green_on_left()
{
	Serial.println();
	Serial.print("	Green On Left: ");
	left();
	up_inverted();
	left();
	down_inverted();
	down_inverted();
	left_inverted();
	up();
	left();
	down_inverted();
	down_inverted();
	left_inverted();
	left_inverted();
}
// insert top layer edges
void cw_rotation() // can also be used for 4 bad edges
{
	Serial.println();
	Serial.print("	CW Rotation: ");
	right();
	back();
	right_inverted();
	back();
	right();
	back();
	back();
	right_inverted();
	flip_cube('f');// rotate cube: right side = front side
	left_inverted();
	back_inverted();
	left();
	back_inverted();
	left_inverted();
	back_inverted();
	back_inverted();
	left();
	flip_cube('F');// rotate cube back to original state: left side = front side
}
void ccw_rotation()
{
	Serial.println();
	Serial.print("	CCW Rotation: ");
	left_inverted();
	back_inverted();
	left();
	back_inverted();
	left_inverted();
	back_inverted();
	back_inverted();
	left();
	flip_cube('F');// rotate cube: left side = front side
	right();
	back();
	right_inverted();
	back();
	right();
	back();
	back();
	right_inverted();
	flip_cube('f');
}
// miscellaneous algorithms
void warm_up() // do it six times to get back to the original position
{
	Serial.println();
	Serial.print("Warmup: ");
	Serial.print("R', D', R, D");
	//r'
	rotate_one();
	push_cube();
	hold_cube();//
	rotate_two();
	release_cube();
	rotate_three();
	push_cube();
	rotate_two();
	push_cube();
	push_cube();
	push_cube();

	//d'

	hold_cube();//
	rotate_three();
	release_cube();

	//r start here

	rotate_two();
	push_cube();
	rotate_three();
	hold_cube();
	rotate_two();
	release_cube();

	// d

	rotate_three();
	push_cube();
	hold_cube();
	rotate_two();
	release_cube();
	push_cube();
	rotate_one();
	push_cube();
	rotate_two();
	push_cube();
	push_cube();
	push_cube();
}
void superflip() // all edges are opposite (checkered pattern)
{
	Serial.println();
	Serial.println("Superflip: ");
	up();
	up();
	down();
	down();

	left();
	left();
	right();
	right();


	front();
	front();
	back();
	back();
}

																						// test it
void scramble() // random 25 moves
{
	Serial.println();
	Serial.println("Scramble: ");
	int move;
	for(int j = 0; j < 25; j++)
	{
		move = random(1, 12);
		//Serial.println(move);
		switch(move)
		{
			case 1:
				right();
				break;
			case 2:
				right_inverted();
				break;
			case 3:
				left();
				break;
			case 4:
				left_inverted();
				break;
			case 5:
				up();
				break;
			case 6:
				up_inverted();
				break;
			case 7:
				down();
				break;
			case 8:
				down_inverted();
				break;
			case 9:
				front();
				break;
			case 10:
				front_inverted();
				break;
			case 11:
				back();
				break;
			case 12:
				back_inverted();
				break;
		}
	}
}



//////////////////////////////// cube_decide functions, used to determine what algorithms and moves to execute ///////////////////////
// cube_decide variables:
int solve_stage = 1;
bool cube_solved = true;
// cube_decide

void cube_decide_cross() 
{
	Serial.println();
	Serial.println();
	Serial.print("Cross: ");
	if (yellow_side[1] == 'y' &&
	    yellow_side[3] == 'y' &&
	    yellow_side[5] == 'y' &&
	    yellow_side[7] == 'y')
	{
		solve_stage = 2;
		Serial.print("Solved.");
		//test_ongoing = false;
	}
	///////////// move the pieces from the sides up /////////////// /// should turn this into a function later(blue_side, moves)
	else if(solve_stage == 1)
	{
		// move from blue_side[3]
		if (blue_side[3] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[3] != 'y')
				{
					left();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from blue_side[5]
		else if (blue_side[5] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[5] != 'y')
				{
					right_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from red_side[5]
		else if (red_side[5] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[1] != 'y')
				{
					up_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from red_side[3]
		else if (red_side[3] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[7] != 'y')
				{
					down();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from green_side[5]
		else if (green_side[5] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[3] != 'y')
				{
					left_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}

		// move from green_side[3]
		else if (green_side[3] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[5] != 'y')
				{
					right();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from orange_side[5]
		else if (orange_side[5] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[7] != 'y')
				{
					down_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from orange_side[3]
		else if (orange_side[3] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[1] != 'y')
				{
					up();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from white_side[1]
		else if (white_side[1] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[7] != 'y')
				{
					down();
					down();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from white_side[7]
		else if (white_side[7] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[1] != 'y')
				{
					up();
					up();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from white_side[3]
		else if (white_side[3] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[3] != 'y')
				{
					left();
					left();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// move from white_side[5]
		else if (white_side[5] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[5] != 'y')
				{
					right();
					right();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		/////////////////
		//////////////
		///////////////////////// get the piece from 2- move spots, like blue_side[7]
		// blue_side[1]
		else if (blue_side[1] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[1] != 'y')
				{
					up();
					front();
					right_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// blue_side[7]
		else if (blue_side[7] == 'y')
		{
			if (yellow_side[1] != 'y')
			{
				up_inverted();
				front();
				right_inverted();
			}
			else
			{
				up_inverted();
			}
		}
		// red_side[1]
		else if (red_side[1] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[3] != 'y')
				{
					left();
					front();
					up_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// red_side[7]
		else if (red_side[7] == 'y')
		{
			if (yellow_side[3] != 'y')
			{
				left_inverted();
				front();
				up_inverted();
			}
			else
			{
				left_inverted();
			}
		}
		// green_side[1]
		else if (green_side[1] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[7] != 'y')
				{
					down();
					front();
					left_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// green_side[7]
		else if (green_side[7] == 'y')
		{
			if (yellow_side[7] != 'y')
			{
				down();
				front_inverted();
				right();
			}
			else
			{
				down();
			}
		}
		// orange_side[1]
		else if (orange_side[1] == 'y')
		{
			for(int x = 0; x < 3; x++) // rotate cube four times, or until there is an empty space
			{
				if (yellow_side[5] != 'y')
				{
					right();
					front();
					down_inverted();
					x = 3; // end loop since yellow piece has reached the top
				}
				else
				{
					front();
				}
			}
		}
		// green_side[7]
		else if (orange_side[7] == 'y')
		{
			if (yellow_side[5] != 'y')
			{
				right_inverted();
				front();
				down_inverted();
			}
			else
			{
				right_inverted();
			}
		}
	}
}
void cube_decide_whole_cross() 
{
	Serial.println();
	Serial.println();
	Serial.print("Whole Cross: ");
	if (solve_stage == 2 &&
	    blue_side[7] == 'b' &&
	    red_side[7] == 'r' &&
	    green_side[7] == 'g' &&
	    orange_side[7] == 'o')
	{
		Serial.print("Solved.");
		solve_stage = 3;
	}
	// green and orange are good
	else if (solve_stage == 2 && blue_side[7] != 'b' && red_side[7] != 'r' && green_side[7] == 'g' && orange_side[7] == 'o')
	{
		flip_cube('F');
		fix_cross_instance_1();
		flip_cube('f');
	}
	// red and orange are good
	else if (solve_stage == 2 && blue_side[7] != 'b' && red_side[7] == 'r' && green_side[7] != 'g' && orange_side[7] == 'o')
	{
		fix_cross_instance_2();
	}
	// red and green are good
	else if (solve_stage == 2 == true && blue_side[7] != 'b' && red_side[7] == 'r' && green_side[7] == 'g' && orange_side[7] != 'o')
	{
		fix_cross_instance_1();
	}
	// blue and orange are good
	else if (solve_stage == 2 && blue_side[7] == 'b' && red_side[7] != 'r' && green_side[7] != 'g' && orange_side[7] == 'o')
	{
		flip_cube('F');
		flip_cube('F');
		fix_cross_instance_1();
		flip_cube('f');
		flip_cube('f');
	}
	// blue and green are good
	else if (solve_stage == 2 && blue_side[7] == 'b' && red_side[7] != 'r' && green_side[7] == 'g' && orange_side[7] != 'o')
	{
		flip_cube('F');
		fix_cross_instance_2();
		flip_cube('f');
	}
	// red and blue are good
	else if (solve_stage == 2 && blue_side[7] == 'b' && red_side[7] == 'r' && green_side[7] != 'g' && orange_side[7] != 'o')
	{
		flip_cube('f');
		fix_cross_instance_1();
		flip_cube('F');
	}
	// none match, cross in done but whole cross isn't
	else if (solve_stage == 2)
	{
		front();
	}
	else
	{
		Serial.println("Error in whole_cross");
	}
}
void cube_decide_corners() // needs fixing, maybe yellows at bottom portion
{
	Serial.println();
	Serial.println();
	Serial.print("Corners (First Layer): ");
	// First layer is done correctly
	if (solve_stage == 3 && yellow_side[0] == 'y' && blue_side[6] == 'b' && yellow_side[2] == 'y' && orange_side[6] == 'o' && 
		green_side[6] == 'g' && yellow_side[6] == 'y' && orange_side[6] == 'o' && yellow_side[8] == 'y' && red_side[6] == 'r')
	{
		Serial.print("Solved.");
		solve_stage = 4;
	}
	else if(solve_stage == 3)
	{
		////////// if THERE ARE yellow on top
		if (blue_side[0] == 'y' || blue_side[2] == 'y' || red_side[0] == 'y' || red_side[2] == 'y' ||
		    green_side[0] == 'y' || green_side[2] == 'y' || orange_side[0] == 'y' || orange_side[2] == 'y' ||
		    white_side[0] == 'y' || white_side[2] == 'y' || white_side[6] == 'y' || white_side[8] == 'y')
		{
			////////// Do all possible cases for corner (4×3):
			//////// 3 cases for the blue/orange sides
			if (blue_side[2] == 'y' && white_side[8] == 'b' && orange_side[0] == 'o')
			{
				fix_corners_instance_2();
			}
			else if (blue_side[2] == 'o' && white_side[8] == 'y' && orange_side[0] == 'b')
			{
				fix_corners_instance_2();
				fix_corners_instance_2();
				back();
				fix_corners_instance_2();
			}
			else if (blue_side[2] == 'b' && white_side[8] == 'o' && orange_side[0] == 'y')
			{
				flip_cube('f');
				fix_corners_instance_1();
				flip_cube('F');
			}
			//////// 3 cases for the orange/green sides
			else if (orange_side[2] == 'y' && white_side[2] == 'o' && green_side[0] == 'g')
			{
				flip_cube('f');
				fix_corners_instance_2();
				flip_cube('F');
			}
			else if (orange_side[2] == 'g' && white_side[2] == 'y' && green_side[0] == 'o')
			{
				flip_cube('f');
				fix_corners_instance_2();
				fix_corners_instance_2();
				back();
				fix_corners_instance_2();
				flip_cube('F');
			}
			else if (orange_side[2] == 'o' && white_side[2] == 'g' && green_side[0] == 'y')
			{
				flip_cube('F');
				flip_cube('F');
				fix_corners_instance_1();
				flip_cube('f');
				flip_cube('f');
			}
			//////// 3 cases for the green/red sides
			else if (green_side[2] == 'y' && white_side[0] == 'g' && red_side[0] == 'r')
			{
				flip_cube('F');
				flip_cube('F');
				fix_corners_instance_2();
				flip_cube('f');
				flip_cube('f');
			}
			else if (green_side[2] == 'r' && white_side[0] == 'y' && red_side[0] == 'g')
			{
				flip_cube('F');
				flip_cube('F');
				fix_corners_instance_2();
				fix_corners_instance_2();
				back();
				fix_corners_instance_2();
				flip_cube('f');
				flip_cube('f');
			}
			else if (green_side[2] == 'g' && white_side[0] == 'r' && red_side[0] == 'y')
			{
				flip_cube('F');
				fix_corners_instance_1();
				flip_cube('f');
			}
			//////// 3 cases for the red/blue sides
			else if (red_side[2] == 'y' && white_side[6] == 'r' && blue_side[0] == 'b')
			{
				flip_cube('F');
				fix_corners_instance_2();
				flip_cube('f');
			}
			else if (red_side[2] == 'b' && white_side[6] == 'y' && blue_side[0] == 'r')
			{
				fix_corners_instance_1();
				fix_corners_instance_1();
				back_inverted();
				fix_corners_instance_1();
			}
			else if (red_side[2] == 'r' && white_side[6] == 'b' && blue_side[0] == 'y')
			{
				fix_corners_instance_1();
			}
			else
			{
				back();  // move yellow on top of correct position
			}
		}
		////////// if there are NO yellows on top and first layer isn't solved already
		else if (yellow_side[0] != 'y' || red_side[8] != 'r' || blue_side[6] != 'b' ||
				 yellow_side[2] != 'y' || orange_side[6] != 'o' || blue_side[8] != 'b' ||
				 yellow_side[8] != 'y' || orange_side[8] != 'o' || green_side[6] != 'g' ||
				 yellow_side[6] != 'y' || red_side[6] != 'r' || blue_side[8] != 'g')
		{
			//////////// Bring all yellow corners up:
			// Blue and red corner
			if (yellow_side[0] != 'y' || red_side[8] != 'r' || blue_side[6] != 'b')
			{
				fix_corners_instance_3();
			}
			// blue and orange corner
			else if (yellow_side[2] != 'y' || orange_side[6] != 'o' || blue_side[8] != 'b')
			{
				flip_cube('f');
				fix_corners_instance_3();
				flip_cube('F');
			}
			// Orange and green corner
			else if (yellow_side[8] != 'y' || orange_side[8] != 'o' || green_side[6] != 'g')
			{
				flip_cube('f');
				flip_cube('f');
				fix_corners_instance_3();
				flip_cube('F');
				flip_cube('F');
			}
			// Green and red corner
			else if (yellow_side[6] != 'y' || red_side[6] != 'r' || blue_side[8] != 'g')
			{
				flip_cube('F');
				fix_corners_instance_3();
				flip_cube('f');
			}
		}
	
		else
		{
			Serial.println("First Layer not Solved.");
		}
	}	
}
void cube_decide_add_edges()
{
	Serial.println();
	Serial.println();
	Serial.print("Edges (Second Layer): ");
	///// Second layer done
	if (solve_stage == 4 &&
	    green_side[3] == 'g' && green_side[5] == 'g' &&
	    red_side[3] == 'r' && red_side[5] == 'r' &&	
	    blue_side[3] == 'b' && blue_side[5] == 'b' &&
	    orange_side[3] == 'o' && orange_side[5] == 'o')
	{
		Serial.print("Solved.");
		solve_stage = 5;
	}
	else if(solve_stage == 4)
	{
		///// red3 --> 2blue
		if(red_side[1] == 'r' && white_side[3] == 'b')
		{
			flip_cube('F');
			add_edges_instance_2();	// two right
			flip_cube('f');
		}
		///// red2 --> 3blue
		else if(blue_side[1] == 'b' && white_side[7] == 'r')
		{

			add_edges_instance_1();	// two left
		}
	
		//// blue3 --> orange
		else if(blue_side[1] == 'b' && white_side[7] == 'o')
		{
			add_edges_instance_2();	// two right
		}
		//// blue --> 3orange
		else if(orange_side[1] == 'o' && white_side[5] == 'b')
		{
			flip_cube('f');
			add_edges_instance_1();	// two left
			flip_cube('F');
		}
		//// orange3 --> green
		else if(orange_side[1] == 'o' && white_side[5] == 'g')
		{
			flip_cube('f');
			add_edges_instance_2();	// two right
			flip_cube('F');
		}
		//// orange --> 3green
		else if(green_side[1] == 'g' && white_side[1] == 'o')
		{
			flip_cube('F');
			flip_cube('F');
			add_edges_instance_1();	// two left
			flip_cube('f');
			flip_cube('f');
		}
	
		//// green3 --> red
		else if(green_side[1] == 'g' && white_side[1] == 'r')
		{
			flip_cube('F');
			flip_cube('F');
			add_edges_instance_2();	// two right
			flip_cube('f');
			flip_cube('f');
		}
		//// green --> 3red
		else if(red_side[1] == 'r' && white_side[3] == 'g')
		{
			flip_cube('F');
			add_edges_instance_1();	// two left
			flip_cube('f');
		}
		//// // rotate top layer to match any missing colors
		else if (blue_side[3] == 'w' || blue_side[5] == 'w' || red_side[3] == 'w' || red_side[5] == 'w' ||
			green_side[3] == 'w' || green_side[5] == 'w' || orange_side[3] == 'w' || orange_side[5] == 'w')
		{
			back();
		}

		///// bring incorrectly placed edges to the top again
		else if (blue_side[3] != 'b' || red_side[5] != 'r' || 
				 red_side[3] != 'r' || green_side[5] != 'g' ||
		         green_side[3] != 'g' || orange_side[5] != 'o' || 
		         orange_side[3] != 'o' || blue_side[5] != 'b')
		{
			if(blue_side[3] != 'b' || red_side[5] != 'r')
			{
				flip_cube('F');
				add_edges_instance_3();
				flip_cube('f');
			}
			else if(red_side[3] != 'r' || green_side[5] != 'g')
			{
				flip_cube('F');
				flip_cube('F');
				add_edges_instance_3();
				flip_cube('f');
				flip_cube('f');
			}
			else if(green_side[3] != 'g' || orange_side[5] != 'o')
			{
				flip_cube('f');
				add_edges_instance_3();
				flip_cube('F');
			}
			else if(orange_side[3] != 'o' || blue_side[5] != 'b')
			{
				add_edges_instance_3();
			}
		}
		else
		{
			Serial.println("second layer not solved.");
		}
	}
}
void cube_decide_white_cross() // looking for two whites, may be more efficient, but current revision get the job done
{
	Serial.println();
	Serial.println();
	Serial.print("White Cross: ");
	if (solve_stage == 5 &&
	    white_side[1] == 'w' &&
	    white_side[3] == 'w' &&
	    white_side[5] == 'w' &&
	    white_side[7] == 'w')
	{
		Serial.print("Solved.");
		solve_stage = 6;
	}
	else if (blue_side[1] == 'w' || red_side[1] == 'w' || green_side[1] == 'w' || orange_side[1] == 'w')
	{
		/// whties in connecting faces
		if(blue_side[1] == 'w' && orange_side[1] == 'w')
		{
			white_cross_on_top();
		}
		else if(orange_side[1] == 'w' && green_side[1] == 'w')
		{
			back();
			white_cross_on_top();
		}
		else if(green_side[1] == 'w' && red_side[1] == 'w')
		{
			back();
			back();
			white_cross_on_top();
		}
		else if(red_side[1] == 'w' && blue_side[1] == 'w')
		{
			back_inverted();
			white_cross_on_top();
		}
		/// whites not on connecting face
		else if(blue_side[1] == 'w')
		{
			white_cross_on_top();
		}
		else if(green_side[1] == 'w')
		{
			back();
			back();
			white_cross_on_top();
		}
		else if(red_side[1] == 'w')
		{
			back_inverted();
			white_cross_on_top();
		}
		else if(orange_side[1] == 'w')
		{
			back();
			white_cross_on_top();
		}
		else
		{
			Serial.println("No white cross");
		}
	}
}
void cube_decide_white_top()
{
	Serial.println();
	Serial.println();
	Serial.print("White Face: ");
	if (white_side[0] == 'w' &&
	    white_side[2] == 'w' &&
	    white_side[6] == 'w' &&
	    white_side[8] == 'w')
	{
		Serial.print("Solved.");
		solve_stage = 7;
	}
	else if(solve_stage == 6)
	{
		/////////////////////////////////// sune cases
		if (white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] == 'w' ||
		    white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] != 'w' ||
		    white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] != 'w' ||
		    white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] != 'w')
		{
			// Any sune orientation is true
			/////////////////// left sune cases:
			if (white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] == 'w' && red_side[0] == 'w' && blue_side[0] == 'w')
			{
				finish_white_face_instance_2();	// left sune
			}
			else if(white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] != 'w' && blue_side[0] == 'w' && orange_side[0] == 'w')
			{
				back();
				finish_white_face_instance_2(); // left sune
			}
			else if(white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] != 'w' && orange_side[0] == 'w' && green_side[0] == 'w')
			{
				back();
				back();
				finish_white_face_instance_2(); // left sune
			}
			else if(white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] != 'w' && green_side[0] == 'w' && red_side[0] == 'w')
			{
				back_inverted();
				finish_white_face_instance_2(); // left sune
			}
			////////////////// right sune cases:
			else if (white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] != 'w' && orange_side[2] == 'w' && blue_side[2] == 'w')
			{
				finish_white_face_instance_1(); // right sune
			}
			else if(white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] != 'w' && blue_side[2] == 'w' && red_side[2] == 'w')
			{
				back_inverted();
				finish_white_face_instance_1(); // right sune
			}
			else if(white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] != 'w' && red_side[2] == 'w' && green_side[2] == 'w')
			{
				back();
				back();
				finish_white_face_instance_1(); // right sune
			}
			else if(white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] == 'w' && orange_side[2] == 'w' && green_side[2] == 'w')
			{
				back();
				finish_white_face_instance_1(); // right sune
			}
			else
			{
				Serial.println("We are sune-less!");
			}
		}
		/// blinker or car
		else if (white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] != 'w')
		{
			// car
			if (red_side[0] == 'w' && red_side[2] == 'w' && orange_side[0] == 'w' && orange_side[2] == 'w')
			{
				finish_white_face_instance_1();
			}
			else if (blue_side[0] == 'w' && blue_side[2] == 'w' && green_side[0] == 'w' && green_side[2] == 'w')
			{
				back();
				finish_white_face_instance_1();
			}
			// blinker
			if (red_side[0] == 'w' && red_side[2] == 'w' && blue_side[2] == 'w' && green_side[0] == 'w')
			{
				finish_white_face_instance_1();
			}
			else if(blue_side[0] == 'w' && blue_side[2] == 'w' && red_side[0] == 'w' && orange_side[2] == 'w')
			{
				back();
				finish_white_face_instance_1();
			}
			else if(orange_side[0] == 'w' && orange_side[2] == 'w' && blue_side[0] == 'w' && green_side[2] == 'w')
			{
				finish_white_face_instance_2();
			}
			else if(green_side[0] == 'w' && green_side[2] == 'w' && orange_side[0] == 'w' && red_side[2] == 'w')
			{
				back_inverted();
				finish_white_face_instance_1();
			}
		}
		//////// bowtie
		if (white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] != 'w' && white_side[8] == 'w' ||
		    white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] == 'w' && white_side[8] != 'w')
		{
			if (blue_side[0] == 'w' && orange_side[2] == 'w')
			{
				finish_white_face_instance_1();
			}
			else if (red_side[0] == 'w' && blue_side[2] == 'w')
			{
				back_inverted();
				finish_white_face_instance_1();
			}
			if (green_side[0] == 'w' && red_side[2] == 'w')
			{
				back_inverted();
				back_inverted();
				finish_white_face_instance_1();
			}
			if (orange_side[0] == 'w' && green_side[2] == 'w')
			{
				back();
				finish_white_face_instance_1();
			}
		}
		/////// chameleon
		if (white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] == 'w' ||
		    white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] == 'w' ||
		    white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] != 'w' ||
		    white_side[0] == 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] != 'w')
		{
			if (white_side[0] == 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] != 'w')
			{
				finish_white_face_instance_1();
			}
			else if (white_side[0] != 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] == 'w')
			{
				back();
				back();
				finish_white_face_instance_1();
			}
			else if (white_side[0] != 'w' && white_side[2] == 'w' && white_side[6] != 'w' && white_side[8] == 'w')
			{
				back_inverted();
				finish_white_face_instance_1();
			}
			else if (white_side[0] == 'w' && white_side[2] != 'w' && white_side[6] == 'w' && white_side[8] != 'w')
			{
				back();
				finish_white_face_instance_1();
			}
		}
	}
}
void cube_decide_oll()
{
	Serial.println();
	Serial.println();
	Serial.print("OLL: ");
	// 
	if (green_side[0] == 'o' && green_side[2] == 'o' && red_side[0] == 'g' && red_side[2] == 'g' &&
	   	blue_side[0] == 'r' && blue_side[2] == 'r' && orange_side[0] == 'b' && orange_side[2] == 'b')
	{
		back();
	}
	else if(green_side[0] == 'b' && green_side[2] == 'b' && red_side[0] == 'o' && red_side[2] == 'o' &&
	   		blue_side[0] == 'g' && blue_side[2] == 'g' && orange_side[0] == 'r' && orange_side[2] == 'r')
	{
		back();
		back();
	}
	else if(green_side[0] == 'r' && green_side[2] == 'r' && red_side[0] == 'b' && red_side[2] == 'b' &&
	   	    blue_side[0] == 'o' && blue_side[2] == 'o' && orange_side[0] == 'g' && orange_side[2] == 'g')
	{
		back_inverted();
	}
	
	if (green_side[0] == 'g' && green_side[2] == 'g' && red_side[0] == 'r' && red_side[2] == 'r' &&
	   	blue_side[0] == 'b' && blue_side[2] == 'b' && orange_side[0] == 'o' && orange_side[2] == 'o')
	{
		Serial.print("Solved.");
		solve_stage = 8;
	}

	else if(solve_stage == 7)
	{
		// green on right cases
		if (blue_side[0] == 'b' && blue_side[2] == 'g' && orange_side[2] == 'b')
		{
			green_on_right();
		}
		else if (red_side[0] == 'b' && red_side[2] == 'g' && blue_side[2] == 'b')
		{
			back_inverted();
			green_on_right();
		}
		else if (green_side[0] == 'b' && green_side[2] == 'g' && red_side[2] == 'b')
		{
			back();
			back();
			green_on_right();
		}
		else if (orange_side[0] == 'b' && orange_side[2] == 'g' && green_side[2] == 'b')
		{
			back();
			green_on_right();
		}

		// green on left cases
		else if (blue_side[0] == 'g' && blue_side[2] == 'b' && red_side[0] == 'b')
		{
			green_on_left();
		}
		else if (red_side[0] == 'g' && red_side[2] == 'b' && green_side[0] == 'b')
		{
			back_inverted();
			green_on_left();
		}
		else if (green_side[0] == 'g' && green_side[2] == 'b' && orange_side[0] == 'b')
		{
			back();
			back();
			green_on_left();
		}
		else if (orange_side[0] == 'g' && orange_side[2] == 'b' && blue_side[0] == 'b')
		{
			back();
			green_on_left();
		}
		// last resort, 2 steps to reach PLL are needed
		// green on right
		else 
		{
			Serial.println("last resort");
			if (blue_side[2] == 'g')
			{
				green_on_right();
			}
			else if(orange_side[2] == 'g')
			{
				back();
				green_on_right();
			}
			else if(green_side[2] == 'g')
			{
				back();
				back();
				green_on_right();
			}
			else if(red_side[2] == 'g')
			{
				back_inverted();
				green_on_right();
			}
			// green on left
			else if (blue_side[0] == 'g')
			{
				green_on_left();
			}
			else if(orange_side[0] == 'g')
			{
				back();
				green_on_left();
			}
			else if(green_side[0] == 'g')
			{
				back();
				back();
				green_on_left();
			}
			else if(red_side[0] == 'g')
			{
				back_inverted();
				green_on_left();
			}
		}
	}

}
void cube_decide_pll()
{
	Serial.println();
	Serial.println();
	Serial.print("PLL: ");
	///////////////////////////////////
	if (blue_side[1] == 'b' && red_side[1] == 'r' && green_side[1] == 'g' && orange_side[1] == 'o')
	{
		Serial.print("Solved.");
		solve_stage = 9;
	}
	else if (solve_stage == 8)
	{	
		Serial.println("inside");
		// counter clockwise rotation cases
		if (red_side[1] == 'b' && blue_side[1] == 'o' && orange_side[1] == 'r')
		{
			ccw_rotation();
		}
		else if (green_side[1] == 'r' && red_side[1] == 'b' && blue_side[1] == 'g')
		{
			flip_cube('F');
			ccw_rotation();
			flip_cube('f');
		}
		else if (orange_side[1] == 'g' && green_side[1] == 'r' && red_side[1] == 'o')
		{
			flip_cube('F');
			flip_cube('F');
			ccw_rotation();
			flip_cube('F');
			flip_cube('F');
		}
		else if (blue_side[1] == 'o' && orange_side[1] == 'g' && green_side[1] == 'b')
		{
			flip_cube('f');
			ccw_rotation();
			flip_cube('F');
		}

		// clockwise rotation cases
		else if (red_side[1] == 'o' && blue_side[1] == 'r' && orange_side[1] == 'b')
		{
			cw_rotation();
		}
		else if (green_side[1] == 'b' && red_side[1] == 'g' && blue_side[1] == 'r')
		{
			flip_cube('F');
			cw_rotation();
			flip_cube('f');
		}
		else if (orange_side[1] == 'r' && green_side[1] == 'o' && red_side[1] == 'g')
		{
			flip_cube('F');
			flip_cube('F');
			cw_rotation();
			flip_cube('F');
			flip_cube('F');
		}
		else if (blue_side[1] == 'g' && orange_side[1] == 'b' && green_side[1] == 'o')
		{
			flip_cube('f');
			cw_rotation();
			flip_cube('F');		
		}
		// all four edges are bad
		else if (blue_side[1] != 'b' && red_side[1] != 'r' && green_side[1] != 'g' && orange_side[1] != 'o')
		{
			cw_rotation();
		}
		else	// there is a problem here
		{
			Serial.println("Problem in Pll (else statement reached)");
		}
	}
	else
	{	
		Serial.println("Error in pll_case_check()");
	}
}
void cube_decide_solved()
{
	Serial.println();
	Serial.println();

	// check if all sides have the correct color 
	for(int i = 0; i < 9; i++)
	{
		if (yellow_side[i] != 'y')
		{
			cube_solved = false;
		}
		if (white_side[i] != 'w')
		{
			cube_solved = false;
		}
		if (blue_side[i] != 'b')
		{
			cube_solved = false;
		}
		if (red_side[i] != 'r')
		{
			cube_solved = false;
		}
		if (green_side[i] != 'g')
		{
			cube_solved = false;
		}
		if (orange_side[i] != 'o')
		{
			cube_solved = false;
		}
	}
	if (cube_solved == true)
	{
		Serial.println("The Whole Cube is solved!!!");
	}
	else
	{
		Serial.println("There is a problem: the cube isn't solved!");
		cube_solved = false;
	}
	print_whole_cube();
	solve_stage = 10;
}

// goes through cube_decide functions sequentially //

void cube_decide()
{
	switch(solve_stage)
	{
		case 1:
			// Cross
			cube_decide_cross();
			break;
		case 2:
			// Whole Cross
			cube_decide_whole_cross();
			break;
		case 3:
			// First layer (corners)
			cube_decide_corners();
			
			break;
		case 4:
			// Second Layer
			cube_decide_add_edges();
			break;
		case 5:
		// White Cross
		cube_decide_white_cross();
			break;
		case 6:
			// White Top
			cube_decide_white_top();
			break;
		case 7:
			// Orientation of the Last Layer
			cube_decide_oll();
			break;
		case 8:
			// Permute the Last Layer
			cube_decide_pll();
			break;
		case 9:
			cube_decide_solved();
			break;
	}

}

//////////// run these on main loop ////////////////////

void auto_test()
{
	int num_of_tests_ran = 1;
	while(test_ongoing == true)
	{
		Serial.println();
		Serial.println();
		Serial.println();
		Serial.print("Test number: ");
		Serial.print(num_of_tests_ran);
		scramble();
		delay(10000);
		print_whole_cube();
		solve_stage = 1;
		// solve the cube
		while(solve_stage != 10)
		{
			cube_decide();
		}
		
		// check if solved
		if (cube_solved == false)
		{
			test_ongoing = false;
		}
		else
		{
			num_of_tests_ran++;
		}
	}
	Serial.println();
	Serial.println();
	Serial.println();
	Serial.print("Error found, test ended at Test number:");
	Serial.print(num_of_tests_ran);
}

void single_run()
{
	print_whole_cube();
	solve_stage = 1;
	// solve the cube
	while(solve_stage != 10)
	{
		cube_decide();
	}
}

// test rotation servo
void rotation_test()
{
	/*
	rotate_one();
	//hold_cube();
	//release_cube();
	push_cube();

	rotate_two();
	//hold_cube();
	//release_cube();
	push_cube();

	rotate_three();
	//hold_cube();
	//release_cube();
	push_cube();
	*/
	
	//
	rotate_one();
	hold_cube();
	rotate_two();
	release_cube();
	push_cube();

	rotate_two();
	hold_cube();
	rotate_one();
	release_cube();
	push_cube();
	
	rotate_two();
	hold_cube();
	rotate_three();
	release_cube();
	push_cube();
	
	rotate_three();
	hold_cube();
	rotate_two();
	release_cube();
	push_cube();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// PROGRAM START ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
	rotate_servo.attach(9);  // attaches the servo on pin 9 to the servo object
	push_servo.attach(5);  // attaches the servo on pin 6 to the servo object
	rotate_servo.write(rotate_pos);
	push_servo.write(push_pos);
	delay(1000);
	Serial.begin(9600);
	while (! Serial); // Wait untilSerial is ready
	//assign_to_current(yellow_side);
	//print_cube(current_side);
}

/////////////// Loop //////////////////
void loop()
{
	/*
	//cube_legality_check();
	//print_cube(white_side);
	auto_test();
	//superflip();
	//rotation_test();
	//single_run();
	//print_whole_cube();
	delay(10000000);

	//do_cross();
	//right();
	*/
	import_cube_colors();
};