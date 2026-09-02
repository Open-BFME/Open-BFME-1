// cl: /DNDEBUG /MD
// Retail 0x007B0330: release the references held by the two composed slots.

class RefCountedResource
{
public:
	virtual void deleteThis();
	int m_refCount;
};

struct ResourceSlot
{
	char m_padding[0x68];
	RefCountedResource *m_resource;
};

class Rva007B0330Owner
{
private:
	char m_padding[0x58];
	ResourceSlot *m_first;
	ResourceSlot *m_second;

public:
	void releaseResources();
};

static void releaseSlotResource( ResourceSlot *slot )
{
	RefCountedResource *resource = slot->m_resource;
	if ( resource != 0 )
	{
		if ( --resource->m_refCount == 0 )
			resource->deleteThis();
		slot->m_resource = 0;
	}
}

void Rva007B0330Owner::releaseResources()
{
	releaseSlotResource( m_first );
	releaseSlotResource( m_second );
}
