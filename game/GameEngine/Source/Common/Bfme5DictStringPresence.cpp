// Tests whether the string stored under one lazily initialized key is nonempty.

class BfmeStringPresenceValue
{
public:
	~BfmeStringPresenceValue(void);
	bool isEmpty(void) const
	{
		return m_header == 0 || m_header->length == 0;
	}

private:
	struct Header
	{
		int references;
		unsigned short length;
	};

	Header *m_header;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;
};

class BfmeStringPresenceDict
{
public:
	BfmeStringPresenceValue getAsciiString(int key, bool *exists) const;
};

extern const StaticNameKey TheKey_playerName;

class BfmeStringPresenceOwner
{
public:
	bool bfmeHasString(void) const;

private:
	int m_prefix;
	BfmeStringPresenceDict m_dict;
};

// ?bfmeHasString@BfmeStringPresenceOwner@@QBE_NXZ
bool BfmeStringPresenceOwner::bfmeHasString(void) const
{
	const BfmeStringPresenceDict *dict = &m_dict;
	bool initialized;
	return dict != 0 &&
		dict->getAsciiString(TheKey_playerName.key(), &initialized).isEmpty();
}
