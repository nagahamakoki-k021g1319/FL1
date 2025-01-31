#pragma once
class FinalTest
{
public:

	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

	void Calculation(int voState, int daState, int viState, int point);
	int CalculationState(int num);
	int CalculationRequiredScore(int point);

private:
	int border[4] = { 11500,13000,14500,16000 };
	int maxState = 1800;
	int pointSeparator[5] = { 1500,2250,3050,3450,3650 };
	

};
