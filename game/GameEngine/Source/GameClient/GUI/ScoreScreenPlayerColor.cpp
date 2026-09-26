// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ScoreScreen PlayerColor provider, retail 0x00571DF0, 76 bytes.

#include <vector>

extern "C" __declspec( dllimport ) int __cdecl sprintf(
	char *destination, const char *format, ... );

extern char g_aptPalantirNumberFormat[];

struct BfmeScoreScreenPlayerRow
{
	int color;
	int faction;
};

class BfmeAptScreenScoreScreen
{
public:
	void _bfme_getPlayerColor( int index, char *output, bool setting );

private:
	char m_unmodelled_prefix[ 0x264 ];
	_STL::vector<BfmeScoreScreenPlayerRow> m_playerTable;
};

// ?_bfme_getPlayerColor@BfmeAptScreenScoreScreen@@QAEXHPAD_N@Z
void BfmeAptScreenScoreScreen::_bfme_getPlayerColor(
	int index, char *output, bool setting )
{
	if( !setting )
	{
		*(unsigned short *)output = (unsigned short)'0';
		if( !m_playerTable.empty() &&
			(unsigned int)index < m_playerTable.size() )
			sprintf( output, g_aptPalantirNumberFormat,
				m_playerTable[ index ].color );
	}
}
