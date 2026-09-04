// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x005293E0, 209 bytes.  This address-derived helper normalizes a
// seven-character map key when the incoming name lacks the retail prefix and
// tests the resulting key against the embedded STL tree.  The second
// parameter is the BFME AsciiString value passed by value; it is represented
// as its one-word string handle here so VC7.1 keeps the retail copy shape.

template <typename T> class StringBase
{
protected:
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	bool startsWith(const char *text, int length) const;

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}

	int length() const
	{
		return m_data ? *(const unsigned short *)((const char *)m_data + 4) : 0;
	}

	protected:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *data);
	AsciiString(const AsciiString &other);
	~AsciiString();

	void set(const char *text, int length);
	void concat(const char *text, int length);

};

class Rva006AEE00Tree
{
public:
	void *find(void *key);

	void *m_root;
};

class Gen005293E0Object
{
public:
	char m_prefix[8];
	Rva006AEE00Tree m_tree;
	int m_ready;
};

// ?bfmeGen005293E0@@YA_NPAVGen005293E0Object@@PAX@Z
bool bfmeGen005293E0(Gen005293E0Object *object, void *text)
{
	Rva006AEE00Tree *tree = (Rva006AEE00Tree *)((char *)object + 8);
	if (!*(int *)((char *)tree + 4))
		return true;

	AsciiString key(*(AsciiString *)text);
	StringBase<char> *textView = (StringBase<char> *)text;
	if (!textView->startsWith("Faction", 7))
	{
		key.set("Faction", 7);
		key.concat(textView->str(), textView->length());
	}

	void *root = tree->m_root;
	void *found = tree->find((void *)&key);
	return found != root;
}
