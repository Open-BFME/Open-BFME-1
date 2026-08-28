// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xB8C];
	int m_B8C;
};

extern GlobalData *TheWritableGlobalData;

class Rva00336870
{
public:
	void set(int value);
};

void Rva00336870::set(int value)
{
	if (value >= 0)
		TheWritableGlobalData->m_B8C = value;
}
