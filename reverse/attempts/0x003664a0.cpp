// ?d_003664a0@@YAXXZ
// partial score=0.97 date=2026-09-20
// cl: /EHsc /MD /O2 /GR- /EHsc- /D_STLP_USE_STATIC_LIB
// stlport

#include <cstring>

extern "C" void *(__cdecl *bfme_memmove_ptr)( void *, const void *, unsigned int );

#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

class GameLogic
{
public:
	bool _bfme_isInLivingWorldCampaign( void );
};

extern GameLogic *TheGameLogic;

struct Rva003664A0String
{
	void *m_data;
};

struct Rva003664A0ArmyVector
{
	int m_values[ 3 ];
};

class Rva00366060
{
public:
	Rva00366060 &operator=( const Rva00366060 &other );

	void *m_vtable;
	int m_index;
	unsigned char m_isActive;
	unsigned char m_pad09[ 3 ];
	Rva003664A0String m_name;
	Rva003664A0String m_faction;
	Rva003664A0String m_icon;
	int m_color;
	int m_nightColor;
	int m_startingCommandPoints;
	int m_unmodelled24;
	int m_unmodelled28;
	int m_unmodelled2C;
	Rva003664A0ArmyVector m_armies;
	int m_unmodelled3C;
	int m_unmodelled40;
	int m_survivalThreshold;
	Rva003664A0String m_displayNameTag;
	unsigned char m_unmodelled4C;
	unsigned char m_pad4D[ 3 ];
	int m_minCommandPoints;
	Rva003664A0String m_replenishArmyName;
};

namespace _STL
{
template <> struct __type_traits<Rva00366060> : __type_traits_aux<1> {};
}

class Rva003664A0Collection
{
public:
	void handle( _STL::vector< void * > &output );

private:
	char m_pad00[ 0x18 ];
	_STL::vector< Rva00366060 > m_playerArmies;
};

void Rva003664A0Collection::handle( _STL::vector< void * > &output )
{
	Rva003664A0Collection *self = this;
	output.clear();
	if( !TheGameLogic->_bfme_isInLivingWorldCampaign() )
		return;

	for( unsigned int i = 0; i < self->m_playerArmies.size(); ++i )
	{
		self->m_playerArmies[ i ] = self->m_playerArmies[ i ];
		Rva00366060 *army = self->m_playerArmies.begin() + i;
		if( army->m_startingCommandPoints == 1 )
			continue;
		if( army->m_startingCommandPoints == 4 )
			continue;
		if( army->m_unmodelled4C )
			continue;
		output.push_back( (void *)(long)army->m_index );
	}
}

// ?handle@Rva003664A0Collection@@QAEXAAV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@@Z
