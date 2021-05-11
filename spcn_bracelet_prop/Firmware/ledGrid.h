#ifndef LEDGRID_H
#define LEDGRID_H
#include "frame.h"
#include "sequenceAnimation.h"

class ledGrid
{
private:
	int m_clockPin, m_dataPin, m_latchPin, m_numIO;
	long m_frameDelayStart;

public:
	ledGrid(int clockPin, int dataPin, int latchPin);
	ledGrid();
	~ledGrid();

	void display(byte* p_segment);				// Displays a segment
	void display(byte p_segment);				// Displays a segment
	void display(frame* p_frame);				// Displays a frame
	void display(sequenceAnimation* p_sequence); // Displays a sequence
	
};

#endif /* LEDGRID_H */