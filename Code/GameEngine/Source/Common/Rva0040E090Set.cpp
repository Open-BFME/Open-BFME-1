// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xC58];
	unsigned char m_C58;
};

extern GlobalData *TheWritableGlobalData;

class Rva0040E090
{
	char m_pad[0x2C];
	int m_2C;
	int m_30;

public:
	void set(int a, int b);
};

void Rva0040E090::set(int a, int b)
{
	m_2C = a;
	m_30 = b;
	TheWritableGlobalData->m_C58 = (unsigned char)(a == 0x40D779);
}
