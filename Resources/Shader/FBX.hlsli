cbuffer cbuff0 : register(b0){
	matrix viewProj;
    matrix world;
    float3 cameraPos;
};

static const uint DIR_LIGHT_NUM = 3;
struct DirLight{
	float3 lightVec;
	float3 lightColor;
	uint active;
};

static const uint CIRCLESHADOW_NUM = 1;
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


//ボーンの最大数
static const int MAX_BONES = 32;

cbuffer skinning:register(b3)//ボーンのスキニング行列が入る
{
	matrix matSkinning[MAX_BONES];
}

//バーテックスバッファーの入力
struct VSInput
{
	float4 pos	: POSITION;//位置   
	float3 normal : NORMAL;//頂点法線
	float2 uv	: TEXCOORD;//テクスチャー座標
	uint4  boneIndices : BONEINDICES;//ボーンの番号
	float4 boneWeights : BONEWEIGHTS;//ボーンのスキンウェイト
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float3 normal :NORMAL; // 法線
	float2 uv  :TEXCOORD; // uv値
};

