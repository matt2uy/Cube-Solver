// gets cube face colours from .py through serial monitor
// uses handshake

void setup()
{
  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready
}

char yellow_side[9];
char white_side[9];
char blue_side[9];
char red_side[9];
char green_side[9];
char orange_side[9];

String raw_cube_string = "";

void print_cube(char cube_side[])
{
	Serial.println('\r');

	Serial.print("Side: ");
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

void print_whole_cube()
{
	print_cube(yellow_side);
	print_cube(white_side);
	print_cube(blue_side);
	print_cube(red_side);
	print_cube(green_side);
	print_cube(orange_side);
}


void accept_string()
{
	char ready_signal = 'ready';
	char received_signal = 'recieved';
	
	for (int piece_num = 0; piece_num < 54; piece_num++)
	{	
		// send ready signal
		Serial.println(ready_signal);
		delay(5);
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


void loop()
{

	accept_string();

	parse_raw_cube();
	print_whole_cube();
	while(true){}
}