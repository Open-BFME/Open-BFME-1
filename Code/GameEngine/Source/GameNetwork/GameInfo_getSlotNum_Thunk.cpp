// cl: /DNDEBUG /MD /EHsc
// readable body of ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z: Code/GameEngine/Source/GameNetwork/GameInfo.cpp
// The local string declarations preserve BFME's by-value ABI and call names.

typedef int Int;
typedef bool Bool;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	int compareNoCase( const StringBase<T> &other ) const throw();

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void translate( const AsciiString &source );
	int compareNoCase( const UnicodeString &other ) const throw()
	{
		return StringBase<unsigned short>::compareNoCase( other );
	}
};

#pragma comment(linker, "/alternatename:?compareNoCase@?$StringBase@G@@QBEHABV1@@Z=?j_0001609f@@YAXXZ")

class GameSlot
{
public:
	virtual void reset(void) = 0;
	Bool isPlayer(UnicodeString userName) const;

protected:
	int m_state;
	unsigned char m_gap08[0x28 - 0x08];
	UnicodeString m_name;
};

__forceinline Bool GameSlot::isPlayer(UnicodeString userName) const
{
	Bool result;
	if (m_state == 5 && m_name.compareNoCase(userName) == 0)
		result = true;
	else
		result = false;

	return result;
}

class GameInfo
{
private:
	unsigned char m_pad0[0x0c];
	Bool m_inGame;
	unsigned char m_pad0d[3];
	void *m_pad10;
	GameSlot *m_slots[8];

public:
	const GameSlot *getConstSlot(Int slotNum) const
	{
		if (slotNum < 0 || slotNum >= 8)
			return 0;
		return m_slots[slotNum];
	}
	Int getSlotNum(AsciiString userName) const;
};

// ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z
Int GameInfo::getSlotNum(AsciiString userName) const
{
	if (!m_inGame)
		return -1;

	UnicodeString uName;
	uName.translate(userName);
	for (Int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot->isPlayer(uName))
			return i;
	}
	return -1;
}
