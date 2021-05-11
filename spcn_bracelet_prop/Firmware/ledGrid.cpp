#include "ledGrid.h"

ledGrid::ledGrid(int clockPin, int dataPin, int latchPin) {
	m_clockPin = clockPin;
	m_dataPin = dataPin;
	m_latchPin = latchPin;

	pinMode(m_clockPin, OUTPUT);
	pinMode(m_dataPin, OUTPUT);
	pinMode(m_latchPin, OUTPUT);

	m_numIO = 8; // Assume 8 outputs

	m_frameDelayStart = micros();
}

ledGrid::ledGrid() : ledGrid(9,10,11){
	// defaults the outputs to D9,10,11
}


ledGrid::~ledGrid()
{
}

void ledGrid::display(byte* p_segment) {
	digitalWrite(m_latchPin, LOW);
	shiftOut(m_dataPin, m_clockPin, LSBFIRST, *p_segment); // (1,1) == 0b10000111
	digitalWrite(m_latchPin, HIGH);
}

void ledGrid::display(byte p_segment) {
	digitalWrite(m_latchPin, LOW);
	shiftOut(m_dataPin, m_clockPin, LSBFIRST, p_segment); // (1,1) == 0b10000111
	digitalWrite(m_latchPin, HIGH);
}

void ledGrid::display(frame* p_frame) {
	display(p_frame->getSegment(p_frame->currSegment()));
	p_frame->nextSegment();
}

void ledGrid::display(sequenceAnimation* p_sequence) {
	if (((double)(micros() - m_frameDelayStart) / (double)1000000) < (double) 1.0 / p_sequence->fps()) { // Convert microseconds to seconds
		display(p_sequence->getFrame(p_sequence->currFrame()));
		return;
	}
	m_frameDelayStart = micros();
	p_sequence->nextFrame();
}