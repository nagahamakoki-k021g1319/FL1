#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);

	// Lambert反射
	float4 shade_color={0, 0, 0, 1};

	//ライト
	for(int i = 0; i < 3; i++)
	{
		if(dirLights[i].active){
			//HalfLamberet
			float NdotL = dot(dirLights[i].lightVec,input.normal);
			float cos = pow(NdotL * 0.5f + 0.7f, 2.0f);

			shade_color.rgb += cos * dirLights[i].lightColor;
		}
	}
	shade_color.rgb = saturate(shade_color.rgb);

	//丸影
	for(int i = 0; i < 1; i++)
	{
		if(circleShadows[i].active){
			float3 casterVec  = circleShadows[i].casterPos - input.svpos.xyz;
			float d = dot(casterVec, circleShadows[i].dir);
			float atten = saturate(1.0f/(circleShadows[i].atten.x + circleShadows[i].atten.y*d+circleShadows[i].atten.z*d*d));
			atten *= step(0, d);
			float3 lightPos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
			float3 lightVec = normalize(lightPos - input.svpos.xyz);
			float cos = dot(lightVec, circleShadows[i].dir);
			float angleatten = smoothstep(circleShadows[i].factorAngleCos.y, circleShadows[i].factorAngleCos.x, cos);
			atten *= angleatten;
			
			shade_color.rgb -= atten;
		}
	}

	// 陰影とテクスチャの色を合成
	return shade_color * texcolor;
}