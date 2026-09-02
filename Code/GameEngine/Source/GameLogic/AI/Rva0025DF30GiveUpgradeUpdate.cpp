// cl: /DNDEBUG /MD /EHsc

class Rva0025DF30Object
{
public:
	void applyUpgrade( int upgrade );
	Rva0025DF30Object *related( int which );
};

class GameLogic
{
public:
	Rva0025DF30Object *findObject( int id );
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
		Rva0025DF30Object *object = TheGameLogic->findObject( m_objectId );
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
