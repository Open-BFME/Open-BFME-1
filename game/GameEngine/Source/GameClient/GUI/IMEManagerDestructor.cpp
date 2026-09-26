// cl: /DNDEBUG /MD /EHsc
// BFME IMEManager destructor, retail 0x0048D8B0 (216 bytes).
//
// The owner is established by the IMEManager constructor's 0x010F9978 vtable,
// the existing IMEManager methods in this directory, and GameClient's
// CreateIMEManagerInterface/delete path.  The candidate fields below are the
// offsets read by this body; the long composition buffers are intentionally
// represented by one opaque span because this destructor does not inspect them.

typedef bool Bool;
typedef int Int;

// Keep the array form visible so MSVC emits the retail operator delete[]
// target (0x00881EF0), rather than folding this array cleanup onto scalar
// operator delete at 0x00881EB0.
void __cdecl operator delete []( void *memory );

class GameWindow
{
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
	virtual void winDestroy( GameWindow *window );
};

extern GameWindowManager *TheWindowManager;
extern void *Rva0048CD50WindowHandle;

extern "C"
{
	void *__stdcall ImmAssociateContext( void *window, void *context );
	int __stdcall ImmReleaseContext( void *window, void *context );
	int __stdcall ImmDestroyContext( void *context );
}

class SubsystemInterface
{
public:
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
};

// The candidate element is the same 4-byte UnicodeString view used by the
// exact closeCandidateList body at 0x0048D530.  Its nonvirtual destructor lets
// MSVC emit the retail array-destruction helper for m_candidateString.
class Rva0048D530CandidateString
{
public:
	~Rva0048D530CandidateString();
	char m_data[4];
};

class IMEManager : public IMEManagerInterface
{
public:
	virtual ~IMEManager();
	virtual void detatch();

private:
	int m_result;                                      // +0x08
	GameWindow *m_window;                              // +0x0c
	void *m_context;                                   // +0x10
	void *m_oldContext;                                // +0x14
	int m_disabled;                                    // +0x18
	Bool m_composing;                                  // +0x1c
	char m_padding1d[0x303c - 0x1d];
	int m_candidateCount;                              // +0x303c
	Rva0048D530CandidateString *m_candidateString;    // +0x3040
	char m_padding3044[8];
	GameWindow *m_candidateWindow;                     // +0x304c
	GameWindow *m_statusWindow;                        // +0x3050
};

// ??1IMEManager@@UAE@XZ
IMEManager::~IMEManager()
{
	if ( m_candidateWindow != 0 )
		TheWindowManager->winDestroy( m_candidateWindow );
	if ( m_statusWindow != 0 )
		TheWindowManager->winDestroy( m_statusWindow );
	if ( m_candidateString != 0 )
	{
		delete [] m_candidateString;
	}

	// IMEManager's vtable slot 10 is the existing 0x000155C3 thunk to
	// the byte-verified detatch body at 0x0048CD50.
	detatch();
	ImmAssociateContext( Rva0048CD50WindowHandle, m_oldContext );
	ImmReleaseContext( Rva0048CD50WindowHandle, m_oldContext );
	if ( m_context != 0 )
		ImmDestroyContext( m_context );
}
