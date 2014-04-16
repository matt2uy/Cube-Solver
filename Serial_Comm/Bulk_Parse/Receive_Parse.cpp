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

String raw_cube_string = "abcdefghi";

void receive_raw_cube()
{
	char ready_signal = 'r';
	
	// send ready signal
	while(Serial.read() != ready_signal)
	{
		Serial.println(ready_signal);
	}
			

	// receive color
	//raw_cube_string = Serial.read();
	//char string = Serial.read();
	while(true)
	{
		Serial.println("string");
	}
}

void parse_raw_cube()
{	// convert to char array
	raw_cube_string.toCharArray(yellow_face, sizeof(yellow_face));
	for(int x = 0; x < 9; x++)
	{
		yellow_face[x] = raw_cube_string[x];
  		Serial.println(raw_cube_string[x]);
	}
}


void loop()
{
	receive_raw_cube();
	//parse_raw_cube();
	
	while(true)
	{
		// do nothing
	}
}