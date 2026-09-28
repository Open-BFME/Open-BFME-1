// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6B4B0 is the namespace-scope dynamic initializer for the
// AudioEventRTS global at 0x012F1318 (BfmeTheEmptyAudioEvent, which the
// ThingTemplate sound lookups hand back when a unit has no sound of its own):
// it constructs the event from the empty AsciiString and an owner ID of zero
// through the two-argument constructor's ILT (0x00025306), then registers the
// TU-local atexit teardown. Defining the global here lets MSVC emit those bytes
// as its compiler-local _$E1; the ledger row names that COFF symbol via
// object-symbol=_$E1. The constructor and destructor are only declared, so this
// TU emits no named function of its own.
// upstream constructor: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

extern AsciiString TheEmptyString;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	~AudioEventRTS();
};

AudioEventRTS BfmeTheEmptyAudioEvent(TheEmptyString, INVALID_ID);
