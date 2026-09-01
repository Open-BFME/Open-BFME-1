// ?addPlayer@LANAPI@@IAEXPAVLANPlayer@@@Z
// partial score=0.82 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

extern "C" int __cdecl _wcsnicmp(const unsigned short *, const unsigned short *, unsigned int);

class UnicodeString
{
public:
	int compareNoCase(const UnicodeString &other) const;
	int compareNoCaseInline(const UnicodeString &other) const
	{
		const unsigned short *left = m_data ? m_data->m_text : (const unsigned short *)L"";
		const unsigned short *right = other.m_data ? other.m_data->m_text : (const unsigned short *)L"";
		int leftLength = m_data ? m_data->m_length : 0;
		int rightLength = other.m_data ? other.m_data->m_length : 0;
		int length = leftLength < rightLength ? leftLength : rightLength;
		int result = _wcsnicmp(left, right, length);
		return result ? result : leftLength - rightLength;
	}

private:
	struct Data
	{
		int m_refs;
		unsigned short m_length;
		unsigned short m_capacity;
		unsigned short m_text[1];
	};

	Data *m_data;
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
	if (!m_lobbyPlayers) {
		m_lobbyPlayers = player;
		player->setNext(0);
		return;
	}

	if (player->getName().compareNoCase(m_lobbyPlayers->getName()) < 0) {
		player->setNext(m_lobbyPlayers);
		m_lobbyPlayers = player;
		return;
	}

	LANPlayer *current = m_lobbyPlayers;
	while (current->getNext()
		&& current->getNext()->getName().compareNoCaseInline(player->getName()) > 0) {
		current = current->getNext();
	}

	player->setNext(current->getNext());
	current->setNext(player);
}
