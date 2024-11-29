//頂点シェーダーの出力構造体
//(頂点シェーダーからピクセルシェーダーへのやり取りに使用する)
struct VSOutput
{
	//システム用頂点座標
    float4 svpos : SV_POSITION;
	//UV値
    float2 uv : TEXCOORD;
};

cbuffer VertexPosColor : register(b0) //送られてきた情報
{
    float3 position;
    float padding;
    float4 color;
}