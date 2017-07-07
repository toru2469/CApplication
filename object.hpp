#pragma once

#include <GL/glut.h>
#include <vector>
#include <array>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/StdVector>

using namespace std;

class Object
{
private:

	// 位置の3次元座標
	array<float, 3> position;
	// 向き(まだ考え中)
	array<float, 3> orientation;

	// マテリアルの色
	array<float, 4> materialDiffuseColor;
	array<float, 4> materialAmbientColor;
	array<float, 4> materialSpecularColor;
	float materialShininess;

	// 描画する際の頂点座標を格納しているvector
	vector<array<float, 3>> vertices;

public:

	Object();

	~Object();

	Object(const Object& object);

	Object(Object&& object);

	Object& operator=(const Object& object);

	Object& operator=(Object&& object);

	// 必要に応じて初期設定
	void setup();

	// 位置や向きを更新
	void update();

	// 頂点座標を描画
	void draw() const;

	// 位置をゲット
	array<float, 3> getPosition() const;

	// 位置をセット
	void setPosition(const array<float, 3>& _position);

	void setPosition(array<float, 3>&& _position);

	// 向きをゲット
	array<float, 3> getOrientation() const;

	// 向きをセット
	void setOrientation(const array<float, 3>& _orientation);

	void setOrientation(array<float, 3>&& _orientation);
};
