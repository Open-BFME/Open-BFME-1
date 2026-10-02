// RVA 0x003C22E0: address-derived owner shared with the matched 0x003C2530 caller.
// Evidence: targets/game/reverse/identity_evidence/rva003c22e0.md
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _M_insert_overflow j_00007e96
#include <vector>
#include <algorithm>
#undef _M_insert_overflow

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Gen_00609320
{
public:
	char m_pad00[4];
	int m_at04;
	int rva003c22e0_at04() const { return m_at04; }
};

extern Gen_00609320 *g_bfmeStateDF;
extern void j_00009831();

class Rva003C2280Item
{
public:
	virtual void slot00( unsigned int );
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual bool slot10();
	virtual bool slot14( bool );
	unsigned int m_counter04;
	unsigned rva003c22e0_at04() const { return m_counter04; }
	bool m_flag;
};

class Rva003C2530Owner
{
public:
	void rva003c22e0();

private:
	char m_pad00[ 0x50 ];
	_STL::vector<Rva003C2280Item *> m_first;
	_STL::vector<Rva003C2280Item *> m_second;
	char m_pad68[ 0x10 ];
	unsigned char m_byte78;
};

void Rva003C2530Owner::rva003c22e0()
{
	typedef unsigned ( Rva003C2280Item::*DecrementCall )();
	union
	{
		void ( *plain )();
		DecrementCall member;
	} decrementCall;
	_STL::vector<Rva003C2280Item *> selected;

	decrementCall.plain = j_00009831;
	if ( g_bfmeStateDF->rva003c22e0_at04() == 1 && *( unsigned char * )( ( char * )TheLivingWorldManager + 0x288 ) == 0 )
	{
		if (m_byte78)
			return;
		for ( unsigned int i = 0; i < m_first.size(); ++i )
		{
			Rva003C2280Item *item = m_first[ i ];
			if ( ( item->rva003c22e0_at04() != 0 && ( item->*decrementCall.member )() == 0 && item->slot10() ) || item->slot14( item->rva003c22e0_at04() == 0 ) )
				selected.push_back( item );
		}

		unsigned int count = selected.size();
		for ( unsigned int i = 0; i < count; ++i )
		{
			Rva003C2280Item *item = selected[ i ];
			Rva003C2280Item **found = _STL::find( m_first.begin(), m_first.end(), item );
			if ( found != m_first.end() )
			{
				if ( *found != 0 )
					( *found )->slot00( 1 );
				m_first.erase( found );
			}
		}
		return;
	}
}
