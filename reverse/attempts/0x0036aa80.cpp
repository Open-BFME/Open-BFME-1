// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z
// partial score=0.88 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /ICode/GameEngine/Source
// stlport

// AttributeModifierPoolUpdate::xfer, retail RVA 0x0036AA80.
// Identity from vtable 0x010E92DC slot 3 and the sibling constructor layout.
// throw() on the StringBase copy ctor recovers retail's this-in-ebx coloring
// and the 0x2C frame; remaining gap is EH state 0/1 around the temp string
// plus STLport _Construct inlining into push_back (598B vs 582B).

#include "Common/System/xfer.h"
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other ) throw();
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

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
	int m_values[ 7 ];
};

// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z
void AttributeModifierPoolUpdate::xfer( Xfer *xfer )
{
	Xfer::Version version;
	version.data[ 0 ] = 1;
	version.data[ 1 ] = 3;
	*xfer == version;

	if ( xfer->IsLoading() )
	{
		_STL::vector<AttributeModifierEntry> *modifiers = &m_modifiers;
		modifiers->erase( modifiers->begin(), modifiers->end() );

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
			modifiers->push_back( entry );
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

	if ( version.data[ 1 ] >= 2 )
	{
		int *values = m_values;
		int remaining = 7;
		do
		{
			*xfer == *reinterpret_cast<unsigned int *>( values - 7 );
			*xfer == *values;
			++values;
			--remaining;
		} while ( remaining );
	}

	UpdateModule::xfer( xfer );
}
