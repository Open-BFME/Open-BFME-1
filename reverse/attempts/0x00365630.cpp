// ?bfmeApplyPair@LivingWorldPlayerArmy@@QAEXPAX0@Z
// partial score=0.9975 date=2026-09-25
// ?bfmeApplyPair@LivingWorldPlayerArmy@@QAEXPAX0@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include <vector>

class AsciiString;

struct AsciiSlot
{
	void *m_data;
};

struct WideSlot
{
	void *m_data;
};

class LivingWorldArmy
{
public:
	LivingWorldArmy(const LivingWorldArmy &other);
	virtual ~LivingWorldArmy();
	AsciiString getName() const;
	void copyFrom(const LivingWorldArmy &other);
	LivingWorldArmy &operator=(const LivingWorldArmy &other)
	{
		copyFrom(other);
		return *this;
	}

private:
	AsciiSlot m_name;
	int m_08;
	int m_0c;
	int m_10[6];
	int m_28[3];
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	AsciiSlot m_4c;
	int m_50[10];
	WideSlot m_78;
	int m_7c[6];
	int m_94[6];
	AsciiSlot m_ac;
	AsciiSlot m_b0;
};

#pragma comment(linker, "/alternatename:??0LivingWorldArmy@@QAE@ABV0@@Z=??0BfmeOwnVUM@@QAE@ABV0@@Z")

inline LivingWorldArmy *bfmeArmyAt(unsigned int offset, LivingWorldArmy *start)
{
	return (LivingWorldArmy *)(offset + (unsigned int)start);
}

class LivingWorldPlayerArmy
{
public:
	virtual void slot0();
	LivingWorldArmy *findArmy(const AsciiString &name, int *outIndex);
	void bfmeApplyPair(void *a, void *b);

private:
	char m_prefix[0x2c];
	std::vector<LivingWorldArmy> m_armies;
};

// ?bfmeApplyPair@LivingWorldPlayerArmy@@QAEXPAX0@Z
void LivingWorldPlayerArmy::bfmeApplyPair(void *a, void *b)
{
	LivingWorldPlayerArmy *source = (LivingWorldPlayerArmy *)a;
	unsigned int i = 0;
	if (m_armies.size() != 0)
	{
		unsigned int offset = 0;
		do
		{
			int sourceIndex;
			LivingWorldArmy *found;
			unsigned int base = (unsigned int)m_armies.begin();
			found = source->findArmy(
				((LivingWorldArmy *)(offset + base))->getName(),
				&sourceIndex);
			if (found)
			{
				LivingWorldPlayerArmy *destination = (LivingWorldPlayerArmy *)b;
				destination->m_armies.push_back(*found);
				if (sourceIndex >= 0 && (unsigned int)sourceIndex < source->m_armies.size())
					source->m_armies.erase(source->m_armies.begin() + sourceIndex);
			}
			++i;
			offset += sizeof(LivingWorldArmy);
		} while (i < m_armies.size());
	}
}
