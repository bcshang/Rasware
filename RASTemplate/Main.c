#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>//Pin help
#include <RASLib/inc/time.h>//Timer help
#include <RASLib/inc/servo.h>//Servo help
#include <RASLib/inc/adc.h>//IR Sensor help
#include <RASLib/inc/time.h>//Time help

/* Brandon
 * Robot Car Program
 * 		Rasware Driven
 *
 * LED Colors: F2:Blue
 *			   F3:Green
 *			   F4:Red
 *
 * Pin Specifications:
 *		Right Servo:B0
 *		Left Servo:	B1
 *
 *		Right IR Sensor: D0
 *      Middle IR Sensor: D1
 *		Left IR Sensor: D2
 */


/*~~~~~Blinking to show program running~~~~~*/
tBoolean blink_on = true;
void blink(void) {
	//Signifies the program is running, F2 is Blue LED
    SetPin(PIN_F2, blink_on);
    blink_on = !blink_on;
}
/*~~~~~Blinking to show program running~~~~~*/


/*~~~~~~~~~~~~~Servo Code~~~~~~~~~~~~~~~~~~~*/
static tServo *servo_R, *servo_L;
static tBoolean Servo_initd = false;

void initServo(void) {
    // don't initialize this if we've already done so
    if (Servo_initd) {
        return;
    }
    Servo_initd = true;
    servo_R = InitializeServo(PIN_B0);
    servo_L = InitializeServo(PIN_B1);
}

 //Movement functions
 static float speed = .3;
 void moveForward(void) {
    SetServo(servo_R, speed);
 	SetServo(servo_L, 1-speed);
 }
 void moveBackward(void) {
 	SetServo(servo_R, 1-speed);
 	SetServo(servo_L, speed);
 }
 void moveStop(void) {
 	SetServo(servo_R, .5);
 	SetServo(servo_L, .5);
 }

 //TODO requires calibration
 void moveRight(void) {
 	SetServo(servo_R, speed);
 	SetServo(servo_L, speed);
 	Wait(1.5);
 	moveStop();
 }
 void moveLeft(void) {
 	SetServo(servo_R, 1-speed);
 	SetServo(servo_L, 1-speed);
 	Wait(1.5);
 	moveStop();
 }
/*~~~~~~~~~~~~Servo Code End~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~IR Sensor Code End~~~~~~~~~~~~~~~*/
static tADC *adc[2];
static tBoolean IR_initd = false;
void initIRSensor(void) {
    // don't initialize this if we've already done so
    if (IR_initd) {
        return;
    }
    
    IR_initd = true;

    // initialize 4 pins to be used for ADC input
    adc[0] = InitializeADC(PIN_D2);
    adc[1] = InitializeADC(PIN_D1);
    adc[2] = InitializeADC(PIN_D0);
}
/*~~~~~~~~~~~~IR Sensor Code End~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~Main Code Start~~~~~~~~~~~~~~~~*/
int main(void) {
	//Function to say the program is running
    CallEvery(blink, 0, 1);

    //Initialize servos and IR sensors
    initIRSensor();

    while (1) {
        Wait(1);
        //Left sense
        if(ADCRead(adc[0])>.6) {
            Printf("Reading Left\n");
            //moveStop();
        }
        //Middle sense
        else if(ADCRead(adc[1])>.6) {
            Printf("Reading Middle\n");
            //moveStop();
        }
        //Right sense
        else if(ADCRead(adc[2])>.6) {
            Printf("Reading Right\n");
            //moveStop();
        }
        else {
            Printf("Reading Nothing\n");
            //moveForward();
        }
    }
}
