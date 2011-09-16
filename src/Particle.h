#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <vector>

#define NUMBER_OF_STATES 10

using std::vector;

class Particle
{
	public:
		Particle(int n);
		~Particle();

		class Point { public: Point(float x, float y, float z) :
			x(x), y(y), z(z) {} float x,y,z;
		};

		void addStartCoordinates(float x, float y, float z);
		void addState(int n, float x, float y, float z);
		void morphToState(float u);
		float* getPosition(int n);

		int getNumber() { return numberOfPoints; }

	private:
		bool wait;
		vector<Point*> currentPosition;
		vector<Point*> lastCompleteState;
		vector<Point*> states[NUMBER_OF_STATES];
		Point* center;
		float *temp;
		int state;
		int numberOfPoints;
};

#endif
