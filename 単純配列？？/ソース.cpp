
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "SimpleArray.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SimpleArray<int> SA{ 1,2,3 };

	ShowArrayA(SA);

	SimpleArray<int> SB{SA};
	ShowArrayB(SB);
	SB[0] = 0xbadface;

	auto SC = SA;
	SC[0] = 0xdeadbeef;
	ShowArrayA(SC);

	SB = SC;
	ShowArrayB(SB);

	ShowArrayA(SA);

	SharedArray<int> SD = MakeArray<int>({ 4,5,6 });
	ShowArrayA(*SD);
	return 0;
}