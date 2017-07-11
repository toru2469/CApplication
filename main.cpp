/******************************************************************************************************************************

	C Application Development (17/07/08)

	------これから実装すべき箇所------

	1. Objectクラス(object.hpp)の衝突判定関数colling
	2. Rocketクラス(object.hpp)の描画関数draw
	3. Meteoriteクラス(object.hpp)の描画関数draw
	4. 衝突した際の挙動をどうするか

	------OpenGL(Glut)のインストール方法(Visual Studio)------

	1. Visual StudioのツールメニューからNuGetパッケージマネージャーからソリューションのNuGetパッケージの管理を開く
	2. 参照タブを開いてインターネットに接続されている状態でglutと検索
	3. nupengl.coreというライブラリが出てくるのでインストールを押すだけ
	
	------ベクトル演算のためのライブラリEigenのインストール方法(Visual Studio)------

	1. Visual StudioのツールメニューからNuGetパッケージマネージャーからソリューションのNuGetパッケージの管理を開く
	2. 参照タブを開いてインターネットに接続されている状態でeigenと検索
	3. eigenというライブラリが出てくるのでインストールを押すだけ

	------Eigenの基本的な使い方------

	1. 初期化: Vector3f v1(1.0, 2.0, 3.0); や Vector3f v2(v1); など
	2. 代入: v1 << 1.0, 2.0, 3.0; や v1 = v2; など
	3. 要素へのアクセス: v1.x() = 1.0; や float x = v.x(); など
	4. 演算: v1 + v2, v1 - v2, v1 * 1.0, v1 / 1.0, v1.dot(v2), v1.cross(v2) など
	5. 関数 f(const Vector3f& v) などに引数として渡す場合は f(v1) 以外にも f({ 1.0, 2.0, 3.0 }) などとできる

******************************************************************************************************************************/

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include "object.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"

int mySpecialValue = 0;

using namespace std;
using namespace Eigen;

// ロケット
unique_ptr<Object> rocket;
// 隕石
vector<unique_ptr<Object>> meteorites;

// カメラ
Camera camera;
// ライト
Light light;

// 乱数生成器
random_device seed;
mt19937 engine(seed());

// 指数分布(1ミリ秒間における隕石の平均発生回数: 0.002回)
exponential_distribution<float> exponentialDistribution(0.002f);
// 次に隕石が発生する時刻
chrono::system_clock::time_point nextTime(chrono::system_clock::now());

// オブジェクトの更新
void update() 
{
	// 現在時刻
	auto time(chrono::system_clock::now());

	// 現在時刻が次に隕石発生時刻を超えたら隕石を発生させる
	if (time > nextTime)
	{
		unique_ptr<Object> meteorite(make_unique<Meteorite>());

		// 隕石は常にロケットの位置の近くに発生するように正規分布を生成(標準偏差: 2.0)
		normal_distribution<float> xDistribution(rocket->getPosition().x(), 2.0f);
		normal_distribution<float> yDistribution(rocket->getPosition().y(), 2.0f);

		// 位置、速度、加速度をセット
		meteorite->setPosition({ xDistribution(engine), yDistribution(engine), 100.0f });
		meteorite->setVelocity({ 0.0f, 0.0f, -0.01f });
		meteorite->setAcceleration({ 0.0f, 0.0f, 0.0f });

		// マテリアルはとりあえず全部白
		Material material;
		material.setDiffuseColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		material.setAmbientColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		material.setSpecularColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		material.setShininess(10.0f);

		meteorite->setMaterial(move(material));

		// 配列にプッシュ
		meteorites.push_back(move(meteorite));

		// 次に隕石が発生するまでの時間は指数分布に従う
		nextTime = time + chrono::milliseconds(static_cast<int>(exponentialDistribution(engine)));
	}

	// カメラを通り過ぎた隕石は消滅
	meteorites.erase(remove_if(begin(meteorites), end(meteorites), [](const auto& meteorite)
	{
		return meteorite->getPosition().z() < camera.getPosition().z();
	}), end(meteorites));

	// 隕石の更新
	for_each(begin(meteorites), end(meteorites), [](auto& meteorite)
	{
		meteorite->update();
	});

	// ロケットの更新
	rocket->update();

	glutPostRedisplay();
}

// オブジェクトの描画
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 隕石の描画
	for_each(begin(meteorites), end(meteorites), [](const auto& meteorite)
	{
		meteorite->draw();
	});

	// ロケットの描画
	rocket->draw();

	glutSwapBuffers();
}

void myTimerFunc(int value)
{
	
	//上下左右移動
	if (mySpecialValue & (1 << 0)) // UP
	{
		rocket->setPosition(rocket->getPosition() + Vector3f(0.0f, -0.15f, 0.0f));
		camera.setPosition(camera.getPosition() + Vector3f(0.0f, -0.15f, 0.0f));
		camera.setTarget(camera.getPosition() + Vector3f(0.0f, 0.0f, 0.15f));
		camera.begin();
	}
	if (mySpecialValue & (1 << 1)) // LEFT
	{
		rocket->setPosition(rocket->getPosition() + Vector3f(-0.15f, 0.0f, 0.0f));
		camera.setPosition(camera.getPosition() + Vector3f(-0.15f, 0.0f, 0.0f));
		camera.setTarget(camera.getPosition() + Vector3f(0.0f, 0.0f, 0.15f));
		camera.begin();
	}
	if (mySpecialValue & (1 << 2)) // RIGHT
	{
		rocket->setPosition(rocket->getPosition() + Vector3f(+0.15f, 0.0f, 0.0f));
		camera.setPosition(camera.getPosition() + Vector3f(+0.15f, 0.0f, 0.0f));
		camera.setTarget(camera.getPosition() + Vector3f(0.0f, 0.0f, 0.15f));
		camera.begin();
	}
	if (mySpecialValue & (1 << 3)) // DOWN
	{
		rocket->setPosition(rocket->getPosition() + Vector3f(0.0f, +0.15f, 0.0f));
		camera.setPosition(camera.getPosition() + Vector3f(0.0f, +0.15f, 0.0f));
		camera.setTarget(camera.getPosition() + Vector3f(0.0f, 0.0f, 0.15f));
		camera.begin();
	}
	glutTimerFunc(10, myTimerFunc, 0);
}

// キーボードコールバック関数
void keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue |= 1 << 0;//mySpecialValueの1bit目を1にする
		break;

	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;//mySpecialValueの2bit目を1にする
		break;

	case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;//mySpecialValueの3bit目を1にする
		break;

	case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;//mySpecialValueの4bit目を1にする
		break;
	}
}

void keyboardUP(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue &= ~(1 << 0);//mySpecialValueの1bit目を0にする
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);//mySpecialValueの2bit目を0にする
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);//mySpecialValueの3bit目を0にする
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);//mySpecialValueの4bit目を0にする
		break;
	default:
		break;
	}

}

// ウィンドウリサイズコールバック関数
void resize(int width, int height)
{
	/*
		ウィンドウサイズが変更された場合でも対応できるようにする
	*/
}

// glの設定
void setup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// カメラ初期位置(0.0, 0.0, 0.0)
	// カメラ初期注視点(0.0, 0.0, 1.0)
	// カメラ初期上向きベクトル(0.0, -1.0, 0.0)
	camera.setPosition({ 0.0f, 0.0f, 0.0f });
	camera.setTarget({ 0.0f, 0.0f, 1.0f });
	camera.setUpVector({ 0.0f, -1.0f, 0.0f });
	camera.begin();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// ライト初期位置(0.0, 10.0, 0.0)
	// ライト拡散反射光(白)
	// ライト環境光(白)
	// ライト鏡面反射光(白)
	light.setPosition({ 0.0f, 10.0f, 0.0f, 1.0f });
	light.setDiffuseColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	light.setAmbientColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	light.setSpecularColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	light.begin();

	// 背景色(黒)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	rocket = make_unique<Rocket>();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("");

	glutIdleFunc(update);
	glutDisplayFunc(draw);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUP);
	glutReshapeFunc(resize);
	myTimerFunc(0);

	setup();
	glutMainLoop();
	
	return 0;
}
