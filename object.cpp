#include "object.hpp"

Object::Object()
{
	setup();
}

Object::~Object()
{
	setup();
}

Object::Object(const Object& object)
	: position(object.position), orientation(object.orientation)
{
	setup();
}

Object::Object(Object&& object)
	: position(move(object.position)), orientation(move(object.orientation))
{
	setup();
}

Object& Object::operator=(const Object& object)
{
	position = object.position;

	return *this;
}

Object& Object::operator=(Object&& object)
{
	position = move(object.position);

	return *this;
}

void Object::setup()
{
	materialDiffuseColor[0] = 0.0;
	materialDiffuseColor[1] = 0.0;
	materialDiffuseColor[2] = 0.0;
	materialDiffuseColor[3] = 1.0;
	
	materialAmbientColor[0] = 0.0;
	materialAmbientColor[1] = 0.0;
	materialAmbientColor[2] = 0.0;
	materialAmbientColor[3] = 1.0;

	materialSpecularColor[0] = 0.0;
	materialSpecularColor[1] = 0.0;
	materialSpecularColor[2] = 0.0;
	materialSpecularColor[3] = 1.0;
	
	materialShininess = 10.0;
}

void Object::update()
{
	/*
		ここでは時間経過に応じた位置、向きの更新を行う
	*/

	position[2] -= 0.02;
}

void Object::draw() const
{
	/*
		頂点座標のvectorをfor文で順に描画する
		こんな感じ
	*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseColor.data());
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientColor.data());
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularColor.data());
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	glPushMatrix();
	{
		glTranslatef(position[0], position[1], position[2]);
		glutSolidSphere(1.0, 30, 30);

		/*
		glBegin(GL_TRIANGLES);
		for_each(begin(vertices), end(vertices), [](const auto& vertex)
		{
		glVertex3fv(vertex.data());
		});
		glEnd();
		*/
	}
	glPopMatrix();
}

array<float, 3> Object::getPosition() const
{
	return position;
}

void Object::setPosition(const array<float, 3>& _position)
{
	position = _position;
}

void Object::setPosition(array<float, 3>&& _position)
{
	position = move(_position);
}

array<float, 3> Object::getOrientation() const
{
	return orientation;
}

void Object::setOrientation(const array<float, 3>& _orientation)
{
	orientation = _orientation;
}

void Object::setOrientation(array<float, 3>&& _orientation)
{
	orientation = move(_orientation);
}