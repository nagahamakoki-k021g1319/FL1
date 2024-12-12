#pragma once
#include "Affin.h"
#include "Vector2.h"
#include "Vector4.h"
#include "DirectXCommon.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4820)
#pragma warning(disable: 4061)
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <vector>
#include <cmath>
#include <wrl.h>
#pragma warning(pop)

using namespace Microsoft::WRL;
using namespace MyEngine;

constexpr float PI = 3.1415926535f;

//struct Vertex {
//	float x, y, z;      // Position
//	float pad;
//	float r, g, b, a;   // Color
//};
/*
class DonutGraph {
public:
	DonutGraph(UINT segmentCount, const std::vector<MyEngine::Vector4>& colors)
		: segmentCount(segmentCount), colors(colors) {
		GenerateVertices();
	}

	void GenerateVertices() {
		float angleStep = 2 * PI / segmentCount;
		float innerRadius = 0.3f;
		float outerRadius = 0.5f;

		for (UINT i = 0; i < segmentCount; ++i) {
			float startAngle = i * angleStep;
			float endAngle = startAngle + angleStep;

			MyEngine::Vector4 color = colors[i % colors.size()];

			// 頂点の生成 (外側と内側の頂点を作成)
			vertices.push_back({ outerRadius * cosf(startAngle), outerRadius * sinf(startAngle), 0.0f, color.x, color.y, color.z, color.w });
			vertices.push_back({ innerRadius * cosf(startAngle), innerRadius * sinf(startAngle), 0.0f, color.x, color.y, color.z, color.w });
			vertices.push_back({ outerRadius * cosf(endAngle), outerRadius * sinf(endAngle), 0.0f, color.x, color.y, color.z, color.w });
			vertices.push_back({ innerRadius * cosf(endAngle), innerRadius * sinf(endAngle), 0.0f, color.x, color.y, color.z, color.w });

			// インデックスの生成
			int baseIndex = i * 4;
			indices.push_back(baseIndex);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 2);

			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 3);
			indices.push_back(baseIndex + 2);
		}
	}
	void Initialize();
	void Update();
	void Draw();

	const std::vector<Vertex>& GetVertices() const { return vertices; }
	const std::vector<UINT>& GetIndices() const { return indices; }

private:


	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;


	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// テクスチャバッファ
	ComPtr<ID3D12Resource>texBuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	UINT sizeVB;
	// 頂点データ配列
	std::vector<Vertex> vertices;
	std::vector<UINT> indices;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;

private:
	UINT segmentCount;
	std::vector<MyEngine::Vector4> colors;

};*/



	//DonutGraph donutGraph(segmentCount, colors);


class DonutGraph
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略

public:
	/// <summary>
	/// 頂点データ構造体
	/// </summary>
	struct VertexPosColor {
		Vector3 pos;      // Position
		float pad;
		Vector4 color;   // Color
	};

	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData {
		Vector4 color; // 色 (RGBA)
		Matrix4 mat;   // ３Ｄ変換行列
	};

	//デフォルトテクスチャ格納ディレクトリ
	std::string kDefaultTextureDirectoryPath = "Resources/";

	UINT segmentCount_ = 12;
	std::vector<MyEngine::Vector4> colors_ = {
		MyEngine::Vector4(1.0f, 0.0f, 0.0f, 1.0f),  // Red
		MyEngine::Vector4(0.0f, 1.0f, 0.0f, 1.0f),  // Green
		MyEngine::Vector4(0.0f, 0.0f, 1.0f, 1.0f)   // Blue
	};
	~DonutGraph() {
		Finalize();
	}
	DonutGraph(){
		GenerateVertices();
	}
	DonutGraph(UINT segmentCount, const std::vector<MyEngine::Vector4>& colors)
		: segmentCount_(segmentCount), colors_(colors) {
		GenerateVertices();
	}

	void GenerateVertices() {
		float angleStep = 2 * PI / segmentCount_;
		float innerRadius = 0.3f;
		float outerRadius = 0.5f;

		for (UINT i = 0; i < segmentCount_; ++i) {
			float startAngle = i * angleStep;
			float endAngle = startAngle + angleStep;

			MyEngine::Vector4 color = colors_[i % colors_.size()];

			// 頂点の生成 (外側と内側の頂点を作成)
			vertices.push_back({ { outerRadius * cosf(startAngle), outerRadius * sinf(startAngle), 0.0f }, 0.0f,{ color.x, color.y, color.z, color.w} });
			vertices.push_back({ { innerRadius * cosf(startAngle), innerRadius * sinf(startAngle), 0.0f}, 0.0f,{color.x, color.y, color.z, color.w } });
			vertices.push_back({ { outerRadius * cosf(endAngle), outerRadius * sinf(endAngle), 0.0f}, 0.0f,{color.x, color.y, color.z, color.w} });
			vertices.push_back({ { innerRadius * cosf(endAngle), innerRadius * sinf(endAngle), 0.0f},0.0f,{color.x, color.y, color.z, color.w } });

			// インデックスの生成
			int baseIndex = i * 4;
			indices.push_back(baseIndex);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 2);

			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 3);
			indices.push_back(baseIndex + 2);
		}
	}

	const std::vector<VertexPosColor>& GetVertices() const { return vertices; }
	const std::vector<UINT>& GetIndices() const { return indices; }

	void SetSizeGraph(Vector2 size) { sizeGraph = size; };
public:

	 void Initialize(DirectXCommon* dxCommon);

	 void Finalize();

	/// <summary>
	/// パイプライン生成
	/// </summary>
	 void CreatGraphicsPipeline();

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	 void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画処理
	/// </summary>
	 void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンド処理</param>
	 void PostDrawScene();

	 void SetShadeNumber(int SetShadeNumber);

	 void SetKernelSize(int range);

	 void SetRadialBlur(Vector2 senter, float intensity, int sample);

private://静的メンバ変数
	static const float clearColor[4];

	static ID3D12Device* device_;

	static ID3D12GraphicsCommandList* commandList;


	static ComPtr<ID3D12Resource> vertBuff;	//頂点バッファ

	//頂点バッファビューの作成
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	static ComPtr<ID3D12Resource> texBuff;

	static ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//深度バッファ
	static ComPtr<ID3D12Resource> depthBuff;
	//RTV用のデスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用のデスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static ComPtr<ID3D12PipelineState> pipelineState;
	static ComPtr<ID3D12RootSignature> rootSignature;
private:
	// 定数バッファ
	static ComPtr<ID3D12Resource> constDataBuff_;

	//// マッピング済みアドレス
	//static SendDataGPU* dataMap;

private:
	// 頂点データ配列
	std::vector<VertexPosColor> vertices;
	std::vector<VertexPosColor*> vertMap;
	std::vector<UINT> indices;

	//UINT segmentCount;
	//std::vector<MyEngine::Vector4> colors;

	static Vector2 sizeGraph;
};

