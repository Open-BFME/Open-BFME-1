// cl: /DNDEBUG /MD /EHsc
// readable body of ??1CountUpTransition@@UAE@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// Open-BFME5: CountUpTransition dtor.
// Early derived vtbl, zero +0x0c, dual Buffer @+0x2c/+0x30, base dtor.

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

class CountUpTransitionBase
{
public:
	virtual ~CountUpTransitionBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class CountUpTransition : public CountUpTransitionBase
{
public:
	virtual ~CountUpTransition();
private:
	unsigned char m_gap[8]; // +0x04 .. +0x0b
	unsigned int m_zero; // +0x0c
	unsigned char m_gap2[0x1c]; // +0x10 .. +0x2b
	CountUpBuffer m_a; // +0x2c
	CountUpBuffer m_b; // +0x30
};

// ??1CountUpTransition@@UAE@XZ
CountUpTransition::~CountUpTransition()
{
	m_zero = 0;
}
