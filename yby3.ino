double ref_voltage=1.2; // Do not forget, Ardinocan read up to 5.2 Vansd will scale the values read upto 5.2 V
double V_ref; //will be up to 1024
double feedback = 0; 
double D=0;
int pwm_pin=10;
int data_read=A5;
#include <PID_v1.h>
double Kp=0.1;
double Ki=0.01;
double Kd=0;
double min_D=12.75;       //0.1*255
double max_D=60;    //0.45*255


PID myPID(&feedback, &D, &V_ref,Kp,Ki,Kd, DIRECT);
double min=0.1;
double max=0.45;

void setup() {
  Serial.begin(9600);
  pinMode(pwm_pin,OUTPUT);

  

TCCR1B = TCCR1B & B11111000 | B00000001; //9. pin 31250kH yaptık
V_ref= ref_voltage/5.2*1024;// this isthe analog correspondence of reference set voltage above
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(min_D, max_D) ;
}

void loop() {
  feedback=0;
for (int i=0; i <= 2; i++){
      feedback=analogRead(data_read)+feedback;    // averaj data
      delayMicroseconds(1);
   }

feedback=feedback/3;
myPID.Compute();
analogWrite(pwm_pin,D);

}
