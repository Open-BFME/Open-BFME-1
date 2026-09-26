// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

#pragma comment(linker, "/alternatename:??4AsciiString@@QAEAAV0@ABV0@@Z=?set@UnicodeString@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:??1AsciiString@@QAE@XZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

struct Rva00135C90Element
{
	void *m_unit;
	int m_flags;
	AsciiString m_name;
};

struct Gen_t_000e5750_p12cd
{
	void *m_unit;
	int m_flags;
	AsciiString m_name;
};

namespace _STL
{
	struct __false_type
	{
	};

	template <typename Type>
	class allocator
	{
	};

	template <typename Type>
	void BfmeElementConstruct( Type *destination, const Type &value );

	template <typename Type>
	void BfmeElementConstruct( void *destination, const Type &value );

	template <typename Type, typename Allocator>
	class vector
	{
	public:
		Type *m_start;
		Type *m_finish;
		Type *m_end_of_storage;

		void push_back( const Type &value, const __false_type &tag );

	protected:
		void _M_insert_overflow( Type *position, const Type &value,
			const __false_type &, unsigned int fillLength, bool atEnd );
	};

	template <>
	__forceinline void BfmeElementConstruct(
		Gen_t_000e5750_p12cd *destination,
		const Gen_t_000e5750_p12cd &value )
	{
		BfmeElementConstruct(
			reinterpret_cast<void *>( destination ),
			reinterpret_cast<const Rva00135C90Element &>( value ) );
	}

	template <typename Type, typename Allocator>
	__forceinline void vector<Type, Allocator>::push_back(
		const Type &value, const __false_type &tag )
	{
		if ( m_finish != m_end_of_storage )
		{
			BfmeElementConstruct( m_finish, value );
			++m_finish;
		}
		else
		{
			_M_insert_overflow( m_finish, value, tag, 1, true );
		}
	}
}

class ProductionPrerequisite
{
public:
	void addUnitPrereq( AsciiString unit, bool orUnitWithPrevious );

private:
	_STL::vector<Gen_t_000e5750_p12cd,
		_STL::allocator<Gen_t_000e5750_p12cd> > m_prereqUnits;
	_STL::vector<int, _STL::allocator<int> > m_prereqSciences;
	_STL::vector<int, _STL::allocator<int> > m_unused;
};

#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@UGen_t_000e5750_p12cd@@V?$allocator@UGen_t_000e5750_p12cd@@@_STL@@@_STL@@IAEXPAUGen_t_000e5750_p12cd@@ABU3@ABU__false_type@2@I_N@Z=?j_0001e13c@@YAXXZ")

// ?addUnitPrereq@ProductionPrerequisite@@QAEXVAsciiString@@_N@Z
void ProductionPrerequisite::addUnitPrereq( AsciiString unit, bool orUnitWithPrevious )
{
	Gen_t_000e5750_p12cd info;
	info.m_name = unit;
	info.m_flags = orUnitWithPrevious ? 1 : 0;
	info.m_unit = 0;
	const _STL::__false_type &tag =
		*reinterpret_cast<const _STL::__false_type *>( &orUnitWithPrevious );
	m_prereqUnits.push_back( info, tag );
}
