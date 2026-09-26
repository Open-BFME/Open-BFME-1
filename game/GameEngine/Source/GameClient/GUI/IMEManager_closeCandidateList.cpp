// cl: /DNDEBUG /MD
// The retail body at 0x0048D530 matches IMEManager::closeCandidateList from
// the upstream BFME family. The candidate window sits at +0x304C, the array
// of UnicodeString values sits at +0x3040, and the count sits at +0x303C.

void __cdecl operator delete []( void *memory );

class GameWindow
{
public:
	void close( bool closeWindow );
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual int winUnsetModal( GameWindow *window );
};

class Rva0048D530CandidateString
{
public:
	~Rva0048D530CandidateString();
	char m_data[4];
};

extern GameWindowManager *TheWindowManager;

class IMEManager
{
	protected:
	void closeCandidateList( int candidateFlags );

private:
	char m_padding303c[0x303c];
	int m_candidateCount;
	Rva0048D530CandidateString *m_candidateString;
	char m_padding3044[8];
	GameWindow *m_candidateWindow;
};

// ?closeCandidateList@IMEManager@@IAEXH@Z
void IMEManager::closeCandidateList( int candidateFlags )
{
	if ( m_candidateWindow != 0 )
	{
		m_candidateWindow->close( true );
		TheWindowManager->winUnsetModal( m_candidateWindow );
	}

	if ( m_candidateString != 0 )
	{
		delete [] m_candidateString;
		m_candidateString = 0;
	}

	m_candidateCount = 0;
}
