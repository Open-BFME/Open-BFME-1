// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: address-scoped Glo012F1028Type item construction, retail
// 0x003C1C50.  The matched caller at 0x003AD8B0 invokes the ILT at 0x0001C03A
// on the global at 0x012F1028 with this exact nine-argument layout.

#include <vector>

class UnicodeString
{
public:
	void set( const UnicodeString &other );

private:
	void *m_data;
};

class AsciiString
{
	void *m_data;
};

struct Rva003C1C50Coord
{
	int x;
	int y;
};

extern void j_0001036b();
extern void j_0002e898();
extern void j_0003688b();
extern void j_00028cf9();
extern void j_00045408();

class Rva003A5450
{
public:
	Rva003A5450();

private:
	void *m_vtable;
	UnicodeString m_name;
	UnicodeString m_secondName;
	Rva003C1C50Coord m_coord;
	int m_14;
	int m_18;
	char m_1C;
	char m_enabled;
	char m_1E;
	char m_1F;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	UnicodeString m_label;
	char m_38[ 8 ];
	UnicodeString m_description;
	char m_finalFlag;
	char m_45[ 3 ];
	int m_48;
	int m_4C;
	int m_50;

	friend class Glo012F1028Type;
};

// The four ILT-routed setters are reached through retail thunks; call them
// directly, with no linker alias.
class Glo012F1028Type
{
public:
	bool addItem( const UnicodeString &name, const UnicodeString &secondName,
		const Rva003C1C50Coord &coord, char flag, char enabled,
		const UnicodeString &label, const AsciiString &ascii,
		const UnicodeString &description, char finalFlag );

private:
	char m_head[ 0x0C ];
	_STL::vector<Rva003A5450 *> m_items;
};

bool Glo012F1028Type::addItem( const UnicodeString &name,
	const UnicodeString &secondName, const Rva003C1C50Coord &coord, char flag,
	char enabled, const UnicodeString &label, const AsciiString &ascii,
	const UnicodeString &description, char finalFlag )
{
	Rva003A5450 *item = new Rva003A5450;
	if ( item == 0 )
		return false;

	item->m_name.set( name );
	item->m_enabled = enabled;
	item->m_secondName.set( secondName );
	item->m_label.set( label );
	item->m_description.set( description );
	item->m_finalFlag = finalFlag;
	union { void (*fn)(); void ( Rva003A5450::*call )( const UnicodeString & ); } uUnicode = { j_0001036b };
	union { void (*fn)(); void ( Rva003A5450::*call )( const Rva003C1C50Coord & ); } uCoord = { j_0002e898 };
	union { void (*fn)(); void ( Rva003A5450::*call )( char ); } uFlag = { j_0003688b };
	union { void (*fn)(); void ( Rva003A5450::*call )( const AsciiString & ); } uAscii = { j_00028cf9 };
	( item->*uUnicode.call )( secondName );
	( item->*uCoord.call )( coord );
	( item->*uFlag.call )( flag );
	( item->*uAscii.call )( ascii );
	m_items.push_back( item );
	return true;
}
