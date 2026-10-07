// cl: /DNDEBUG /MD /EHsc

typedef int Int;

template <class Type>
class StringBase
{
public:
	void concat( const char *text, int length );

private:
	StringBase( const char *text );
	StringBase( const StringBase &that );
	~StringBase();
	void releaseBuffer();
	friend class AsciiString;
};

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( *(const StringBase<char> *)&that );
	}
	// Retail releases the string by calling StringBase<char>::releaseBuffer
	// (0x00887940) directly, not the out-of-line ~StringBase<char> at 0x0005E490.
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}
	private:
	void *m_text;
};

class UserPreferences
{
public:
	virtual void _bfme_slot0( void ) = 0;
	virtual void _bfme_slot1( void ) = 0;
	virtual void _bfme_slot2( void ) = 0;
	virtual void _bfme_slot3( void ) = 0;
	virtual void _bfme_slot4( void ) = 0;
	virtual void _bfme_slot5( void ) = 0;
	virtual AsciiString _bfme_getAsciiString( AsciiString key, AsciiString defaultValue ) const = 0;
	virtual void _bfme_setAsciiString( AsciiString key, AsciiString value ) = 0;
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	int m_pad[5];
	int m_rankPoints[9];
	int getPoints( AsciiString name ) const;
	int getRank( AsciiString name ) const;
};

int SkirmishBattleHonors::getRank( AsciiString name ) const
{
	int points = getPoints( name );
	int rank = 0;
	while ( rank < 9 && points >= m_rankPoints[rank] )
		++rank;
	return rank + 1;
}

