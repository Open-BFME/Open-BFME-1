// cl: /DNDEBUG /MD /EHsc
// Retail 0x0019B4C0 clears both 32-entry side arrays and their SidesInfo records.

class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	void deleteInstance()
	{
		if (this)
			delete this;
	}
};

class Dict
{
public:
	void clear();
};

class ScriptList
{
public:
	virtual ~ScriptList();
	void deleteInstance()
	{
		if (this)
			delete this;
	}
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();

private:
	void *m_data;
};

class UnicodeString : public BFMERetailAsciiString
{
public:
	void set(const UnicodeString &other);
};

static __forceinline UnicodeString *rva0019be80Copy(
	UnicodeString *first, UnicodeString *last, UnicodeString *result)
{
	int count = ((unsigned char *)last - (unsigned char *)first) >> 2;
	while (count > 0)
	{
		result->set(*first);
		++first;
		++result;
		--count;
	}
	return result;
}

class Rva0019BE80UnicodeStrings
{
public:
	UnicodeString *begin()
	{
		return m_first;
	}

	UnicodeString *end()
	{
		return m_last;
	}

	__forceinline UnicodeString *erase(UnicodeString *first, UnicodeString *last)
	{
		UnicodeString *result = rva0019be80Copy(last, m_last, first);
		UnicodeString *finish = m_last;
		for (UnicodeString *item = result; item != finish; ++item)
			reinterpret_cast<BFMERetailAsciiString *>(item)->~BFMERetailAsciiString();
		m_last = result;
		return first;
	}

	__forceinline void clear()
	{
		erase(begin(), end());
	}

private:
	UnicodeString *m_first;
	UnicodeString *m_last;
	UnicodeString *m_capacity;
};

class Rva0019BE80SideInfo
{
public:
	__forceinline void clear()
	{
		if (m_buildList)
			m_buildList->deleteInstance();
		m_buildList = 0;
		m_dict.clear();
		if (m_scripts)
			m_scripts->deleteInstance();
		m_scripts = 0;
		m_strings.clear();
	}

private:
	BuildListInfo *m_buildList;
	Dict m_dict;
	ScriptList *m_scripts;
	Rva0019BE80UnicodeStrings m_strings;
};

class Rva0019BE80SidesList
{

private:
	void clearSideStorageAt0019B4C0();
	unsigned char m_prefix[0x28];
	int m_numSides;
	Rva0019BE80SideInfo m_sides[32];
	int m_numSkirmishSides;
	Rva0019BE80SideInfo m_skirmishSides[32];
};

void Rva0019BE80SidesList::clearSideStorageAt0019B4C0()
{
	m_numSides = 0;
	m_numSkirmishSides = 0;
	for (int i = 0; i < 32; ++i)
	{
		m_sides[i].clear();
		m_skirmishSides[i].clear();
	}
}
