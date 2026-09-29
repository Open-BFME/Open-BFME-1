// ??1PlayerTemplate@@QAE@XZ
// partial score=0.7792 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// This source uses STLport interfaces and pinned BFME headers.
// stlport
// 701 of 702 bytes; probe reports shape 1.000 and all 31 EH state stores match.
// The whole residue is one register swap in the FIRST vector destructor (+0x1C7):
// retail holds _M_start in EAX and the byte count in ECX (a 6-byte
// `81 f9 80 00 00 00`), VC7.1 here holds them in ECX and EAX (5-byte
// `3d 80 00 00 00`), which also makes the body 1 byte short. The SECOND vector
// destructor matches retail exactly.
// 2026-09-28 (opencode/space-bunny-free) NEW EVIDENCE, and the reason the block
// below is now the real container instead of a hand-rolled class:
//  * Common/STLTypedefs.h (pulled in by Common/INI.h) defines _STLP_USE_NEWALLOC,
//    so in a default TU `std::vector<int>` deallocates with a bare
//    `::operator delete` and VC7.1 FOLDS retail's `cmp bytes,0x80` away: the
//    vector cleanup collapses to `if (start) operator delete(start)` (measured:
//    663 B for one member, 625 B for two). Retail's body needs the other arm,
//    so the node allocator is mandatory here.
//  * inputs/reference/shims/stlp_nodealloc/Common/STLTypedefs.h is the repo's
//    shim for exactly this (guarded by BFME_STLP_NODE_ALLOC); the cl: line below
//    is the flag set already matched at
//    game/GameEngine/Source/Common/Bfme5UnwoundDestructors.cpp.
//  * With that configuration the members are declared `_STL::vector<int>` and the
//    emitted code is byte-identical to the hand-rolled class (701 B, 153 non-reloc
//    diffs, first at +0x1C8, shape 1.000) while the two `__node_alloc` call sites
//    now carry retail's own symbol
//    `?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z` directly, so the
//    Rva00082E5F0NodeAllocator shim and its /alternatename pragma are gone.
//    The `sar ecx,2 / shl ecx,2` pair is STLport's own
//    `allocator<T>::deallocate` (`__n * sizeof(value_type)`), not a hand spelling.
//  * The residue is therefore NOT a source-shape problem: the genuine container
//    spelling reproduces it. Ruled out again, all byte-identical at 701 B with
//    start in ECX: two distinct element types; an explicit `allocator<int>`
//    template argument; `_STL::vector` at one site and the modelled class at the
//    other, in both directions; a `_STLP_alloc_proxy` deriving from a node
//    allocator; the destructor split into a base class; a nested `{ }`; a
//    `do{}while(0)`; `size_t` counts; direct member use instead of locals; an
//    out-of-line forceinline `destroy()`; a member subobject struct; /O1 /Os /Ot
//    /Ob0 /Ob1 /Ob2 /G4 /G5 /G6 /G7 /Fr /Gs /Gy on the cl: line (all 701 B, and
//    /G7 makes it 703 B).
//  * Retail really does alternate these two sites: only 9 sites in the whole image
//    load _M_start into EAX (0x0E297C, 0x147109, 0x1DAFD9, 0x2660C7, 0x2CC122,
//    0x2CC4D9, 0x3495F3, 0x52A7AD, 0x64638A) and only 0x3492A0 contains both an
//    EAX-start and an ECX-start cleanup, in the opposite order to this body.
//  * blocker=regalloc. The honest next lever is a differently-patched VC7.1 or an
//    inline-asm move, not another C++ spelling.
// NOTE: keep `// cl:` and `// stlport` inside the first 2048 bytes of this file;
// tools/crosslink.py only scans that window, and dropping the cl: line silently
// rebuilds this TU with the wrong allocator and a 25-byte-shorter body.
// NOTE: with the long cl: line the markers must not be pushed past 2048 bytes by
// header prose; putting the markers first (as here) is what makes the node-alloc
// configuration compile at all.
// The constructors and INI name table establish the 0x124-byte PlayerTemplate
// layout. The destructor releases both vectors and every string member.
#include "Common/INI.h"
#define ANIM2D_INLINE_SNAPSHOT_DTOR
#include "Common/Money.h"
#include "Common/NameKeyGenerator.h"
#include <vector>

template <class CharT> class Rva000E27A0StringBase
{
public:
	~Rva000E27A0StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	CharT *m_data;
};

class Rva000E27A0StringView
{
public:
	~Rva000E27A0StringView() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

#pragma comment(linker, "/alternatename:?releaseBuffer@?$Rva000E27A0StringBase@G@@AAEXXZ=?releaseBuffer@?$StringBase@G@@AAEXXZ")
#pragma comment(linker, "/alternatename:?releaseBuffer@Rva000E27A0StringView@@AAEXXZ=?releaseBuffer@Rva000E27A0StringView@@AAEXXZ")

struct Rva000E27A0ColorStorage
{
	float red;
	float green;
	float blue;
};

class Rva000E27A0Object060
{
public:
	~Rva000E27A0Object060();
	char m_data[0x0c];
};

class Rva000E27A0Object06C
{
public:
	~Rva000E27A0Object06C();
	char m_data[0x14];
};

class Rva000E27A0Object080
{
public:
	~Rva000E27A0Object080();
	char m_data[0x0c];
};

class Rva000E27A0Object0E8
{
public:
	~Rva000E27A0Object0E8();
	char m_data[0x0c];
};



#pragma comment(linker, "/alternatename:??1Rva000E27A0Object060@@QAE@XZ=?j_000032b5@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva000E27A0Object06C@@QAE@XZ=?j_00032227@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva000E27A0Object080@@QAE@XZ=?j_0002ac20@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva000E27A0Object0E8@@QAE@XZ=?j_00026ab2@@YAXXZ")

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *value);

class Rva000E27A0SoundRef
{
public:
	virtual ~Rva000E27A0SoundRef();
	void releaseAtRva000E27A0()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}
	volatile long m_refCount;
};

class Rva000E27A0SoundSlot
{
public:
	~Rva000E27A0SoundSlot()
	{
		if (m_object != 0)
			m_object->releaseAtRva000E27A0();
	}

	Rva000E27A0SoundRef *m_object;
};

class PlayerTemplate
{
public:
	~PlayerTemplate();

private:
	NameKeyType m_at_000;                         // +0x000
	Rva000E27A0StringBase<unsigned short> m_at_004;  // +0x004
	Rva000E27A0StringView m_at_008;                  // +0x008
	char m_at_00c[0x10];                         // +0x00c
	Money m_at_01c;                                 // +0x01c
	Rva000E27A0ColorStorage m_at_028;                 // +0x028
	Rva000E27A0StringView m_at_034;      // +0x034
	Rva000E27A0StringView m_at_038[10];     // +0x038
	Rva000E27A0Object060 m_at_060;             // +0x060
	Rva000E27A0Object06C m_at_06c;             // +0x06c
	Rva000E27A0Object080 m_at_080;         // +0x080
	_STL::vector<int> m_intrinsicSciences;         // +0x08c
	_STL::vector<int> m_at_098;       // +0x098
	Rva000E27A0StringView m_at_0a4;       // +0x0a4
	Rva000E27A0StringView m_at_0a8;     // +0x0a8
	Rva000E27A0StringView m_at_0ac;  // +0x0ac
	Rva000E27A0StringView m_at_0b0;     // +0x0b0
	int m_at_0b4;         // +0x0b4
	Rva000E27A0StringView m_at_0b8;       // +0x0b8
	bool m_at_0bc;                               // +0x0bc
	bool m_at_0bd;                           // +0x0bd
	char m_at_0be[2];
	int m_at_0c0;                            // +0x0c0
	int m_at_0c4;                              // +0x0c4
	int m_at_0c8;                              // +0x0c8
	Rva000E27A0StringView m_at_0cc;      // +0x0cc
	Rva000E27A0StringView m_at_0d0;       // +0x0d0
	Rva000E27A0StringView m_at_0d4;          // +0x0d4
	Rva000E27A0StringView m_at_0d8;          // +0x0d8
	Rva000E27A0StringView m_at_0dc;           // +0x0dc
	Rva000E27A0StringView m_at_0e0;          // +0x0e0
	Rva000E27A0StringView m_at_0e4;         // +0x0e4
	Rva000E27A0Object0E8 m_at_0e8;                   // +0x0e8
	Rva000E27A0Object0E8 m_at_0f4;                 // +0x0f4
	Rva000E27A0SoundSlot m_at_100;           // +0x100
	Rva000E27A0SoundSlot m_at_104;          // +0x104
	Rva000E27A0SoundSlot m_at_108;      // +0x108
	Rva000E27A0StringView m_at_10c;   // +0x10c
	Rva000E27A0StringView m_at_110;             // +0x110
	Rva000E27A0StringView m_at_114;           // +0x114
	bool m_at_118;                                   // +0x118
	char m_at_119[3];
	Rva000E27A0StringView m_at_11c;     // +0x11c
	Rva000E27A0StringView m_at_120;     // +0x120
};

// ??1PlayerTemplate@@QAE@XZ present-unmatched
PlayerTemplate::~PlayerTemplate()
{
}
