cbuffer cbuff0 : register(b0){
	matrix viewProj;
    matrix world;
    float3 cameraPos;
	uint enableLighting;
};

cbuffer cbuff1 : register(b1) {
	float3 m_ambient : packoffset(c0); //アンビエント係数
	float3 m_diffuse : packoffset(c1); //ディフューズ係数
	float3 m_specular : packoffset(c2); //スペキュラー係数
	float m_alpha : packoffset(c2.w); //アルファ
}

static const uint DIR_LIGHT_NUM = 3;
struct DirLight{
	float3 lightVec;
	float3 lightColor;
	uint active;
};

static const uint CIRCLESHADOW_NUM = 15;
struct CircleShadow{
	float3 dir;
	float3 casterPos;
	float distanceCasterLight;
	float3 atten;
	float2 factorAngleCos;
	uint active;
};

cbuffer cbuff0 : register(b2){
	float3 ambientColor;
	DirLight dirLights[DIR_LIGHT_NUM];
	CircleShadow circleShadows[CIRCLESHADOW_NUM];
}

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float3 normal :NORMAL; // 法線ベクトル
	float2 uv  :TEXCOORD; // uv値
	float4 worldpos : POSITION;
};
