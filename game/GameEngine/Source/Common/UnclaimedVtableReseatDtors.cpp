// Seventeen unclaimed seven-byte __thiscall bodies with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / ret
//
// An empty destructor of a polymorphic class: it re-seats a vftable at +0 and
// returns nothing (a constructor would also return `this` in eax).  Precedent:
// TrivialVirtualDestructors.cpp.  Each sat in a .text gap no ledger row
// covered: 16-byte-aligned start after an int3 pad run, ret followed by int3
// padding or the next matched row, and no call, ILT stub, table slot, code
// immediate, pin or dir32 name at the address.
//
// WHICH CLASS.  Re-seating vftable V makes the body ~V or the destructor of
// any trivially-destructible descendant of V: MSVC 7.1 drops a derived class's
// own vftable store when the inlined base destructor re-stores the base one,
// and retail has hundreds of such bodies over far fewer vftables.  So the
// vftable's owner is not proof of this body's owner; each class keeps the
// destructor's own address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// 0x01129AF4 is the vftable the dir32 record owns as ??_7Rva007EA6D0Deleting@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva007EA6C0VtableReseat@@6B@ replaced with ??_7Rva007EA6D0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007EA6D0Deleting@@6B@")[];

class __declspec(novtable) Rva007EA6C0VtableReseat
{
public:
	virtual ~Rva007EA6C0VtableReseat();
};

Rva007EA6C0VtableReseat::~Rva007EA6C0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007EA6D0Deleting@@6B@");
}
// 0x0112B3AC is the vftable Rva007F4860VptrCtor.cpp emits (ledger dir32 row
// ??_7Rva007F4860Owner@@6B@); this class's own vftable was the unrecorded name
// the dir32 gate debt at 0x0112B3AC retires.  novtable suppresses it (and its
// ??_G); the seven-byte body is the explicit store of the recorded vtable alone,
// matching retail 0x007F48B0.
// retired debt: ??_7Rva007F48B0VtableReseat@@6B@ replaced with ??_7Rva007F4860Owner@@6B@
extern "C" void *__identifier("??_7Rva007F4860Owner@@6B@")[];

class __declspec(novtable) Rva007F48B0VtableReseat
{
public:
	virtual ~Rva007F48B0VtableReseat();
};

Rva007F48B0VtableReseat::~Rva007F48B0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F4860Owner@@6B@");
}
// 0x0112B3E4 is the vftable the dir32 record owns as ??_7Rva007F48D0Deleting@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112B3E4 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva007F48C0VtableReseat@@6B@ replaced with ??_7Rva007F48D0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007F48D0Deleting@@6B@")[];

class __declspec(novtable) Rva007F48C0VtableReseat
{
public:
	virtual ~Rva007F48C0VtableReseat();
};

Rva007F48C0VtableReseat::~Rva007F48C0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F48D0Deleting@@6B@");
}
// 0x0112B890 is the vftable the dir32 record owns as ??_7Rva007F89B0Deleting@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva007F8720VtableReseat@@6B@ replaced with ??_7Rva007F89B0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007F89B0Deleting@@6B@")[];

class __declspec(novtable) Rva007F8720VtableReseat
{
public:
	virtual ~Rva007F8720VtableReseat();
};

Rva007F8720VtableReseat::~Rva007F8720VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F89B0Deleting@@6B@");
}
// 0x0112B954 is the vftable the dir32 record owns as ??_7Rva007F8F40Deleting@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112B954 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva007F8DA0VtableReseat@@6B@ replaced with ??_7Rva007F8F40Deleting@@6B@
extern "C" void *__identifier("??_7Rva007F8F40Deleting@@6B@")[];

class __declspec(novtable) Rva007F8DA0VtableReseat
{
public:
	virtual ~Rva007F8DA0VtableReseat();
};

Rva007F8DA0VtableReseat::~Rva007F8DA0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F8F40Deleting@@6B@");
}
// 0x0112B9A8 is the vftable the dir32 record owns as ??_7Rva007F96A0Deleting@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva007F95D0VtableReseat@@6B@ replaced with ??_7Rva007F96A0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007F96A0Deleting@@6B@")[];

class __declspec(novtable) Rva007F95D0VtableReseat
{
public:
	virtual ~Rva007F95D0VtableReseat();
};

Rva007F95D0VtableReseat::~Rva007F95D0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F96A0Deleting@@6B@");
}
// 0x0112B3B8 is the vftable the dir32 record owns as ??_7Rva007FA8E0Deleting@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva007FA670VtableReseat@@6B@ replaced with ??_7Rva007FA8E0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007FA8E0Deleting@@6B@")[];

class __declspec(novtable) Rva007FA670VtableReseat
{
public:
	virtual ~Rva007FA670VtableReseat();
};

Rva007FA670VtableReseat::~Rva007FA670VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007FA8E0Deleting@@6B@");
}
// 0x0112BC0C is the vftable the dir32 record owns as ??_7Rva007FAD50Deleting@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112BC0C retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva007FA970VtableReseat@@6B@ replaced with ??_7Rva007FAD50Deleting@@6B@
extern "C" void *__identifier("??_7Rva007FAD50Deleting@@6B@")[];

class __declspec(novtable) Rva007FA970VtableReseat
{
public:
	virtual ~Rva007FA970VtableReseat();
};

Rva007FA970VtableReseat::~Rva007FA970VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007FAD50Deleting@@6B@");
}
// 0x0112BEB0 is the vftable the dir32 record owns as ??_7Rva007FBBE0Deleting@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112BEB0 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva007FBB50VtableReseat@@6B@ replaced with ??_7Rva007FBBE0Deleting@@6B@
extern "C" void *__identifier("??_7Rva007FBBE0Deleting@@6B@")[];

class __declspec(novtable) Rva007FBB50VtableReseat
{
public:
	virtual ~Rva007FBB50VtableReseat();
};

Rva007FBB50VtableReseat::~Rva007FBB50VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007FBBE0Deleting@@6B@");
}
// 0x0112C148 is the vftable the dir32 record owns as ??_7Rva007FD040Deleting@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112C148 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva007FCFB0VtableReseat@@6B@ replaced with ??_7Rva007FD040Deleting@@6B@
extern "C" void *__identifier("??_7Rva007FD040Deleting@@6B@")[];

class __declspec(novtable) Rva007FCFB0VtableReseat
{
public:
	virtual ~Rva007FCFB0VtableReseat();
};

Rva007FCFB0VtableReseat::~Rva007FCFB0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007FD040Deleting@@6B@");
}
// 0x0112C408 is the vftable the dir32 record owns as ??_7T2EmptyDtor_008018a0@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112C408 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva00801420VtableReseat@@6B@ replaced with ??_7T2EmptyDtor_008018a0@@6B@
extern "C" void *__identifier("??_7T2EmptyDtor_008018a0@@6B@")[];

class __declspec(novtable) Rva00801420VtableReseat
{
public:
	virtual ~Rva00801420VtableReseat();
};

Rva00801420VtableReseat::~Rva00801420VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7T2EmptyDtor_008018a0@@6B@");
}
// 0x0112C4E8 is the vftable the dir32 record owns as ??_7Rva00802380Base@@6B@
// (with ??_7T2EmptyDtor_00802360@@6B@ at the same address); this class's own
// vftable was the unrecorded name the dir32 gate debt at 0x0112C4E8 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva00802200VtableReseat@@6B@ replaced with ??_7Rva00802380Base@@6B@
extern "C" void *__identifier("??_7Rva00802380Base@@6B@")[];

class __declspec(novtable) Rva00802200VtableReseat
{
public:
	virtual ~Rva00802200VtableReseat();
};

Rva00802200VtableReseat::~Rva00802200VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00802380Base@@6B@");
}
// 0x0112C4FC is the vftable the dir32 record owns as ??_7Rva00802680Base@@6B@
// (with ??_7T2EmptyDtor_00802450@@6B@ at the same address); this class's own
// vftable was the unrecorded name the dir32 gate debt at 0x0112C4FC retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva00802280VtableReseat@@6B@ replaced with ??_7Rva00802680Base@@6B@
extern "C" void *__identifier("??_7Rva00802680Base@@6B@")[];

class __declspec(novtable) Rva00802280VtableReseat
{
public:
	virtual ~Rva00802280VtableReseat();
};

Rva00802280VtableReseat::~Rva00802280VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00802680Base@@6B@");
}
// 0x0112C570 is the vftable the dir32 record owns as ??_7Rva00802CA0Base@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva00802870VtableReseat@@6B@ replaced with ??_7Rva00802CA0Base@@6B@
extern "C" void *__identifier("??_7Rva00802CA0Base@@6B@")[];

class __declspec(novtable) Rva00802870VtableReseat
{
public:
	virtual ~Rva00802870VtableReseat();
};

Rva00802870VtableReseat::~Rva00802870VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00802CA0Base@@6B@");
}
// 0x0112C640 is the vftable the dir32 record owns as ??_7Rva00802EC0Base@@6B@
// (with ??_7T2EmptyDtor_00802ea0@@6B@ at the same address); this class's own
// vftable was the unrecorded name the dir32 gate debt at 0x0112C640 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva00802E30VtableReseat@@6B@ replaced with ??_7Rva00802EC0Base@@6B@
extern "C" void *__identifier("??_7Rva00802EC0Base@@6B@")[];

class __declspec(novtable) Rva00802E30VtableReseat
{
public:
	virtual ~Rva00802E30VtableReseat();
};

Rva00802E30VtableReseat::~Rva00802E30VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00802EC0Base@@6B@");
}
// 0x0112C754 is the vftable the dir32 record owns as ??_7T2EmptyDtor_00806460@@6B@;
// this class's own vftable was the unrecorded name the dir32 gate debt at 0x0112C754 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva008062F0VtableReseat@@6B@ replaced with ??_7T2EmptyDtor_00806460@@6B@
extern "C" void *__identifier("??_7T2EmptyDtor_00806460@@6B@")[];

class __declspec(novtable) Rva008062F0VtableReseat
{
public:
	virtual ~Rva008062F0VtableReseat();
};

Rva008062F0VtableReseat::~Rva008062F0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7T2EmptyDtor_00806460@@6B@");
}
// 0x0113CBAC is the vftable the dir32 record owns as ??_7Rva00938BF0Deleting@@6B@; novtable
// suppresses this class's own name and the body stores the recorded one.
// retired debt: ??_7Rva00938BC0VtableReseat@@6B@ replaced with ??_7Rva00938BF0Deleting@@6B@
extern "C" void *__identifier("??_7Rva00938BF0Deleting@@6B@")[];

class __declspec(novtable) Rva00938BC0VtableReseat
{
public:
	virtual ~Rva00938BC0VtableReseat();
};

Rva00938BC0VtableReseat::~Rva00938BC0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00938BF0Deleting@@6B@");
}
