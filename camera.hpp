#pragma once

#include <Eigen/Dense>
#include <GLUT/glut.h>
#include <GL/freeglut.h>

using namespace std;
using namespace Eigen;

class Camera
{
private:

	Vector3f position;
	Vector3f target;
	Vector3f upVector;

public:

	Vector3f getPosition() const;
	void setPosition(const Vector3f&);
	void setPosition(Vector3f&&);

	Vector3f getTarget() const;
	void setTarget(const Vector3f&);
	void setTarget(Vector3f&&);

	Vector3f getUpVector() const;
	void setUpVector(const Vector3f&);
	void setUpVector(Vector3f&&);

	void begin() const;
};
