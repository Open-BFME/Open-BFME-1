// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// OVERRIDE<T>::operator-> inlined into `(m_thing->m_kindof >> 7) & 1`.
// Same null-arm idiom as S2OverrideFieldAccessors.cpp: the empty OVERRIDE
// returns NULL from the inlined operator, so the bit extract is duplicated
// onto both arms and MSVC keeps the register form `mov eax,[eax+0xC8]`.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_head;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if( !m_overridable )
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
private:
	const T *m_overridable;
};

class Rva001C80F0Thing : public Overridable
{
public:
	char m_gap[ 0xC8 - 8 ];
	unsigned m_kindof;
};

class Rva001C80F0
{
public:
	unsigned value() const;
	char m_head[ 4 ];
	OVERRIDE< Rva001C80F0Thing > m_thing;
};

unsigned Rva001C80F0::value() const
{
	return ( m_thing->m_kindof >> 7 ) & 1;
}
