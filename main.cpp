#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include "object.hpp"

using namespace std;

// 隕石
vector<Object> meteorites;
// ロケット
Object rocket;

// カメラの位置、向き
array<float, 3> cameraPosition;
array<float, 3> cameraOrientation;

// ライトの位置、向き、色など
array<float, 4> lightPosition;
array<float, 4> lightOrientation;
array<float, 4> lightDiffuseColor;
array<float, 4> lightSpecularColor;
array<float, 4> lightAmbientColor;

// 乱数生成器
random_device seed;
mt19937 engine(seed());
// 一様分布[-5.0, 5.0]
uniform_real_distribution<float> uniformDistribution(-5.0, 5.0);
// 指数分布(隕石の1ミリ秒間における平均発生回数: 0.002回)
exponential_distribution<float> exponentialDistribution(0.002);

// 次に隕石が発生する時刻
chrono::system_clock::time_point nextTime;

// オブジェクトの更新
void update() 
{
	// 現在時刻
	auto time(chrono::system_clock::now());

	// 現在時刻が次に隕石発生時刻を超えたら隕石を発生させる
	if (time > nextTime)
	{
		meteorites.emplace_back();
		meteorites.back().setPosition({
			uniformDistribution(engine), // x座標は一様分布に従う
			uniformDistribution(engine), // y座標は一様分布に従う
			100.0                        // z座標は100で固定
		});

		// 次に隕石が発生するまでの時間は指数分布に従う
		nextTime = time + chrono::milliseconds(static_cast<int>(exponentialDistribution(engine)));
	}

	meteorites.erase(remove_if(begin(meteorites), end(meteorites), [](const auto& meteorite)
	{
		return meteorite.getPosition()[2] < cameraPosition[2];
	}), end(meteorites));

	// 隕石の更新
	for_each(begin(meteorites), end(meteorites), [](auto& meteorite)
	{
		meteorite.update();
	});

	// ロケットの更新
	rocket.update();

	glutPostRedisplay();
}

// オブジェクトの描画
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 隕石の描画
	for_each(begin(meteorites), end(meteorites), [](const auto& meteorite)
	{
		meteorite.draw();
	});

	// ロケットの描画
	rocket.draw();

	glutSwapBuffers();
}

// キーボードコールバック関数
void keyboard(unsigned char key, int x, int y)
{
	array<float, 3> vx(0.1, 0.0, 0.0);
	array<float, 3> vy(0.0, 0.1, 0.0);
	array<float, 3> vz(0.0, 0.0, 0.1);
	switch (key) {
	case GLUT_KEY_UP:
		rocket.setPosition(rocket.getPosition() + vz);
		break;

	case GLUT_KEY_LEFT:
		rocket.setPosition(rocket.getPosition() - vx);
		break;

	case GLUT_KEY_RIGHT:
		rocket.setPosition(rocket.getPosition() + vx);

	case GLUT_KEY_DOWN:
		rocket.setPosition(rocket.getPosition() - vz);
	}
	
	/* 
		キーボード入力によってロケットの位置や向きを更新

		(例) ロケットの位置を(x, y, z)だけ移動させる場合
			
			array<float, 3> v(x, y, z);
			rocket.setPosition(rocket.getPosition() + v);
	*/
}

// ウィンドウリサイズコールバック関数
void resize(int width, int height)
{
	/*
		ウィンドウサイズが変更された場合でも対応できるようにする
	*/
}

// glの初期化
void setup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// カメラ初期位置(0.0, 0.0, 0.0)
	// カメラ初期注視点(0.0, 0.0, 1.0)
	// カメラ初期上向きベクトル(0.0, -1.0, 0.0)
	cameraPosition[0] = 0.0;
	cameraPosition[1] = 0.0;
	cameraPosition[2] = 0.0;

	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], 
		0.0, 0.0, 1.0, 0.0, -1.0, 0.0);

	// ライト初期位置(0.0, 10.0, 0.0)
	// ライト拡散反射光(白)
	// ライト環境光(白)
	// ライト鏡面反射光(白)
	lightPosition[0] = 0.0;
	lightPosition[1] = 10.0; 
	lightPosition[2] = 0.0; 
	lightPosition[3] = 1.0;

	lightDiffuseColor[0] = 1.0;
	lightDiffuseColor[1] = 1.0; 
	lightDiffuseColor[2] = 1.0; 
	lightDiffuseColor[3] = 1.0;

	lightAmbientColor[0] = 1.0;
	lightAmbientColor[1] = 1.0;
	lightAmbientColor[2] = 1.0;
	lightAmbientColor[3] = 1.0;

	lightSpecularColor[0] = 1.0;
	lightSpecularColor[1] = 1.0;
	lightSpecularColor[2] = 1.0;
	lightSpecularColor[3] = 1.0;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor.data());
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularColor.data());

	// 背景色(白)
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutIdleFunc(update);
	glutDisplayFunc(draw);
	glutSpecialFunc(keyboard);
	glutReshapeFunc(resize);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("");

	setup();
	glutMainLoop();
	
	return 0;
}
