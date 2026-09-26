// ?d_003c2fc0@@YAXXZ
// partial score=0.35 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// LivingWorldLogic constructor, retail 0x003C2FC0, 394 bytes.
// TheLivingWorldLogic is initSubsystem<LivingWorldLogic>-registered
// (reverse/functions.csv 0x00074810). The class installs a second vtable at
// this+0x08 (0x010EDBC8, temporarily 0x01073744 while SubsystemInterface's
// own base ctor runs); slot 2 of that second table is the landed literal
// name getter at 0x003C31B0, whose own note already says it returns
// "LivingWorldLogic". No override of that interface is needed to land this
// constructor, so the second vtable is stored as a plain field, the same
// raw-vptr technique Rva003C8880Ctor.cpp uses for its own vtable value.
// The sized-list constructor this body calls at 0x003C15C0 is already
// landed and its own note names this address as "the neutral physical
// owner" that "loads this+0xC0", which is exactly where m_regionListStorage
// sits below. m_regionManager at +0x28 is the same field
// LivingWorldLogic::setMissionObjectiveVisible (0x003C29D0, already landed)
// reads; its constructor is already landed address-derived at 0x003C8880.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void loadIniFilesFromLegend() {}
	virtual void postProcessLoad() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}

private:
	AsciiString m_name;
};

// Minimal re-declaration of the already-landed sized-list constructor's
// element type (Rva003C15C0LivingWorldListCtor.cpp); only the size (12
// bytes: a wide-string handle plus two ints) matters for this call site.
class UnicodeStringHandle
{
public:
	UnicodeStringHandle() : m_text( 0 ) {}

private:
	void *m_text;
};

struct Rva003C15C0Element
{
	UnicodeStringHandle m_text;
	int m_word4;
	int m_word8;
};

typedef _STL::list<Rva003C15C0Element> Rva003C15C0List;

// Region-manager constructor, already landed address-derived at 0x003C8880.
class Rva003C8880
{
public:
	Rva003C8880();
};

class LivingWorldLogic : public SubsystemInterface
{
public:
	LivingWorldLogic();

	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	void *volatile m_secondVtable;				// +0x08, second vtable slot (see header comment)
	UnsignedInt m_unk0c;
	UnsignedInt m_unk10;
	UnsignedInt m_unk14;
	UnsignedInt m_unk18;
	unsigned char m_unk1c;
	unsigned char m_pad1d[ 3 ];
	UnsignedInt m_unk20;
	UnsignedInt m_unk24;
	Rva003C8880 *m_regionManager;				// +0x28
	unsigned char m_unk2c;
	unsigned char m_unk2d;
	unsigned char m_pad2e[ 2 ];
	UnsignedInt m_currentRegionNamePtr;			// +0x30, AsciiString m_currentRegionName's data pointer
	UnsignedInt m_unk34;
	UnsignedInt m_unk38;
	UnsignedInt m_unk3c;
	UnsignedInt m_unk40;
	unsigned char m_unk44;
	unsigned char m_unk45;
	unsigned char m_pad46[ 2 ];
	UnsignedInt m_unk48;
	unsigned char m_unk4c;
	unsigned char m_unk4d;
	unsigned char m_unk4e;
	unsigned char m_pad4f;
	UnsignedInt m_unk50;
	UnsignedInt m_unk54;
	UnsignedInt m_unk58;
	UnsignedInt m_unk5c;
	UnsignedInt m_unk60;
	UnsignedInt m_unk64;
	UnsignedInt m_unk68;
	UnsignedInt m_unk6c;
	UnsignedInt m_unk70;
	UnsignedInt m_unk74;
	unsigned char m_unk78;
	unsigned char m_pad79[ 3 ];
	UnsignedInt m_unk7c;
	unsigned char m_unk80;
	unsigned char m_pad81[ 3 ];
	UnsignedInt m_unk84;
	UnsignedInt m_unk88;
	UnsignedInt m_unk8c;
	UnsignedInt m_unk90;
	UnsignedInt m_unk94;
	UnsignedInt m_unk98;
	UnsignedInt m_unk9c;
	UnsignedInt m_unka0;
	UnsignedInt m_unka4;
	UnsignedInt m_unka8;
	UnsignedInt m_unkac;
	UnsignedInt m_unkb0;
	UnsignedInt m_unkb4;
	UnsignedInt m_unkb8;
	UnsignedInt m_unkbc;
	unsigned char m_regionListStorage[ 4 ];		// +0xc0, placement-new'd below
	UnsignedInt m_unkc4;
	unsigned char m_unkc8;
	unsigned char m_padc9[ 3 ];
	UnsignedInt m_unkcc;
	UnsignedInt m_unkd0;
	UnsignedInt m_unkd4;
	UnsignedInt m_unkd8;
};

// ??0LivingWorldLogic@@QAE@XZ
LivingWorldLogic::LivingWorldLogic()
	: SubsystemInterface()
{
	m_secondVtable = (void *)0x01073744;

	m_unk0c = 0;
	m_unk10 = 0;
	m_unk14 = 0;
	m_unk18 = 0;
	m_unk1c = 0;
	m_unk20 = 0;
	m_unk24 = 0;

	m_secondVtable = (void *)0x010EDBC8;

	m_unk2c = 0;
	m_unk2d = 1;
	m_currentRegionNamePtr = 0;
	m_unk34 = 0;
	m_unk38 = 0;
	m_unk3c = 0;
	m_unk40 = 0;
	m_unk44 = 0;
	m_unk45 = 0;
	m_unk48 = 0;
	m_unk4c = 0;
	m_unk4d = 0;
	m_unk4e = 0;
	m_unk50 = 0;
	m_unk54 = 0;
	m_unk58 = 0;
	m_unk5c = 0;
	m_unk60 = 0;
	m_unk64 = 0;
	m_unk68 = 0;
	m_unk6c = 0;
	m_unk70 = 0;
	m_unk74 = 1;
	m_unk78 = 0;
	m_unk7c = 0;
	m_unk80 = 0;
	m_unk84 = 0;
	m_unk88 = 0;
	m_unk8c = 0;
	m_unk90 = 1;
	m_unk94 = 0;
	m_unk98 = 0;
	m_unk9c = 0;
	m_unka0 = 1;
	m_unka4 = 0;
	m_unka8 = 0;
	m_unkac = 0;
	m_unkb0 = 0;
	m_unkb4 = 0;
	m_unkb8 = 0;
	m_unkbc = 0;

	new ( m_regionListStorage ) Rva003C15C0List( 0 );

	m_unkc4 = 0;
	m_unkc8 = 0;
	m_unkcc = 0;
	m_unkd0 = 0;
	m_unkd4 = 0;
	m_unkd8 = 0;

	m_regionManager = new Rva003C8880();
}
