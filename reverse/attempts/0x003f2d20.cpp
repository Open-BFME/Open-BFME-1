// ?rva003f2d20@Rva003F2D20Owner@@QAE_NHH@Z
// partial score=0.8 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: cold-region dump body with no named caller, vtable slot, string
// literal or ZH twin that proves a class/method identity. Its sole caller,
// 0x003F55E0, is itself unconverted; re_attempts.log describes that body as a
// BFME spiral cell-search driver that probes this function once before the
// spiral loop, then calls a second predicate (0x003F1690, also unconverted)
// four times per ring. This body reads that same 0x003F1690 predicate: it
// forwards this object's fields plus the two candidate-cell arguments, and on
// a false/zero result keeps a running "closest so far" record in three of its
// own fields. Kept under an address-qualified name; see docs/naming_evidence.md.

typedef int Int;
typedef unsigned char UByte;

// 0x003F1690 (337B, also a still-unconverted dump): eleven explicit stack
// arguments plus a thiscall receiver read from this object's own field 0.
// Only the call-site shape (types/order) is asserted here, not its body.
class Rva003F1690Owner
{
public:
	bool rva003f1690( Int, Int, Int, Int, Int, Int, Int, Int, void *, Int, Int * );
};

// The retail thunk at 0x0003DC4E (thunks_029.cpp) tail-jumps straight to
// 0x003F1690; alias our typed call onto that already-compiled symbol.
#pragma comment(linker, "/alternatename:?rva003f1690@Rva003F1690Owner@@QAE_NHHHHHHHHPAXHPAH@Z=?j_0003dc4e@@YAXXZ")

class Rva003F2D20Owner
{
public:
	bool rva003f2d20( Int cellX, Int cellY );

private:
	Rva003F1690Owner *m_00;
	Int m_04;
	Int m_08;
	UByte m_0c;
	UByte m_0d;
	Int m_10;
	Int m_14;
	Int m_18;
	Int m_1c;
	Int m_20;
	Int m_24;
	unsigned char m_28[ 4 ];
};

// ?rva003f2d20@Rva003F2D20Owner@@QAE_NHH@Z
bool Rva003F2D20Owner::rva003f2d20( Int cellX, Int cellY )
{
	Int out;
	if ( !m_00->rva003f1690( m_04, m_08, m_0c, cellX, cellY, m_14, m_10, m_0d,
							  &m_28, m_18, &out ) )
		return false;

	if ( out == 0 )
		return true;

	if ( out < m_24 || m_24 == 0 )
	{
		m_24 = out;
		m_1c = cellX;
		m_20 = cellY;
	}
	return false;
}
