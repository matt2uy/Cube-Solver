// gets cube face colours from .py through serial monitor
// uses handshake

void setup()
{
  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready
}

char yellow_face[9];
String white_face[9];
String blue_face[9];
String red_face[9];
String green_face[9];
String orange_face[9];

String raw_cube_string = "abcd";

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




void loop()
{
  raw_cube_string.toCharArray(yellow_face, sizeof(yellow_face));
  Serial.println(raw_cube_string[1]);

  while(true)
  {
    // do nothing

  }
}