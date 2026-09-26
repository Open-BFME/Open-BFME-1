// ?reportWatchdog@Rva0010B8A0Owner@@QAEXXZ
// partial score=0.9 date=2026-09-06
// ?reportWatchdog@Rva0010B8A0Owner@@QAEXXZ
class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned( unsigned value );
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String( const char *text );
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish( int report );
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream( void *owner, void *context );
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern "C" void __cdecl _bfme_debugRecordCallsite( int kind );
extern "C" bool __cdecl _bfme_debugReportingEnabled( void );
__declspec(noreturn) void __stdcall _CxxThrowException( void *object, void *throwInfo );

namespace Debug
{
	class Format
	{
	public:
		Format( const char *fmt, ... );
	private:
		char m_buf[ 0x200 ];
	};
}

struct Rva0010B8A0Owner
{
	char m_pad[ 0x50 ];
	int m_threadId;

	void reportWatchdog( void );
};

void Rva0010B8A0Owner::reportWatchdog( void )
{
	if( _bfme_debugReportingEnabled() )
	{
		_bfme_debugRecordCallsite( 1 );
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream( 0, 0 );
		Debug::Format fmt(
			"Watchdog: Parent thread (ID %d) has stopped responding.\n\n"
			"I'm going to force a crash; please report it.", m_threadId );
		stream->Put_String( (const char *)&fmt );
		stream->Finish( 2 );
	}
	_CxxThrowException( (void *)0, (void *)0 );
}
