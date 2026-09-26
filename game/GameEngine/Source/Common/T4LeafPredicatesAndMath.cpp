// cl: /EHs-c-
//
// Seven leaf bodies from the 0x005E97B0..0x0060D680 slice: no calls, no unwind
// frame, no globals except two floating-point literals.  Each is decided
// entirely by its own bytes.
//
// As in T4SmallMembers.cpp the receiver is a carrier class named after the
// member's own address, padded so that the one or two fields the body proves
// land at the offsets retail uses.  The offsets, widths and operand order are
// the evidence; the class names are not.
//
// THE TWO x87 ACCUMULATORS (0x005FF710, 0x00600400) are pure field arithmetic
// and their OPERAND ORDER is what fixes the source.  MSVC 7.1 emits `fld A /
// fadd B` for `A + B` in that order, so `m_field10 = m_field10 + m_field14`
// and `m_field10 += m_field14` are the same code while `m_field14 = m_field18
// * m_field14` and `m_field14 *= m_field18` are NOT -- retail loads the
// right-hand factor first in every multiply here, which is why the multiplies
// are spelled out long-hand and the adds are not.  Every operand is a `dword
// ptr` field access, so all of them are `float`.
//
// THE TWO INTEGER PREDICATES are branchless and their exact shape is the
// evidence:
//
//   0x005F2FF0 -- `cmp edx,4 / setne al / dec eax / and eax,6`.  setne then
//   dec turns "equal" into -1 and "not equal" into 0, and the mask picks the
//   value.  That is MSVC's branchless form of a conditional expression whose
//   two results are 6 and 0, not an `if`, which would branch.
//
//   0x005F3010 -- `test dl,dl / sete al` on a byte field: a negation of a
//   boolean, returned zero-extended in eax.
//
//   0x00609150 -- four compares against 0, 7, 1 and 5, each jumping to the
//   same `mov eax,1`, falling through to `xor eax,eax`.  The ORDER of the
//   compares is source order for a short-circuit `||` chain; the value tested
//   first is compared against zero with `test`, which is what MSVC does for
//   `x == 0` and not for a switch.
//
// THE TWO FLOAT COMPARISONS use `fucompp / fnstsw ax / test ah,0x44`, MSVC's
// equality idiom, against literals the build resolves as DIR32 operands.  Both
// literals are in the image and are transcribed, not guessed: 0.0f at
// 0x01075350 and 1.0f at 0x01075334.
//
//   0x005F4180 takes a pointer and no receiver -- `ret` with no pop and ecx
//   never read -- so it is a free function, and it returns 1 or 0 through two
//   branches, an `int`.
//
//   0x0060C2E0 stores the sum with `fst` rather than `fstp`, keeping it on the
//   stack for the comparison that follows, so the field written and the value
//   compared are the same expression.  `test ah,1 / jne` skips the store when
//   C0 is set, i.e. when the sum is BELOW the literal, so the guarded store
//   runs on greater-or-equal.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address.

typedef int Int;

// ---------------------------------------------------------------------------
// 0x005FF710
// ---------------------------------------------------------------------------
class T4Host005FF710
{
public:
	void update( void );
private:
	unsigned char m_pad[ 0x10 ];
	float m_field10;
	float m_field14;
	float m_field18;
	float m_field1C;
	float m_field20;
	float m_field24;
};

void T4Host005FF710::update( void )
{
	m_field10 = m_field10 + m_field14;
	m_field14 = m_field18 * m_field14;
	m_field1C = m_field20 + m_field1C;
	m_field20 = m_field24 * m_field20;
}

// ---------------------------------------------------------------------------
// 0x00600400
// ---------------------------------------------------------------------------
class T4Host00600400
{
public:
	void update( void );
private:
	unsigned char m_pad[ 0x10 ];
	float m_field10;
	float m_field14;
	float m_field18;
	float m_field1C;
	float m_field20;
	float m_field24;
	float m_field28;
	float m_field2C;
	float m_field30;
	float m_field34;
	float m_field38;
	float m_field3C;
};

void T4Host00600400::update( void )
{
	m_field10 = m_field10 + m_field1C;
	m_field14 = m_field20 + m_field14;
	m_field18 = m_field18 + m_field24;
	m_field1C = m_field28 * m_field1C;
	m_field20 = m_field2C * m_field20;
	m_field24 = m_field30 * m_field24;
	m_field34 = m_field34 + m_field38;
	m_field38 = m_field3C * m_field38;
}

// ---------------------------------------------------------------------------
// 0x005F2FF0
// ---------------------------------------------------------------------------
class T4Host005F2FF0
{
public:
	Int value( void ) const;
private:
	unsigned char m_pad[ 0x0c ];
	Int m_field0C;
};

Int T4Host005F2FF0::value( void ) const
{
	return m_field0C == 4 ? 6 : 0;
}

// ---------------------------------------------------------------------------
// 0x005F3010
// ---------------------------------------------------------------------------
class T4Host005F3010
{
public:
	Int isClear( void ) const;
private:
	unsigned char m_pad[ 0x80 ];
	bool m_field80;
};

Int T4Host005F3010::isClear( void ) const
{
	return m_field80 == false;
}

// ---------------------------------------------------------------------------
// 0x00609150
// ---------------------------------------------------------------------------
class T4Host00609150
{
public:
	Int matches( void ) const;
private:
	unsigned char m_pad[ 0x10c ];
	Int m_field10C;
};

Int T4Host00609150::matches( void ) const
{
	Int value = m_field10C;
	return value == 0 || value == 7 || value == 1 || value == 5;
}

// ---------------------------------------------------------------------------
// 0x005F4180
// ---------------------------------------------------------------------------
Int t4IsZero005F4180( const float *value )
{
	return *value == 0.0f;
}

// ---------------------------------------------------------------------------
// 0x0060C2E0
// ---------------------------------------------------------------------------
class T4Host0060C2E0
{
public:
	void advance( void );
private:
	unsigned char m_pad[ 0x48 ];
	Int m_field48;
	unsigned char m_pad2[ 0x20 ];
	float m_field6C;
	float m_field70;
};

void T4Host0060C2E0::advance( void )
{
	m_field70 = m_field6C + m_field70;
	if ( m_field70 >= 1.0f )
	{
		m_field48 = 0;
	}
}
