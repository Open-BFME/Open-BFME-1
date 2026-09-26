// Nine more members of the mnemonic-only families anchored at 0x0007C530,
// 0x000659C0, 0x00098430 and 0x004C11B0 -- five guarded dispatches and four
// straight-line field writes.  They share a mnemonic sequence with their
// siblings and nothing else, so each is written for what its own bytes show.
//
// (A) FOUR GUARDED TAIL DISPATCHES THROUGH A GLOBAL POINTER:
//
//     mov ecx,[<GLOBAL>] / test ecx,ecx / je out
//     mov eax,[ecx] / jmp dword ptr [eax+<SLOT>] / out: ret
//
// ecx is loaded from a fixed address and never adjusted, so the global holds
// the receiver directly and its vptr is at offset 0.  Control leaves through
// `jmp`, so the callee's `ret` is this function's and neither side takes stack
// arguments; the guarded path falls through to a bare `ret` with NO value
// materialised in eax, so nothing is returned.  Three of the four read the same
// global at 0x012ED668 and dispatch slots 0x170, 0x154 and 0x164 of it; the
// fourth reads 0x01306DF0 and dispatches slot 4.
//
// (B) ONE GUARDED TAIL DISPATCH ON THIS (0x002D9AC0):
//
//     mov al,[ecx+4] / test al,al / je out / mov eax,[ecx] / jmp [eax+0x24]
//
// The vptr comes from `this` itself and ecx is never touched, so the call is
// this object's own virtual, guarded by a ONE-BYTE flag at +4 -- `mov al` and
// `test al,al`, not the four-byte pair.  Thirteen concrete bytes, no
// relocations.
//
// (C) THREE STRAIGHT-LINE FIELD WRITES.  0x007E8AC0 clears a byte THROUGH a
// pointer it holds at +0x10 before writing three of its own fields; 0x00588E40
// materialises -2 once (`mov eax,0xFFFFFFFE`) and a zero once (`xor edx,edx`)
// and spends them across five stores; 0x0073A860 is __cdecl, IGNORES ITS FIRST
// ARGUMENT and publishes the second into a global alongside three constants.
// That an argument is unused is what the bytes show -- [esp+4] is never read --
// and the first parameter's type is not recovered.
//
// (D) ONE GUARDED RELEASE THROUGH A STACK-PASSED VIRTUAL (0x00739C10):
//
//     push esi / mov esi,ecx / mov eax,[esi] / test eax,eax / je out
//     mov ecx,[eax] / push eax / call dword ptr [ecx+8]
//     mov dword ptr [esi],0 / out: pop esi / ret
//
// THE RECEIVER IS PUSHED, NOT PUT IN ecx: ecx holds the VFTABLE and eax holds
// the object, which is the reverse of a __thiscall virtual call.  So the
// dispatched member is a virtual declared __stdcall -- there is no stack
// adjustment after the call, so the callee pops.  The `je` lands PAST the store
// of 0, so the clear is inside the source's own `if`.  Every byte is concrete.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class R2GlobalReceiver
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00C();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01C();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02C();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03C();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04C();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05C();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06C();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07C();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08C();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09C();
	virtual void slot0A0();
	virtual void slot0A4();
	virtual void slot0A8();
	virtual void slot0AC();
	virtual void slot0B0();
	virtual void slot0B4();
	virtual void slot0B8();
	virtual void slot0BC();
	virtual void slot0C0();
	virtual void slot0C4();
	virtual void slot0C8();
	virtual void slot0CC();
	virtual void slot0D0();
	virtual void slot0D4();
	virtual void slot0D8();
	virtual void slot0DC();
	virtual void slot0E0();
	virtual void slot0E4();
	virtual void slot0E8();
	virtual void slot0EC();
	virtual void slot0F0();
	virtual void slot0F4();
	virtual void slot0F8();
	virtual void slot0FC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11C();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12C();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13C();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14C();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15C();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16C();
	virtual void slot170();
};

extern R2GlobalReceiver *R2Ptr012ED668;
extern R2GlobalReceiver *R2Ptr01306DF0;

void Rva0007C530() { if ( R2Ptr012ED668 ) { R2Ptr012ED668->slot170(); } }
void Rva002EEA30() { if ( R2Ptr012ED668 ) { R2Ptr012ED668->slot154(); } }
void Rva002EEA50() { if ( R2Ptr012ED668 ) { R2Ptr012ED668->slot164(); } }
void Rva007B7600() { if ( R2Ptr01306DF0 ) { R2Ptr01306DF0->slot004(); } }

class Rva002D9AC0 : public R2GlobalReceiver
{
public:
	bool m_flag;
	void run();
};
void Rva002D9AC0::run() { if ( m_flag ) { slot024(); } }

class Rva007E8AC0
{
public:
	char m_leadingA[ 0x10 ];
	char *m_at10;
	char m_leadingB[ 4 ];
	int m_at18;
	char m_leadingC[ 8 ];
	int m_at24;
	char m_leadingD[ 4 ];
	int m_at2C;
	void run();
};
void Rva007E8AC0::run()
{
	*m_at10 = 0;
	m_at18 = 0;
	m_at24 = 0;
	m_at2C = 4;
}

class Rva00588E40
{
public:
	char m_leading[ 8 ];
	char m_at08;
	char m_padding[ 3 ];
	int m_at0C;
	int m_at10;
	int m_at14;
	int m_at18;
	void run();
};
void Rva00588E40::run()
{
	m_at08 = 0;
	m_at0C = -2;
	m_at10 = -2;
	m_at14 = -2;
	m_at18 = 0;
}

extern int R2Glob013071C8;
extern int R2Glob013071C4;
extern void *R2Glob013071C0;
extern int R2Glob012BC140;
extern char R2Glob013071D0;
extern int R2Glob013071B4;
extern int R2Glob013071B0;
extern int R2Glob013071AC;
extern int R2Glob0130720C;
extern int R2Glob01307208;
extern int R2Glob01307204;

void Rva0073A860( int unused, void *value )
{
	R2Glob013071C8 = 0;
	R2Glob013071C4 = 12;
	R2Glob013071C0 = value;
	R2Glob012BC140 = 1;
	R2Glob013071D0 = 0;
}

// ?Rva0073B540@@YGXHH@Z
void __stdcall Rva0073B540( int first, int second )
{
	R2Glob013071B4 = 0;
	R2Glob013071B0 = first;
	R2Glob013071AC = second;
	R2Glob013071C8 = 0;
	R2Glob013071C4 = 12;
	R2Glob013071C0 = (void *)second;
	R2Glob012BC140 = 1;
	R2Glob013071D0 = 0;
	R2Glob0130720C = 0;
	R2Glob01307208 = first;
	R2Glob01307204 = second;
}

// Paired with the adjacent retail selector at 0x00739CC0; both are
// address-derived scalar mappings in this common R2 helper region.
int Rva00739D20( int value, bool enabled )
{
	int result = 0;
	switch ( value - 20 )
	{
	case 0:
		result = enabled ? 5 : 2;
		break;
	case 1:
		result = 2;
		break;
	case 2:
		result = 1;
		break;
	case 3:
		result = 3;
		break;
	case 4:
		result = 4;
		break;
	default:
		break;
	}
	return result;
}

class Rva00739C10Owned
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void __stdcall slot08();
};
class Rva00739C10
{
public:
	Rva00739C10Owned *m_owned;
	void release();
};
void Rva00739C10::release()
{
	if ( m_owned )
	{
		m_owned->slot08();
		m_owned = 0;
	}
}
