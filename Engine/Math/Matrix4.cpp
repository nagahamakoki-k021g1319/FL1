/**
 * @file Matrix4.cpp
 * @brief Matrix4
 */

#include "Matrix4.h"
#include "Affin.h"

using namespace MyEngine;
Matrix4::Matrix4() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0.0f;
		}
	}

}

Matrix4::Matrix4(float num) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = num;
		}
	}

}

// 成分を指定しての生成
Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Matrix4 Matrix4::Initialize() {
	Matrix4 matInitialize{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matInitialize;
}

Vector3 Matrix4::transform(const Vector3& v, const Matrix4& matrix4) {

	float w = v.x * matrix4.m[0][3] + v.y * matrix4.m[1][3] + v.z * matrix4.m[2][3] + matrix4.m[3][3];

	Vector3 result{
		(v.x * matrix4.m[0][0] + v.y * matrix4.m[1][0] + v.z * matrix4.m[2][0] + matrix4.m[3][0]) / w,
		(v.x * matrix4.m[0][1] + v.y * matrix4.m[1][1] + v.z * matrix4.m[2][1] + matrix4.m[3][1]) / w,
		(v.x * matrix4.m[0][2] + v.y * matrix4.m[1][2] + v.z * matrix4.m[2][2] + matrix4.m[3][2]) / w,
	};

	return result;
}

Matrix4 Matrix4::MakeInverse(const Matrix4* mat)
{
	assert(mat);

	//掃き出し法を行う行列
	float sweep[4][8]{};
	//定数倍用
	float constTimes = 0.0f;
	//許容する誤差
	float MAX_ERR = 1e-10f;
	//戻り値用
	Matrix4 retMat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//weepの左側に逆行列を求める行列をセット
			sweep[i][j] = mat->m[i][j];

			//sweepの右側に単位行列をセット
			sweep[i][4 + j] = MakeIdentity().m[i][j];
		}
	}

	//全ての列の対角成分に対する繰り返し
	for (int i = 0; i < 4; i++)
	{
		//最大の絶対値を注目対角成分の絶対値と仮定
		float max = float(fabs(sweep[i][i]));
		int maxIndex = i;

		//i列目が最大の絶対値となる行を探す
		for (int j = i + 1; j < 4; j++)
		{
			if (fabs(sweep[j][i]) > max)
			{
				max = float(fabs(sweep[j][i]));
				maxIndex = j;
			}
		}

		if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
		{
			//逆行列は求められない
			return MakeIdentity();
		}

		//操作(1):i行目とmaxIndex行目を入れ替える
		if (i != maxIndex)
		{
			for (int j = 0; j < 8; j++)
			{
				float tmp = sweep[maxIndex][j];
				sweep[maxIndex][j] = sweep[i][j];
				sweep[i][j] = tmp;
			}
		}

		//sweep[i][i]に掛けると1になる値を求める
		constTimes = 1 / sweep[i][i];

		//操作(2):p行目をa倍する
		for (int j = 0; j < 8; j++)
		{
			//これによりsweep[i][i]が1になる
			sweep[i][j] *= constTimes;
		}

		//操作(3)によりi行目以外の行のi列目を0にする
		for (int j = 0; j < 4; j++)
		{
			if (j == i)
			{
				//i行目はそのまま
				continue;
			}

			//i行目に掛ける値を求める
			constTimes = -sweep[j][i];

			for (int k = 0; k < 8; k++)
			{
				//j行目にi行目をa倍した行を足す
				//これによりsweep[j][i]が0になる
				sweep[j][k] += sweep[i][k] * constTimes;
			}
		}
	}

	//sweepの右半分がmatの逆行列
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			retMat.m[i][j] = sweep[i][4 + j];
		}
	}

	return retMat;
}

void Matrix4::MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix)
{

	float width = 1.0f / (right - left);
	float height = 1.0f / (top - bottom);
	float range = 1.0f / (far_ - near_);

	matrix.m[0][0] = width * 2;

	matrix.m[1][1] = height * 2;

	matrix.m[2][2] = range;

	matrix.m[3][0] = -(left + right) * width;
	matrix.m[3][1] = -(top + bottom) * height;
	matrix.m[3][2] = range * -near_;
	matrix.m[3][3] = 1.0f;

	matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
		matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
		matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;
}

void Matrix4::MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix)
{

	float sinFov = 0.0f;
	float cosFov = 0.0f;
	Affin::SinCos(sinFov, cosFov, 0.5f * fovAngleY);

	float range = far_ / (far_ - near_);
	float height = cosFov / sinFov;

	matrix.m[0][0] = height / aspect;

	matrix.m[1][1] = cosFov / sinFov;

	matrix.m[2][2] = range;
	matrix.m[2][3] = 1.0f;

	matrix.m[3][2] = -range * near_;

	matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
		matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
		matrix.m[2][0] = matrix.m[2][1] =
		matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][3] = 0.0f;
}

void Matrix4::MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat)
{
	Vector3 zVec = target - eye;
	zVec.nomalize();

	Vector3 xVec = up.cross(zVec);
	xVec.nomalize();

	Vector3 yVec = zVec.cross(xVec);
	yVec.nomalize();

	mat.m[0][0] = xVec.x;
	mat.m[0][1] = xVec.y;
	mat.m[0][2] = xVec.z;
	mat.m[1][0] = yVec.x;
	mat.m[1][1] = yVec.y;
	mat.m[1][2] = yVec.z;
	mat.m[2][0] = zVec.x;
	mat.m[2][1] = zVec.y;
	mat.m[2][2] = zVec.z;
	mat.m[3][0] = eye.x;
	mat.m[3][1] = eye.y;
	mat.m[3][2] = eye.z;
}

Vector3 Matrix4::bVelocity(Vector3& velocity, Matrix4& mat) {
	Vector3 result = { 0,0,0 };

	//内積
	result.x = velocity.x * mat.m[0][0] +
			   velocity.y * mat.m[1][0] +
			   velocity.z * mat.m[2][0];

	result.y = velocity.x * mat.m[0][1] +
			   velocity.y * mat.m[1][1] +
			   velocity.z * mat.m[2][1];

	result.z = velocity.x * mat.m[0][2] +
			   velocity.y * mat.m[1][2] +
			   velocity.z * mat.m[2][2];

	return result;
}

Matrix4 Matrix4::Rotation(const Vector3& rotation, int X_1_Y_2_Z_3_XYZ_6) {
	int rotaX = 1;
	int rotaY = 2;
	int rotaZ = 3;

	if (X_1_Y_2_Z_3_XYZ_6 == rotaX) {
		Matrix4 matRotX = {
		  1.0f,0.0f,0.0f,0.0f,
		  0.0f,cosf(rotation.x),sinf(rotation.x),0.0f,
		  0.0f,-sinf(rotation.x),cosf(rotation.x),0.0f,
		  0.0f,0.0f,0.0f,1.0f
		};
		Matrix4 rotationX = Initialize();
		rotationX *= matRotX;

		return rotationX;
	}
	else if (X_1_Y_2_Z_3_XYZ_6 == rotaY) {
		Matrix4 matRotY = {
			cosf(rotation.y), 0.0f, -sinf(rotation.y), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(rotation.y), 0.0f, cosf(rotation.y),  0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		Matrix4 rotationY = Initialize();
		rotationY *= matRotY;

		return rotationY;
	}
	else if (X_1_Y_2_Z_3_XYZ_6 == rotaZ) {
		Matrix4 matRotZ = {
		  cosf(rotation.z),sinf(rotation.z),0.0f,0.0f,
		  -sinf(rotation.z),cosf(rotation.z),0.0f,0.0f,
		  0.0f,0.0f,1.0f,0.0f,
		  0.0f,0.0f,0.0f,1.0f
		};
		Matrix4 rotationZ = Initialize();
		rotationZ *= matRotZ;

		return rotationZ;
	}
	else {
		Matrix4 matRotXYZ;
		Matrix4 matRot_X, matRot_Y, matRot_Z;
		matRot_X = {
		  1.0f,0.0f,0.0f,0.0f,
		  0.0f,cosf(rotation.x),sinf(rotation.x),0.0f,
		  0.0f,-sinf(rotation.x),cosf(rotation.x),0.0f,
		  0.0f,0.0f,0.0f,1.0f
		};
		matRot_Y = {
			cosf(rotation.y), 0.0f, -sinf(rotation.y),
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			sinf(rotation.y), 0.0f, cosf(rotation.y),
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		matRot_Z = {
		  cosf(rotation.z),sinf(rotation.z),0.0f,0.0f,
		  -sinf(rotation.z),cosf(rotation.z),0.0f,0.0f,
		  0.0f,0.0f,1.0f,0.0f,
		  0.0f,0.0f,0.0f,1.0f
		};
		//各軸の回転行列を合成
		matRotXYZ = Initialize();

		matRotXYZ *= matRot_X;
		matRotXYZ *= matRot_Y;
		matRotXYZ *= matRot_Z;

		return matRotXYZ;
	}
}

//	--		 --			--		 --
//	| a b c d |			| A B C D |
//	| e f g h |	   X	| E F G H |
//	| i j k l |			| I J K L |
//	| m n o p |			| M N O P |
//	--		 --			--		 --

Matrix4& MyEngine::operator*=(Matrix4& m1, const Matrix4& m2) {

	Matrix4 result{ 0 };

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			result.m[i][k] =
				m1.m[i][0] * m2.m[0][k] +
				m1.m[i][1] * m2.m[1][k] +
				m1.m[i][2] * m2.m[2][k] +
				m1.m[i][3] * m2.m[3][k];
		}
	}
	m1 = result;
	return m1;
}

// 2項演算子オーバーロード ( 行列と行列の積 )
const Matrix4 MyEngine::operator*(const Matrix4& m1, const Matrix4& m2) {
	Matrix4 result = m1;

	return result *= m2;
}
//2項演算子オーバーロード ( ベクトルと行列の積 )
const Vector3 MyEngine::operator*(const Vector3& v, const Matrix4& m2) {
	Matrix4 mat = Affin::matUnit();
	Vector3 result = mat.transform(v, m2);
	return result;
}
