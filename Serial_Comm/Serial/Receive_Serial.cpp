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

void receive_face(char cube_face[])
{
	char ready_signal = 'ready';
	char received_signal = 'recieved';
	
	for (int piece_num = 0; piece_num < 9; piece_num++)
	{	
		// send ready signal
		Serial.println(ready_signal);
		delay(10);
			
		// receive color
		cube_face[piece_num] = Serial.read();
		delay(10);

		// send color confirmed signal
		Serial.println(received_signal);
		delay(10);
	}
}

void receive_whole_cube()
{
	receive_face(yellow_face);
	receive_face(white_face);
	receive_face(blue_face);
	receive_face(red_face);
	receive_face(green_face);
	receive_face(orange_face);
}

void loop()
{
	for(int i = 0; i < 1; i++)
	{
		receive_whole_cube();
	}
	
	Serial.println("Done!");
		
	while(true)
	{
		// do nothing
	}
}