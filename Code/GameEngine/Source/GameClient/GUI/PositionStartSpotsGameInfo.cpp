// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

template <typename T>
class StringBase
{
protected:
	StringBase( const StringBase<T> &that );

public:
	void set( const StringBase<T> &that );

	friend class AsciiString;

	private:
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	AsciiString( const AsciiString &that ) : StringBase<char>( that ) {}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	AsciiString &operator=( const AsciiString &that )
	{
		set( that );
		return *this;
	}
};

class GameSlot
{
public:
	void *m_vptr;
	unsigned char m_pad04[ 5 ];
	Bool m_hasMap;
};

class GameInfo
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual Int getLocalSlotNum() const;

	AsciiString getMap() const;
	const GameSlot *getConstSlot( Int slot ) const;

	unsigned char m_pad04[ 9 ];
	Bool m_inGame;
};

class GameWindow;

void positionStartSpots( AsciiString mapName, GameWindow *buttonMapStartPositions[],
	GameWindow *mapWindow, Bool onLoadScreen );

// ?positionStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@PAV2@_N@Z
void positionStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[],
	GameWindow *mapWindow, Bool onLoadScreen )
{
	AsciiString localMapFname = myGame->getMap();
	if (!myGame->m_inGame)
	{
		Int localIdx = myGame->getLocalSlotNum();
		if (localIdx == -1)
			localMapFname = AsciiString::TheEmptyString;
		else if (!myGame->getConstSlot( localIdx )->m_hasMap)
			localMapFname = AsciiString::TheEmptyString;
	}
	positionStartSpots( localMapFname, buttonMapStartPositions, mapWindow,
		onLoadScreen );
}
