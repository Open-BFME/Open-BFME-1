// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::queueUpgrade, retail 0x00151170, 146 bytes.
//
// The reference's body with one BFME change carried all the way through: the
// method takes a second argument, and it is handed both to canAffordUpgrade --
// which grows to four arguments, the reference's FALSE staying last -- and to
// the production update's queueUpgrade.
//
// The reference's canProduceUpgrade check is gone. Everything else is its own:
// the affordability test, the OBJECT-type pair of tests (the type is the word
// at UpgradeTemplate+0x04 and OBJECT is 1), the production interface, and the
// queue-full check against 4 through vtable slot 4 before the queue at slot 3.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;

class Player;

enum UpgradeType { UPGRADE_TYPE_PLAYER = 0, UPGRADE_TYPE_OBJECT = 1 };

enum CanMakeType { CANMAKE_QUEUE_FULL = 4 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType(void) const { return m_type; }

private:
	unsigned char m_unmodelled_000[4];
	UpgradeType m_type;					// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	virtual void unusedSlot00();
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade);		// vtable +0x04
	virtual void unusedSlot02();
	virtual void queueUpgrade(const UpgradeTemplate *upgrade, Bool bfmeFlag);	// vtable +0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;					// ILT 0x00020824
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;				// ILT 0x0000BA37
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;			// ILT 0x000077B6
	ProductionUpdateInterface *getProductionUpdateInterface(void);			// ILT 0x00003B52
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	Bool canAffordUpgrade(Player *player, const UpgradeTemplate *upgrade, Bool bfmeFlag, Bool forceCheck) const;	// ILT 0x0001CEA9
};

extern UpgradeCenter *TheUpgradeCenter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void queueUpgrade(const UpgradeTemplate *upgrade, Bool bfmeFlag);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::queueUpgrade( const UpgradeTemplate *upgrade, Bool bfmeFlag )
{
	if (!upgrade)
		return;

	_STL::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *thisMember = (*i);
		if( ! TheUpgradeCenter->canAffordUpgrade( thisMember->getControllingPlayer(), upgrade, bfmeFlag, false ) )
		{
			continue;
		}
		if( upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT )
		{
			if( thisMember->hasUpgrade( upgrade ) || !thisMember->affectedByUpgrade( upgrade ) )
				continue;
		}

		// producer must have a production update
		ProductionUpdateInterface *pu = thisMember->getProductionUpdateInterface();
		if( pu == 0 )
			continue;

		if ( pu->canQueueUpgrade( upgrade ) == CANMAKE_QUEUE_FULL )
			continue;

		// queue the upgrade "research"
		pu->queueUpgrade( upgrade, bfmeFlag );
	}
}
