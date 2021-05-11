#ifndef FRAME_H
#define FRAME_H
#include <Arduino.h>

/*
Stores the LED segment sequence for one frame, since we can only light up one LED at a
time due to hardware.

Requirements:
The Segments assumes you already know how many LEDs you want to light up
*/
class frame
{
private:
	byte* m_ledSegments;
	int m_arrSize;
	int m_numSegments;
	int m_currSegment;

public:
	// Constructors
	frame(int numLEDSegments);
	frame(int col, int row);
	frame();
	~frame();
	
	// Accessors
	int numSegments();
	byte* getSegment(int p_index);
	byte* operator[](int p_index);
	int currSegment();

	// Mutators
	byte genSegment(int col, int row); // Converts x,y to a byte array
	void addSegment(byte segment);
	void addSegment(int col, int row);
	
	void nextSegment();

	// Memory Management
	void resize(int new_size);
};

#endif /* FRAME_H */