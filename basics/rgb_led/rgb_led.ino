#define red 9
#define green 10
#define blue 11

#define pot A0

int red_value = 0;
int green_value = 0;
int blue_value = 0;
int level = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  level = analogRead(pot);

  if(level < 341) {
    level = (level*3)/4;

    red_value = 255- level;
    green_value = level;
    blue_value = 0;
  }
  else if(level < 682){
     level = (level-341)*3/4;

     red_value = 0;
     green_value = 255- level;
     blue_value = level;
  }
  else{
    level = (level-683)*3/4;

     red_value = level;
     green_value = 0;
     blue_value = 255-level;
  }
  analogWrite(red, 255-red_value);
  analogWrite(green, 255-green_value);
  analogWrite(blue, 255-blue_value);

}
