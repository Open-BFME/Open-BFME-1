// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x003C9B60 (261 bytes), the INI block parser registered for the
// "LivingWorldRegionCampaign" block: the static BlockParse node at VA
// 0x012B4848 holds the name string (0x010EE05C) and this body's ILT
// (0x0004A4EE), and the dynamic initializer at 0x00C6B330 links it onto the
// block list at 0x0130CE50.  The C++ name stays address-derived.
//
// It reads the LivingWorldRegionManager from Glo012F1028 +0x28 (the member
// Glo012F1028Type_Rva003BDA10.cpp names), builds the block's 0x58-byte object
// (constructor 0x003C9670) from the name token, fills it from the field table
// at 0x010EDC48, runs the two passes at 0x003C7A40 and 0x003C7B10 on it, and
// appends it to the manager's pointer vector at +0x28.  That object is the
// region container, not a region: the table's "Region" entry (parser
// 0x003C9980) appends 0xF4-byte region objects to its +0x30 vector.  Its class
// name stays address-derived.
//
// Shape: retail stores the new object pointer into its frame slot at the
// definition (+0x7B, before the name temporary's EH state ends) and keeps it
// in ESI for every use.  That is a direct STLport push_back(object) on the
// native <vector>; a hand-written vector shim or an inline by-value append
// wrapper moves the store down to the append.

#include <vector>

#include "ascii_string.h"

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

// 0x58 bytes: the `push 0x58' in front of the constructor call.
class Rva003C9670
{
public:
	Rva003C9670( const AsciiString &name );		// 0x003C9670

private:
	unsigned char m_body[ 0x58 ];
};

// Receiver of the 0x003C7A40 pass (called through ILT 0x0002E88E with the
// new object in ECX); owner and method name not recovered.
class Rva003C7A40Owner
{
public:
	void rva003C7A40();
};

// Landed as ?step@Gen003C7B10Owner@@QAEXXZ (0x003C7B10, ILT 0x00019984).
class Gen003C7B10Owner
{
public:
	void step();
};

class LivingWorldRegionManager
{
public:
	unsigned char m_pad00[ 0x28 ];
	std::vector<Rva003C9670 *> m_vector28;
};

class Glo012F1028Type
{
public:
	unsigned char m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
};

extern Glo012F1028Type *Glo012F1028;

// ?Rva003C9B60Parse@@YAXPAVINI@@@Z
void Rva003C9B60Parse( INI *ini )
{
	LivingWorldRegionManager *manager = Glo012F1028->m_regionManager;

	const char *token = ini->getNextToken();

	Rva003C9670 *object = new Rva003C9670( AsciiString( token ) );

	ini->initFromINI( object, (const FieldParse *)0x010EDC48 );

	( (Rva003C7A40Owner *)object )->rva003C7A40();
	( (Gen003C7B10Owner *)object )->step();

	manager->m_vector28.push_back( object );
}
