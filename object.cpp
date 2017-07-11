#include "object.hpp"

void Object::setup()
{
	// なにか初期化したいときに
}

void Object::update()
{
	// 等加速度運動を仮定して位置更新
	position += velocity + acceleration * 0.5;
	velocity += acceleration;
}

void Object::draw() const
{
	// 頂点座標を順に描画していく

	material.begin();

	glPushMatrix();
	{
		glTranslatef(position.x(), position.y(), position.z());

		glBegin(GL_TRIANGLES);
		{
			for_each(begin(vertices), end(vertices), [](const auto& vertex)
			{
				glVertex3fv(vertex.data());
			});
		}
		glEnd();
	}
	glPopMatrix();
}

bool Object::colliding(const Object& object)
{
	// 衝突判定のコードをかく
	// ...
}

vector<Vector3f, aligned_allocator<Vector3f>>& Object::getVertices()
{
	return vertices;
}

const vector<Vector3f, aligned_allocator<Vector3f>>& Object::getVertices() const
{
	return vertices;
}

Vector3f Object::getPosition() const
{
	return position;
}

void Object::setPosition(const Vector3f& _position)
{
	position = _position;
}

void Object::setPosition(Vector3f&& _position)
{
	position = move(_position);
}

Vector3f Object::getOrientation() const
{
	return orientation;
}

void Object::setOrientation(const Vector3f& _orientation)
{
	orientation = _orientation;
}

void Object::setOrientation(Vector3f&& _orientation)
{
	orientation = move(_orientation);
}

Vector3f Object::getVelocity() const
{
	return velocity;
}

void Object::setVelocity(const Vector3f& _velocity)
{
	velocity = _velocity;
}

void Object::setVelocity(Vector3f&& _velocity)
{
	velocity = move(_velocity);
}

Vector3f Object::getAcceleration() const
{
	return acceleration;
}

void Object::setAcceleration(const Vector3f& _acceleration)
{
	acceleration = _acceleration;
}

void Object::setAcceleration(Vector3f&& _acceleration)
{
	acceleration = move(_acceleration);
}

Material Object::getMaterial() const
{
	return material;
}

void Object::setMaterial(const Material& _material)
{
	material = _material;
}

void Object::setMaterial(Material&& _material)
{
	material = move(_material);
}