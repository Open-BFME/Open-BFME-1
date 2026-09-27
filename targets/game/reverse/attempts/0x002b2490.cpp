// ?rva002B2490@WallUpgradeUpdate@@QAEXXZ
// partial score=0.949 date=2026-09-27
// The matched update caller reaches 0x002B2490 through ILT 0x0000FBAA.
// It calls the target as a WallUpgradeUpdate member with no arguments.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/Common /Igame/GameEngine/Source/GameLogic /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#include "Common/BitFlags.h"

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual int allow(void *) = 0;
	virtual int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear)
	{}
	~PartitionFilterAcceptByKindOf()
	{
		*(volatile unsigned int *)this = 0x01083B5C;
	}
	virtual int allow(void *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class Rva00260180SelfFilter : public PartitionFilter
{
public:
	explicit Rva00260180SelfFilter(void *object)
	{
		m_next = 0;
		*(volatile unsigned int *)this = 0x01095724;
		m_object = object;
	}
	~Rva00260180SelfFilter()
	{
		*(volatile unsigned int *)this = 0x01083B5C;
	}
	virtual int allow(void *);

	void *m_object;
};

class WallUpgradeUpdate
{
public:
	void rva002B2490();

private:
	unsigned char m_pad000[8];
	void *m_owner;
	unsigned char m_pad00c[0x1c];
	int m_partnerId;
};

class BfmeC1050
{
public:
	void *bfmeGo1050D(int position, int radiusBits, int includeOwner,
		int filters);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

#pragma comment(linker, "/alternatename:?bfmeGo1050D@BfmeC1050@@QAEPAXHHHH@Z=?bfmeGo1050D@BfmeC1050@@QAEXHHHH@Z")
#pragma comment(linker, "/alternatename:??1PartitionFilterAcceptByKindOf@@QAE@XZ=?j_0002feb4@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00260180SelfFilter@@QAE@XZ=?j_0004773a@@YAXXZ")

void WallUpgradeUpdate::rva002B2490()
{
	if (m_partnerId != 0)
		return;

	void *owner = m_owner;
	void *position = (char *)owner + 0x38;
	void *partner;
	{
		partner = ((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D(
			(int)position, 0x43480000, 1,
			(int)Rva00260180SelfFilter(owner).link(
				&PartitionFilterAcceptByKindOf(
					BitFlags<192>(BitFlags<192>::kInit, 7, 91),
					KINDOFMASK_NONE)));
	}

	if (partner != 0)
		m_partnerId = *(int *)((char *)partner + 0x74);
}
