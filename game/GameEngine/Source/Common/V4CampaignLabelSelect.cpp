// cl: /Igame/Libraries/Source/WWVegas/WWLib
// One 44-byte __stdcall free function that fills a string object with one of two
// literals chosen by a byte read out of a global object:
//
//     mov eax,ds:[0x012F1024] / mov cl,[eax+0x1C] / test cl,cl
//     mov ecx,[esp+4] / push 0x10 / je .good
//     push offset "GUI:EvilCampaign" / call <set> / ret 4
//   .good:
//     push offset "GUI:GoodCampaign" / call <set> / ret 4
//
// WHAT THE BYTES SHOW.  The incoming ecx is OVERWRITTEN with [esp+4] before it
// is ever read, so nothing arrives in a register: this is a free function whose
// single stack argument is the receiver of the call, and `ret 4` pops it.  Both
// arms push the same literal length 0x10 and the same callee, and both the
// receiver load and that push are hoisted ABOVE the branch, so the two arms
// differ in exactly one operand -- the string.
//
// THE CALLEE IS THE LEDGER'S OWN.  0x00887D20 is already matched as
// StringBase<char>::set(const char *,int), so declaring that template with that
// one signature reproduces the decorated name and needs no pin.  The literal
// length 0x10 is a plain immediate in the instruction stream, not a computed
// strlen: both strings are sixteen characters, and the byte gate verifies each
// literal against the bytes at the address the DIR32 site points at.
//
// THE STRINGS ARE THE ONLY IDENTITY HERE.  "GUI:EvilCampaign" and
// "GUI:GoodCampaign" are BFME campaign-side labels, so the global at 0x012F1024
// holds a one-byte "is the evil campaign selected" flag at +0x1C.  The function's
// own name is still derived from its address, and so is the global's type.

#include "string_base.h"

// One type for 0x012F1024, shared with V4TwoCallForwarders.cpp, which calls the
// niladic member declared here.
class Glo012F1024Type
{
public:
	void step();
	char m_pad00[ 0x1C ];
	bool m_at1C;
};

extern Glo012F1024Type * Glo012F1024;

void __stdcall Rva003BDB40( StringBase< char > * out )
{
	if( Glo012F1024->m_at1C )
		out->set( "GUI:EvilCampaign", 0x10 );
	else
		out->set( "GUI:GoodCampaign", 0x10 );
}
