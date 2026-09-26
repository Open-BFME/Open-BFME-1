// cl: /DNDEBUG /MD /EHsc

template <class Type>
class StringBase
{
private:
	StringBase( const char *text );
	StringBase( const StringBase &that );
	~StringBase();
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
	~AsciiString()
	{
		((StringBase<char> *)this)->~StringBase();
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
	int m_pad[4];
	int m_rankPoints[10];
	int getPoints( AsciiString name ) const;
	int getPointsToNextRank( AsciiString name, int rank ) const;
};

int SkirmishBattleHonors::getPointsToNextRank( AsciiString name, int rank ) const
{
	if ( rank == 10 )
		return 0;
	return m_rankPoints[rank] - getPoints( name );
}
