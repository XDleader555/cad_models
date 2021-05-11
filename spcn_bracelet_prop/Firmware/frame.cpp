#include "frame.h"

/*
	Constructors
*/


frame::frame(int numLEDSegments) {
	m_ledSegments = new byte[numLEDSegments];
	m_arrSize = numLEDSegments;
	m_numSegments = 0;
	m_currSegment = 0;
}

frame::frame(int col, int row) : frame(1) {
	addSegment(col, row);
}

frame::frame() : frame(0) {

}

frame::~frame()
{
	/*
	for (int i = 0; i < m_numSegments; i++) {
		delete m_ledSegments[i];
		m_ledSegments[i] = NULL;
	}
	*/

	delete[] m_ledSegments;
	m_ledSegments = NULL;
}

/*
	Accessors
*/

int frame::numSegments() {
	return m_numSegments;
}

byte* frame::getSegment(int p_index) {
	// Assumes the array isnt a size of 0
	return &(m_ledSegments[p_index]);
}

byte* frame::operator[](int p_index) {
	return getSegment(p_index);
}

int frame::currSegment() {
	return m_currSegment;
}

/*
	Mutators
*/

byte frame::genSegment(int col, int row) {
	/*
	int rowNibble = 1 << (4 - row);// == 8 or 00001000
	int colNibble = 1 << (4 - col);// == 7 or 00000111
	*/

	// mirrored for rev 3 hardware
	int rowNibble = 1 << (4 - col);// == 8 or 00001000
	int colNibble = 1 << (4 - row);// == 7 or 00000111

	for (int i = 0; i < 4; i++)
		colNibble = colNibble ^ (1 << (3 - i)); // invert column nibble

	rowNibble = rowNibble << 4; // Shift over 4 times to make room for the column == 10000000?
	rowNibble = rowNibble | colNibble; // Add the two together to get the byte

	// Quick fix for having the first bit last
	int finalByte = ((rowNibble & 1) << 7) | (rowNibble >> 1);

	return finalByte;
}

void frame::addSegment(byte segment) {
	m_ledSegments[m_numSegments++] = segment;
}

void frame::addSegment(int p_col, int p_row) {
	addSegment(genSegment(p_col, p_row));
}

void frame::nextSegment() {
	if (m_currSegment >= m_numSegments-1)
		m_currSegment = 0;
	else
		m_currSegment++;
}

/*
	Memory Management
*/

void resize(int new_size) {
	// TO DO
}