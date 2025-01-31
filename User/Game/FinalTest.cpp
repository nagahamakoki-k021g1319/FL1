#include "FinalTest.h"
#include<math.h>

void FinalTest::Initialize()
{
}

void FinalTest::Update(){

}


void FinalTest::Calculation(int voState, int daState, int viState, int score) {
    int totalStatePoint = static_cast<int>(floor((CalculationState(voState) + CalculationState(daState) + CalculationState(viState)) * 2.3f));
    int scorePoint = CalculationRequiredScore(score);
    int totalPoint = totalStatePoint + scorePoint;

    if (totalPoint<=border[0]) {
        //a
    }else if (totalPoint <= border[1]) {
        //s
    }else if (totalPoint <= border[2]) {
        //s+
    }else if (totalPoint <= border[3]) {
        //ss
    }
}

int FinalTest::CalculationState(int num) {
	int result;
	if (num <= 1770) {
		result = num + 30;
	}else {
		result = 1800;
	}
	return result;
}

int FinalTest::CalculationRequiredScore(int point) {
    int result;
    if (point <= 1500) {
        result = point / 0.3;
    }else if (point <= 2250) {
        result = 5000 + ceil((point - 1500) / 0.15f);
    }else if (point <= 3050) {
        result = 10000 + ceil((point - 2250) / 0.08f);
    }else if (point <= 3450) {
        result = 20000 + ceil((point - 3050) / 0.04f);
    }else if (point <= 3650) {
        result = 30000 + ceil((point - 3450) / 0.02f);
    } else {
        result = 40000 + ceil((point - 3650) / 0.01f);
    }
    return result;
}

void FinalTest::Draw()
{
}

void FinalTest::ApplyGlobalVariables()
{
}