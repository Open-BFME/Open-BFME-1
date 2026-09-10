// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

namespace _STL
{

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};

}

extern void __cdecl operator delete(void *block);
extern void __cdecl bfmeFreeScalar(void *block);

class SoundKeyPair
{
public:
	~SoundKeyPair();
};

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

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
				_STL::__node_alloc<true, 0>::_M_deallocate(start, bytes);
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
