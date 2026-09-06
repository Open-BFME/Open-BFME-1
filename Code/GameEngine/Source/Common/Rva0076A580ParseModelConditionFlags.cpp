// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

typedef int Int;

#include <bitset>

extern "C" __declspec( dllimport ) int __cdecl _strnicmp(
	const char *, const char *, unsigned int );

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps = 0 );
	static Int scanIndexList( const char *token, const char *const *names );
};

template <int NUMBITS>
class BitFlags
{
	public:
		void clear()
		{
			m_bits.reset();
		}

		void set( Int bitIndex )
		{
			m_bits._Unchecked_set( bitIndex );
		}

		void clearBit( Int bitIndex )
		{
			m_bits._Unchecked_reset( bitIndex );
		}

	private:
		_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> Rva0076A580ModelConditionFlags;

void parseModelConditionFlags(
	INI *ini,
	Rva0076A580ModelConditionFlags *all,
	Rva0076A580ModelConditionFlags *positive )
{
	all->clear();
	positive->clear();

	for (const char *token = ini->getNextTokenOrNull(); token != 0;
		token = ini->getNextTokenOrNull())
	{
		bool notCondition = _strnicmp( token, "NOT_", 4 ) == 0;
		const char *name = token + (notCondition ? 4 : 0);
		Int bitIndex = INI::scanIndexList( name,
			reinterpret_cast< const char *const * >( 0x012A6918 ) );
		all->set( bitIndex );
		if (!notCondition)
			positive->set( bitIndex );
		else
			positive->clearBit( bitIndex );
	}
}
