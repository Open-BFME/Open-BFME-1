// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Retail 0x0015FC60 clears one model-condition bit and, when the bit was set,
// reapplies the model. The owner name is not guessed: the body has no named
// caller in the current source surface. The helper is the existing pinned
// BfmeOwnerVNI::bfmeApply1VNI body reached through ILT 0x0002191D, the same
// one the move at 0x001B7CD0 calls.

typedef unsigned int UnsignedInt;

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class Rva0015FC60Owner
{
public:
	void clearCondition( UnsignedInt index );

private:
	unsigned char m_beforeConditionWords[ 0x110 ];
	UnsignedInt m_conditionWords[ 8 ];
};

void Rva0015FC60Owner::clearCondition( UnsignedInt index )
{
	UnsignedInt bit = 1U << ( index & 0x1f );

	if( ( bit & m_conditionWords[ index >> 5 ] ) != 0 )
	{
		m_conditionWords[ index >> 5 ] &= ~bit;
		( (BfmeOwnerVNI *)this )->bfmeApply1VNI();
	}
}
