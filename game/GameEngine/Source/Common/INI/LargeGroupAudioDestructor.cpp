// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib

// The first base of this dtor's owner is SubsystemInterface: its destructor
// body is the 14 bytes at 0x009A1A40 that ??1SubsystemInterface@@UAE@XZ owns.
// SubsystemInterface is vptr + m_name, eight bytes, which is what leaves the
// second base's vptr at +0x08 and the first vector at +0x0C.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "PreRTS.h"

#include "subsystem_interface.h"

namespace _STL
{

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *memory, unsigned int bytes );
};

}

void __cdecl operator delete( void *memory );
void Gen0082E5F0( void *memory, unsigned int bytes );

// The dtor's first base release call goes through retail's ILT thunk at
// 0x0004A5A7, so it is referenced by address, not by a spelled-out member.
extern void j_0004a5a7();

class HordeContainModuleDataBase
{
public:
	virtual ~HordeContainModuleDataBase() {}
	virtual void bfmeSlot0();
};

class GenLargeGroupAudioElement
{
public:
	virtual ~GenLargeGroupAudioElement();
};

class AudioVector
{
public:
	~AudioVector()
	{
		if ( m_begin )
		{
			unsigned int bytes = (unsigned int)( m_capacity - m_begin ) * sizeof( void * );
			if ( bytes > 128 )
				::operator delete( m_begin );
			else
				Gen0082E5F0( m_begin, bytes );
		}
	}

	void **m_begin;
	void **m_end;
	void **m_capacity;
};

// Cast target for the ILT-routed release call below; the member signature is
// the one retail resolved at the thunk, so it is expressed as a member
// function pointer type rather than a named member.
class Gen_003CFC90
{
};

class LargeGroupAudio : public SubsystemInterface,
	public HordeContainModuleDataBase
{
public:
	virtual ~LargeGroupAudio();

	AudioVector m_0C;
	AudioVector m_18;
	AudioVector m_24;
	GenLargeGroupAudioElement *m_unusedKnownKeys;
};

// ??1LargeGroupAudio@@UAE@XZ
LargeGroupAudio::~LargeGroupAudio()
{
	typedef void (Gen_003CFC90::*Fn)();
	union { void (*fn)(); Fn call; } u = { j_0004a5a7 };
	( ( (Gen_003CFC90 *)this )->*u.call )();

	void **it = m_18.m_begin;
	void **end = m_18.m_end;
	while ( it != end )
	{
		delete (GenLargeGroupAudioElement *)*it;
		++it;
		end = m_18.m_end;
	}

	delete m_unusedKnownKeys;
}
