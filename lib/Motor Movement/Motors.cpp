#include <Arduino.h>
#include <Motors.h>

void Motor::Setup(int enA, int in1, int in2, bool reversed){
  enAPin = enA;
  in1Pin = in1;
  in2Pin = in2;
  reversedDirection = reversed;
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void Motor::Move(int speed){
	 if(reversedDirection){
  		if(speed > 0){
  			digitalWrite(in1Pin, LOW);
  			digitalWrite(in2Pin, HIGH);
  			analogWrite(enAPin, abs(speed));
        Serial.print("HMMMMMMMM");
  	} else if(speed < 0){
  			digitalWrite(in1Pin, HIGH);
  			digitalWrite(in2Pin, LOW);
  			analogWrite(enAPin, abs(speed));
        Serial.print("HMMMMMMMM");
    } else {
  			digitalWrite(in1Pin, LOW);
  			digitalWrite(in2Pin, LOW);
  			analogWrite(enAPin, 255);
  		}
	}else{
      if(speed > 0){
  			digitalWrite(in1Pin, HIGH);
  			digitalWrite(in2Pin, LOW);
  			analogWrite(enAPin, abs(speed));
        Serial.print("HMMMMMMMM");
  	 }else if(speed < 0){
  			digitalWrite(in1Pin, LOW);
  			digitalWrite(in2Pin, HIGH);
  			analogWrite(enAPin, abs(speed));
        Serial.print("HMMMMMMMM");
  	 }else {
  			digitalWrite(in1Pin, LOW);
  			digitalWrite(in2Pin, LOW);
  			analogWrite(enAPin, 255);
		}
	}
}
