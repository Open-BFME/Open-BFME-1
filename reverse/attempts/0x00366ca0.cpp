// ?xfer@BfmeLivingWorldPlayerArmyCollection@@QAEXPAVXfer@@@Z
// partial score=0.22 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// A collection-level xfer for LivingWorldPlayerArmy, retail RVA 0x00366CA0
// (612B). Sits among the dense LivingWorldPlayerArmy neighbourhood in
// INILivingWorldPlayerArmy.cpp/LivingWorldPlayerArmyXfer.cpp/etc: calls the
// matched default ctor (0x3649D0), copy ctor (0x3651E0), destructor
// (0x362B20), the element xfer (0x365880) and the vector<LivingWorldPlayerArmy>
// range erase (0x3668E0). A second, parallel vector<Int> ("unique ids") is
// xferred the same way, matching the Gen_t_000bbe70_m4pod POD insert
// overflow this body also calls.
//
// Field layout is read straight off the disassembly: four header fields at
// +4/+8/+0x10/+0x14, each a single xfer call through Xfer's own vtable at a
// specific byte offset (0x68/0x50/0x8c/0x78) that does not obviously match
// any "natural" Xfer overload's declared slot -- retail's Xfer reconstruction
// elsewhere in this codebase already shows many differently-typed overloads
// folding to the same body, so the byte offset is the only proven fact.
// Rather than guess which C++ overload happens to land on each exact slot,
// this reaches each vtable offset through a placeholder-slot interface (the
// same BFME_SLOT technique used throughout this codebase), exactly mirroring
// the retail instruction shape (mov edx,[xfer]; push &field; call
// [edx+OFFSET]). LivingWorldPlayerArmy::xfer is reached the same way for the
// per-element calls in the save loop (vtable slot 0xc).

#include <vector>

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

#include "ascii_string.h"

#define XFER_SLOT(N) virtual void slot##N(void *field)

class XferHeaderSlots
{
public:
	XFER_SLOT(00); XFER_SLOT(01); XFER_SLOT(02); XFER_SLOT(03); XFER_SLOT(04); XFER_SLOT(05);
	XFER_SLOT(06); XFER_SLOT(07); XFER_SLOT(08); XFER_SLOT(09); XFER_SLOT(10);
	XFER_SLOT(11); XFER_SLOT(12); XFER_SLOT(13); XFER_SLOT(14); XFER_SLOT(15);
	XFER_SLOT(16); XFER_SLOT(17); XFER_SLOT(18); XFER_SLOT(19);
	virtual void at50(void *field);					// offset 0x50
	XFER_SLOT(21); XFER_SLOT(22); XFER_SLOT(23); XFER_SLOT(24); XFER_SLOT(25);
	virtual void at68(void *field);					// offset 0x68
	XFER_SLOT(27); XFER_SLOT(28); XFER_SLOT(29);
	virtual void at78(void *field);					// offset 0x78
	XFER_SLOT(31); XFER_SLOT(32); XFER_SLOT(33); XFER_SLOT(34);
	virtual void at8c(void *field);					// offset 0x8c
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool IsLoading() const;
};

class LivingWorldPlayerArmy
{
public:
	LivingWorldPlayerArmy();
	LivingWorldPlayerArmy(const LivingWorldPlayerArmy &other);
	virtual ~LivingWorldPlayerArmy();
	virtual void slot1();
	virtual void slot2();
	virtual void bfmeXfer(Xfer *xfer);					// offset 0xc

private:
	char m_body[0x54];
};

class BfmeLivingWorldPlayerArmyCollection
{
public:
	void xfer(Xfer *xfer);

private:
	char m_pad00[4];
	Int m_fieldA;					// +0x04, xfer slot 0x68
	Int m_fieldB[2];				// +0x08, xfer slot 0x50 (8 bytes)
	Int m_version;					// +0x10, xfer slot 0x8c
	Int m_fieldD;					// +0x14, xfer slot 0x78 (also used for the Int count/value fields)
	std::vector<LivingWorldPlayerArmy> m_armies;	// +0x18
	std::vector<Int> m_uniqueIds;			// +0x24
};

// ?xfer@BfmeLivingWorldPlayerArmyCollection@@QAEXPAVXfer@@@Z
void BfmeLivingWorldPlayerArmyCollection::xfer(Xfer *xferArg)
{
	((XferHeaderSlots *)xferArg)->at68(&m_fieldA);
	((XferHeaderSlots *)xferArg)->at50(&m_fieldB);
	((XferHeaderSlots *)xferArg)->at8c(&m_version);
	((XferHeaderSlots *)xferArg)->at78(&m_fieldD);

	if (xferArg->IsLoading())
	{
		m_armies.erase(m_armies.begin(), m_armies.end());
		m_uniqueIds.erase(m_uniqueIds.begin(), m_uniqueIds.end());

		Int count = 0;
		((XferHeaderSlots *)xferArg)->at78(&count);
		for (Int i = 0; i < count; ++i)
		{
			LivingWorldPlayerArmy army;
			army.bfmeXfer(xferArg);
			m_armies.push_back(army);
		}

		Int idCount = 0;
		((XferHeaderSlots *)xferArg)->at78(&idCount);
		for (Int i = 0; i < idCount; ++i)
		{
			Int value = 0;
			((XferHeaderSlots *)xferArg)->at78(&value);
			m_uniqueIds.push_back(value);
		}
	}
	else
	{
		Int count = (Int)m_armies.size();
		((XferHeaderSlots *)xferArg)->at78(&count);
		for (Int i = 0; i < count; ++i)
			m_armies[i].bfmeXfer(xferArg);

		Int idCount = (Int)m_uniqueIds.size();
		((XferHeaderSlots *)xferArg)->at78(&idCount);
		for (Int i = 0; i < idCount; ++i)
			((XferHeaderSlots *)xferArg)->at78(&m_uniqueIds[i]);
	}
}
