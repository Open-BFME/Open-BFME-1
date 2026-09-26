// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

extern "C" __declspec(dllimport) void *__cdecl memmove( void *destination, const void *source,
	unsigned int bytes );

class LivingWorldPlayerArmy
{
public:
	char m_unmodelled00[ 0x20 ];
	int m_startingCommandPoints;
	char m_unmodelled24[ 0x34 ];
};

struct Rva00364E70SelectedPointer
{
	LivingWorldPlayerArmy *m_army;
};


class Gen_ve_003628f0;

typedef std::vector<Gen_ve_003628f0 *> RvaPointerStdVector;
typedef _STL::allocator<Gen_ve_003628f0 *> RvaPointerAllocator;

template <>
__declspec( noinline ) _STL::_Vector_base<Gen_ve_003628f0 *, RvaPointerAllocator>::_Vector_base(
	size_t __n, const RvaPointerAllocator &__a ) :
	_M_start( 0 ), _M_finish( 0 ), _M_end_of_storage( __a, 0 )
{
	_M_start = _M_end_of_storage.allocate( __n );
	_M_finish = _M_start;
	_M_end_of_storage._M_data = _M_start + __n;
}

template <>
__declspec( noinline ) RvaPointerAllocator RvaPointerStdVector::get_allocator() const
{
	return _STLP_CONVERT_ALLOCATOR( ( const allocator_type & )this->_M_end_of_storage, Gen_ve_003628f0 * );
}

class RvaPointerVector : public
	_STL::_Vector_base<Gen_ve_003628f0 *, RvaPointerAllocator>
{
public:
	typedef _STL::_Vector_base<Gen_ve_003628f0 *, RvaPointerAllocator> Base;

	RvaPointerVector( const RvaPointerVector &other ) :
		Base( static_cast<unsigned int>( other._M_finish - other._M_start ),
			reinterpret_cast<const RvaPointerStdVector &>( other ).get_allocator() )
	{
		Gen_ve_003628f0 * const *last = other._M_finish;
		Gen_ve_003628f0 * const *first = other._M_start;
		Gen_ve_003628f0 **destination = this->_M_start;
		Gen_ve_003628f0 **finish = destination;
		if( last != first )
		{
			unsigned int bytes = static_cast<unsigned int>(
				reinterpret_cast<const char *>( last ) -
				reinterpret_cast<const char *>( first ) );
			finish = reinterpret_cast<Gen_ve_003628f0 **>(
				static_cast<char *>( memmove( destination, first, bytes ) ) + bytes );
		}
		this->_M_finish = finish;
	}
};

class BfmeLivingWorldPlayerArmyCollection
{
public:
	RvaPointerVector collectModeFourArmyPointers();

private:
	char m_unmodelled[ 0x18 ];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

// ?collectModeFourArmyPointers@BfmeLivingWorldPlayerArmyCollection@@QAE?AVRvaPointerVector@@XZ
RvaPointerVector BfmeLivingWorldPlayerArmyCollection::collectModeFourArmyPointers()
{
	std::vector<Rva00364E70SelectedPointer> selected;
	for( unsigned int i = 0; i < m_playerArmies.size(); ++i )
	{
		if( m_playerArmies[ i ].m_startingCommandPoints == 4 )
		{
			Rva00364E70SelectedPointer army = { &m_playerArmies[ i ] };
			selected.push_back( army );
		}
	}
	return reinterpret_cast<const RvaPointerVector &>( selected );
}
