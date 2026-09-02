// cl: /DNDEBUG /MD /EHsc

#include <new>

class BfmeShadowBufferOwnerBase
{
public:
	virtual ~BfmeShadowBufferOwnerBase() {}
};

class BfmeShadowRefCount
{
public:
	virtual void Delete_This();
	int m_refCount;

	void Release_Ref()
	{
		if (--m_refCount == 0)
			Delete_This();
	}
};

struct BfmeShadowBufferEntry
{
	BfmeShadowRefCount *resource;
	void *allocation0;
	void *allocation1;
	void *allocation2;
	unsigned int unreconstructed10;
	unsigned int unreconstructed14;
};

class BfmeVolumetricShadowBufferOwner : public BfmeShadowBufferOwnerBase
{
	unsigned char m_unreconstructed_004[ 0x64 ];
	BfmeVolumetricShadowBufferOwner **m_prevLink;
	BfmeVolumetricShadowBufferOwner *m_next;
	unsigned int m_unreconstructed_070;
	BfmeShadowRefCount *m_resource;
	int m_entryCount;
	BfmeShadowBufferEntry *m_entries;

public:
	virtual ~BfmeVolumetricShadowBufferOwner();
};

BfmeVolumetricShadowBufferOwner::~BfmeVolumetricShadowBufferOwner()
{
	if (m_next != 0)
		m_next->m_prevLink = m_prevLink;
	*m_prevLink = m_next;

	if (m_resource != 0)
		m_resource->Release_Ref();

	for (int i = 0; i < m_entryCount; ++i)
	{
		m_entries[i].resource->Release_Ref();
		::operator delete(m_entries[i].allocation0);
		::operator delete(m_entries[i].allocation1);
		::operator delete(m_entries[i].allocation2);
	}

	::operator delete(m_entries);
}
