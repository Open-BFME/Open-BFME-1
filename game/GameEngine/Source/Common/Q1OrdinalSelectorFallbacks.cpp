// Eight seventeen-byte __cdecl functions laid out on a 0x20 stride over
// 0x00417120-0x00417200, differing in exactly ONE byte of payload:
//
//     push <ORDINAL> / call <REL32> / test eax,eax / jne ret
//     mov eax,<ADDRESS> / ret
//
// WHAT THE BYTES SHOW.  The pushed ordinals are 0x58,0x59,0x5A,0x5B,0x5C,0x5D,
// 0x5E,0x5F -- eight consecutive values, one per function, in address order.
// The callee is the same for all eight and so is the fallback address, so THE
// ORDINAL IS THE ONLY AXIS.
//
// The callee is __stdcall, and that is read off the bytes rather than assumed:
// the argument is pushed, the call is followed by no `add esp`, and the
// function returns immediately -- so the callee popped it.  Its return value is
// used directly as this function`s, and the `jne` skips the fallback, so the
// whole body is `result = f( K ); return result ? result : ADDRESS;`.
//
// WHAT THE BYTES CANNOT DECIDE.  The fallback address itself is one relocated
// field, so its four bytes are not evidence -- but the ADDRESS is.  0x012F1318 is
// the shared empty audio event that
// game/GameEngine/Source/Common/Audio/BfmeTheEmptyAudioEventGlobal.cpp defines as
// `AudioEventRTS BfmeTheEmptyAudioEvent` (matched row ?Rva00C6B4B0Init@@YAXXZ,
// whose $E initializer builds it from the empty AsciiString and owner 0), and
// what ThingTemplate::getSound hands back when a unit has no sound of its own.
// What is also evidence is that all eight fallbacks carry the SAME four bytes, so
// one extern object serves all eight and verify_dir32_consistency holds.  Its type
// stays INCOMPLETE: only its address is ever taken here, and an incomplete type is
// the declaration that asserts the least.  Nothing here says what the ordinal
// selects, and nothing says the eight consecutive ordinals index anything
// contiguous.
//
// IDENTITY IS NOT RECOVERED for anything but that global.  Every other name is
// derived from an address; the callee pin is address-derived and additive.

class AudioEventRTS;
extern AudioEventRTS BfmeTheEmptyAudioEvent;

void *__stdcall Q1Selector0000286A( int ordinal );

// The independently carved boundary immediately before this family is a
// one-byte return. No semantic identity is asserted beyond its address.
void Rva00417110()
{
}

#define Q1_SELECT_OR_FALLBACK( NAME, ORDINAL )                            \
	void *NAME();                                                         \
	void *NAME()                                                          \
	{                                                                     \
		void *selected = Q1Selector0000286A( ORDINAL );                       \
		return selected ? selected : (void *)&BfmeTheEmptyAudioEvent;           \
	}

Q1_SELECT_OR_FALLBACK( Rva00417200, 0x5F )
Q1_SELECT_OR_FALLBACK( Rva00417120, 0x58 )
Q1_SELECT_OR_FALLBACK( Rva00417140, 0x59 )
Q1_SELECT_OR_FALLBACK( Rva00417160, 0x5A )
Q1_SELECT_OR_FALLBACK( Rva00417180, 0x5B )
Q1_SELECT_OR_FALLBACK( Rva004171A0, 0x5C )
Q1_SELECT_OR_FALLBACK( Rva004171C0, 0x5D )
Q1_SELECT_OR_FALLBACK( Rva004171E0, 0x5E )

void *__stdcall Rva00417260( int selector )
{
	void *selected;
	switch ( selector )
	{
		case 1: selected = Q1Selector0000286A( 0x58 ); break;
		case 2: selected = Q1Selector0000286A( 0x59 ); break;
		case 3: selected = Q1Selector0000286A( 0x5A ); break;
		default: selected = Q1Selector0000286A( 0x57 ); break;
	}
	return selected ? selected : (void *)&BfmeTheEmptyAudioEvent;
}

void *__stdcall Rva004172A0( int selector )
{
	void *selected;
	switch ( selector )
	{
		case 1: selected = Q1Selector0000286A( 0x5C ); break;
		case 2: selected = Q1Selector0000286A( 0x5D ); break;
		case 3: selected = Q1Selector0000286A( 0x5E ); break;
		default: selected = Q1Selector0000286A( 0x5B ); break;
	}
	return selected ? selected : (void *)&BfmeTheEmptyAudioEvent;
}
