// cl: /DNDEBUG /MD /EHsc

extern "C" void __cdecl __identifier("?clearStatus@Object@@QAEXW4ObjectStatusTypes@@@Z")();
class Object;

class Rva0025DF30Object
{
public:
	void applyUpgrade(int a0) {
	 // retail body is ledgered as ?clearStatus@Object@@QAEXW4ObjectStatusTypes@@@Z; call it by that defined name
	 union { void (__cdecl *symbol)(); void (Rva0025DF30Object::*member)(int); } c;
	 c.symbol = &__identifier("?clearStatus@Object@@QAEXW4ObjectStatusTypes@@@Z");
	 (this->*c.member)(a0);
	}
	Rva0025DF30Object *related( int which );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

class Rva0025DF30GiveUpgradeUpdate
{
public:
	void update();
private:
	unsigned char m_lead[ 0xac ];
	int m_objectId;
};

void Rva0025DF30GiveUpgradeUpdate::update()
{
	if ( m_objectId != 0 )
	{
		Rva0025DF30Object *object =
			(Rva0025DF30Object *)TheGameLogic->findObjectByID( m_objectId );
		if ( object != 0 )
		{
			object->applyUpgrade( 0x41 );
			Rva0025DF30Object *related = object->related( 0 );
			if ( related != 0 )
				related->applyUpgrade( 0x41 );
		}
		m_objectId = 0;
	}
}
