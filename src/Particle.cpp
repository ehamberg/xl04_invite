#include "Particle.h"

Particle::Particle(int n)
{
	numberOfPoints = n;
	center = new Point(0.0, 0.0, 0.0);
	temp = new float[3];
	state = 0;
	wait = false;
}

Particle::~Particle()
{
	delete center;
	delete temp;
}

void Particle::addStartCoordinates(float x, float y, float z)
{
	currentPosition.push_back(new Point(x, y, z));
	lastCompleteState.push_back(new Point(x, y, z));
}

void Particle::addState(int n, float x, float y, float z)
{
	if (n <= NUMBER_OF_STATES-1)
		states[n].push_back(new Point(x, y, z));
}

void Particle::morphToState(float u)
{
	if (u > (float)(state+1)) {
		if (state < NUMBER_OF_STATES-1)
			state++;
		for (int i = 0; i < numberOfPoints; i++) {
			lastCompleteState[i]->x = currentPosition[i]->x;
			lastCompleteState[i]->y = currentPosition[i]->y;
			lastCompleteState[i]->z = currentPosition[i]->z;
		}
	}

	u -= (float)state;

	for (int i = 0; i < numberOfPoints; i++) {
		currentPosition[i]->x =
			lastCompleteState[i]->x + (states[state][i]->x - lastCompleteState[i]->x)*u;
		currentPosition[i]->y =
			lastCompleteState[i]->y + (states[state][i]->y - lastCompleteState[i]->y)*u;
		currentPosition[i]->z =
			lastCompleteState[i]->z + (states[state][i]->z - lastCompleteState[i]->z)*u;
	}
}

float* Particle::getPosition(int n)
{
	temp[0] = currentPosition[n]->x;
	temp[1] = currentPosition[n]->y;
	temp[2] = currentPosition[n]->z;

	return temp;
}
