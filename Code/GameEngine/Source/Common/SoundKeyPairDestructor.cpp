// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC
// stlport

#include <vector>
#include <string.h>

class LargeGroupAudioKeyMap
{
public:
	~LargeGroupAudioKeyMap();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

struct Gen003D1380Elem
{
	char m_padding[0x30];
	char m_audio[4];
	char m_tail[8];

	~Gen003D1380Elem();
};

typedef _STL::vector<Gen003D1380Elem> RetailGen003D1380Vector;

struct Gen003D1380Vector
{
	Gen003D1380Elem *m_begin;
	Gen003D1380Elem *m_end;
	Gen003D1380Elem *m_capacity;
};

static __forceinline void destroyGen003D1380Vector(Gen003D1380Vector *vector)
{
	((RetailGen003D1380Vector *)vector)->~RetailGen003D1380Vector();
}

struct SoundKeyGroup
{
	char m_padding[8];
	Gen003D1380Vector m_entries;
};

class SoundKeyVector
{
public:
	~SoundKeyVector()
	{
		if (m_begin)
		{
			unsigned int bytes =
				(unsigned int)(m_capacity - m_begin) * sizeof(void *);
			if (bytes > 128)
				::operator delete(m_begin);
			else
				_STL::__node_alloc<true, 0>::deallocate(m_begin, bytes);
		}
	}

	void **m_begin;
	void **m_end;
	void **m_capacity;
};

class SoundKeyPair
{
public:
	~SoundKeyPair();

private:
	LargeGroupAudioKeyMap m_keyMap;
	AsciiString m_headerKey;
	SoundKeyGroup *m_groups[4];
	void *m_owner;
	SoundKeyVector m_second;
	SoundKeyVector m_first;
};

// ??1SoundKeyPair@@QAE@XZ
SoundKeyPair::~SoundKeyPair()
{
	SoundKeyPair *self = this;
	SoundKeyGroup **groupSlot = self->m_groups;
	volatile int groupCount = 4;
	do
	{
		SoundKeyGroup *group = *groupSlot;
		if (group)
		{
			Gen003D1380Elem *item = group->m_entries.m_begin;
			while (item != group->m_entries.m_end)
			{
				item->~Gen003D1380Elem();
				memset(item->m_audio, 0, sizeof(item->m_audio));
				++item;
			}
		}
		++groupSlot;
	}
	while (--groupCount != 0);

	int remainingGroups = 4;
	groupSlot = self->m_groups;
	do
	{
		SoundKeyGroup *group = *groupSlot;
		if (group)
		{
			destroyGen003D1380Vector(&group->m_entries);
			::operator delete(group);
			*groupSlot = 0;
		}
		++groupSlot;
	}
	while (--remainingGroups != 0);
}
