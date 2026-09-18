// cl: /DNDEBUG /MD /O2 /EHsc

typedef bool Bool;
typedef int Int;

class GameWindow;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void slot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool slot06( Int arg );
	virtual void slot07();
	virtual void slot08( Int arg );

	void *m_name;
};

class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface() {}
	virtual void attach( GameWindow *window ) = 0;
	virtual void detatch() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual Bool isEnabled() = 0;
	virtual Bool isAttachedTo( GameWindow *window ) = 0;
	virtual GameWindow *getWindow() = 0;
	virtual Bool isComposing() = 0;
	virtual void getCompositionString( void *string ) = 0;
	virtual Int getCompositionCursorPosition() = 0;
	virtual Int getIndexBase() = 0;
	virtual Int getCandidateCount() = 0;
	virtual void *getCandidate( Int index ) = 0;
	virtual Int getSelectedCandidateIndex() = 0;
	virtual Int getCandidatePageSize() = 0;
	virtual Int getCandidatePageStart() = 0;
	virtual Bool serviceIMEMessage( void *window, unsigned int message,
		Int wParam, Int lParam ) = 0;
	virtual Int result() = 0;
};

class IMEManager : public IMEManagerInterface
{
public:
	IMEManager();
	virtual ~IMEManager();

private:
	Int m_result;
	GameWindow *m_window;
	void *m_context;
	void *m_oldContext;
	Int m_disabled;
	Bool m_composing;
	unsigned short m_compositionString[0x801];
	unsigned short m_resultsString[0x801];
	char m_padding2022[0x1002];
	Int m_compositionCursorPos;
	Int m_compositionStringLength;
	Int m_indexBase;
	Int m_pageStart;
	Int m_pageSize;
	Int m_selectedIndex;
	Int m_candidateCount;
	void *m_candidateString;
	Bool m_unicodeIME;
	char m_padding3045[3];
	Int m_compositionCharsDisplayed;
	GameWindow *m_candidateWindow;
	GameWindow *m_statusWindow;
	GameWindow *m_candidateTextArea;
	GameWindow *m_candidateUpArrow;
	GameWindow *m_candidateDownArrow;
};

IMEManager::IMEManager()
{
	m_result = 0;
	m_window = 0;
	m_context = 0;
	m_oldContext = 0;
	m_disabled = 0;
	m_composing = false;
	m_compositionCursorPos = 0;
	m_compositionStringLength = 0;
	m_indexBase = 1;
	m_pageStart = 0;
	m_pageSize = 0;
	m_selectedIndex = 0;
	m_candidateCount = 0;
	m_candidateString = 0;
	m_unicodeIME = false;
	m_compositionCharsDisplayed = 0;
	m_candidateWindow = 0;
	m_statusWindow = 0;
	m_candidateTextArea = 0;
	m_candidateUpArrow = 0;
	m_candidateDownArrow = 0;
	for ( Int i = 0; i < 0x801; ++i )
	{
		m_compositionString[i] = 0;
		m_resultsString[i] = 0;
	}
}
