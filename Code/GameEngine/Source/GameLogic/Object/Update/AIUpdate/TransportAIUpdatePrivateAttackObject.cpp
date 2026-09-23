// ?privateAttackObject@TransportAIUpdate@@MAEXPAVObject@@HW4CommandSourceType@@@Z
// partial score=0.98 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// stlport

// TransportAIUpdate::privateAttackObject, retail 0x002C7250 (177 bytes).
//
// Identity: vtable 0x010C96A0 is the table the landed TransportAIUpdate
// constructor (0x002C7020) installs; this body is its slot 30 (+0x78) via ILT
// 0x00040980. The landed AIUpdateInterface::aiDoCommand (0x00277780) sends
// command 0x0b -- the value AICommandInterface::aiAttackObject (0x001535A0)
// builds -- through +0x78 with parms->m_obj. TransportAIUpdate overrides exactly
// slots 30/34/36, and the three bodies fan out to aiAttackObject /
// aiForceAttackObject / aiAttackPosition: the three Zero Hour
// TransportAIUpdate overrides. This one is the ZH body line for line.
//
// The tail call is AIUpdateInterface's slot 30, ILT 0x00039F7C -> 0x00278D50.
// The ledger currently spells that name at 0x002737B0, which is slot 35 (+0x8c,
// aiDoCommand case 0x0d with parms->m_team), so the base-call REL32 cannot
// resolve until that row is re-homed.
//
// The OVERRIDE/Overridable/BitFlags shims are the ZH shapes on purpose: with
// hand-flattened accessors MSVC swaps EBX/EBP between cmdSource and the list.

#include <list>
#include <bitset>

typedef bool Bool;
typedef int Int;

// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

enum KindOfType { KINDOF_BIT56 = 56 };
enum DisabledType { DISABLED_BIT2 = 2, DISABLED_BIT4 = 4 };

class Object;
typedef _STL::list<Object *> ContainedItemsList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride( void ) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;			// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if (!m_overridable)
			return 0;
		return (T*) m_overridable->getFinalOverride();
	}
	operator const T*( ) const { return operator->(); }

private:
	const T *m_overridable;
};

template <size_t NUMBITS> class BitFlags
{
public:
	Bool test( Int i ) const { return m_bits.test(i); }
private:
	_STL::bitset<NUMBITS> m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( KindOfType t ) const { return m_kindof.test(t); }

private:
	char m_unmodelled_08[0xC8 - 0x08];
	BitFlags<128> m_kindof;				// +0xC8
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual Bool isPassengerAllowedToFire() const = 0;						///< +0xa0
	virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual const ContainedItemsList *getContainedItemsList() const = 0;	///< +0x104
};

class AIUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf( KindOfType t ) const { return getTemplate()->isKindOf(t); }

private:
	void *m_vtbl;
	OVERRIDE<ThingTemplate> m_template;		// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isDisabledByType( DisabledType type ) const { return m_disabledMask.test(type); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad008[0x1a4 - 0x8];
	BitFlags<32> m_disabledMask;			// +0x1a4
	unsigned char m_pad1a8[0x1fc - 0x1a8];
	ContainModuleInterface *m_contain;		// +0x1fc
	unsigned char m_pad200[0x204 - 0x200];
	AIUpdateInterface *m_ai;				// +0x204
};

// Retail ILT 0x0002EDCF -> 0x001535A0.
class AICommandInterface
{
public:
	virtual void slot00();
	void aiAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
};

class AIUpdateInterfaceModuleHead
{
public:
	virtual void slot00();
	Object *getObject() const { return m_object; }
private:
	void *dword_4;
	Object *m_object;						///< retail this+0x8
	unsigned char m_pad0c[0x20 - 0xc];
};

class AIUpdateInterface : public AIUpdateInterfaceModuleHead, public AICommandInterface
{
protected:
	virtual void privateAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
};

// Opaque callee identity at the witnessed AI-update slot 30 body.
class Rva00278D50
{
public:
	void slot30(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
};

class TransportAIUpdate : public AIUpdateInterface
{
protected:
	virtual void privateAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
};

void TransportAIUpdate::privateAttackObject( Object *victim, Int maxShotsToFire, CommandSourceType cmdSource )
{
	ContainModuleInterface* contain = getObject()->getContain();
	if( contain != 0  &&  contain->isPassengerAllowedToFire() )
	{
		if( cmdSource == CMD_FROM_PLAYER  ||  cmdSource == CMD_FROM_SCRIPT )
		{
			const ContainedItemsList *passengerList = contain->getContainedItemsList();
			ContainedItemsList::const_iterator passengerIterator;
			passengerIterator = passengerList->begin();

			while( passengerIterator != passengerList->end() )
			{
				Object *passenger = *passengerIterator;
				//Advance to the next iterator
				passengerIterator++;

				if ( passenger->isKindOf( KINDOF_BIT56 ) )
				{
					if( passenger->isDisabledByType( DISABLED_BIT2 ) 
						|| passenger->isDisabledByType( DISABLED_BIT4 ) )
						continue;
				}
				
				AIUpdateInterface *passengerAI = passenger->getAIUpdateInterface();
				if( passengerAI )
				{
					passengerAI->aiAttackObject( victim, maxShotsToFire, cmdSource );
				}
			}
		}
	}

	((Rva00278D50 *)this)->slot30( victim, maxShotsToFire, cmdSource );
}
