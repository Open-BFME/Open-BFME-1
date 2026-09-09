// ?d_00187860@@YAXXZ
// partial score=0.62 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the VERSIONED form of the same hand-over family.
//
// The two-byte block handed to slot ten is not a constant pair: the first
// byte is a kind and the SECOND is a version, seeded with the writer's
// current version and read back by the callee.  Bodies that seed it with 1
// never look at it again; bodies that seed it with 2 or 3 test it afterwards
// -- `cmp byte ptr [esp+9], 2` / `jb` -- and skip the hand-overs a reader of
// an older file must not perform.  That is a plain `if (version >= N)` around
// the tail of the body, and the compare is UNSIGNED, so the field is an
// unsigned char.
//
// The compare reads the block through esp, so its offset moves with every
// pending __cdecl cleanup; matching it means tracking the stack delta rather
// than the literal displacement.

struct BfmeVersionBlock
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmeVersion;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeAskAt10(void);		// slot 4, vtable+0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);		// slot 9, vtable+0x24
	virtual void bfmeSeed(BfmeVersionBlock *version);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);		// slot 12, vtable+0x30
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeTakeAt4C(void *item);		// slot 19, vtable+0x4C
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);		// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeTakeAt68(void *item);		// slot 26, vtable+0x68
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeTakeAt7C(void *item);		// slot 31, vtable+0x7C
	virtual void bfmeSlot32(void);
	virtual void bfmeTakeAt84(void *item);		// slot 33, vtable+0x84
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

class BfmeSubAccept_00002DEC
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002DEC
};

class BfmeSubAccept_00029DAC
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00029DAC
};

void bfmeHandOver_00004B79(BfmeSeedTarget *target, void *item);		// ILT 0x00004B79
void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);		// ILT 0x0000C9B4
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);		// ILT 0x0000FFE2
void bfmeHandOver_00020879(BfmeSeedTarget *target, void *item);		// ILT 0x00020879
void bfmeHandOver_00043301(BfmeSeedTarget *target, void *item);		// ILT 0x00043301

// The 0x00187860 body is the accepting sub-object reached from the matched
// Gen_002B5250/Gen_002C1740 seed bodies.  Keep the owner class empty: its
// one-byte placeholder is what preserves the parent offsets (+0x340/+0x34C).
// This TU-local view carries only the proven retail fields of the sub-object.
struct Rva00187860Coord3D
{
	float x;
	float y;
	float z;

	void set(const Rva00187860Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

namespace Rva00187860Stl
{
struct __false_type
{
};

template <class Type> class allocator
{
};

template <class Type, class Allocator> class vector
{
public:
	int size(void) const
	{
		return (int)(m_finish - m_start);
	}

	Type &operator[](unsigned int index)
	{
		return m_start[index];
	}

	void append(const Type &value, const __false_type &tag)
	{
		if (m_finish != m_endOfStorage)
		{
			if (m_finish != 0)
			{
				*m_finish = value;
			}
			++m_finish;
		}
		else
		{
			_M_insert_overflow(m_finish, value, tag, 1, true);
		}
	}

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};
}

template <class T> class Rva00187860StringBase
{
	friend class Rva00187860AsciiString;

private:
	Rva00187860StringBase() : m_data(0) {}
	Rva00187860StringBase(const Rva00187860StringBase<T> &other);
	~Rva00187860StringBase();
	void set(const Rva00187860StringBase<T> &other);

protected:
	bool hasText(void) const
	{
		const unsigned char *data = (const unsigned char *)m_data;
		return data != 0 && *(const unsigned short *)(data + 4) != 0;
	}

	private:
	void *m_data;
};

class Rva00187860AsciiString : private Rva00187860StringBase<char>
{
public:
	Rva00187860AsciiString() : Rva00187860StringBase<char>() {}
	Rva00187860AsciiString(const Rva00187860AsciiString &other)
		: Rva00187860StringBase<char>(other) {}
	~Rva00187860AsciiString() {}
	void set(const Rva00187860AsciiString &other)
	{
		Rva00187860StringBase<char>::set(other);
	}
	bool hasText(void) const
	{
		return Rva00187860StringBase<char>::hasText();
	}
};

struct Rva00187860RoadRecord
{
	char m_pad0[4];
	int m_value;
};

struct Rva00187860NameRecord
{
	char m_pad0[8];
	Rva00187860AsciiString m_name;
};

struct Rva00187860CommandRecord
{
	char m_pad0[12];
	Rva00187860AsciiString m_name;
};

class Rva00187860Path
{
public:
	Rva00187860Path();

private:
	char m_storage[0x24];
};

class Rva00187860Embedded
{
public:
	virtual void accept(BfmeSeedTarget *target);
};

struct Rva00187860RoadRecord;

class Rva00187860TerrainLogic
{
public:
	virtual void slot00(void); virtual void slot01(void);
	virtual void slot02(void); virtual void slot03(void);
	virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void);
	virtual void slot08(void); virtual void slot09(void);
	virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void);
	virtual void slot14(void); virtual void slot15(void);
	virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void);
	virtual void slot20(void); virtual void slot21(void);
	virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void);
	virtual void slot26(void); virtual void slot27(void);
	virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void);
	virtual Rva00187860RoadRecord *getValue(int value);
	virtual void slot33(void); virtual void slot34(void);
	virtual void slot35(void);
	virtual void *setName(Rva00187860AsciiString value);
};

extern Rva00187860TerrainLogic *TheTerrainLogic;

class Rva00187860CommandButton;
class Rva00187860ControlBar
{
public:
	Rva00187860CommandButton *findCommandButton(
		const Rva00187860AsciiString &name);
};

extern Rva00187860ControlBar *TheControlBar;

// No source identity has been proved for the final Path/selection helper;
// keep the call address-derived and scoped to this reconstruction rather than
// inventing a class/member spelling for it.
void Rva00187860PathAccept(Rva00187860Path *path,
	BfmeSeedTarget *target);

struct Rva00187860View
{
	char m_pad0[0x24];
	Rva00187860Stl::vector<Rva00187860Coord3D,
		Rva00187860Stl::allocator<Rva00187860Coord3D> > m_points;
	Rva00187860RoadRecord *m_roadRecord;
	Rva00187860NameRecord *m_nameRecord;
	void *m_pointOwner;
	Rva00187860Embedded *m_embedded;
	char m_pad40[0x58];
	Rva00187860CommandRecord *m_commandRecord;
	Rva00187860Path *m_path;
};

class Gen_000C7C40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x0C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x10
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x14
};

class Gen_0016BA30
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x5C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x60
	char m_bfmeItem3;				// +0x61
};

class Gen_0016C120
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
	char m_bfmeItem2;				// +0x55
	char m_bfmePad3[0x2];
	char m_bfmeItem3;				// +0x58
};

class Gen_0016C350
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x4E];
	char m_bfmeItem0;				// +0x4E
	char m_bfmePad1[0x5];
	char m_bfmeItem1;				// +0x54
	char m_bfmePad2[0x3];
	void *m_bfmeHeld2;				// +0x58
	char m_bfmeItem3;				// +0x5C
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x60
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x64
	char m_bfmePad6[0xB];
	char m_bfmeItem6;				// +0x70
};

class Gen_001F7FE0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_00201B00
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_0020D2B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_00212FC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00031557

	char m_bfmePad0[0xE0];
	BfmeSubAccept_00029DAC m_bfmeSub0;		// +0xE0
};

class Gen_00217810
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00036714

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
};

class Gen_00248BE0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0000EAA7

	char m_bfmePad0[0x9B8];
	char m_bfmeItem0;				// +0x9B8
};

class Gen_00250A80
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000099CB

};

class Gen_00281CD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmeItem2;				// +0x29
};

class Gen_002B5250
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00043441

	char m_bfmePad0[0x340];
	BfmeSubAccept_00002DEC m_bfmeSub0;		// +0x340
	char m_bfmePad1[0x9F];
	char m_bfmeItem1;				// +0x3E0
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x3E4
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x3E8
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x3EC
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x3F0
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x3F4
	char m_bfmePad7[0xB];
	char m_bfmeItem7;				// +0x400
	char m_bfmeItem8;				// +0x401
	char m_bfmeItem9;				// +0x402
	char m_bfmeItem10;				// +0x403
	char m_bfmeItem11;				// +0x404
};

class Gen_002BEC60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
};

class Gen_002C1740
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00043441

	char m_bfmePad0[0x340];
	char m_bfmeItem0;				// +0x340
	char m_bfmePad1[0xB];
	BfmeSubAccept_00002DEC m_bfmeSub1;		// +0x34C
	char m_bfmePad2[0x9F];
	char m_bfmeItem2;				// +0x3EC
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x3F0
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x3F4
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x3F8
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x3FC
	char m_bfmePad7[0x63];
	char m_bfmeItem7;				// +0x460
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x464
	char m_bfmePad9[0x3];
	char m_bfmeItem9;				// +0x468
	char m_bfmePad10[0x3];
	char m_bfmeItem10;				// +0x46C
	char m_bfmePad11[0x3];
	char m_bfmeItem11;				// +0x470
	char m_bfmePad12[0x3];
	char m_bfmeItem12;				// +0x474
	char m_bfmePad13[0x3];
	char m_bfmeItem13;				// +0x478
	char m_bfmePad14[0x3];
	char m_bfmeItem14;				// +0x47C
	char m_bfmePad15[0xB];
	char m_bfmeItem15;				// +0x488
	char m_bfmePad16[0x3];
	char m_bfmeItem16;				// +0x48C
	char m_bfmePad17[0x3];
	char m_bfmeItem17;				// +0x490
	char m_bfmePad18[0x3];
	char m_bfmeItem18;				// +0x494
	char m_bfmePad19[0x3];
	char m_bfmeItem19;				// +0x498
	char m_bfmePad20[0xB];
	char m_bfmeItem20;				// +0x4A4
	char m_bfmePad21[0xB];
	char m_bfmeItem21;				// +0x4B0
};

class Gen_002D4710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000183FE

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_005BAC70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x7];
	char m_bfmeItem2;				// +0x10
	char m_bfmePad3[0x1];
	char m_bfmeItem3;				// +0x12
	char m_bfmePad4[0x1];
	char m_bfmeItem4;				// +0x14
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x18
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x1C
	char m_bfmePad7[0xF];
	char m_bfmeItem7;				// +0x2C
};

// ?bfmeSeed@Gen_000C7C40@@QAEXPAVBfmeSeedTarget@@@Z		106 bytes
void Gen_000C7C40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 3;

	target->bfmeSeed(&version);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt78(&m_bfmeItem2);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt78(&m_bfmeItem3);
	}
	if ( version.m_bfmeVersion >= 3 )
	{
		target->bfmeTakeAt78(&m_bfmeItem4);
	}
}

// ?bfmeSeed@Gen_0016BA30@@QAEXPAVBfmeSeedTarget@@@Z		120 bytes
void Gen_0016BA30::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 3;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( !target->bfmeAskAt10() )
	{
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
		if ( version.m_bfmeVersion >= 2 )
		{
			target->bfmeTakeAt8C(&m_bfmeItem2);
		}
		if ( version.m_bfmeVersion >= 3 )
		{
			target->bfmeTakeAt8C(&m_bfmeItem3);
		}
	}
}

// ?bfmeSeed@Gen_0016C120@@QAEXPAVBfmeSeedTarget@@@Z		113 bytes
void Gen_0016C120::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( !target->bfmeAskAt10() )
	{
		target->bfmeTakeAt78(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
		if ( version.m_bfmeVersion >= 2 )
		{
			target->bfmeTakeAt78(&m_bfmeItem3);
		}
	}
}

// ?bfmeSeed@Gen_0016C350@@QAEXPAVBfmeSeedTarget@@@Z		147 bytes
void Gen_0016C350::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( !target->bfmeAskAt10() )
	{
		target->bfmeTakeAt74(&m_bfmeItem3);
		target->bfmeTakeAt78(&m_bfmeItem4);
		target->bfmeTakeAt30(m_bfmeHeld2);
		target->bfmeTakeAt60(&m_bfmeItem5);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem6);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		if ( version.m_bfmeVersion >= 2 )
		{
			bfmeHandOver_00004B79(target, &m_bfmeItem1);
		}
	}
}

// ?bfmeSeed@Gen_001F7FE0@@QAEXPAVBfmeSeedTarget@@@Z		77 bytes
void Gen_001F7FE0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	target->bfmeTakeAt8C(&m_bfmeItem0);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt74(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00201B00@@QAEXPAVBfmeSeedTarget@@@Z		84 bytes
void Gen_00201B00::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 3;

	target->bfmeSeed(&version);
	if ( version.m_bfmeVersion >= 2 )
	{
		bfmeAccept(target);

	}
	if ( version.m_bfmeVersion >= 3 )
	{
		target->bfmeTakeAt6C(&m_bfmeItem1);
	}
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0020D2B0@@QAEXPAVBfmeSeedTarget@@@Z		66 bytes
void Gen_0020D2B0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	if ( version.m_bfmeVersion >= 2 )
	{
		bfmeAccept(target);

	}
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00212FC0@@QAEXPAVBfmeSeedTarget@@@Z		64 bytes
void Gen_00212FC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( version.m_bfmeVersion >= 2 )
	{
		m_bfmeSub0.bfmeAccept(target);
	}
}

// ?bfmeSeed@Gen_00217810@@QAEXPAVBfmeSeedTarget@@@Z		66 bytes
void Gen_00217810::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt8C(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00248BE0@@QAEXPAVBfmeSeedTarget@@@Z		66 bytes
void Gen_00248BE0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt74(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00250A80@@QAEXPAVBfmeSeedTarget@@@Z		45 bytes
void Gen_00250A80::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

}

// ?bfmeSeed@Gen_00281CD0@@QAEXPAVBfmeSeedTarget@@@Z		91 bytes
void Gen_00281CD0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	target->bfmeTakeAt74(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt8C(&m_bfmeItem2);
	}
}

// ?bfmeSeed@Gen_002B5250@@QAEXPAVBfmeSeedTarget@@@Z		240 bytes
void Gen_002B5250::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeAskAt10() )
	{
		BfmeVersionBlock version;

		version.m_bfmeKind = 1;
		version.m_bfmeVersion = 1;

		target->bfmeSeed(&version);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt74(&m_bfmeItem3);
		bfmeHandOver_00020879(target, &m_bfmeItem2);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem4);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem5);
		target->bfmeTakeAt60(&m_bfmeItem6);
		target->bfmeTakeAt8C(&m_bfmeItem7);
		target->bfmeTakeAt8C(&m_bfmeItem8);
		target->bfmeTakeAt8C(&m_bfmeItem9);
		target->bfmeTakeAt8C(&m_bfmeItem10);
		target->bfmeTakeAt8C(&m_bfmeItem11);
		m_bfmeSub0.bfmeAccept(target);
	}
}

// ?bfmeSeed@Gen_002BEC60@@QAEXPAVBfmeSeedTarget@@@Z		69 bytes
void Gen_002BEC60::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt78(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_002C1740@@QAEXPAVBfmeSeedTarget@@@Z		394 bytes
void Gen_002C1740::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeAccept(target);

	if ( !target->bfmeAskAt10() )
	{
		m_bfmeSub1.bfmeAccept(target);
		target->bfmeTakeAt60(&m_bfmeItem0);
		bfmeHandOver_0000FFE2(target, &m_bfmeItem2);
		target->bfmeTakeAt78(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem5);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem6);
		target->bfmeTakeAt24(&m_bfmeItem7, 4);
		target->bfmeTakeAt6C(&m_bfmeItem9);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem16);
		target->bfmeTakeAt8C(&m_bfmeItem17);
		target->bfmeTakeAt24(&m_bfmeItem18, 4);
		target->bfmeTakeAt8C(&m_bfmeItem10);
		target->bfmeTakeAt8C(&m_bfmeItem15);
		target->bfmeTakeAt60(&m_bfmeItem14);
		target->bfmeTakeAt6C(&m_bfmeItem8);
		target->bfmeTakeAt6C(&m_bfmeItem11);
		target->bfmeTakeAt6C(&m_bfmeItem12);
		target->bfmeTakeAt6C(&m_bfmeItem13);
		if ( version.m_bfmeVersion >= 2 )
		{
			target->bfmeTakeAt60(&m_bfmeItem19);
			target->bfmeTakeAt60(&m_bfmeItem20);
			target->bfmeTakeAt8C(&m_bfmeItem21);
		}
	}
}

// ?bfmeSeed@Gen_002D4710@@QAEXPAVBfmeSeedTarget@@@Z		66 bytes
void Gen_002D4710::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt8C(&m_bfmeItem0);
	}
	bfmeAccept(target);

}

// ?bfmeSeed@Gen_005BAC70@@QAEXPAVBfmeSeedTarget@@@Z		135 bytes
void Gen_005BAC70::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	target->bfmeTakeAt7C(&m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
	target->bfmeTakeAt84(&m_bfmeItem2);
	target->bfmeTakeAt7C(&m_bfmeItem3);
	target->bfmeTakeAt7C(&m_bfmeItem4);
	target->bfmeTakeAt74(&m_bfmeItem5);
	target->bfmeTakeAt6C(&m_bfmeItem6);
	if ( version.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt4C(&m_bfmeItem7);
	}
}

// ?bfmeAccept@BfmeSubAccept_00002DEC@@QAEXPAVBfmeSeedTarget@@@Z
// Retail 0x00187860 (805 bytes).  The caller-backed +0x340 sub-object owns a
// Coord3D vector and the two string/path hand-off records below.  The view is
// deliberately separate from BfmeSubAccept_00002DEC so the already matched
// parent seed classes retain their one-byte embedded-subobject layout.
void BfmeSubAccept_00002DEC::bfmeAccept(BfmeSeedTarget *target)
{
	BfmeVersionBlock version;
	Rva00187860View *self = (Rva00187860View *)this;
	int count;
	Rva00187860Stl::vector<Rva00187860Coord3D,
		Rva00187860Stl::allocator<Rva00187860Coord3D> > *points;
	Rva00187860Coord3D point;
	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 1;
	target->bfmeSeed(&version);

	bfmeHandOver_00043301(target, (void *)self);
	bfmeHandOver_00004B79(target, (char *)self + 4);
	target->bfmeTakeAt60((char *)self + 8);
	bfmeHandOver_0000C9B4(target, (char *)self + 0x14);
	bfmeHandOver_0000C9B4(target, (char *)self + 0x18);
	target->bfmeTakeAt68((char *)self + 0x1c);
	target->bfmeTakeAt68((char *)self + 0x20);

	count = self->m_points.size();
	points = &self->m_points;
	target->bfmeTakeAt78(&count);
	if (target->bfmeSlot1())
	{
		Rva00187860Stl::__false_type tag;
		for (int i = 0; i < count; ++i)
		{
			target->bfmeTakeAt60(&point);
			points->append(point, tag);
		}
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			point.set(&(*points)[i]);
			target->bfmeTakeAt60(&point);
		}
	}

	int value = 0x7fffffff;
	if (self->m_roadRecord != 0)
	{
		value = self->m_roadRecord->m_value;
		target->bfmeTakeAt74(&value);
	}
	if (target->bfmeSlot1() && value != 0x7fffffff)
	{
		self->m_roadRecord = TheTerrainLogic->getValue(value);
	}

	Rva00187860AsciiString firstName;
	if (self->m_nameRecord != 0)
	{
		firstName.set(self->m_nameRecord->m_name);
	}
	target->bfmeTakeAt68(&firstName);
	if (target->bfmeSlot1() && firstName.hasText())
	{
		Rva00187860AsciiString savedName(firstName);
		self->m_nameRecord = (Rva00187860NameRecord *)
			TheTerrainLogic->setName(savedName);
	}

	target->bfmeTakeAt78(&self->m_pointOwner);
	self->m_embedded->accept(target);

	Rva00187860AsciiString commandName;
	if (self->m_commandRecord != 0)
	{
		commandName.set(self->m_commandRecord->m_name);
	}
	target->bfmeTakeAt68(&commandName);
	if (commandName.hasText() && self->m_commandRecord == 0)
	{
		self->m_commandRecord = (Rva00187860CommandRecord *)
			TheControlBar->findCommandButton(commandName);
	}

	bool pathReady = self->m_path != 0;
	target->bfmeTakeAt8C(&pathReady);
	if (pathReady && self->m_path == 0)
		self->m_path = new Rva00187860Path;
	if (pathReady)
		Rva00187860PathAccept(self->m_path, target);
}
