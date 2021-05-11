#ifndef SEQUENCE
#define SEQUENCE
#include "frame.h"

class sequenceAnimation
{
private:
	frame** m_frames;
	int m_arrSize;
	int m_numFrames;
	int m_currFrame; // Iterator
	int m_repeats;
	double m_fps;


public:
	// Constructors
	sequenceAnimation(int p_numFrames);
	sequenceAnimation();
	~sequenceAnimation();

	// Accessors
	int numFrames();
	int currFrame();
	int repeats();
	double fps();
	frame* getFrame(int frameIndex);
	frame* operator[](int frameIndex);

	// Mutators
	void addFrame(frame* new_frame);
	void setFPS(double new_fps);
	void nextFrame();
	void setFrame(int p_frame);
	void iteratorReset();
	void repeatReset();
	void resize(int new_size);
};

#endif /* SEQUENCE */