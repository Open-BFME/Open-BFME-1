// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini
//
// INI::parseDynamicAudioEventRTS, the body. 0x000BB9A0, 348 bytes (the map said
// 347; the compiled body is 348 bytes and matches retail through +0x15B,
// short of the 0x000BBB00 padding row).
//
// Retail's ILT thunk 0x0002E2DA (ledgered as ?parseDynamicAudioEventRTS@INI@@
// in INIParseDynamicAudioEventRTSThunk.cpp, which tail-calls this shim name)
// jumps straight here, and ThingTemplate's field table binds the Voice* tokens
// to that thunk. So this is the parser itself; it keeps the shim name the
// landed thunk already calls.
//
// Zero Hour's body plus the validation tail BFME also added to
// parseAudioEventRTS (0x000BBB60, landed in ini.cpp): an event the audio
// manager cannot resolve throws INIException(3, "Invalid Sound '%s'").
// Differences from the reference that the bytes show:
//  - the event is not pooled: `push 0x74; call ??2@YAPAXI@Z` and the
//    inline constructor stores the class vftable, then builds m_event at +4
//    through the two-argument AudioEventRTS constructor (TheEmptyString, 0);
//  - "NoSound" frees through vtable slot 0 with 1, a virtual scalar delete;
//  - TheAudio's getInfoForAudioEvent is slot +0xAC and isValidAudioEvent +0x5C
//    (the same BFME slots ini.cpp documents for parseAudioEventRTS).

#include "Common/INIException.h"
#include "Common/AsciiString.h"	// inputs/reference/shims/ini: isEmpty and str() inline, as retail emits them

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *string1, const char *string2);

enum ObjectID { INVALID_ID = 0 };

// AsciiString::TheEmptyString; ascii_string.h has no static member for it.
extern const AsciiString Rva01336E50EmptyString;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
// m_eventName at +0x14 is the reference's; only what this body touches is spelled out.
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, ObjectID ownerID );
	void setEventName( AsciiString name );
	const AsciiString &getEventName() const { return m_eventName; }

private:
	void *m_vtbl;
	char m_head[0x10];
	AsciiString m_eventName;
	char m_tail[0x70 - 0x18];
};

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS() : m_event(Rva01336E50EmptyString, INVALID_ID) { }
	virtual ~DynamicAudioEventRTS();

	AudioEventRTS m_event;
};

// Retail's AudioManager vtable: slot +0x5C and +0xAC (BFME's order, not the stock header's).
class AudioManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58();
	virtual Bool isValidAudioEvent( const AudioEventRTS *eventToCheck ) const;	// +0x5C
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
	virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
	virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
	virtual void va0(); virtual void va4(); virtual void va8();
	virtual void getInfoForAudioEvent( const AudioEventRTS *eventToFindAndFill ) const;	// +0xAC
};

struct Rva005A00B0AudioClient;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;	// TheAudio, 0x012ED668

class INIParseDynamicAudioEventRTSShim
{
public:
	static void parse( INI *ini, void *instance, void *store, const void *userData );

private:
	// Inlined; the call boundary is what keeps MSVC from hoisting the name's
	// address above the isEmpty test, which retail reads straight off +0x18.
	static bool isNamedOtherThanNoSound( const AudioEventRTS &event )
	{
		return event.getEventName().compareNoCase("NoSound") != 0;
	}
};

// ?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z
void INIParseDynamicAudioEventRTSShim::parse( INI *ini, void * /*instance*/, void *store, const void * /*userData*/ )
{
	const char *token = ini->getNextToken();
	DynamicAudioEventRTS **theSound = (DynamicAudioEventRTS **)store;

	// translate the string into a sound
	if (_stricmp(token, "NoSound") == 0)
	{
		if (*theSound)
		{
			delete *theSound;
			*theSound = 0;
		}
		return;
	}

	if (*theSound == 0)
		*theSound = new DynamicAudioEventRTS;
	(*theSound)->m_event.setEventName(AsciiString(token));

	if (*theSound)
		((AudioManager *)TheAudioClientUpdate)->getInfoForAudioEvent(&(*theSound)->m_event);

	if (*theSound &&
			!(*theSound)->m_event.getEventName().isEmpty() &&
			isNamedOtherThanNoSound((*theSound)->m_event) &&
			!((AudioManager *)TheAudioClientUpdate)->isValidAudioEvent(&(*theSound)->m_event))
	{
		throw INIException(3, "Invalid Sound '%s'", (*theSound)->m_event.getEventName().str());
	}
}
