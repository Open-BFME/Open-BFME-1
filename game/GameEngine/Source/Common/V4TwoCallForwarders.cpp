// Three __thiscall members whose entire body is TWO calls in sequence and whose
// second call leaves through a `jmp` where it can:
//
//   0x003BCA30  mov ecx,[ecx+0x28] / call <A> / mov ecx,ds:[G] / jmp <B>
//   0x003BEED0  push esi / mov esi,ecx / mov ecx,ds:[G] / call <A>
//               mov ecx,esi / pop esi / jmp <B>
//   0x003C0E40  mov eax,[esp+4] / push esi / push eax / mov esi,ecx / call <A>
//               push eax / mov ecx,esi / call <B> / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  Each call sets ecx and nothing else, so every callee is
// a niladic __thiscall member -- except the third, which pushes one argument
// into the first call and then pushes that call's RESULT into the second, so
// there the two are chained: `this->second( this->first( a ) )`.  A receiver
// that comes out of `ds:[G]` is a global pointer, and a receiver of `[ecx+0x28]`
// is a member; the first row needs neither saved, so it keeps no frame at all
// and its second call is a tail `jmp`.  The second row must keep `this` alive
// across its first call, which is exactly what the `push esi` buys, and it still
// tail-jumps.  The third cannot: it has to pop esi after the second call, so its
// second call is a `call` and the body ends in `ret 4`.
//
// The first row's second callee, 0x00383860, is a body the ledger already names,
// so it needs no pin.
//
// IDENTITY IS NOT RECOVERED.  Every other name is derived from an address; the
// callee and global pins are address-derived and additive.

class Rva00383860
{
public:
	void invoke();
};

class Gen003C75A0Owner
{
public:
	void step();
};

// The global at 0x012F1024 is the same one V4CampaignLabelSelect.cpp reads a
// flag out of, so it carries ONE type here and there rather than two.
class Glo012F1024Type
{
public:
	void step();
	char m_pad00[ 0x1C ];
	bool m_at1C;
};

extern Rva00383860 *      Glo012F0898;
extern Glo012F1024Type *  Glo012F1024;

class Rva003BCA30
{
public:
	void run();
	char                m_pad00[ 0x28 ];
	Gen003C75A0Owner *  m_at28;
};
void Rva003BCA30::run()
{
	m_at28->step();
	Glo012F0898->invoke();
}

class Rva003BEED0
{
public:
	void run();
	void finish();
};
void Rva003BEED0::run()
{
	Glo012F1024->step();
	finish();
}

class Rva003C0E40
{
public:
	void  run( int a );
	int   first( int a );
	void  second( int value );
};
void Rva003C0E40::run( int a )
{
	second( first( a ) );
}
