// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const char *text);
};

void __stdcall armyNameFromIndex(unsigned int index, AsciiString *out)
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
