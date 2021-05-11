
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "ledGrid.h"
#include "sequenceAnimation.h"

#define buttonPin 2
ledGrid mainGrid(4, 0, 3);
sequenceAnimation clockWork(12);
//sequenceAnimation zigZag(16);
//sequenceAnimation radial(12);
//sequenceAnimation roundNRound(18);

bool awake = false;
#define awakeTimeout 5000
long awakeTimer;
int programSelect = 1;

bool run = false;
#define runTimeout 7200000
long runTimer;

struct point {
	int m_col;
	int m_row;

	point(int col, int row) : m_col(col), m_row(row) {};
};

void sleep();
void wakeUpNow();
void selSequence(); // Runs user select sequence mode

void setup()
{
	pinMode(buttonPin, INPUT_PULLUP);
	pinMode(buttonPin, HIGH);

	/* 
		clockWork sequence Compile
	*/
	point differentiating[12] = { point(1,1),point(2,1),point(3,1),point(4,1),point(4,2),point(4,3),point(4,4),point(3,4),point(2,4),point(1,4),point(1,3),point(1,2) };
	frame* tempFrame;

	for (int i = 0; i < 12; i++) {
		// set tempFrame to a new frame
		tempFrame = new frame(5);			// I also know there's 5 LEDs per frame
		for (int row = 2; row <= 3; row++) 
			for (int col = 2; col <= 3; col++)
				tempFrame->addSegment(col, row);	// Add the center 4 LEDs

		// Add the differentiating LED
		tempFrame->addSegment(differentiating[i].m_col, differentiating[i].m_row);

		// Add the frame to the sequence
		clockWork.addFrame(tempFrame);
	}
	clockWork.setFPS(25);
	/*
		clockWork sequence Compiled
	*/

	/*
		zigZag Compile
	*/

	/*
	zigZag.addFrame(new frame(1, 1));
	zigZag.addFrame(new frame(2, 1));
	zigZag.addFrame(new frame(3, 1));
	zigZag.addFrame(new frame(4, 1));
	zigZag.addFrame(new frame(4, 2));
	zigZag.addFrame(new frame(3, 2));
	zigZag.addFrame(new frame(2, 2));
	zigZag.addFrame(new frame(1, 2));
	zigZag.addFrame(new frame(1, 3));
	zigZag.addFrame(new frame(2, 3));
	zigZag.addFrame(new frame(3, 3));
	zigZag.addFrame(new frame(4, 3));
	zigZag.addFrame(new frame(4, 4));
	zigZag.addFrame(new frame(3, 4));
	zigZag.addFrame(new frame(2, 4));
	zigZag.addFrame(new frame(1, 4));
	*/
}

long buttonPoll = millis();

void loop()
{
	if (millis() - awakeTimer > awakeTimeout)
		awake = false;
	if (millis() - runTimer > runTimeout)
		run = false;

	if (run) {
		if(programSelect == 1)
			mainGrid.display(&clockWork);
		if (programSelect == 2)
			mainGrid.display(&clockWork);
		if (programSelect == 3)
			mainGrid.display(&clockWork);
		if (programSelect == 4)
			mainGrid.display(&clockWork);


		if (!digitalRead(buttonPin) && millis() - buttonPoll > 100) {
			mainGrid.display((byte)0);
			long tempTimer = millis();
			while (!digitalRead(buttonPin)) {
				if (run) {
					if (programSelect == 1)
						mainGrid.display(&clockWork);
					if (programSelect == 2)
						mainGrid.display(&clockWork);
					if (programSelect == 3)
						mainGrid.display(&clockWork);
					if (programSelect == 4)
						mainGrid.display(&clockWork);
				}
				else
					mainGrid.display((byte)0);
				if (millis() - tempTimer > 3000) {
					run = false;
					awake = 0;
				}
			}

			buttonPoll = millis();
		}
	} else if (awake) { // is awake, but not running
		if (!digitalRead(buttonPin) && millis() - buttonPoll > 100) {
			while (!digitalRead(buttonPin)) {
				// do nothing
			}
			run = true;
			buttonPoll = millis();
		}
	} else { // we're not awake and we're not running
		sleep();
	}
	/*
	if (!digitalRead(buttonPin)) {
		frame tempFrame2(1);
		tempFrame2.addSegment(1, 1);
		mainGrid.display(&tempFrame2);
	}
	else {
		frame tempFrame(1);
		tempFrame.addSegment(0);
		mainGrid.display(&tempFrame);
	}
	*/
}

void sleep() {
	run = false;
	awake = false;
	mainGrid.display((byte) 0);

	detachInterrupt(0);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
	sleep_enable();          // enables the sleep bit in the mcucr register
							 // so sleep is possible. just a safety pin
	attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
										// wakeUpNow when pin 2 gets CHANGE
	sleep_mode();            // here the device is actually put to sleep!!
							 // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

	sleep_disable();         // first thing after waking from sleep:
							 // disable sleep...
	detachInterrupt(0);      // disables interrupt 0 on pin 2 so the
							 // wakeUpNow code will not be executed
							 // during normal running time.

	long progTimer = millis();
	while (!digitalRead(buttonPin)) {
		if (millis() - progTimer > 1000) {
			selSequence();
			if (programSelect == 1)
				clockWork.setFPS(25);
			if (programSelect == 2)
				clockWork.setFPS(10);
			if (programSelect == 3)
				clockWork.setFPS(2);
			if (programSelect == 4)
				clockWork.setFPS(45);
			break;
		}
	}

	awakeTimer = millis();
	runTimer = millis();
	buttonPoll = millis();
	//attachInterrupt(0, buttonPress, LOW);9

}

void wakeUpNow() {
	// Code run on wakeup
	awake = true;
}

void selSequence() {
	frame progReady(4);
	progReady.addSegment(1, 1);
	progReady.addSegment(4, 1);
	progReady.addSegment(1, 4);
	progReady.addSegment(4, 4);

	// Wait for user to let go of the button
	while (!digitalRead(buttonPin)) {
		mainGrid.display(&progReady);
	}

	while (true) {
		// LED Notification
		if (programSelect >= 1)
			mainGrid.display(progReady.genSegment(1, 1));
		if (programSelect >= 2)
			mainGrid.display(progReady.genSegment(2, 1));
		if (programSelect >= 3)
			mainGrid.display(progReady.genSegment(3, 1));
		if (programSelect >= 4)
			mainGrid.display(progReady.genSegment(4, 1));

		// Check if exit
		if (!digitalRead(buttonPin) && millis() - buttonPoll > 100) {
			long exitTimer = millis();
			while (!digitalRead(buttonPin)) {
				if (programSelect >= 1)
					mainGrid.display(progReady.genSegment(1, 1));
				if (programSelect >= 2)
					mainGrid.display(progReady.genSegment(2, 1));
				if (programSelect >= 3)
					mainGrid.display(progReady.genSegment(3, 1));
				if (programSelect >= 4)
					mainGrid.display(progReady.genSegment(4, 1));

				if (millis() - exitTimer > 1000) {
					mainGrid.display((byte)0);
					awake = false;
					while (!digitalRead(buttonPin)) {
						//wait for the user to let go
					}
					return;
				}
			}

			if (programSelect == 4)
				programSelect = 1;
			else
				programSelect++;

			buttonPoll = millis();
		}
	}
}