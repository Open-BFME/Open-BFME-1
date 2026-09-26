// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC

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

#pragma comment(linker, "/alternatename:?bfmeRelease@Gen_003CFC90@@QAEXXZ=?j_0004a5a7@@YAXXZ")

class Rva004948B0Base
{
public:
	virtual ~Rva004948B0Base();
	virtual void bfmeSubsystemSlot();

private:
	void *m_name;
};

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

class Gen_003CFC90
{
public:
	void bfmeRelease();
};

class LargeGroupAudio : public Rva004948B0Base,
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
	( (Gen_003CFC90 *)this )->bfmeRelease();

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
