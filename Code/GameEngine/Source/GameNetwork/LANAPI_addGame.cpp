// cl: /DNDEBUG /MD /EHsc
// readable body of ?addGame@LANAPI@@IAEXPAVLANGameInfo@@@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// LANAPI::addGame, 0x00686DF0, 376 bytes.
//
// Named from its callers: RequestGameCreate (0x00687E90) and handleGameAnnounce
// (0x0068C110) both reach it, and addGame is the one thing the reference has
// them both call. The body confirms it -- a sorted insert into m_games at
// this+0x0C, walking m_next at +0x398 and ordering by
// LANGameInfo::getName().compareNoCase(). It is the reference's body unchanged,
// including the reference's own asymmetry: the head comparison tests < 0 and
// the walk tests > 0.
//
// compareNoCase is declared nothrow here, and that is the whole difference
// between 376 bytes and 412. Each block builds two UnicodeString temporaries
// and destroys them again; with compareNoCase able to throw, MSVC has to bump
// the unwind state after the second temporary is constructed and again after
// it is destroyed, four extra stores per block. Retail has neither, so its
// compiler knew the compare could not throw: one state covers the pair and the
// two-bit liveness mask in ebx tells the funclet which of them to destroy.
// Nothing else -- optimisation flags included -- collapses those states.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;

#define NULL 0

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	// Declared nothrow, and that is load-bearing -- see the note at the top.
	Int compareNoCase(const StringBase<T> &other) const throw();	// retail 0x0009EFE0

private:
	void releaseBuffer();					// retail 0x008881D0

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { ((StringBase<WideChar> *)this)->releaseBuffer(); }

	Int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<WideChar> *)this)->compareNoCase(*(const StringBase<WideChar> *)&other);
	}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnicodeString getName(void);				// ILT thunk 0x00041FC9

	LANGameInfo *getNext(void) { return m_next; }
	void setNext(LANGameInfo *next) { m_next = next; }

	UnsignedByte m_bfmeHead[0x398];
	LANGameInfo *m_next;					// this+0x398
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
protected:
	void addGame(LANGameInfo *game);

	UnsignedByte m_bfmeHead[0x0C];
	LANGameInfo *m_games;					// this+0x0C
};

// ?addGame@LANAPI@@IAEXPAVLANGameInfo@@@Z
void LANAPI::addGame( LANGameInfo *game )
{
	if (!m_games)
	{
		m_games = game;
		game->setNext(NULL);
		return;
	}
	else
	{
		if (game->getName().compareNoCase(m_games->getName()) < 0)
		{
			game->setNext(m_games);
			m_games = game;
			return;
		}
		else
		{
			LANGameInfo *g = m_games;
			while (g->getNext() && g->getNext()->getName().compareNoCase(game->getName()) > 0)
			{
				g = g->getNext();
			}
			game->setNext(g->getNext());
			g->setNext(game);
			return;
		}
	}
}
