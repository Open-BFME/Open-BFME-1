// ?update@Rva0025E450GiveUpgradeCleanup@@QAEXXZ
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Rva0025E450Action
{
public:
	void apply( int value );
};

struct Rva0025E450Owner
{
	unsigned char m_lead[ 0x204 ];
	Rva0025E450Action *m_action;
};

class Rva0025E450Object {};

class GameLogic
{
public:
	Rva0025E450Object *findObject( int id );
};

extern GameLogic *TheGameLogic;

class Rva0025E450GiveUpgradeCleanup
{
public:
	void update();
	void finish();
private:
	unsigned char m_lead[ 8 ];
	Rva0025E450Owner *m_owner;
	unsigned char m_gap0[ 0xa0 ];
	int m_objectId;
	unsigned char m_gap1[ 0x39 ];
	unsigned char m_pending;
};

void Rva0025E450GiveUpgradeCleanup::update()
{
	Rva0025E450Object *object = TheGameLogic->findObject( m_objectId );
	if ( object != 0 && m_pending )
	{
		( (Rva0025E450Action *)( (char *)m_owner->m_action + 0x20 ) )->apply( 2 );
		m_pending = 0;
		finish();
	}
}
