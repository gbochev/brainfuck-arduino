String commands = "";
#define MEMORY 48
void setup() {
  Serial.begin(9600); 
}
char readFromSerial()
{
  while(true)// if there is no input, it loops
  {
  if(Serial.available()>0)
    return Serial.read();
  }
}
void loop() {

  if (Serial.available() > 0) {
    commands = Serial.readStringUntil('\n');
    char memory[MEMORY]= {0};
    int counter = 0;
    int i;
    for (i = 0; i < commands.length(); i++ )
    {
      switch (commands[i])
      {
      case '>':
        if(counter<MEMORY)
          counter++;
        break;
      case '<':
        if(counter>0)
          counter--;
        break;
      case '+':
        memory[counter]++;
        break;
      case '-':
        memory[counter]--;
        break;
      case '.':
        Serial.print(memory[counter]);
        break;
      case ',':
        memory[counter] = readFromSerial();
        break;
      case '[':
        if (memory[counter] == 0)
        {

          int brackets = 0;
          int j;
          for (j = i + 1; j < commands.length(); j++)
          {
            if (commands[j] == '[') brackets++;
            if (commands[j] == ']' && brackets == 0)
            {
              i = j;
              break;
            }
            if (commands[j] == ']' && brackets != 0) brackets--;
          }
        }
        break;
      case ']':
        if (memory[counter] != 0)
        {

          int brackets = 0;
          int j;
          for (j = i-1; j > 0; j--)
          {
            if (commands[j] == ']') brackets++;
            if (commands[j] == '[' && brackets == 0)
            {
              i = j;
              break;
            }
            if (commands[j] == '[' && brackets != 0) brackets--;
          }

        }
        break;
      }
    }
  }
}


