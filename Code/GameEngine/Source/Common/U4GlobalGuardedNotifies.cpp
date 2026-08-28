// Three bodies from the 0x005E97B0..0x0060D680 slice whose whole content is a
// null test around one call.
//
// 0x006057C0 (51 bytes) -- assignment with a self-check:
//
//     mov eax,[esp+4] / push esi / mov esi,ecx / cmp eax,esi / je OUT
//     mov ecx,[eax+4]  / mov [esi+4], ecx
//     mov edx,[eax+8]  / mov [esi+8], edx
//     mov eax,[eax+0x10] / mov [esi+0x10],eax
//     mov ecx,[<GLOBAL>] / test ecx,ecx / je OUT / push esi / call <A>
//     OUT: mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `mov eax,esi` before `ret 4` returns the receiver, and
// the argument is compared against `this` before anything is copied: that is
// `if (&other != this)` guarding a copy-assignment, and the returned receiver
// is `return *this`.  THE COPIED FIELDS ARE 4, 8 AND 0x10 ONLY -- 0 and 0xC are
// read by nothing and written by nothing, so the operator assigns three of the
// class's members and leaves the others alone.  A compiler-generated assignment
// would copy every member; a `memcpy`-shaped one would not skip a hole.  Both
// jumps land on the same instruction, so the global test is INSIDE the
// self-check, not after it.
//
// 0x00604C00 (22 bytes) -- the same global, a different call:
//
//     mov eax,ecx / mov ecx,[<GLOBAL>] / test ecx,ecx / je OUT
//     add eax,-0xC / push eax / call <B> / OUT: ret
//
// `add eax,-0xC` on `this` with NO null guard around it is a pointer adjustment
// the compiler knows cannot be null -- which `this` never is.  Subtracting is
// base-to-DERIVED, so the receiver is a subobject at offset 0xC of the object
// being handed over.  The two calls take differently adjusted pointers, so they
// are two different entry points, and both are reached through the same global
// dword at 0x012F10D0, which is therefore a pointer and is loaded into ecx --
// a __thiscall receiver -- rather than pushed.
//
// 0x0060C2C0 (21 bytes) -- a free function guarding the receiver itself:
//
//     mov ecx,[esp+4] / test ecx,ecx / je OUT
//     mov eax,[esp+8] / push eax / call <C> / OUT: ret 8
//
// The receiver arrives as an ORDINARY STACK ARGUMENT and is moved into ecx, and
// the function pops its own two dwords: __stdcall wrapping a __thiscall call.
// The null test is on the receiver, so the source tests the pointer it was
// handed before calling through it.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address, the
// global's address is a DIR32 operand copied from retail, and the three call
// targets are pinned in reverse/symbols.csv by the addresses their REL32s
// resolve to.  The unread fields are spelled `int` because a slot nothing
// touches has no type in evidence.

class U4Owner00604C00;
class U4Assign006057C0;

// The object the global at 0x012F10D0 points at.  Its two entry points are
// 0x00409040 and 0x004090C0.
class U4Notify
{
public:
	void noteAssign( U4Assign006057C0 *a );
	void noteOwner( U4Owner00604C00 *o );
};

extern U4Notify *g_u4Notify;

// ---------------------------------------------------------------- 0x006057C0

class U4Assign006057C0
{
public:
	U4Assign006057C0 &operator=( const U4Assign006057C0 &other );
	int m_f00;
	int m_f04;
	int m_f08;
	int m_f0C;
	int m_f10;
};

U4Assign006057C0 &U4Assign006057C0::operator=( const U4Assign006057C0 &other )
{
	if ( &other != this )
	{
		m_f04 = other.m_f04;
		m_f08 = other.m_f08;
		m_f10 = other.m_f10;
		if ( g_u4Notify != 0 )
			g_u4Notify->noteAssign( this );
	}
	return *this;
}

// ---------------------------------------------------------------- 0x00604C00

class U4Inner00604C00
{
public:
	void detach( void );
};

void U4Inner00604C00::detach( void )
{
	U4Owner00604C00 *owner = (U4Owner00604C00 *)( (char *)this - 0x0C );
	if ( g_u4Notify != 0 )
		g_u4Notify->noteOwner( owner );
}

// ---------------------------------------------------------------- 0x0060C2C0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/WW3D/pluglib/WWmatrix3.h
class Matrix3
{
};

class Matrix3D
{
public:
	void Set_Rotation( const Matrix3 &rotation );
	// Retail takes this snapshot in a fixed load/store sequence before
	// replacing its rotation, so the view preserves those observable accesses.
	volatile float m_bfme00;
	volatile float m_bfme01;
	volatile float m_bfme02;
	volatile float m_bfme03;
	volatile float m_bfme10;
	volatile float m_bfme11;
	volatile float m_bfme12;
	volatile float m_bfme13;
	volatile float m_bfme20;
	volatile float m_bfme21;
	volatile float m_bfme22;
	volatile float m_bfme23;
};

class U4MatrixTarget0060C2C0
{
public:
	virtual void v00( void );
	virtual void v01( void );
	virtual void v02( void );
	virtual void v03( void );
	virtual void v04( void );
	virtual void v05( void );
	virtual void v06( void );
	virtual void v07( void );
	virtual void v08( void );
	virtual void v09( void );
	virtual void v10( void );
	virtual void v11( void );
	virtual void v12( void );
	virtual void v13( void );
	virtual void v14( void );
	virtual void v15( void );
	virtual void v16( void );
	virtual void v17( void );
	virtual void v18( void );
	virtual void v19( void );
	virtual void prepare( void );
	virtual void apply( const Matrix3D &matrix );
	char m_bfmeHead[0x14];
	Matrix3D m_bfmeMatrix;
};

// 0x0061D4D0
class U4Target0060C2C0
{
public:
	void hand( void *payload );

private:
	char m_bfmeHead[0x08];
	U4MatrixTarget0060C2C0 *m_bfmePrimary;
	U4MatrixTarget0060C2C0 *m_bfmeSecondary;
};

void U4Target0060C2C0::hand( void *payload )
{
	U4MatrixTarget0060C2C0 *primary = m_bfmePrimary;
	if ( primary != 0 )
	{
		primary->prepare();
		Matrix3D matrix;
		matrix.m_bfme00 = primary->m_bfmeMatrix.m_bfme00;
		matrix.m_bfme01 = primary->m_bfmeMatrix.m_bfme01;
		matrix.m_bfme02 = primary->m_bfmeMatrix.m_bfme02;
		matrix.m_bfme03 = primary->m_bfmeMatrix.m_bfme03;
		matrix.m_bfme10 = primary->m_bfmeMatrix.m_bfme10;
		matrix.m_bfme11 = primary->m_bfmeMatrix.m_bfme11;
		matrix.m_bfme12 = primary->m_bfmeMatrix.m_bfme12;
		matrix.m_bfme13 = primary->m_bfmeMatrix.m_bfme13;
		matrix.m_bfme20 = primary->m_bfmeMatrix.m_bfme20;
		matrix.m_bfme21 = primary->m_bfmeMatrix.m_bfme21;
		matrix.m_bfme22 = primary->m_bfmeMatrix.m_bfme22;
		matrix.m_bfme23 = primary->m_bfmeMatrix.m_bfme23;
		matrix.Set_Rotation( *(const Matrix3 *)payload );
		m_bfmePrimary->apply( matrix );
		if ( m_bfmeSecondary != 0 )
			m_bfmeSecondary->apply( matrix );
	}
}

void __stdcall u4Guarded0060C2C0( U4Target0060C2C0 *target, void *payload )
{
	if ( target != 0 )
		target->hand( payload );
}
