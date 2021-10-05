#include <Wire.h>

#define rows 5
#define cols 6

int rowPins[rows] = {9,7,5,6,4};
int colPins[cols] = {10,16,A2,A1,A0,15};

int prevScan[rows][cols] = {{1,1,1,1,1,1}, {1,1,1,1,1,1}, {1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1}};
int currScan[rows][cols] = {{1,1,1,1,1,1}, {1,1,1,1,1,1}, {1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1}};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  for(int i = 0; i < rows; i++){
    pinMode(rowPins[i], OUTPUT);
    
    digitalWrite(rowPins[i],HIGH); 
  }
  for(int i = 0; i < cols; i++){
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for(int i = 0; i < rows; i++){
    digitalWrite(rowPins[i], LOW);
    for(int j = 0; j < cols; j++){
      currScan[i][j] = digitalRead(colPins[j]);
      if(currScan[i][j] != prevScan[i][j]){
        Serial.print("key ");
        Serial.print(i);
        Serial.print(" ");
        Serial.print(j);
        Serial.print(" to state ");
        Serial.println(currScan[i][j]);
        
        if(currScan[i][j] == 0){
          writePress(i, j);
        }
        else{
          writeRelease(i, j);
        }
      }
      prevScan[i][j] = currScan[i][j];
    }
    digitalWrite(rowPins[i], HIGH);
  }
}

void writePress(int row, int col){
  int boole = 0;
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(row);        // sends five bytes
  Wire.write(col); 
  Wire.write(boole);// sends one byte  
  Wire.endTransmission(4); 
  delay(1);
}

void writeRelease(int row, int col){
  int boole = 1;
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(row);        // sends five bytes
  Wire.write(col); 
  Wire.write(boole);// sends one byte  
  Wire.endTransmission(4); 
  delay(1);
}
