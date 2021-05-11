#include "sequenceAnimation.h"

/*
	Constructors
*/
sequenceAnimation::sequenceAnimation(int p_numFrames) {
	m_frames = new frame*[p_numFrames];
	m_arrSize = p_numFrames;
	m_numFrames = 0;
	m_currFrame = 0; // Iterator
	m_repeats = 0;
	//m_fps = ((double) 12/ (double) 60);
	m_fps = 1;
}

sequenceAnimation::sequenceAnimation() : sequenceAnimation(0) {

}

sequenceAnimation::~sequenceAnimation() {
	// We already deleted all the frames - might want to look into this just in case
	delete[] m_frames;
	m_frames = NULL;
}

/*
	Accessors
*/

int sequenceAnimation::numFrames() {
	return m_numFrames;
}

int sequenceAnimation::currFrame() {
	return m_currFrame;
}

int sequenceAnimation::repeats() {
	return m_repeats;
}

double sequenceAnimation::fps() {
	return m_fps;
}

frame* sequenceAnimation::getFrame(int index) {
	return m_frames[index];
}

frame* sequenceAnimation::operator[](int index) {
	return getFrame(index);
}

/*
	Mutators
*/

void sequenceAnimation::addFrame(frame* new_frame) {
	m_frames[m_numFrames++] = new_frame;
}

void sequenceAnimation::setFPS(double new_fps) {
	m_fps = new_fps;
}
void sequenceAnimation::nextFrame() {
	if (m_currFrame >= m_arrSize - 1)
		iteratorReset();
	else
		m_currFrame++;
}

void sequenceAnimation::setFrame(int p_frame) {
	m_currFrame = p_frame;
}

void sequenceAnimation::iteratorReset() {
	m_currFrame = 0;
	m_repeats++;
}

void sequenceAnimation::repeatReset() {
	m_repeats = 0;
}

void sequenceAnimation::resize(int new_size) {
	// TO DO
}