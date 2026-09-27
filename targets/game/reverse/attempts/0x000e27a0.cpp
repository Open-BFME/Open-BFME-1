// ??1PlayerTemplate@@QAE@XZ
// partial score=0.99 date=2026-09-27
// The probe normalizes every instruction to retail, but VC7.1 assigns the second vector pointers to opposite registers.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// This source uses STLport interfaces and pinned BFME headers.
// The constructors and INI name table establish the 0x124-byte PlayerTemplate layout.
// The destructor releases both vectors and every string member.

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

class Rva00082E5F0NodeAllocator
{
public:
	static void deallocate( void *pointer, unsigned int bytes );
};
#pragma comment(linker, "/alternatename:?deallocate@Rva00082E5F0NodeAllocator@@SAXPAXI@Z=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

class Rva000BB6C0VectorBase
{
public:
	__forceinline ~Rva000BB6C0VectorBase()
	{
		int *first = begin();
		if ( first != 0 )
		{
			unsigned int bytes = size() * sizeof( int );
			if ( bytes > 0x80 )
				::operator delete( first );
			else
				Rva00082E5F0NodeAllocator::deallocate( first, bytes );
		}
	}

private:
	__forceinline int *begin() const { return m_first; }
	__forceinline unsigned int size() const { return (unsigned int)( m_end - m_first ); }
	int *m_first;
	int *m_last;
	int *m_end;
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
	Rva000BB6C0VectorBase m_intrinsicSciences;         // +0x08c
	Rva000BB6C0VectorBase m_at_098;       // +0x098
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
