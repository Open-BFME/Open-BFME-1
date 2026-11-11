// Ten unclaimed eleven-byte __thiscall bodies with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / jmp <base destructor>
//
// An empty destructor of a derived class: it re-seats the vftable at +0 and
// tail-jumps into the base destructor (precedent: VptrTailJumpDestructors.cpp,
// whose comment gives the full reasoning).  Each body sat in a .text gap no
// ledger row covered: 16-byte-aligned start after an int3 pad run, the jmp
// followed by int3 padding or the next matched row, and no call, ILT stub,
// table slot, code immediate, pin or dir32 name at the address.
//
// WHERE THE JUMP GOES.  The displacement is read off the retail bytes.  Nine
// bodies jump to 0x007EB6C0, matched as ??1BfmeDirtyBase@@UAE@XZ, and one to
// 0x007FA650, matched as ??1Rva00803890Base@@UAE@XZ; both bases are declared
// here under those names (each is declared in its own source, not a header)
// so the jump resolves through the ledger with no new pin.
//
// WHICH CLASS.  A destructor that only re-seats vftable V and then runs the
// base destructor is ~V or the destructor of any trivially-destructible
// descendant of V: MSVC 7.1 drops a derived class's own vftable store when
// the inlined base destructor re-stores the base one.  So V's owner is not
// this body's owner, and each class keeps the destructor's own address.
//
// IDENTITY IS NOT RECOVERED for the derived classes.  Every name is derived
// from an address.
//
// WHICH VFTABLE NAME.  Each retail vftable already has a recorded dir32 name
// (a sibling deleting destructor's class), so every class here is novtable and
// stores that recorded name explicitly instead of emitting a second name.

struct BfmeDirtyBase
{
public:
	virtual ~BfmeDirtyBase();
};

class Rva00803890Base
{
public:
	virtual ~Rva00803890Base();
};

// retired debt: ??_7Rva007E9080ReseatTailDtor@@6B@ replaced with ??_7Gen007E9B10@@6B@ (0x01129758)
extern "C" void *__identifier("??_7Gen007E9B10@@6B@")[];
class __declspec(novtable) Rva007E9080ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007E9080ReseatTailDtor();
};
Rva007E9080ReseatTailDtor::~Rva007E9080ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007E9B10@@6B@");
}
// retired debt: ??_7Rva007F03B0ReseatTailDtor@@6B@ replaced with ??_7Gen007F1BF0@@6B@ (0x0112A5F8)
extern "C" void *__identifier("??_7Gen007F1BF0@@6B@")[];
class __declspec(novtable) Rva007F03B0ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F03B0ReseatTailDtor();
};
Rva007F03B0ReseatTailDtor::~Rva007F03B0ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F1BF0@@6B@");
}
// retired debt: ??_7Rva007F1C80ReseatTailDtor@@6B@ replaced with ??_7Gen007F2120@@6B@ (0x0112AB34)
extern "C" void *__identifier("??_7Gen007F2120@@6B@")[];
class __declspec(novtable) Rva007F1C80ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F1C80ReseatTailDtor();
};
Rva007F1C80ReseatTailDtor::~Rva007F1C80ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F2120@@6B@");
}
// retired debt: ??_7Rva007F2200ReseatTailDtor@@6B@ replaced with ??_7Gen007F2E30@@6B@ (0x0112AC70)
extern "C" void *__identifier("??_7Gen007F2E30@@6B@")[];
class __declspec(novtable) Rva007F2200ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F2200ReseatTailDtor();
};
Rva007F2200ReseatTailDtor::~Rva007F2200ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F2E30@@6B@");
}
// 0x0112AF04 is the vftable the dir32 record owns as ??_7Gen007F33E0@@6B@
// (with ??_7Rva007F2F50CleanupDeleting@@6B@ at the same address); this class's
// own vftable was the unrecorded name the dir32 gate debt at 0x0112AF04 retires.
// novtable suppresses it (and its ??_G); the eleven-byte body is the explicit
// store of the recorded vtable followed by the tail-jump into the base dtor.
// retired debt: ??_7Rva007F2E90ReseatTailDtor@@6B@ replaced with ??_7Gen007F33E0@@6B@
extern "C" void *__identifier("??_7Gen007F33E0@@6B@")[];

class __declspec(novtable) Rva007F2E90ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F2E90ReseatTailDtor();
};

Rva007F2E90ReseatTailDtor::~Rva007F2E90ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F33E0@@6B@");
}
// retired debt: ??_7Rva007F3590ReseatTailDtor@@6B@ replaced with ??_7Gen007F40C0@@6B@ (0x0112B048)
extern "C" void *__identifier("??_7Gen007F40C0@@6B@")[];
class __declspec(novtable) Rva007F3590ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F3590ReseatTailDtor();
};
Rva007F3590ReseatTailDtor::~Rva007F3590ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F40C0@@6B@");
}
// retired debt: ??_7Rva007F4120ReseatTailDtor@@6B@ replaced with ??_7Gen007F47E0@@6B@ (0x0112B248)
extern "C" void *__identifier("??_7Gen007F47E0@@6B@")[];
class __declspec(novtable) Rva007F4120ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F4120ReseatTailDtor();
};
Rva007F4120ReseatTailDtor::~Rva007F4120ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F47E0@@6B@");
}
// retired debt: ??_7Rva007F48A0ReseatTailDtor@@6B@ replaced with ??_7Rva007F4900CleanupDeleting@@6B@ (0x0112B3C8)
extern "C" void *__identifier("??_7Rva007F4900CleanupDeleting@@6B@")[];
class __declspec(novtable) Rva007F48A0ReseatTailDtor : public Rva00803890Base
{
public:
	virtual ~Rva007F48A0ReseatTailDtor();
};
Rva007F48A0ReseatTailDtor::~Rva007F48A0ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F4900CleanupDeleting@@6B@");
}
// retired debt: ??_7Rva007FADD0ReseatTailDtor@@6B@ replaced with ??_7Gen007FBAF0@@6B@ (0x0112BCD0)
extern "C" void *__identifier("??_7Gen007FBAF0@@6B@")[];
class __declspec(novtable) Rva007FADD0ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007FADD0ReseatTailDtor();
};
Rva007FADD0ReseatTailDtor::~Rva007FADD0ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007FBAF0@@6B@");
}
// 0x0112BEE8 is the vftable the dir32 record owns as ??_7Gen007FCF50@@6B@
// (with ??_7Rva007FC120CleanupDeleting@@6B@ at the same address); same
// novtable spelling as Rva007F2E90ReseatTailDtor above; every class in
// this file now stores its recorded vftable name explicitly.
// retired debt: ??_7Rva007FBC20ReseatTailDtor@@6B@ replaced with ??_7Gen007FCF50@@6B@
extern "C" void *__identifier("??_7Gen007FCF50@@6B@")[];

class __declspec(novtable) Rva007FBC20ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007FBC20ReseatTailDtor();
};

Rva007FBC20ReseatTailDtor::~Rva007FBC20ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007FCF50@@6B@");
}
