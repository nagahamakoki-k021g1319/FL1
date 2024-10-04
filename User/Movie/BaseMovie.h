#pragma once
#include "Input.h"
#include <array>
#include "Sprite.h"
#include <memory>

class TGameCamera;

class BaseMovie {
public:
	// デストラクタ
	virtual ~BaseMovie();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update(TGameCamera* camera);

	// 描画
	void Draw();

	// ムービーバー初期化
	void MovieBarInInit();
	void MovieBarOutInit();

	// ムービーバーにょっき
	void MovieBarOut(const float timer);

	// ムービーバーにょっき
	void MovieBarIn(const float timer);

	const bool& GetIsFinish() const;

	void SetIsFinish(bool isFinish);

protected:
	bool isFinish_ = 0;
	float phaseTimer_ = 0;
	float phaseTime_ = 0;

	std::array<std::unique_ptr<Sprite>, 2> movieBar_;
	std::array<MyEngine::Vector2, 2> movieBarPos_;
};
