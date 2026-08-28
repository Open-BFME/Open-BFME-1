// ?bfmeExportStatus@Object@@QBEXPAVBfmeObjectStatus@@@Z
// partial score=0.89 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	void set( const AsciiString &other );
private:
	void *m_data;
};

class UnicodeString
{
public:
	void set( const UnicodeString &other );
private:
	void *m_data;
};

class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;
};

class ThingTemplate
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_unmodelled_08[ 0x18 ];
	AsciiString m_name;
};

class ExperienceTracker
{
public:
	unsigned char m_unmodelled_00[ 0x0C ];
	UnsignedInt m_value0C;
	unsigned char m_unmodelled_10[ 0x14 ];
	Bool m_flag24;
	unsigned char m_unmodelled_25[ 3 ];
	UnsignedInt m_value28;
};

struct UpgradeMask
{
	UnsignedInt bits[ 6 ];
};

template <size_t NUMBITS>
class BitFlags
{
	public:
	void clear( void )
	{
		m_bits.reset();
	}

	private:
	_STL::bitset<NUMBITS> m_bits;
};

class BfmeObjectStatus
{
public:
	void *m_vtable;                                      // +0x00
	AsciiString m_templateName;                          // +0x04
	UnsignedInt m_value08;                               // +0x08
	UnsignedInt m_value0C;                               // +0x0C
	UpgradeMask m_upgrades;                              // +0x10
	BitFlags<96> m_clearMask;                            // +0x28
	unsigned char m_unmodelled_34[ 5 ];
	Bool m_flag39;                                       // +0x39
	unsigned char m_unmodelled_3A[ 2 ];
	UnsignedInt m_value3C;
	UnsignedInt m_value40;
	UnsignedInt m_value44;
	UnsignedInt m_value48;
	AsciiString m_ascii4C;
	unsigned char m_unmodelled_50[ 0x28 ];
	UnicodeString m_unicode78;
};

class Object
{
public:
	void bfmeExportStatus( BfmeObjectStatus *out ) const;

	unsigned char m_unmodelled_000[ 4 ];
	ThingTemplate *m_template;                           // +0x004
	unsigned char m_unmodelled_008[ 0x208 ];
	ExperienceTracker *m_experienceTracker;              // +0x210
	unsigned char m_unmodelled_214[ 0x10 ];
	UpgradeMask m_upgrades;                              // +0x224
	unsigned char m_unmodelled_23C[ 0x138 ];
	UnsignedInt m_value374;
	UnsignedInt m_value378;
	UnsignedInt m_value37C;
	UnsignedInt m_value380;
	unsigned char m_unmodelled_384[ 4 ];
	UnicodeString m_unicode388;
	AsciiString m_ascii38C;
};

void Object::bfmeExportStatus( BfmeObjectStatus *out ) const
{
	const ThingTemplate *thingTemplate = m_template;
	ExperienceTracker *tracker = m_experienceTracker;
	if( thingTemplate && thingTemplate->m_nextOverride )
		thingTemplate = reinterpret_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride() );

	out->m_templateName.set( thingTemplate->m_name );
	out->m_value08 = tracker->m_value0C;
	out->m_value0C = tracker->m_value28;
	out->m_flag39 = tracker->m_flag24;
	out->m_upgrades = m_upgrades;
	out->m_value3C = m_value374;
	out->m_value44 = m_value37C;
	out->m_value40 = m_value378;
	out->m_value48 = m_value380;
	out->m_unicode78.set( m_unicode388 );
	out->m_ascii4C.set( m_ascii38C );
	out->m_clearMask.clear();
}
