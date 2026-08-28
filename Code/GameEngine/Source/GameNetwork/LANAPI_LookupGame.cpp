// cl: /DNDEBUG /MD /EHsc
// readable body of ?LookupGame@LANAPI@@UAEPAVLANGameInfo@@VUnicodeString@@@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// Retail 0x00688520, LANAPI vtable slot 42 -- slot 41 is OnNameChange and slot
// 43 LookupGameByListOffset, both already ledgered, which brackets it.
//
// Its own TU with hand-rolled classes: retail's LANGameInfo carries its next
// pointer at +0x398 where the vendored Zero Hour header puts it at +0x360, and
// the name comparison is inlined -- both string internals (length word at +4,
// text at +8, "" when the handle is null) and the compare loop itself.
//
// Two shapes matter for the compare. The mismatch branch has to compute the
// difference and return it only when non-zero, falling through to the length
// difference otherwise: that is what puts retail's `jne` over the length
// subtraction there, and an early `return *a - *b` lays the block out after the
// length path instead, jumping back. And it needs __forceinline -- MSVC will not
// inline a function containing a loop on its own.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;		// MSVC 7.1 has no native WideChar here

struct BfmeUnicodeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;			// +4
	UnsignedShort m_pad;
	// WideChar text[] at +8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }
	const WideChar *str() const { return m_data ? (const WideChar *)(m_data + 1) : (const WideChar *)L""; }

	__forceinline Int compare(const UnicodeString &that) const
	{
		Int thatLen = that.getLength();
		const WideChar *thatText = that.str();
		Int thisLen = getLength();
		const WideChar *thisText = str();

		Int n = thisLen < thatLen ? thisLen : thatLen;

		while (n > 0)
		{
			if (*thisText != *thatText)
			{
				Int diff = *thisText - *thatText;
				if (diff != 0)
					return diff;

				break;
			}

			++thisText;
			++thatText;
			--n;
		}

		return thisLen - thatLen;
	}

protected:
	void releaseBuffer();			// retail 0x008881D0

	BfmeUnicodeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnicodeString getName(void);		// ILT thunk 0x00041FC9

	unsigned char m_bfmeHead[0x398];
	LANGameInfo *m_next;			// +0x398
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual LANGameInfo *LookupGame(UnicodeString gameName);

protected:
	unsigned char m_bfmeHead[0x0C - 4];	// after the vptr
	LANGameInfo *m_games;			// +0x0C
};

// ?LookupGame@LANAPI@@UAEPAVLANGameInfo@@VUnicodeString@@@Z
LANGameInfo *LANAPI::LookupGame(UnicodeString gameName)
{
	LANGameInfo *theGame = m_games;

	while (theGame && theGame->getName().compare(gameName) != 0)
	{
		theGame = theGame->m_next;
	}

	return theGame;			// NULL means we didn't find anything.
}
