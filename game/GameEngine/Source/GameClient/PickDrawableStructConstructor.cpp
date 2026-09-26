// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// BFME's PickDrawableStruct constructor.  The retail kind-of storage is six
// dwords; the second six-dword region is part of the shipped object layout and
// is explicitly cleared along with the first.  Only the first region is
// consumed by the selection filter.

class BfmeKindOfMask
{
public:
	unsigned int m_words[6];
};

class InGameUI
{
private:
	unsigned char m_padding00[0x12b1];

public:
	bool m_forceAttackMode;
};

extern InGameUI *TheInGameUI;

class Open24590D0Out
{
public:
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;
	unsigned int m_fourth;
	unsigned int m_fifth;
};

extern int Rva00459060(bool mode);
extern void Rva004590D0(unsigned int flags, Open24590D0Out *out);

struct PickDrawableStruct
{
	void *drawableListToFill;
	bool forceAttackMode;
	unsigned char m_reserved;
	unsigned char m_padding06[2];
	BfmeKindOfMask kindofsToMatch;
	BfmeKindOfMask m_reservedMask;

	PickDrawableStruct();
};

PickDrawableStruct::PickDrawableStruct()
{
	m_reserved = 0;
	for (unsigned int i = 0; i != 6; ++i)
	{
		kindofsToMatch.m_words[i] = 0;
	}
	for (unsigned int i = 0; i != 6; ++i)
	{
		m_reservedMask.m_words[i] = 0;
	}
	drawableListToFill = 0;
	forceAttackMode = 0;
	for (unsigned int i = 0; i != 6; ++i)
	{
		kindofsToMatch.m_words[i] = 0;
	}
	for (unsigned int i = 0; i != 6; ++i)
	{
		m_reservedMask.m_words[i] = 0;
	}
	forceAttackMode = TheInGameUI->m_forceAttackMode;
	unsigned int pickType = (unsigned int)Rva00459060(forceAttackMode);
	Rva004590D0(pickType, (Open24590D0Out *)&kindofsToMatch);
	if (!forceAttackMode)
	{
		*(unsigned int *)((unsigned char *)this + 0x0c) |= 0x02000000;
	}
}
