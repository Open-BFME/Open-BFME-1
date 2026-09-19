// ?d_00364e70@@YAXXZ
// partial score=0.72 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <new>
#include <vector>

class LivingWorldPlayerArmy
{
public:
	char m_unmodelled00[ 0x20 ];
	int m_startingCommandPoints;
	char m_unmodelled24[ 0x34 ];
};

extern "C" void *memmove( void *destination, const void *source,
	unsigned int bytes );

typedef std::vector<LivingWorldPlayerArmy *> RvaPointerVectorBase;

class RvaPointerVector : public RvaPointerVectorBase
{
public:
	_STL::allocator<LivingWorldPlayerArmy *> get_allocator() const;
};

template <typename T, typename A>
class RvaOutputBase
{
public:
	RvaOutputBase( unsigned int count, const A &alloc );

protected:
	T *m_start;
	T *m_finish;
	T *m_end;
};

class BfmeOtherDPH : public RvaOutputBase<LivingWorldPlayerArmy *,
	_STL::allocator<LivingWorldPlayerArmy *> >
{
public:
	BfmeOtherDPH( const RvaPointerVector &source ) :
		RvaOutputBase<LivingWorldPlayerArmy *,
			_STL::allocator<LivingWorldPlayerArmy *> >(
			static_cast<unsigned int>( source.size() ), source.get_allocator() )
	{
		const LivingWorldPlayerArmy * const *last = source.end();
		const LivingWorldPlayerArmy * const *first = source.begin();
		LivingWorldPlayerArmy **result = this->m_start;
		this->m_finish = last == first ? result :
			static_cast<LivingWorldPlayerArmy **>( memmove( result, first,
			static_cast<unsigned int>( reinterpret_cast<const char *>( last ) -
				reinterpret_cast<const char *>( first ) ) ) ) + ( last - first );
	}
};

class BfmeSubDPH
{
public:
	void bfmeCallDPH( BfmeOtherDPH *other );

private:
	char m_unmodelled00[ 0x18 ];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

void BfmeSubDPH::bfmeCallDPH( BfmeOtherDPH *other )
{
	std::vector<LivingWorldPlayerArmy *> selected;
	for( unsigned int i = 0; i < m_playerArmies.size(); ++i )
	{
		LivingWorldPlayerArmy *army = &m_playerArmies[ i ];
		if( army->m_startingCommandPoints == 4 )
			selected.push_back( army );
	}
	new ( other ) BfmeOtherDPH(
		*reinterpret_cast<const RvaPointerVector *>( &selected ) );
}
