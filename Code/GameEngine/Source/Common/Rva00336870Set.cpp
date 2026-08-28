// cl: /O2 /Ob0
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xB8C];
	int m_maxParticleCount;
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
		TheWritableGlobalData->m_maxParticleCount = value;
}
