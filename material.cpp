#include "material.hpp"

Vector4f Material::getDiffuseColor() const
{
	return diffuseColor;
}

void Material::setDiffuseColor(const Vector4f& _diffuseColor)
{
	diffuseColor = _diffuseColor;
}

void Material::setDiffuseColor(Vector4f&& _diffuseColor)
{
	diffuseColor = move(_diffuseColor);
}

Vector4f Material::getSpecularColor() const
{
	return specularColor;
}

void Material::setSpecularColor(const Vector4f& _specularColor)
{
	specularColor = _specularColor;
}

void Material::setSpecularColor(Vector4f&& _specularColor)
{
	specularColor = move(_specularColor);
}

Vector4f Material::getAmbientColor() const
{
	return ambientColor;
}

void Material::setAmbientColor(const Vector4f& _ambientColor)
{
	ambientColor = _ambientColor;
}

void Material::setAmbientColor(Vector4f&& _ambientColor)
{
	ambientColor = move(_ambientColor);
}

float Material::getShininess() const
{
	return shininess;
}

void Material::setShininess(float _shininess)
{
	shininess = _shininess;
}

void Material::begin() const
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor.data());
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor.data());
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor.data());
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}