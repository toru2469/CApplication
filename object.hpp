#pragma once

#include <GLUT/glut.h>
#include <vector>
#include <array>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include "material.hpp"

using namespace std;
using namespace Eigen;

// 一般的なオブジェクトのクラス
class Object
{
protected:

	// 位置
	Vector3f position;
	// 向き
	Vector3f orientation;
	// 速度
	Vector3f velocity;
	// 加速度
	Vector3f acceleration;

	// マテリアル
	Material material;

	// 頂点座標
	vector<Vector3f, aligned_allocator<Vector3f>> vertices;

public:

	virtual ~Object() = default;

	// 初期設定
	void setup();

	// 位置や向きを更新
	void update();

	// 頂点座標を描画
	virtual void draw() const;

	// 衝突判定
	bool colliding(const Object&);

	vector<Vector3f, aligned_allocator<Vector3f>>& getVertices();
	const vector<Vector3f, aligned_allocator<Vector3f>>& getVertices() const;
	
	Vector3f getPosition() const;
	void setPosition(const Vector3f&);
	void setPosition(Vector3f&&);

	Vector3f getOrientation() const;
	void setOrientation(const Vector3f&);
	void setOrientation(Vector3f&&);

	Vector3f getVelocity() const;
	void setVelocity(const Vector3f&);
	void setVelocity(Vector3f&&);

	Vector3f getAcceleration() const;
	void setAcceleration(const Vector3f&);
	void setAcceleration(Vector3f&&);

	Material getMaterial() const;
	void setMaterial(const Material&);
	void setMaterial(Material&&);
};

// ロケットクラス
class Rocket : public Object
{
public:

	void draw() const override
	{
		material.begin();

		glPushMatrix();
		{
			glTranslatef(position.x(), position.y(), position.z());

			// ここにロケット描画のコードを書く
			// ...
		}
		glPopMatrix();
	}
};

// 隕石クラス
class Meteorite : public Object
{
public:

	void draw() const override
	{
		material.begin();

		glPushMatrix();
		{
			glTranslatef(position.x(), position.y(), position.z());

			// ここに隕石描画のコードを書く
			// とりあえずは球体
			glutSolidSphere(0.5, 30, 30);
		}
		glPopMatrix();
	}
};
