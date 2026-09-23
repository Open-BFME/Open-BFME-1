// ?bfmeUseXI@BfmeTargetXI@@QAEXPAVBfmeMsgXI@@@Z
// Retail 0x00369240 (427 B, ret 4, int3 padding from 0x003693EB).
// Identity: ILT 0x0002D754 and the BfmeOwnerXI::bfmeSendXI caller; the class
// tokens stay opaque. The body removes one modifier from the 16-byte-entry
// vector at +0x20/+0x24 (same layout as AttributeModifierPoolUpdate's
// neighbours at 0x00369460), clears the modifier's model conditions, trims
// the body's max health by attribute 13, plays the modifier FX unless the
// list is blocked and drops the per-type count at +0x4C.
// The flags getter 0x0036B250 is called directly under its address-derived
// pin (ILT 0x0001FAE6). The FX tail goes through the null test, then the
// inline FXList::doFXObjChecked member, with every object read spelled as
// the inline getObject() accessor so the receiver stays in ESI.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii/Common /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <bitset>

#include "AsciiString.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags()
	{
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;

class Object;

class Rva00369240Body
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Real slot10();
	virtual void slot14();
	virtual Real slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58( Real, Int );
};

class Object
{
public:
	void clearAndSetModelConditionFlags( const ModelConditionFlags &clr, const ModelConditionFlags &set );
	void clearModelConditionFlags( const ModelConditionFlags &clr )
	{
		ModelConditionFlags empty;
		clearAndSetModelConditionFlags( clr, empty );
	}

	unsigned char m_unreconstructed000[0x200];
	Rva00369240Body *m_body200;
};

class FXList
{
public:
	Bool bfmeIsBlocked() const;
	void doFXObjChecked( const Object *primary, const Object *secondary = 0 ) const
	{
		if( !bfmeIsBlocked() )
			doFXObj( primary, secondary );
	}
	void doFXObj( const Object *primary, const Object *secondary ) const;
};

struct AttributeModifierDefinition
{
	UnsignedInt m_unreconstructed00[3];
	UnsignedInt m_typeMask0C;
};

class AttributeModifierDefinitionStore
{
public:
	Int indexOf( Int key ) const;
	Bool getValue( Int modifierIndex, Int attribute, Real *value ) const;
	Int secondaryValueAt( Int modifierIndex, const Object *obj ) const;
	AttributeModifierDefinition *findDefinition( UnsignedInt modifierIndex );
	ModelConditionFlags rva0036B250ConditionsAt( Int modifierIndex ) const;
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

struct Gen_t_00368d50_p16cd
{
	~Gen_t_00368d50_p16cd();

	UnsignedInt m_nameKey;
	AsciiString m_name;
	UnsignedInt m_frame;
	UnsignedInt m_expirationFrame;
};

class BfmeMsgXI
{
public:
	AsciiString m_name;
};

class BfmeTargetXI
{
public:
	void bfmeUseXI( BfmeMsgXI *msg );
	Object *getObject() const { return m_object; }

private:
	void *m_vftable;
	void *m_unreconstructed04;
	Object *m_object;
	unsigned char m_unreconstructed0C[0x20 - 0x0C];
	_STL::vector<Gen_t_00368d50_p16cd> m_modifiers;
	unsigned char m_unreconstructed2C[0x4C - 0x2C];
	Int m_typeCounts[7];
};

static inline Int firstTypeIndex( UnsignedInt mask )
{
	for( Int i = 0; i < 7; ++i )
	{
		if( mask & ( 1 << ( (UnsignedInt)i % 32 ) ) )
			return i;
	}
	return -1;
}

void BfmeTargetXI::bfmeUseXI( BfmeMsgXI *msg )
{
	Int index = TheAttributeModifierDefinitionStore->indexOf(
		TheNameKeyGenerator->nameToKey( msg->m_name.str() ) );
	if( index < 0 )
		return;

	for( _STL::vector<Gen_t_00368d50_p16cd>::iterator it = m_modifiers.begin(); it != m_modifiers.end(); ++it )
	{
		if( it->m_nameKey != (UnsignedInt)index )
			continue;

		m_modifiers.erase( it );

		ModelConditionFlags clr = TheAttributeModifierDefinitionStore->rva0036B250ConditionsAt( index );
		getObject()->clearModelConditionFlags( clr );

		Real amount = 0.0f;
		TheAttributeModifierDefinitionStore->getValue( index, 13, &amount );
		if( amount > 0.0f )
		{
			Rva00369240Body *body = getObject()->m_body200;
			if( body && body->slot10() > 0.0f )
				body->slot58( body->slot18() - amount, 1 );
		}

		const FXList *fx = (const FXList *)TheAttributeModifierDefinitionStore->secondaryValueAt( index, getObject() );
		if( fx )
			fx->doFXObjChecked( getObject() );

		AttributeModifierDefinition *def = TheAttributeModifierDefinitionStore->findDefinition( index );
		if( def )
			--m_typeCounts[firstTypeIndex( def->m_typeMask0C )];
		return;
	}
}
