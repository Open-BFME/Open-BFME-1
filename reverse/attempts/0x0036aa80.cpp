// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z
// partial score=0.85 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /ICode/GameEngine/Source
// stlport

// Identity from the AttributeModifierPoolUpdate vtable at 0x010E92DC slot 3
// and the sibling field layouts in AttributeModifierPoolUpdateConstructor.cpp
// and AttributeModifierPoolUpdate_bfmeGetBonus.cpp: m_modifiers begins at
// this+0x20, m_maxFrame at +0x2c, the two 7-entry UnsignedInt arrays at
// +0x30 and +0x4c. UpdateModule's own layout (vtable + PB_DeepBase fields +
// two interface vtables + three ints) totals 0x20 bytes.

#include "Common/System/xfer.h"
#include "StringInline.h"
#include <vector>

class Thing;
class ModuleData;
class Object;

class PB_DeepBase
{
public:
	PB_DeepBase( Thing *, const ModuleData * );
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class PB_BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class PB_UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class UpdateModule : public PB_DeepBase,
	public PB_BehaviorModuleInterface,
	public PB_UpdateModuleInterface
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: PB_DeepBase( thing, moduleData ),
		  m_f14( 0 ),
		  m_f18( -1 ),
		  m_f1c( -1 )
	{
	}

protected:
	virtual void xfer( Xfer *xfer );

	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

// The nameKey field xfers through Xfer::operator==(int&), not the unsigned
// overload: NameKeyType is a plain int in this tree, and the two overloads
// sit at different vtable slots (0x78 vs 0x74), so the wrong one is a real
// codegen difference, not cosmetic.
struct AttributeModifierEntry
{
	int m_nameKey;
	AsciiString m_name;
	unsigned int m_expirationFrame;
	unsigned int m_unknown;

	AttributeModifierEntry( const AsciiString &name )
		: m_nameKey( 0 ), m_name( name ), m_expirationFrame( 0 ), m_unknown( 0 )
	{
	}
};

class AttributeModifierPoolUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );

private:
	_STL::vector<AttributeModifierEntry> m_modifiers;
	unsigned int m_maxFrame;
	unsigned int m_activationFrames[ 7 ];
	unsigned int m_values[ 7 ];
};

void AttributeModifierPoolUpdate::xfer( Xfer *xfer )
{
	Xfer::Version version;
	version.data[ 0 ] = 1;
	version.data[ 1 ] = 3;
	*xfer == version;

	if ( xfer->IsLoading() )
	{
		m_modifiers.erase( m_modifiers.begin(), m_modifiers.end() );

		int count = 0;
		*xfer == count;
		for ( int index = 0; index < count; ++index )
		{
			AttributeModifierEntry entry( AsciiString( "" ) );

			*xfer == entry.m_nameKey;
			if ( version.data[ 1 ] >= 3 )
				*xfer == entry.m_name;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unknown;
			m_modifiers.push_back( entry );
		}
	}
	else
	{
		int count = static_cast<int>( m_modifiers.size() );
		*xfer == count;
		for ( AttributeModifierEntry *source = m_modifiers.begin();
			source != m_modifiers.end(); ++source )
		{
			AttributeModifierEntry entry = *source;

			*xfer == entry.m_nameKey;
			if ( version.data[ 1 ] >= 3 )
				*xfer == entry.m_name;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unknown;
		}
	}

	if ( version.data[ 0 ] >= 2 )
	{
		for ( int index = 0; index < 7; ++index )
		{
			*xfer == m_activationFrames[ index ];
			*xfer == m_values[ index ];
		}
	}

	UpdateModule::xfer( xfer );
}
