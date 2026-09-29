// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

namespace _STL
{

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

}

extern void __cdecl operator delete(void *block);
extern void __cdecl bfmeFreeScalar(void *block);

class SoundKeyPair
{
public:
	~SoundKeyPair();
};

#include "ascii_string.h"

class SoundKeyVector
{
public:
	~SoundKeyVector()
	{
		SoundKeyPair **start = m_begin;
		if (start)
		{
			unsigned int bytes = (unsigned int)(m_capacity - start) *
				sizeof(SoundKeyPair *);
			if (bytes > 0x80)
				::operator delete(start);
			else
				_STL::nodePoolDeallocate(start, bytes);
		}
	}

	SoundKeyPair **m_begin;
	SoundKeyPair **m_end;
	SoundKeyPair **m_capacity;
};

class BfmeSinkVUH
{
public:
	virtual ~BfmeSinkVUH();
};

class BfmeBaseVUH
{
public:
	virtual ~BfmeBaseVUH()
	{
		if (m_owner)
			delete m_owner;
		m_owner = 0;
	}

	BfmeSinkVUH *m_owner;
	unsigned char m_isOverride;
	unsigned char m_padding09[3];
};

class LargeGroupAudioMap : public BfmeBaseVUH
{
public:
	virtual ~LargeGroupAudioMap();

private:
	unsigned char m_padding0c[8];
	AsciiString m_soundName;
	SoundKeyVector m_sound;
};

// ??1LargeGroupAudioMap@@UAE@XZ
LargeGroupAudioMap::~LargeGroupAudioMap()
{
	SoundKeyPair **it = m_sound.m_begin;
	SoundKeyPair **end = m_sound.m_end;
	while (it != end)
	{
		SoundKeyPair *pair = *it;
		if (pair)
		{
			pair->~SoundKeyPair();
			bfmeFreeScalar(pair);
		}
		++it;
		end = m_sound.m_end;
	}
}
