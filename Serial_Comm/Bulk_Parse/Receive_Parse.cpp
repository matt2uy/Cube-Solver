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

String raw_cube_string = "y, b, w, r, r, g";

void receive_raw_cube()
{
	char ready_signal = 'ready';
	
	// send ready signal
	Serial.println(ready_signal);
	delay(10);
			
	// receive color
	raw_cube_string = Serial.read();
	delay(10);
}

String get_value(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++)
  {
    if(data.charAt(i)==separator || i==maxIndex)
    {
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void parse_raw_cube()
{
	for(int x = 0; x < 9; x++)
	{
		yellow_face[x] = get_value(raw_cube_string, ', ', x);
		Serial.println(x);
	}
}


void loop()
{
	receive_raw_cube();
	parse_raw_cube();
		
	while(true)
	{
		// do nothing
		Serial.println("Done!");
	}
}