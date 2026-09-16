// ?setCondition@Rva002D9F30Owner@@QAEXXZ
// partial score=0.98 date=2026-09-16
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Retail 0x002D9F30 sets one model-condition bit on the object at +8, using
// the index held at +0x64 of the record at +4, and tail-calls the reapply. The
// owner name is not guessed: the body has no named caller in the current
// source surface. The helper is the existing pinned
// BfmeOwnerVNI::bfmeApply1VNI body reached through ILT 0x0002191D.

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

	UnsignedInt index = record->m_conditionIndex;

	if( index == 0xffffffff )
		return;

	UnsignedInt bit = 1U << ( index & 0x1f );

	if( ( target->m_conditionWords[ index >> 5 ] & bit ) != 0 )
		return;

	target->m_conditionWords[ index >> 5 ] |= bit;
	( (BfmeOwnerVNI *)target )->bfmeApply1VNI();
}
