// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_INFANTRY = 8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual void overridableAnchor();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(UnsignedInt)kind >> 5] & (1 << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed08[0xC8 - 0x08];
	UnsignedInt m_kindOf[3];
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
class OVERRIDE
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value == 0)
			return 0;
		if (value->m_nextOverride)
			value = static_cast<const T *>(value->m_nextOverride->getFinalOverride());
		return value;
	}

private:
	// Retail materializes the OVERRIDE member address before loading it; this keeps VC7.1
	// from folding that access into its owner's addressing mode.
	const T *volatile m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual ~Thing();
	Bool isKindOf(KindOfType kind) const { return m_template->isKindOf(kind); }

private:
	OVERRIDE<ThingTemplate> m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h
class OpenContainModuleData
{
public:
	unsigned char m_unreconstructed00[0x150];
	Bool m_showPips;
};

#define OPEN_CONTAIN_SLOT(N) virtual void openContainSlot##N() = 0

class OpenContain
{
public:
	OPEN_CONTAIN_SLOT(00); OPEN_CONTAIN_SLOT(01); OPEN_CONTAIN_SLOT(02); OPEN_CONTAIN_SLOT(03);
	OPEN_CONTAIN_SLOT(04); OPEN_CONTAIN_SLOT(05); OPEN_CONTAIN_SLOT(06); OPEN_CONTAIN_SLOT(07);
	OPEN_CONTAIN_SLOT(08); OPEN_CONTAIN_SLOT(09); OPEN_CONTAIN_SLOT(10); OPEN_CONTAIN_SLOT(11);
	OPEN_CONTAIN_SLOT(12); OPEN_CONTAIN_SLOT(13); OPEN_CONTAIN_SLOT(14); OPEN_CONTAIN_SLOT(15);
	OPEN_CONTAIN_SLOT(16); OPEN_CONTAIN_SLOT(17); OPEN_CONTAIN_SLOT(18); OPEN_CONTAIN_SLOT(19);
	OPEN_CONTAIN_SLOT(20); OPEN_CONTAIN_SLOT(21); OPEN_CONTAIN_SLOT(22);
	virtual Int getContainMax() const = 0;                         // vtable +0x5C
	OPEN_CONTAIN_SLOT(24); OPEN_CONTAIN_SLOT(25); OPEN_CONTAIN_SLOT(26); OPEN_CONTAIN_SLOT(27);
	OPEN_CONTAIN_SLOT(28); OPEN_CONTAIN_SLOT(29); OPEN_CONTAIN_SLOT(30); OPEN_CONTAIN_SLOT(31);
	OPEN_CONTAIN_SLOT(32); OPEN_CONTAIN_SLOT(33); OPEN_CONTAIN_SLOT(34); OPEN_CONTAIN_SLOT(35);
	OPEN_CONTAIN_SLOT(36); OPEN_CONTAIN_SLOT(37); OPEN_CONTAIN_SLOT(38); OPEN_CONTAIN_SLOT(39);
	OPEN_CONTAIN_SLOT(40); OPEN_CONTAIN_SLOT(41); OPEN_CONTAIN_SLOT(42); OPEN_CONTAIN_SLOT(43);
	OPEN_CONTAIN_SLOT(44); OPEN_CONTAIN_SLOT(45);
	virtual Int getExtraSlotsInUse() = 0;                         // vtable +0xB8
	OPEN_CONTAIN_SLOT(47); OPEN_CONTAIN_SLOT(48); OPEN_CONTAIN_SLOT(49); OPEN_CONTAIN_SLOT(50);
	OPEN_CONTAIN_SLOT(51); OPEN_CONTAIN_SLOT(52); OPEN_CONTAIN_SLOT(53); OPEN_CONTAIN_SLOT(54);
	OPEN_CONTAIN_SLOT(55); OPEN_CONTAIN_SLOT(56); OPEN_CONTAIN_SLOT(57); OPEN_CONTAIN_SLOT(58);
	OPEN_CONTAIN_SLOT(59); OPEN_CONTAIN_SLOT(60); OPEN_CONTAIN_SLOT(61); OPEN_CONTAIN_SLOT(62);
	OPEN_CONTAIN_SLOT(63);
	virtual Int getContainCount(Bool countRiders) const = 0;      // vtable +0x100

	virtual Bool getContainerPipsToShow(Int &numTotal, Int &numFull, Int &numInfantry,
		Int &secondTotal, Int &secondFull, Int &secondInfantry);

private:
	unsigned char m_unreconstructed04[0x14];
	_STL::list<Object *> m_containList;                           // interface this+0x18
};

#undef OPEN_CONTAIN_SLOT

Bool OpenContain::getContainerPipsToShow(Int &numTotal, Int &numFull, Int &numInfantry,
	Int &secondTotal, Int &secondFull, Int &secondInfantry)
{
	secondTotal = 0;
	secondFull = 0;
	secondInfantry = 0;

	const OpenContainModuleData *moduleData =
		*reinterpret_cast<OpenContainModuleData *const *>(reinterpret_cast<const char *>(this) - 0x1C);
	if (moduleData->m_showPips)
	{
		numTotal = getContainMax();
		numFull = getContainCount(false) + getExtraSlotsInUse();
		numInfantry = 0;

		for (_STL::list<Object *>::const_iterator it = m_containList.begin();
			it != m_containList.end(); ++it)
		{
			if ((*it)->isKindOf(KINDOF_INFANTRY))
				++numInfantry;
		}
		return true;
	}

	numTotal = 0;
	numFull = 0;
	return false;
}
