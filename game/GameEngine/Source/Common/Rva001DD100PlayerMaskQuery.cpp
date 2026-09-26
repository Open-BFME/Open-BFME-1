// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmePlayer001DD100
{
	unsigned char m_unreconstructed_00[0x24];
	int m_playerIndex;

	int getPlayerIndex( void ) const { return m_playerIndex; }
};

class BfmeD1025
{
public:
	unsigned short bfmeLookup1025( int playerIndex, int flags, int extra );
};

extern BfmeD1025 *g_rva005655C0PlayerList;

class Rva001DD100PlayerMaskQuery
{
public:
	unsigned int queryMask( void ) const;

private:
	unsigned char m_unreconstructed_00[8];
	BfmePlayer001DD100 *m_player;
	bool m_match;
	unsigned char m_padding_0d[3];
	int m_flags;
};

unsigned int Rva001DD100PlayerMaskQuery::queryMask( void ) const
{
	unsigned int result = g_rva005655C0PlayerList->bfmeLookup1025(
		m_player->getPlayerIndex(), m_flags | 1, 0 );
	if( !m_match )
	{
		result = ~result;
	}
	return result;
}
