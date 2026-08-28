// cl: /O2 /Ob0
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xA74];
	unsigned char m_disableCameraMovement;
};

extern GlobalData *TheWritableGlobalData;

class Rva0073B880
{
	char m_pad0[0x58];
	int m_58;
	char m_pad1[4];
	int m_60;
	int m_64;
	char m_pad2[0x27D - 0x68];
	unsigned char m_27D;

public:
	void set(int value);
};

void Rva0073B880::set(int value)
{
	if (!TheWritableGlobalData->m_disableCameraMovement || value == 0)
	{
		m_58 = value;
		m_64 = 0;
		m_60 = 0;
		m_27D = 0;
	}
}
