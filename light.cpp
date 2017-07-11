#include "light.hpp"

Vector4f Light::getPosition() const
{
	return position;
}

void Light::setPosition(const Vector4f& _position)
{
	position = _position;
}

void Light::setPosition(Vector4f&& _position)
{
	position = move(_position);
}

Vector4f Light::getDiffuseColor() const
{
	return diffuseColor;
}

void Light::setDiffuseColor(const Vector4f& _diffuseColor)
{
	diffuseColor = _diffuseColor;
}

void Light::setDiffuseColor(Vector4f&& _diffuseColor)
{
	diffuseColor = move(_diffuseColor);
}

Vector4f Light::getSpecularColor() const
{
	return specularColor;
}

void Light::setSpecularColor(const Vector4f& _specularColor)
{
	specularColor = _specularColor;
}

void Light::setSpecularColor(Vector4f&& _specularColor)
{
	specularColor = move(_specularColor);
}

Vector4f Light::getAmbientColor() const
{
	return ambientColor;
}

void Light::setAmbientColor(const Vector4f& _ambientColor)
{
	ambientColor = _ambientColor;
}

void Light::setAmbientColor(Vector4f&& _ambientColor)
{
	ambientColor = move(_ambientColor);
}

void Light::begin() const
{
	glLightfv(GL_LIGHT0, GL_POSITION, position.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor.data());
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor.data());
}