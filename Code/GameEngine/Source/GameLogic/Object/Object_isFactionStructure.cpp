// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?isFactionStructure@Object@@QBE_NXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Open-BFME: Object::isFactionStructure, retail 0x001C5730. The surviving
// Object.cpp source spells this as isAnyKindOf(KINDOFMASK_FS). Retail builds
// the six-dword mask here with bits 61, 62, 63, 64, and 134 set.

#include <bitset>

typedef int Int;
typedef bool Bool;

template <size_t NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	inline BitFlags(
		BogusInitType,
		Int idx1,
		Int idx2,
		Int idx3,
		Int idx4,
		Int idx5 )
	{
		m_bits.set( idx1 );
		m_bits.set( idx2 );
		m_bits.set( idx3 );
		m_bits.set( idx4 );
		m_bits.set( idx5 );
	}

private:
	// The retail intersection body processes six dwords. The 116 template
	// argument below preserves the already-verified Thing ABI symbol name.
	_STL::bitset<192> m_bits;
};

typedef BitFlags<116> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isAnyKindOf( const KindOfMaskType &mask ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isFactionStructure() const;
};

Bool Object::isFactionStructure() const
{
	return isAnyKindOf(
		KindOfMaskType( KindOfMaskType::kInit, 61, 62, 63, 64, 134 ) );
}
