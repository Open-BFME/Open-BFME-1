// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: MetaMap::~MetaMap (0x005B7260, 144 B). MetaMap derives from
// SubsystemInterface and keeps a singly-linked MetaMapRec list at +8 (the
// same layout MetaMap::getMetaMapRec already pins in
// MetaMap_getMetaMapRecThunk.cpp: m_next@0, m_description (UnicodeString)@0x1c,
// m_displayName (UnicodeString)@0x20). The body walks the list, releases
// each node's two wide strings, frees the node with plain operator delete,
// then chains to the base SubsystemInterface destructor.

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

	void *m_data;

private:
	void releaseBuffer();
};

class UnicodeStringField : private StringBase<unsigned short>
{
public:
	~UnicodeStringField() {}
};

struct MetaMapRec
{
	MetaMapRec *m_next;					// +0x00
	unsigned char m_gap[0x1c - 4];
	UnicodeStringField m_description;			// +0x1c
	UnicodeStringField m_displayName;			// +0x20
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class MetaMap : public SubsystemInterface
{
public:
	virtual ~MetaMap();

private:
	unsigned char m_unreconstructed04[ 8 - 4 ];
	MetaMapRec *m_metaMaps;				// +0x08
};

// ??1MetaMap@@UAE@XZ
MetaMap::~MetaMap()
{
	while ( m_metaMaps )
	{
		MetaMapRec *next = m_metaMaps->m_next;
		delete m_metaMaps;
		m_metaMaps = next;
	}
}
