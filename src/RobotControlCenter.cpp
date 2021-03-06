/*
 * ExampleRobot.cpp
 *  Remember, Remember the 5th of november
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#include "RobotControlCenter.h"

void RobotControlCenter::loop() {
	if (esp_timer_get_time() - lastPrint > 500
			|| esp_timer_get_time() < lastPrint // check for the wrap over case
					) {
		switch (state) {
		case Startup:
			setup();
			state = WaitForConnect;
			break;
		case WaitForConnect:
#if defined(USE_WIFI)
			if (manager.getState() == Connected)
#endif
				state = run; // begin the main operation loop
			break;
		default:
			break;
		}
		lastPrint = esp_timer_get_time(); // ensure 0.5 ms spacing *between* reads for Wifi to transact
	}
	if (state != Startup) {
		// If this is run before the sensor reads, the I2C will fail because the time it takes to send the UDP causes a timeout
		fastLoop();    // Run PID and wifi after State machine on all states
	}

}

RobotControlCenter::RobotControlCenter(String * mn) {
	pidList[0] = &motor1;
	pidList[1] = &motor2;
	pidList[2] = &motor3;
	state = Startup;
	name = mn;
	robot = NULL;
}

void RobotControlCenter::setup() {
	if (state != Startup)
		return;
	state = WaitForConnect;
#if defined(USE_WIFI)
	manager.setup();
#else
	Serial.begin(115200);
#endif

	motor1.attach(MOTOR1_PWM, MOTOR1_ENCA, MOTOR1_ENCB);
	motor2.attach(MOTOR2_PWM, MOTOR2_ENCA, MOTOR2_ENCB);
	motor3.attach(MOTOR3_PWM, MOTOR3_DIR, MOTOR3_ENCA, MOTOR3_ENCB);
	// Set the setpoint the current position in motor units to ensure no motion
	motor1.setSetpoint(motor1.getPosition());
	motor2.setSetpoint(motor2.getPosition());
	motor3.setSetpoint(motor3.getPosition());
	ESP32PWM dummy;
	dummy.getChannel(); // skip the second 10khz motor
	// Set up digital servo for the gripper
	servo.setPeriodHertz(330);
	servo.attach(SERVO_PIN, 1000, 2000);
	robot = new StudentsRobot(&motor1, &motor2, &motor3, &servo);


#if defined(USE_WIFI)
	// Attach coms
	coms.attach(new NameCheckerServer(name));
	coms.attach(new DiscoveryPacket(&coms));
#endif

}

void RobotControlCenter::fastLoop() {
	if (state == Startup)    // Do not run before startp
		return;
#if defined(USE_WIFI)
	manager.loop();
	if (manager.getState() == Connected)
		coms.server(); // @suppress("Method cannot be resolved")
	else {
		return;
	}
#endif
	robot->pidLoop();
	robot->updateStateMachine();

}
