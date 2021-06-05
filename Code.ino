#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27,20,4);

Servo myservo1;  
Servo myservo2; 

const int out_sensor=5;
int out_state;
int count; // Variable to store the number of people inside
int limit = 3; // The maximum occupancy 


int pos1,pos2;

void setup() {
  pinMode(out_sensor, INPUT);
  Serial.begin(9600);
  myservo1.attach(7);  
  myservo2.attach(8); 
  myservo1.write(90);
  myservo2.write(90);
  mlx.begin();  
 
  lcd.init();
  lcd.backlight();
}

void loop() {

          out_state=digitalRead(out_sensor); 
          Serial.println(count);
            
          if(out_state==LOW){ // If anyone hovers over the IR sensor
            count--; // Value stored in count variable will be decreased by one as the person is exiting the building or vehicle
            
            
            for(pos1 = 90; pos1 <= 180; pos1 += 1)
          {                                 
            myservo1.write(pos1);
            myservo2.write(180-pos1);         
            delay(15);
          }
            delay(5000);

           for(pos1 = 180; pos1>=90; pos1 -=1)
           {
            myservo1.write(pos1);
            myservo2.write(180-pos1);     
            delay(15);                     
           }

            
            
            if(count<0){
              count=0;
            }
          }


  
          lcd.setCursor(0,0);
          lcd.print("ObjectTemp:");


                    int temp_obj = mlx.readObjectTempC();
   Serial.print(temp_obj);
   Serial.print("\n");
          
          if(temp_obj < 33){
           lcd.setCursor(0,1);
           lcd.print(temp_obj);
           lcd.print("Not detected,retest!");
              
          }
          
          if(temp_obj > 33 && temp_obj <38){
           lcd.setCursor(0,1);
           lcd.print(temp_obj);
           lcd.print("body temperature ok "); 

             


           if(count<limit)
    {
     count++; // Count will increase by one as a person is entering
      for(pos1 = 90; pos1 <= 180; pos1 += 1)
          {                                 
            myservo1.write(pos1);
            myservo2.write(180-pos1);         
            delay(15);
          }
            delay(5000);

           for(pos1 = 180; pos1>=90; pos1 -=1)
           {
            myservo1.write(pos1);
            myservo2.write(180-pos1);     
            delay(15);                     
           }

    }
          
          } 
          
          if(temp_obj>37){
            lcd.setCursor(0,1);
            lcd.print(temp_obj);
            lcd.print("     Keep out!       ");
            delay(500);
            
         }


             
}
