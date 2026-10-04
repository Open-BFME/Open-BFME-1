// lane 25 scratch only: HorseHordeContainModuleData destructor reconstruction.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
#include <set>
#include <vector>

extern void j_00017657();
extern void j_00026f35();

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	void releaseBuffer();

private:
	void *m_004;
};

#include "ascii_string.h"

class BfmeHordeContainSplitResultList
{
public:
	virtual void slot0();
	~BfmeHordeContainSplitResultList();
};

// Retail releases this record through the ILT thunk at 0x00026f35.  The name
// stays address-derived so this layout witness cannot collide with the real
// AudioEventRTS destructor (0x000B31F0, AudioEventRTSCopyAndLifetime.cpp).
class Rva002469D0AudioEvent
{
public:
	~Rva002469D0AudioEvent()
	{
		typedef void (Rva002469D0AudioEvent::*Release)();
		union { void (*fn)(); Release call; } u = { j_00026f35 };
		(this->*u.call)();
	}

private:
	unsigned char m_data[0x70];
};

// The destructor only proves member layouts.  These names deliberately carry
// the target RVA until a source or field witness gives the records identities.
class Rva002469D0AudioEntry
{
public:
	~Rva002469D0AudioEntry() {}

private:
	BFMERetailAsciiString m_00;
	BFMERetailAsciiString m_04;
	Rva002469D0AudioEvent m_08;
	Rva002469D0AudioEvent m_78;
};

class Rva002469D0TwoAsciiEntry
{
public:
	~Rva002469D0TwoAsciiEntry() {}

private:
	BFMERetailAsciiString m_00;
	BFMERetailAsciiString m_04;
};

class Rva002469D0OneAsciiEntry
{
public:
	~Rva002469D0OneAsciiEntry() {}

private:
	BFMERetailAsciiString m_00;
};

struct Gen_t_002360c0_k4
{
	int m_00[1];
};

bool operator==(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
bool operator<(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
typedef _STL::_Rb_tree<Gen_t_002360c0_k4, Gen_t_002360c0_k4,
	_STL::_Identity<Gen_t_002360c0_k4>, _STL::less<Gen_t_002360c0_k4>,
	_STL::allocator<Gen_t_002360c0_k4> > Rva002469D0TreeK4;

class HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();

private:
	unsigned char m_004_to_223[0x220];
};

class HorseHordeContainModuleData
	: public HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HorseHordeContainModuleData();

private:
	std::vector<BfmeHordeContainSplitResultList *> m_224;
	std::vector<Rva002469D0AudioEntry *> m_230;
	std::vector<Rva002469D0TwoAsciiEntry *> m_23c;
	AsciiString m_248;
	std::list<int> m_24c;
	Rva002469D0TreeK4 m_250;
	Rva002469D0TreeK4 m_25c;
	unsigned char m_pad268[0x24];
	std::vector<AsciiString> m_28c;
	unsigned char m_pad298[0xc];
	std::vector<Rva002469D0OneAsciiEntry *> m_2a4;
	std::vector<AsciiString> m_2b0;
	std::vector<AsciiString> m_2bc;
	unsigned char m_pad2c8[0xc];
	AsciiString m_2d4;
	unsigned char m_tail_2d8_to_2f3[0x1c];
};

typedef char Rva002469D0SizeCheck[(sizeof(HorseHordeContainModuleData) == 0x2f4) ? 1 : -1];

// ??1HorseHordeContainModuleData@@UAE@XZ
HorseHordeContainModuleData::~HorseHordeContainModuleData()
{
	for (unsigned int i = 0; i < m_224.size(); ++i)
	{
		// Retail releases each split-result record through the ILT thunk at
		// 0x00017657, not through a local scalar deleting destructor.
		typedef void (BfmeHordeContainSplitResultList::*Release)();
		union { void (*fn)(); Release call; } u = { j_00017657 };
		BfmeHordeContainSplitResultList *rec = m_224[i];
		if (rec)
		{
			(rec->*u.call)();
			::operator delete(rec);
		}
	}
	m_224.clear();

	for (unsigned int i = 0; i < m_230.size(); ++i)
	{
		delete m_230[i];
	}
	m_230.clear();

	for (unsigned int i = 0; i < m_23c.size(); ++i)
	{
		delete m_23c[i];
	}
	m_23c.clear();

	m_24c.clear();
	m_250.clear();
	m_25c.clear();
	m_28c.clear();
	m_2b0.clear();

	for (unsigned int i = 0; i < m_2a4.size(); ++i)
	{
		delete m_2a4[i];
	}
	m_2a4.clear();
	m_2bc.clear();
}
