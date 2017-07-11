#include "camera.hpp"

Vector3f Camera::getPosition() const
{
	return position;
}

void Camera::setPosition(const Vector3f& _position)
{
	position = _position;
}
void Camera::setPosition(Vector3f&& _position)
{
	position = move(_position);
}

Vector3f Camera::getTarget() const 
{
	return target;
}

void Camera::setTarget(const Vector3f& _target)
{
	target = _target;
}

void Camera::setTarget(Vector3f&& _target)
{
	target = move(_target);
}

Vector3f Camera::getUpVector() const
{
	return upVector;
}

void Camera::setUpVector(const Vector3f& _upVector)
{
	upVector = _upVector;
}
void Camera::setUpVector(Vector3f&& _upVector)
{
	upVector = _upVector;
}

void Camera::begin() const
{
	glLoadIdentity();

	gluLookAt(
		position.x(), position.y(), position.z(),
		target.x(), target.y(),target.z(),
		upVector.x(), upVector.y(), upVector.z());
}