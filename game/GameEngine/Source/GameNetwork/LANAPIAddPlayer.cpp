// cl: /DNDEBUG /MD /EHsc
// Sorted lobby insertion at RVA 0x00686FD0, anchored by RequestSetName.
// Names are one-pointer StringBase views with a 16-bit header length at +4.
// The head comparison stays out of line; the loop contains the same operation.

typedef unsigned short WideChar;

struct Rva0009ECA0NoCaseTraits
{
	int compareNoCaseRaw(const WideChar *left, const WideChar *right,
		int length) const throw();
};

template <typename T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const throw();

	// Same source-level operation as the matched wide StringBase compare,
	// exposed only to reproduce the loop's inlined body in this TU.
	int compareNoCaseInline(const StringBase<T> &other) const throw()
	{
		const int otherLength = other.m_data ? other.m_data->m_length : 0;
		const WideChar *otherData = other.m_data
			? &other.m_data->m_text[0] : (const WideChar *)L"";
		const int myLength = m_data ? m_data->m_length : 0;
		const WideChar *myData = m_data
			? &m_data->m_text[0] : (const WideChar *)L"";
		const int length = myLength < otherLength ? myLength : otherLength;
		Rva0009ECA0NoCaseTraits traits;
		int result = traits.compareNoCaseRaw(myData, otherData, length);
		if (result == 0)
			result = myLength - otherLength;
		return result;
	}

private:
	struct Header
	{
		int m_refs;
		unsigned short m_length;
		unsigned short m_unobserved06;
		T m_text[1];
	};
	Header *m_data;
};

class UnicodeString : public StringBase<WideChar>
{
};

class LANPlayer
{
public:
	const UnicodeString &getName() const { return m_name; }
	LANPlayer *getNext() const { return m_next; }
	void setNext(LANPlayer *next) { m_next = next; }

private:
	UnicodeString m_name;
	char m_padding04[0x0C];
	LANPlayer *m_next;
	unsigned char m_addressBytes[8];
};

class LANAPI
{
protected:
	void addPlayer(LANPlayer *player);

private:
	char m_padding00[8];
	LANPlayer *m_lobbyPlayers;
};

void LANAPI::addPlayer(LANPlayer *player)
{
	if (!m_lobbyPlayers)
	{
		m_lobbyPlayers = player;
		player->setNext(0);
		return;
	}

	if (player->getName().compareNoCase(m_lobbyPlayers->getName()) < 0)
	{
		player->setNext(m_lobbyPlayers);
		m_lobbyPlayers = player;
		return;
	}

	LANPlayer *current = m_lobbyPlayers;
	while (current->getNext()
		&& current->getNext()->getName().compareNoCaseInline(player->getName()) > 0)
	{
		current = current->getNext();
	}

	player->setNext(current->getNext());
	current->setNext(player);
}
