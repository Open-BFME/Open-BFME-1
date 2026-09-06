// cl: /DNDEBUG /DWIN32 /D_WINDOWS /EHsc

typedef bool Bool;

class GameWindow;

class Glo012F3344Type
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual GameWindow *slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual GameWindow *slot3C() = 0;
};

extern Glo012F3344Type *Glo012F3344;

class Open2Dtor4793C0
{
public:
	~Open2Dtor4793C0();

	char m_data[ 0x10 ];
};

class GameWindowInputData
{
};

class Gen_uw_00021431
{
public:
	~Gen_uw_00021431();

	char m_data[ 0x1A8 ];
};

class GameWindowAnchor
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void release( int force ) = 0;
};

extern void W3DRadarResetLock();
extern void W3DRadarResetUnlock();

class GameWindow
{
protected:
	virtual ~GameWindow();

	GameWindowAnchor *m_anchor;
	char m_data[ 0x28 ];
	Gen_uw_00021431 m_instData;
	GameWindowInputData *m_inputData;
	char m_data2[ 0x38 ];
	Open2Dtor4793C0 *m_editData;
};

GameWindow::~GameWindow()
{
	if( Glo012F3344 && Glo012F3344->slot3C() == this )
		Glo012F3344->slot28();

	if( m_inputData )
		delete m_inputData;
	m_inputData = 0;

	if( m_editData )
		delete m_editData;
	m_editData = 0;

	if( m_anchor )
	{
		W3DRadarResetLock();

		if( m_anchor )
			m_anchor->release( 1 );

		W3DRadarResetUnlock();
	}
}
