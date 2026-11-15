// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail 0x003601A0, 100 bytes. A thiscall member that ignores this: the
// matched caller BfmeFirstWalkOnArmy::lookupWaypoints (0x00360220) loads ecx
// (mov ecx,edx) before calling it through ILT 0x00038915.
class BfmeFirstWalkOnArmy
{
public:
	void armyNameFromIndex(unsigned int index, AsciiString *out);
};

void BfmeFirstWalkOnArmy::armyNameFromIndex(unsigned int index, AsciiString *out)
{
	switch (index)
	{
	case 0:
		*out = "TopArmy";
		break;
	case 3:
		*out = "BottomArmy";
		break;
	case 2:
		*out = "RightArmy";
		break;
	case 1:
		*out = "LeftArmy";
		break;
	}
}
