// Four destructors whose whole body is a vptr store followed by a tail `jmp`:
//
//     mov dword ptr [ecx],<DIR32>            ; this class's own vftable
//     [ add ecx,<OFFSET> ]                   ; only when a MEMBER follows
//     jmp <REL32>                            ; the one thing left to destroy
//
// WHAT THE BYTES SHOW.  A destructor that opens by writing offset 0 with a
// vftable address is the destructor of a POLYMORPHIC class -- the store exists
// to reseat the vptr before subobjects run.  Exactly one destructor follows and
// control leaves through a `jmp`, so there is exactly ONE thing to destroy and
// no unwind funclet is needed: none of the four carries an EH frame.
//
// THE `add ecx` SPLITS THE FAMILY.  `add ecx,0xC` before the jump means the
// receiver is a MEMBER at offset 0xC; no adjustment at all means the receiver
// is `this` itself, i.e. a BASE at offset 0.  Two rows of each.
//
// The two base-at-zero rows are the destructors of classes the tree already
// spells: MidVptrOnlyDerivedCtors.cpp names 0x003BB2E0 and 0x003BB310 as the
// vptr-only derived constructors over GenBase003BB1E0, and each stores exactly
// the vftable its destructor here stores back (0x010ED7C8 and 0x010ED7E4).  The
// same class names are reused so the vftable DIR32 stays one symbol per class,
// and the base destructor at 0x003BB260 is the counterpart of the base
// constructor at 0x003BB1E0 that file already pins.
//
// 0x003B85F0 stores 0x010EC784, which R2ZeroingConstructors.cpp records the
// constructor at 0x003B85D0 writing to offset 0 of the same object.  That file
// says the bytes do not decide whether such a leading store is a vptr; a
// destructor STARTING with the store decides it here, so this row is spelled
// with a vptr and the class is named for its own address rather than reusing
// that file's Rva003B85D0.  Its member at 0xC is destroyed by 0x00887940, the
// destructor BigTwoMemberDtors.cpp already calls Mem00887940.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Mem00887940
{
public:
	~Mem00887940();
};

class Mem003AB460
{
public:
	~Mem003AB460();
};

class GenBase003BB1E0
{
public:
	virtual void handle();
	~GenBase003BB1E0();
};

#define BFME_VPTR_MEMBER_TAIL_DTOR( NAME, MEMBER )                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void handle();                                            \
		~NAME();                                                          \
		int    m_at04;                                                    \
		int    m_at08;                                                    \
		MEMBER m_at0C;                                                    \
	};                                                                    \
	NAME::~NAME() {}

#define BFME_VPTR_BASE_TAIL_DTOR( NAME )                                  \
	class NAME : public GenBase003BB1E0                                   \
	{                                                                     \
	public:                                                               \
		virtual void handle();                                            \
		~NAME();                                                          \
	};                                                                    \
	NAME::~NAME() {}

BFME_VPTR_MEMBER_TAIL_DTOR( Rva003B85F0, Mem00887940 )
BFME_VPTR_MEMBER_TAIL_DTOR( Rva003BA640, Mem003AB460 )

BFME_VPTR_BASE_TAIL_DTOR( Rva003BB2E0 )
BFME_VPTR_BASE_TAIL_DTOR( Rva003BB310 )
