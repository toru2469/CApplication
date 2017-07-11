#pragma once

#include <Eigen/Dense>
#include <GLUT/glut.h>
#include <GL/freeglut.h>

using namespace std;
using namespace Eigen;

class Material
{
private:

	Vector4f diffuseColor;
	Vector4f ambientColor;
	Vector4f specularColor;
	float shininess;

public:

	Vector4f getDiffuseColor() const;
	void setDiffuseColor(const Vector4f&);
	void setDiffuseColor(Vector4f&&);

	Vector4f getSpecularColor() const;
	void setSpecularColor(const Vector4f&);
	void setSpecularColor(Vector4f&&);

	Vector4f getAmbientColor() const;
	void setAmbientColor(const Vector4f&);
	void setAmbientColor(Vector4f&&);

	float getShininess() const;
	void setShininess(float);

	void begin() const;
};
