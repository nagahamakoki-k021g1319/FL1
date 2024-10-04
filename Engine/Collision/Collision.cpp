/**
 * @file Collision.cpp
 * @brief 衝突判定関数
 */

#include "Collision.h"

using namespace DirectX;
using namespace MyEngine;

void Collision::ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest)
{
	//pointがp0の外側の頂点領域の中にあるかどうかチェック
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	Vector3 p0_p2 = triangle.p2 - triangle.p0;
	Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_p1.dot(p0_pt);
	float d2 = p0_p2.dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0が最近傍
		*closest = triangle.p0;
		return;
	}

	// pointがp1の外側の頂点領域の中にあるかどうかチェック
	Vector3 p1_pt = point - triangle.p1;

	float d3 = p0_p1.dot(p1_pt);
	float d4 = p0_p2.dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1が最近傍
		*closest = triangle.p1;
		return;
	}

	// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// pointがp2の外側の頂点領域の中にあるかどうかチェック
	Vector3 p2_pt = point - triangle.p2;

	float d5 = p0_p1.dot(p2_pt);
	float d6 = p0_p2.dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter)
{
	Vector3 p;

	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	Vector3 v = p - sphere.center;

	float vp = v.dot(v);

	if (vp > sphere.radius * sphere.radius) { return false; }

	if (inter) {
		*inter = p;
	}

	return true;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
	float distV = sphere.center.dot(plane.normal);

	float dist = distV - plane.distance;

	if (fabs(dist) > sphere.radius) { return false; }

	// 擬似交点を計算
	if (inter)
	{
		// 平面上の再接近点を、疑似交点とする
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, Vector3* inter)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値

	float d1 = plane.normal.dot(ray.dir);
	// 裏面には当たらない
	if (d1 > -epsilon)
	{
		return false;
	}

	float d2 = plane.normal.dot(ray.start);
	float dist = d2 - plane.distance;

	float t = dist / -d1;

	if (t < 0) return false;

	// 距離を書き込む
	if (distance)
	{
		*distance = t;
	}

	// 交点を計算
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, Vector3* inter)
{
	Plane plane;

	Vector3 interPlane;
	plane.normal = triangle.normal;
	plane.distance = triangle.normal.dot(triangle.p0);

	if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }

	const float epsilon = 1.0e-5f;

	Vector3 m;

	Vector3 pt_p0 = triangle.p0 - interPlane;
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);

	if (m.dot(triangle.normal) < -epsilon) { return false; }

	// 辺p1_p2について
	Vector3 pt_p1 = triangle.p1 - interPlane;
	Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	// 辺の外側
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// 辺p2_p0について
	Vector3 pt_p2 = triangle.p2 - interPlane;
	Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	// 辺の外側
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}
	if (inter)
	{
		*inter = interPlane;
	}

	// 内側なので、当たっている
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, Vector3* inter)
{
	Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - sphere.radius * sphere.radius;
	// layの始点がsphereの外側にあり(c > 0)、layがsphereから離れていく方向を
	// 差している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// 負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f)
	{
		return false;
	}

	// レイは球と交差している。
	// 交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	// tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::CheckSphere2Cylinder(Sphere& sphere, Cylinder& cylinder, Vector3* inter) {
	//球の中心の高さが円柱の高さの中
	if (sphere.center.y < cylinder.center.y + cylinder.height && sphere.center.y > cylinder.center.y) {
		//高さ無視
		Vector3 side1 = { cylinder.center.x, 0.0f,cylinder.center.z };
		Vector3 side2 = { sphere.center.x, 0.0f,sphere.center.z };
		if (Vector3::Distance(side1, side2) < sphere.radius + cylinder.radius) {
			if (inter) {
				*inter = cylinder.center;
				float angle = atan2f(sphere.center.x - cylinder.center.x, sphere.center.z - cylinder.center.z);
				*inter += {cylinder.radius* sinf(angle), sphere.center.y, cylinder.radius* cosf(angle)};
			}
			return true;
		}
	}

	//上側
	Vector3 up = cylinder.center;
	up.y += cylinder.height;
	if (Vector3::Distance(sphere.center, up) < sphere.radius + cylinder.radius) {
		if (inter) {
			*inter = up + (sphere.center - up) / 2;
		}
		return true;
	}

	//下側
	Vector3 down = cylinder.center;
	if (Vector3::Distance(sphere.center, down) < sphere.radius + cylinder.radius) {
		if (inter) {
			*inter = down + (sphere.center - down) / 2;
		}
		return true;
	}

	return false;
}

bool Collision::CheckCylinder2Cylinder(Cylinder& cylinder1, Cylinder& cylinder2) {
	Vector3 side1 = { cylinder1.center.x, 0.0f, cylinder1.center.z };
	Vector3 side2 = { cylinder2.center.x, 0.0f, cylinder2.center.z };
	if (Vector3::Distance(side1, side2) < cylinder1.radius + cylinder2.radius) {
		if (cylinder1.center.y < cylinder2.center.y + cylinder2.height &&
			cylinder1.center.y + cylinder1.height > cylinder2.center.y) {
			return true;
		}
	}

	return false;
}

bool Collision::BoxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth)
{

	//プレイヤー
	float pXMin = player.x - playerWidth.x;

	float pXMax = player.x + playerWidth.x;

	float pYMin = player.y - playerWidth.y;

	float pYMax = player.y + playerWidth.y;

	float pZMin = player.z - playerWidth.z;

	float pZMax = player.z + playerWidth.z;

	//敵
	//平面
	float eXMin = enemy.x - enemyWidth.x;

	float eXMax = enemy.x + enemyWidth.x;

	float eYMin = enemy.y - enemyWidth.y;

	float eYMax = enemy.y + enemyWidth.y;

	float eZMin = enemy.z - enemyWidth.z;

	float eZMax = enemy.z + enemyWidth.z;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}

bool Collision::BoxCircle(Vector3 boxPos, Vector3 circlePos, Vector3 boxWidth, float circleWidth)
{
	//プレイヤー
	float bXMin = boxPos.x - boxWidth.x;

	float bXMax = boxPos.x + boxWidth.x;

	float bYMin = boxPos.y - boxWidth.y;

	float bYMax = boxPos.y + boxWidth.y;

	float bZMin = boxPos.z - boxWidth.z;

	float bZMax = boxPos.z + boxWidth.z;

	XMFLOAT3 box1 = { bXMax,bYMax,bZMax };

	XMFLOAT3 box2 = { bXMin,bYMax,bZMax };

	XMFLOAT3 box3 = { bXMin,bYMax,bZMin };

	XMFLOAT3 box4 = { bXMax,bYMax,bZMin };

	XMFLOAT3 box5 = { bXMax,bYMin,bZMax };

	XMFLOAT3 box6 = { bXMin,bYMin,bZMax };

	XMFLOAT3 box7 = { bXMin,bYMin,bZMin };

	XMFLOAT3 box8 = { bXMax,bYMin,bZMin };

	double bo1c = (box1.x - circlePos.x) * (box1.x - circlePos.x) + (box1.y - circlePos.y) * (box1.y - circlePos.y) + (box1.z - circlePos.z) * (box1.z - circlePos.z);
	double bo2c = (box2.x - circlePos.x) * (box2.x - circlePos.x) + (box2.y - circlePos.y) * (box2.y - circlePos.y) + (box2.z - circlePos.z) * (box2.z - circlePos.z);
	double bo3c = (box3.x - circlePos.x) * (box3.x - circlePos.x) + (box3.y - circlePos.y) * (box3.y - circlePos.y) + (box3.z - circlePos.z) * (box3.z - circlePos.z);
	double bo4c = (box4.x - circlePos.x) * (box4.x - circlePos.x) + (box4.y - circlePos.y) * (box4.y - circlePos.y) + (box4.z - circlePos.z) * (box4.z - circlePos.z);
	double bo5c = (box5.x - circlePos.x) * (box5.x - circlePos.x) + (box5.y - circlePos.y) * (box5.y - circlePos.y) + (box5.z - circlePos.z) * (box5.z - circlePos.z);
	double bo6c = (box6.x - circlePos.x) * (box6.x - circlePos.x) + (box6.y - circlePos.y) * (box6.y - circlePos.y) + (box6.z - circlePos.z) * (box6.z - circlePos.z);
	double bo7c = (box7.x - circlePos.x) * (box7.x - circlePos.x) + (box7.y - circlePos.y) * (box7.y - circlePos.y) + (box7.z - circlePos.z) * (box7.z - circlePos.z);
	double bo8c = (box8.x - circlePos.x) * (box8.x - circlePos.x) + (box8.y - circlePos.y) * (box8.y - circlePos.y) + (box8.z - circlePos.z) * (box8.z - circlePos.z);

	double circleLen = circleWidth * circleWidth;
	if (circleLen >= bo1c || circleLen >= bo2c || circleLen >= bo3c || circleLen >= bo4c || circleLen >= bo5c || circleLen >= bo6c || circleLen >= bo7c || circleLen >= bo8c) {
		return true;
	}

	return false;
}

bool Collision::CircleCollision(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth)
{
	float lol = { (enemyPos.x - playerPos.x) * (enemyPos.x - playerPos.x) + (enemyPos.y - playerPos.y) * (enemyPos.y - playerPos.y) + (enemyPos.z - playerPos.z) * (enemyPos.z - playerPos.z) };

	float redius = { (playerWidth + enemyWidth) * (playerWidth + enemyWidth) };


	if (lol <= redius) {
		return true;
	}

	return false;
}

bool Collision::CircleCollisionXZ(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth)
{
	float lol = { (enemyPos.x - playerPos.x) * (enemyPos.x - playerPos.x) + (0 - 0) * (0 - 0) + (enemyPos.z - playerPos.z) * (enemyPos.z - playerPos.z) };

	float redius = { (playerWidth + enemyWidth) * (playerWidth + enemyWidth) };

	if (lol <= redius) {
		return true;
	}

	return false;
}

bool Collision::CheckSphere2Sphere(BaseCollider& sphere1, BaseCollider& sphere2, Vector3* inter) {
	if (Vector3::Distance(sphere1.GetCenter(), sphere2.GetCenter()) <= sphere1.GetRad() + sphere2.GetRad()) {
		Vector3 vec = sphere2.GetCenter() - sphere1.GetCenter();
		Vector3 inter_ = vec.nomalize() * sphere1.GetRad() + sphere1.GetCenter();
		*inter = inter_;
		return true;
	}

	return false;
}