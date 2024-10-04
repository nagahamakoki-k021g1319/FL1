/**
 * @file ConvertXM.h
 * @brief DirectXMathを自作にクラスに変換
 */

#pragma once
#include <DirectXMath.h>
#include "Matrix4.h"

using namespace DirectX;

namespace MyEngine {
	class ConvertXM
	{

	public:
		/**
		 * @brief XMMATRIXをMatrix4に変換
		*/
		static Matrix4 ConvertXMMATtoMat4(XMMATRIX XMMat);
		/**
		 * @brief Matrix4をXMMATRIXに変換
		*/
		static XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);

		/**
		 * @brief XMFLOAT3をVector3に変換
		*/
		static Vector3 ConvertXMFlo3toVec3(XMFLOAT3 XMFlo3);
		/**
		 * @brief Vector3をXMFLOAT3に変換
		*/
		static XMFLOAT3 ConvertVec3toXMFlo3(Vector3 vec3);

	private:
		XMMATRIX xmMat_;
		Matrix4 mat4_;

		XMFLOAT3 xmFlo3_;
		Vector3 vec3_;

	};
}