// cl: /DNDEBUG /MD /EHsc
// readable body of ?clearModelConditionState@Object@@QAEXW4ModelConditionFlagType@@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::clearModelConditionState, retail 0x00162CD0. Builds a single-bit
// flag mask on the stack and hands it to the shared apply helper at
// 0x001C7370 with the set flag false.

#include <string.h>

typedef unsigned int UnsignedInt;

enum ModelConditionFlagType { MODELCONDITION_FIRST = 0 };

class ModelConditionFlags
{
public:
	ModelConditionFlags();
	void set( ModelConditionFlagType bit );

	UnsignedInt m_bits[ 3 ];
};

// ??0ModelConditionFlags@@ present-unmatched
inline ModelConditionFlags::ModelConditionFlags()
{
	memset( m_bits, 0, sizeof( m_bits ) );
}

// ?set@ModelConditionFlags@@ present-unmatched
inline void ModelConditionFlags::set( ModelConditionFlagType bit )
{
	m_bits[ (UnsignedInt)bit >> 5 ] |= 1 << ( (UnsignedInt)bit & 31 );
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void clearModelConditionState( ModelConditionFlagType a );
	void applyRva1C7370( const ModelConditionFlags &flags, bool set );
};

// ?clearModelConditionState@Object@@QAEXW4ModelConditionFlagType@@@Z
void Object::clearModelConditionState( ModelConditionFlagType a )
{
	ModelConditionFlags c;
	c.set( a );
	applyRva1C7370( c, false );
}
