// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// DrawModule default bodies, retail RVAs 0x0074FF80 to 0x00750220.
// The opaque default virtuals sit at the same slots in many draw-module tables,
// including DrawModule's primary table VA 0x01121BA8; their names stay
// RVA-derived because a slot index and return shape prove no lexical name.
// setHidden and bfmeCondition4Callback retain the identities supported by their
// slot and caller evidence below; the callback remains nonvirtual in this view.
// This declaration is partial; its order does not reproduce the full retail table.

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class DrawModule
{
public:
	virtual void rva0074FF80();
	virtual void setHidden(Bool hidden);
	virtual void rva0074FFB0(UnsignedInt);
	virtual void rva0074FFC0(UnsignedInt);
	virtual void rva0074FFE0(Real);
	virtual void rva0074FFF0(UnsignedInt);
	virtual void rva00750000(UnsignedInt);
	virtual void rva00750030(UnsignedInt, UnsignedInt);
	virtual void rva00750040();
	virtual void rva00750050(UnsignedInt);
	virtual void rva00750060(UnsignedInt);
	virtual void rva00750070(UnsignedInt);
	virtual void rva00750090(UnsignedInt, UnsignedInt, UnsignedInt);
	virtual void rva007500A0();
	virtual Bool rva007500C0() const;
	virtual Bool rva007500D0() const;
	virtual void *rva007500F0();
	virtual void *rva007500E0();
	virtual void *rva00750110();
	virtual void *rva00750100();
	virtual void *rva00750120();
	virtual void *rva00750150();
	virtual void *rva00750140();
	virtual void *rva00750160();
	virtual void rva00750180(UnsignedInt);
	virtual Bool rva007501A0() const;
	virtual void rva007501E0();
	virtual void rva007501F0(UnsignedInt);
	virtual void rva00750200(UnsignedInt);
	void bfmeCondition4Callback();
};

// DrawModule slot 14 at retail RVA 0x0074FF90 is an empty setHidden method.
// W3DLightDrawDestructor.cpp records the vtable slot and the bool ABI.
// ?setHidden@DrawModule@@UAEX_N@Z
void DrawModule::setHidden(Bool hidden)
{
}

// ?rva0074FF80@DrawModule@@UAEXXZ
void DrawModule::rva0074FF80()
{
}

// ?rva0074FFB0@DrawModule@@UAEXI@Z
void DrawModule::rva0074FFB0(UnsignedInt)
{
}

// ?rva0074FFC0@DrawModule@@UAEXI@Z
void DrawModule::rva0074FFC0(UnsignedInt)
{
}

// ?rva0074FFE0@DrawModule@@UAEXM@Z
void DrawModule::rva0074FFE0(Real)
{
}

// ?rva0074FFF0@DrawModule@@UAEXI@Z
void DrawModule::rva0074FFF0(UnsignedInt)
{
}

// ?rva00750000@DrawModule@@UAEXI@Z
void DrawModule::rva00750000(UnsignedInt)
{
}

// ?rva00750030@DrawModule@@UAEXII@Z
void DrawModule::rva00750030(UnsignedInt, UnsignedInt)
{
}

// ?rva00750040@DrawModule@@UAEXXZ
void DrawModule::rva00750040()
{
}

// ?rva00750050@DrawModule@@UAEXI@Z
void DrawModule::rva00750050(UnsignedInt)
{
}

// ?rva00750060@DrawModule@@UAEXI@Z
void DrawModule::rva00750060(UnsignedInt)
{
}

// ?rva00750070@DrawModule@@UAEXI@Z
void DrawModule::rva00750070(UnsignedInt)
{
}

// ?rva00750090@DrawModule@@UAEXIII@Z
void DrawModule::rva00750090(UnsignedInt, UnsignedInt, UnsignedInt)
{
}

// DrawModule vtable slot 31 identifies this body at retail 0x007500A0.
// ?rva007500A0@DrawModule@@UAEXXZ
void DrawModule::rva007500A0()
{
}

// ?rva007500C0@DrawModule@@UBE_NXZ
Bool DrawModule::rva007500C0() const
{
	return true;
}

// ?rva007500D0@DrawModule@@UBE_NXZ
Bool DrawModule::rva007500D0() const
{
	return false;
}

// ?rva007500E0@DrawModule@@UAEPAXXZ
void *DrawModule::rva007500E0()
{
	return 0;
}

// ?rva007500F0@DrawModule@@UAEPAXXZ
void *DrawModule::rva007500F0()
{
	return 0;
}

// ?rva00750100@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750100()
{
	return 0;
}

// ?rva00750110@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750110()
{
	return 0;
}

// ?rva00750120@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750120()
{
	return 0;
}

// ?rva00750140@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750140()
{
	return 0;
}

// ?rva00750150@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750150()
{
	return 0;
}

// ?rva00750160@DrawModule@@UAEPAXXZ
void *DrawModule::rva00750160()
{
	return 0;
}

// ?rva00750180@DrawModule@@UAEXI@Z
void DrawModule::rva00750180(UnsignedInt)
{
}

// ?rva007501A0@DrawModule@@UBE_NXZ
Bool DrawModule::rva007501A0() const
{
	return false;
}

// DrawModule vtable slot 54 identifies this body at retail 0x007501E0.
void DrawModule::rva007501E0()
{
}

// ?rva007501F0@DrawModule@@UAEXI@Z
void DrawModule::rva007501F0(UnsignedInt)
{
}

// ?rva00750200@DrawModule@@UAEXI@Z
void DrawModule::rva00750200(UnsignedInt)
{
}

// Retail RVA 0x00750220 is DrawModule vtable slot 58.
// Drawable::bfmeNotifyCondition4Modules calls this empty callback.
void DrawModule::bfmeCondition4Callback()
{
}
