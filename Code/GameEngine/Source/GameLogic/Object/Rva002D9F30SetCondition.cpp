// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Retail 0x002D9F30 sets one model-condition bit on the object at +8, using
// the index held at +0x64 of the record at +4, and tail-calls the reapply. The
// owner name is not guessed: the body has no named caller in the current
// source surface. The helper is the existing pinned
// BfmeOwnerVNI::bfmeApply1VNI body reached through ILT 0x0002191D, which
// jumps to Object::notifyModelConditionChanged (0x001BE1C0).
//
// The set is a clear-and-set whose clear index is the -1 sentinel held in a
// local. That half folds away entirely, but it is still present when MSVC
// orders the commutative TEST, so the flag word stays first (test ecx,edx at
// +0x34, as retail). A bare test-and-set, or the sentinel passed as a literal,
// encodes test edx,ecx. ArmorUpgrade::upgradeImplementation (0x002D2D20)
// shows the same effect: its clear-path test is word-first only while its set
// path is in the function too.

typedef unsigned int UnsignedInt;

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class Rva002D9F30Target
{
public:
	unsigned char m_beforeConditionWords[ 0x110 ];
	UnsignedInt m_conditionWords[ 8 ];

	__forceinline bool testCondition( UnsignedInt index ) const
	{
		return ( m_conditionWords[ index >> 5 ] & ( 1U << ( index & 0x1f ) ) ) != 0;
	}

	__forceinline void clearAndSetCondition( UnsignedInt clearIndex, UnsignedInt setIndex )
	{
		bool changed = false;

		if( clearIndex != 0xffffffff && testCondition( clearIndex ) )
		{
			m_conditionWords[ clearIndex >> 5 ] &= ~( 1U << ( clearIndex & 0x1f ) );
			changed = true;
		}

		if( setIndex != 0xffffffff && !testCondition( setIndex ) )
		{
			m_conditionWords[ setIndex >> 5 ] |= 1U << ( setIndex & 0x1f );
			changed = true;
		}

		if( changed )
			( (BfmeOwnerVNI *)this )->bfmeApply1VNI();
	}
};

class Rva002D9F30Record
{
public:
	unsigned char m_beforeIndex[ 0x64 ];
	UnsignedInt m_conditionIndex;
};

class Rva002D9F30Owner
{
public:
	void setCondition();

private:
	unsigned char m_bfmePad000[ 4 ];
	Rva002D9F30Record *m_record;
	Rva002D9F30Target *m_target;
};

void Rva002D9F30Owner::setCondition()
{
	Rva002D9F30Target *target = m_target;
	Rva002D9F30Record *record = m_record;

	if( target == 0 || record == 0 )
		return;

	UnsignedInt clearIndex = 0xffffffff;
	target->clearAndSetCondition( clearIndex, record->m_conditionIndex );
}
