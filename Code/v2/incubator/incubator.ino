/*
 * SSD1306 code from: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/
 */
#include <Wire.h>
#include <Adafruit_GFX.h>     
#include <Adafruit_SSD1306.h>
// #include <DallasTemperature.h>// DS18B20 lib
#include <MsTimer2.h>         
#include <SPI.h>
#include <SD.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4
#define TEMP0 A3
#define ONE_WIRE_BUS 2 
#define WARMER 5
#define tim 1000 // timer, set as 1k ms
#define BUZZER 13 // pin D13
// OLED parameter
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

File myFile;
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);

_Bool timer_state;        //timer status
unsigned char temps[80];  //store temp value
unsigned char val ;       //time of storing temperature
unsigned int beep_time;   //unacceptable time 
unsigned int beep_begin = 180;//start beeping time
unsigned int beep_end = 180;  //total beeping time(s)
float temp;
float sum = 0.0;
bool initialized;

void setup() {
  Serial.begin(9600);
  Wire.begin();     

  
//  sensors.begin();  // initialize DS18B20 lib

  pinMode(10, OUTPUT);
  if (!SD.begin()) {
    Serial.println("initialization failed!");
  }
  
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  
  MsTimer2::set(tim, refresh);
  MsTimer2::start();

  // Initialize pins
  pinMode(TEMP0, INPUT);
  
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  pinMode(WARMER, OUTPUT);
  digitalWrite(WARMER, LOW);
  
  display.clearDisplay();
  unsigned char i;
  // At beginning, OLED screen will just show a flat line for 30
  for (i = 0; i < 80; i++) {       
    temps[i] = 30;
  }

  initialized = false;

}

void loop() {
  if (timer_state == true) {
    /*
    sensors.requestTemperatures();            // request temp
    float temp = sensors.getTempCByIndex(0);
    */
    // read temperature and update OLED screen
    temp = read_temp();
    Serial.print(temp);
    Serial.println(" C"); // serialport send temp data
    Temp_coord(temp);     // change temp into coordinates
    Temp_display(temp);   // OLED show temp
    Warm(temp);           // heater and BUZZER control
    temp_save(temp);      // store temp data
    timer_state = false;
  }
}

void refresh() {   
  timer_state = true;
}

void Temp_display(float temp) { //OLED display temp，input=temp
  display.clearDisplay();       // clear screen
  display.setTextColor(WHITE);  // set while to be visable
  display.setTextSize(1);       //set text size
  display.setCursor(85, 0);     //set cursor place
  display.print("Temp:");       //words
  display.setCursor(85, 15);    //set cursor place
  display.print((String)temp);          //show temp
  display.print("C");
  display.drawLine(0, 0, 0, 30, WHITE);   //draw Y axis
  display.drawLine(0, 30, 80, 30, WHITE); //draw X axis

  Display_temps();              //show temp point
  display.display();            //update screen
}

void Warm(float temp) {          //decide to warm&alarm or not
  if (temp <= 34.5) {               //below 34.5 celcius
    digitalWrite(WARMER, HIGH);  //start heater
  }
  if (temp >= 35.5) {         //above 35.5
    digitalWrite(WARMER, LOW);   //heater off
  }
  if (temp <= 34 || temp > 36) {
    beep_time += (tim / 1000);
  }
  else {
    initialized = true;
    beep_time = 0;
  }
  if (beep_time > beep_begin && beep_time < beep_begin + beep_end && initialized) { 
    //unacceptable temp for 3 min，3X60=180s
    digitalWrite(BUZZER, HIGH);
  }
  else {
    digitalWrite(BUZZER, LOW);
  }
  if (beep_time  >= beep_begin + beep_end) {
    beep_time = 0;
  }
}

void Display_temps() {
  unsigned char i;
  for (i = 0; i <= 79; i++) {    //show temp points chronologically
    display.drawPixel(i, temps[i], WHITE);
  }
  display.display();
}

float read_temp() {
  // Take average of a couple reads
  unsigned char i;
  sum = 0;
  for (i = 0; i < 5; i++) {
    sum += ((analogRead(TEMP0) * 500.0) / 1024.0);
  }
  sum /= 5.0;
  return sum;
  
  //return ((analogRead(TEMP0) * 500.0) / 1024.0); // reading * 5000 / 1024 calibrates ADC to volts, and division by 10 calibrates to celcius
}

void Temp_coord(float temp) {
  unsigned char i;
  if (val < 79) {   //first 79 points show as it is
    temps[val] = 60 - char(temp * 1.5 + 0.5);
    val++;
  }
  else {
    for (i = 0; i <= 79; i++) {  //80 and more, push the first point
      temps[i] = temps[i + 1];
    }
    temps[79] = 60 - char(temp * 1.5  + 0.5); //fill in the last temp as the 79th point
  }
}

void temp_save(float temp) {
  //open file, only one at a time
  myFile = SD.open("temp.CSV", FILE_WRITE);
  // if open, write down
  if (myFile)
  {
    Serial.print("Writing to test.txt...");
    time_disposal();
    myFile.print((String)temp);
    myFile.println("C");
    // close file
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    //if not open, show this
    Serial.println("error opening test.txt");
  }
}

void time_disposal() {  //read and show as hour, min, and second
  long val = millis();   //val=ms，below is turning it into hour, min, and sec
  unsigned char hour = (val / 1000) / 3600;
  unsigned char minusrt = ((val / 1000) / 60) % 60;
  unsigned char second = (val / 1000) % 60;
  myFile.print(hour);
  myFile.print("：");
  myFile.print(minusrt);
  myFile.print("：");
  myFile.print(second);
  myFile.print(",");      //write in chronological order
}
