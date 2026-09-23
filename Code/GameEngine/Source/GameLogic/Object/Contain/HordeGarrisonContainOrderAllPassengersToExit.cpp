// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: HordeGarrisonContain::orderAllPassengersToExit, retail 0x00249A20.
//
// Owner: ??0HordeGarrisonContain (0x00248F90) installs vtable 0x010AFB40 at
// this+0x20, whose slot +0x6C is ILT 0x0000A4D4 -> 0x00249A20. GarrisonContain's
// +0x20 vtable 0x010AB598 has a different body there (0x00228230), so this class
// is the first override; ContestableContain (0x010AB140) and SlaughterHordeContain
// (0x010B0F40) derive from HordeGarrisonContain and inherit the slot.
// Method: slot +0x6C is what matched AIGroup::groupEvacuate (0x00156690) calls as
// contain->orderAllPassengersToExit(cmdSource), and the base body in that slot at
// 0x00228230 is the Zero Hour OpenContain::orderAllPassengersToExit aiExit loop.
// Slot +0x104 (0x0021B850, lea eax,[ecx+0x18]) returns &m_containList: 0x00228230
// walks its result the way Zero Hour walks getContainedItemsList(). Retail calls
// it here and discards the result.
//
// Unlike the base body, this override walks a COPY of the list and gives a rider
// with its own contain module a chance to take the order first (contain slot
// +0x68, then slot +0x80 of what it returns); neither slot has a proven name.

#include <list>

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object;

typedef _STL::list<Object *> ContainedItemsList;

class AICommandInterface
{
public:
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
};

// The 0x20-byte module head both AIUpdateInterface and the contain module
// start with; the owning Object sits at +0x08 (the contain body reads it at
// interface-0x18).
class BfmeRva249A20UpdateHead
{
public:
	virtual void slot00();
	Object *getObject() const { return m_object; }

private:
	unsigned char m_unreconstructed_04[0x08 - 0x04];
	Object *m_object;			// +0x08
	unsigned char m_unreconstructed_0C[0x20 - 0x0C];
};

class AIUpdateInterface : public BfmeRva249A20UpdateHead, public AICommandInterface
{
};

class Rva00249A20RiderExit
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void forwardExitRva00249A20(Object *container, CommandSourceType commandSource);	// +0x80
};

#define CONTAIN_SLOT(n) virtual void slot##n();

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25)
	virtual Rva00249A20RiderExit *getRva00219470();			// +0x68
	virtual void orderAllPassengersToExit(CommandSourceType commandSource);	// +0x6C
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const;	// +0x104
};

#undef CONTAIN_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	unsigned char m_unreconstructed_000[0x1fc];
	ContainModuleInterface *m_contain;	// +0x1FC
	unsigned char m_unreconstructed_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;		// +0x204
};

class HordeGarrisonContain : public BfmeRva249A20UpdateHead, public ContainModuleInterface
{
public:
	virtual void orderAllPassengersToExit(CommandSourceType commandSource);

private:
	unsigned char m_unreconstructed_24[0x38 - 0x24];
	ContainedItemsList m_containList;	// +0x38
};

// ?orderAllPassengersToExit@HordeGarrisonContain@@UAEXW4CommandSourceType@@@Z
void HordeGarrisonContain::orderAllPassengersToExit(CommandSourceType commandSource)
{
	ContainedItemsList riders(m_containList);
	getContainedItemsList();
	for (ContainedItemsList::iterator it = riders.begin(); it != riders.end(); ++it)
	{
		Object *rider = *it;
		if (rider->getContain())
		{
			Rva00249A20RiderExit *riderExit = rider->getContain()->getRva00219470();
			if (riderExit)
				riderExit->forwardExitRva00249A20(getObject(), commandSource);
		}
		else if (rider->getAI())
		{
			rider->getAI()->aiExit(getObject(), commandSource);
		}
	}
}
