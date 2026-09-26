// cl: /DNDEBUG /MD /EHsc
// Retail establishes the 36-byte layout; list helper names and unknown field types remain descriptive.

template<class T> class StringBase
{
	friend class AsciiString;
private:
	StringBase(const StringBase &);
	~StringBase();
private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class FXNugget
{
public:
	virtual ~FXNugget();
};

struct FXNuggetNode
{
	FXNuggetNode *next;
	FXNuggetNode *prev;
	FXNugget *value;
};

struct Rva0042D170Member04
{
	Rva0042D170Member04(const Rva0042D170Member04 &);
	~Rva0042D170Member04();
	FXNuggetNode *head;
};

struct Rva0042D170Member18
{
	Rva0042D170Member18(const Rva0042D170Member18 &);
	~Rva0042D170Member18();
	void *m_head;
};

void __cdecl bfmeDeallocate(void *, unsigned int);

class FXList
{
public:
	FXList(const FXList &other);
	virtual ~FXList();
	void clear();
private:
	Rva0042D170Member04 m_nuggets;
	unsigned char m_field08;
	AsciiString m_string0C;
	unsigned char m_playEvenIfShrouded;
	int m_trackingFrames;
	Rva0042D170Member18 m_list18;
	int m_cullTrackingMax;
	int m_cullTrackingMin;
};

FXList::FXList(const FXList &other)
	: m_nuggets(other.m_nuggets)
	, m_field08(other.m_field08)
	, m_string0C(other.m_string0C)
	, m_playEvenIfShrouded(other.m_playEvenIfShrouded)
	, m_trackingFrames(other.m_trackingFrames)
	, m_list18(other.m_list18)
	, m_cullTrackingMax(other.m_cullTrackingMax)
	, m_cullTrackingMin(other.m_cullTrackingMin)
{
}

FXList::~FXList()
{
	clear();
}

void FXList::clear()
{
	FXNuggetNode *node = m_nuggets.head->next;
	while (node != m_nuggets.head)
	{
		delete node->value;
		node = node->next;
	}
	FXNuggetNode *walk = m_nuggets.head->next;
	while (walk != m_nuggets.head)
	{
		FXNuggetNode *current = walk;
		walk = walk->next;
		bfmeDeallocate(current, sizeof(FXNuggetNode));
	}
	m_nuggets.head->next = m_nuggets.head;
	m_nuggets.head->prev = m_nuggets.head;
}
