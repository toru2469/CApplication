#pragma once

#include <Eigen/Dense>
#include <GLUT/glut.h>
#include <GL/freeglut.h>

using namespace std;
using namespace Eigen;

class Light
{
private:

	Vector4f position;
	Vector4f diffuseColor;
	Vector4f specularColor;
	Vector4f ambientColor;

public:

	Vector4f getPosition() const;
	void setPosition(const Vector4f&);
	void setPosition(Vector4f&&);

	Vector4f getDiffuseColor() const;
	void setDiffuseColor(const Vector4f&);
	void setDiffuseColor(Vector4f&&);

	Vector4f getSpecularColor() const;
	void setSpecularColor(const Vector4f&);
	void setSpecularColor(Vector4f&&);

	Vector4f getAmbientColor() const;
	void setAmbientColor(const Vector4f&);
	void setAmbientColor(Vector4f&&);

	void begin() const;
};
