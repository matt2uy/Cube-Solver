// gets cube face colours from .py through serial monitor
// uses handshake

void setup()
{
  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready
}

char yellow_face[9];
char white_face[9];
char blue_face[9];
char red_face[9];
char green_face[9];
char orange_face[9];

String raw_cube_string = "";

void receive_raw_cube()
{
	char ready_signal = 'r';
	
	// send ready signal
	while(Serial.read() != ready_signal)
	{
		Serial.println(ready_signal);
		delay(10);
	}
			
	Serial.println("here");
	// receive color
	//raw_cube_string = Serial.read();
	//char string = Serial.read();
}

void accept_string()
{
	while(raw_cube_string == "")
	{
		char character;
		while(Serial.available()) 
		{
		    character = Serial.read();
		   	raw_cube_string.concat(character);
		}
		delay(100);
	}
	Serial.print("String Accepted: ");
	Serial.print(raw_cube_string);
}

void parse_raw_cube() // need an input of 54 char length string
{	// convert to char array
	Serial.print("Parsing... ");
	raw_cube_string.toCharArray(yellow_face, sizeof(yellow_face));
	Serial.println("yellow...");
	for(int x = 0; x < 9; x++)
	{
		yellow_face[x] = raw_cube_string[x];
  		Serial.println(yellow_face[x]);
	}
	/*Serial.println("white...");
	for(int x = 9; x < 18; x++)
	{
		white_face[x-9] = raw_cube_string[x];
  		Serial.println(white_face[x-9]);
	}*/
}


void loop()
{

	accept_string();

	parse_raw_cube();
	while(true){}
}