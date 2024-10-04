#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	//環境反射光
	float3 ambient = m_ambient;
	float3 shade_color = {0,0,0};

	if(enableLighting){
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
		for(int i = 0; i < CIRCLESHADOW_NUM; i++)
		{
			if (circleShadows[i].active != 0)
			{
				//オブジェクト表面からキャスターへのベクトル
			    float3 casterv = circleShadows[i].casterPos - input.worldpos.xyz;
				//東映方向での減衰
			   float d = dot(casterv, circleShadows[i].dir);
				//距離減衰係数
			   float atten = saturate(1.0f / (circleShadows[i].atten.x + circleShadows[i].atten.y * d + circleShadows[i].atten.z * d * d));
				//距離がminusなら0にする
			   atten *= step(0, d);
				//仮想ライトの座標
			   float3 lightpos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
				//オブジェクト表面からライトへのベクトル
			   float3 lightv = normalize(lightpos - input.worldpos.xyz);
				//角度減衰
			   float cos = dot(lightv, circleShadows[i].dir);
				//減衰開始角度から、減衰終了角度にかけて減衰
				//減衰開始角度の内側は1倍減衰終了角度の外側は0倍の光度
			   float angleatten = smoothstep(circleShadows[i].factorAngleCos.x, circleShadows[i].factorAngleCos.y, cos);
				//角度減衰を乗算
			   atten *= angleatten;

				//すべてを減算する
			   shade_color.rgb -= atten;
			}
		}
	}else{
		shade_color.rgb = float3(1,1,1);
	}
	
	
	return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
}