// Eight tiny bodies that free something the object owns and clear the field:
//
//     push esi / mov esi,ecx / mov ecx,[esi+<OFF>] / test ecx,ecx / je out
//     mov eax,[ecx] / push 1 / call dword ptr [eax]
//     out: mov dword ptr [esi+<OFF>],0 / pop esi / ret
//
// WHAT THE BYTES SHOW.  `push 1` followed by an indirect call through VFTABLE
// SLOT 0 is the MSVC scalar-deleting-destructor calling convention: that is
// what `delete p` compiles to when p's class has a virtual destructor, and
// nothing else in this compiler emits a literal 1 into slot 0.  So the owned
// class is polymorphic and its destructor is virtual.  The `test`/`je` pair is
// the null test `delete` emits on its own; the source need not contain one.
//
// WHERE THE `je` LANDS SPLITS THE FAMILY, and that is the whole of the source
// difference.  Seven of the eight jump ONTO the store of 0, so the clear is
// unconditional and the source is `delete m_p; m_p = 0;`.  ONE -- 0x00670150,
// `je +0x0D` -- jumps PAST it to `pop esi`, so its clear is inside an `if` the
// source wrote, and MSVC then elided delete's own redundant test.  A size
// comparison cannot see this difference: both spellings are 25 bytes.
//
// ONE MEMBER IS NOT A MEMBER.  0x007837C0 reads its object from [esp+8] after
// the push and ends in a bare `ret`: a free function taking the owner by
// pointer, __cdecl, otherwise identical.  Every byte of all six of these is
// concrete.
//
// TWO MEMBERS FREE THROUGH A GLOBAL FUNCTION POINTER instead (0x006915E0 and
// 0x00691600, byte-identical to each other):
//
//     ... mov al,[esi+4] / test al,al / je out / mov eax,[esi] / push eax
//     call dword ptr [<GLOBAL>] / mov byte ptr [esi+4],0 / out: pop esi / ret
//
// Here the guard is a ONE-BYTE flag, not the pointer, and the pointer at +0 is
// passed as an ordinary stack argument.  NO STACK ADJUSTMENT FOLLOWS THE CALL,
// so the callee pops its own argument: the pointer is __stdcall, not __cdecl --
// the __cdecl spelling compiles three bytes longer with an `add esp,4`.  The
// call site is a DIR32 the patcher fills from retail and the extern name is
// address-derived; the argument and result types are a guess consistent with
// one pushed dword and a discarded result.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define R2_RELEASE( NAME, OFF )                                           \
	class NAME##Owned                                                     \
	{                                                                     \
	public:                                                               \
		virtual ~NAME##Owned();                                             \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ OFF ];                                              \
		NAME##Owned *m_owned;                                               \
		void release();                                                     \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                     \
		m_owned = 0;                                                        \
	}

#define R2_RELEASE_HEAD( NAME )                                           \
	class NAME##Owned                                                     \
	{                                                                     \
	public:                                                               \
		virtual ~NAME##Owned();                                             \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME##Owned *m_owned;                                               \
		void release();                                                     \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                     \
		m_owned = 0;                                                        \
	}

#define R2_RELEASE_GUARDED_CLEAR( NAME, OFF )                             \
	class NAME##Owned                                                     \
	{                                                                     \
	public:                                                               \
		virtual ~NAME##Owned();                                             \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ OFF ];                                              \
		NAME##Owned *m_owned;                                               \
		void release();                                                     \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		if ( m_owned )                                                      \
		{                                                                   \
			delete m_owned;                                                   \
			m_owned = 0;                                                      \
		}                                                                   \
	}

R2_RELEASE_HEAD( Rva004C11B0 )
R2_RELEASE_GUARDED_CLEAR( Rva00670150, 0x8 )
R2_RELEASE( Rva008B3990, 0x20 )
R2_RELEASE( Rva00971120, 0x14 )
R2_RELEASE( Rva00971B70, 0x14 )

class Rva007837C0Owned
{
public:
	virtual ~Rva007837C0Owned();
};
class Rva007837C0Owner
{
public:
	char m_leading[ 0x4 ];
	Rva007837C0Owned *m_owned;
};
void Rva007837C0( Rva007837C0Owner *owner )
{
	delete owner->m_owned;
	owner->m_owned = 0;
}

extern void ( __stdcall *R2Fptr01358ECC )( void *object );

class Rva006915E0
{
public:
	void *m_object;
	bool m_live;
	void release();
};
void Rva006915E0::release()
{
	if ( m_live )
	{
		R2Fptr01358ECC( m_object );
		m_live = false;
	}
}
class Rva00691600
{
public:
	void *m_object;
	bool m_live;
	void release();
};
void Rva00691600::release()
{
	if ( m_live )
	{
		R2Fptr01358ECC( m_object );
		m_live = false;
	}
}
