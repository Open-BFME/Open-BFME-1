// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/GameEngine/Source /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// FILE: INILivingWorldAnimObject.cpp /////////////////////////////////////////
//
// The LivingWorldAnimObject block, retail 0x0060A3A0. BFME-only; the INI block
// table in .data names it, and the "LivingWorldAnimObject" literal sits in the
// same run as the field table this body pushes (0x01115B60).
//
// Same shape as ParseArmyIconBlock in INIArmyIcon.cpp - guard the token, look
// the record up on TheLivingWorldManager by name, hand it to initFromINI - with
// two differences: this one does not throw on a null INI, and it does not test
// the lookup's result before parsing into it.
//
// The manager keeps the stand-in class name INIArmyIcon.cpp gave it. That is
// not a claim about what BFME calls it; it is so the one global at 0x012F706C
// keeps one decorated name across both translation units. The record itself is
// named by its Snapshot vtable: its GetSnapshotName slot returns the adjacent
// "LivingWorldAnimObject" literal.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <vector>

#include "Common/AsciiString.h"
#include "Common/System/xfer.h"

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer( Xfer &xfer ) = 0;
};

class LivingWorldAnimObject : public Snapshot
{
public:
	LivingWorldAnimObject( const AsciiString &name );
	virtual ~LivingWorldAnimObject();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() { return "LivingWorldAnimObject"; }
	virtual void DoXfer( Xfer &xfer );
	static const FieldParse m_fieldParseTable[];		// 0x01115B60

private:
	int m_zero04;
	int m_zero08;
	AsciiString m_model;
	bool m_hasAnim;
	bool m_xfer;
	unsigned char m_pad12[ 2 ];
	float m_orientAngle;
	AsciiString m_name;
	Coord3DBase m_position;
};

class BfmeLivingWorldManagerIcons
{
public:
	LivingWorldAnimObject *findAnimObject( const AsciiString &name );

private:
	char m_unmodelled[ 0x258 ];
	std::vector<LivingWorldAnimObject *> m_animObjects;
};

extern BfmeLivingWorldManagerIcons *TheLivingWorldManager;		// 0x012F706C

LivingWorldAnimObject::LivingWorldAnimObject( const AsciiString &name ) :
	m_hasAnim( false ),
	m_xfer( false ),
	m_orientAngle( 0 ),
	m_name( name )
{
	m_zero04 = 0;
	m_zero08 = 0;
}

LivingWorldAnimObject::~LivingWorldAnimObject()
{
}

void LivingWorldAnimObject::LoadPostProcess()
{
}

void LivingWorldAnimObject::DoXfer( Xfer &xfer )
{
	xfer == m_name;
	xfer == m_position;
}

LivingWorldAnimObject *BfmeLivingWorldManagerIcons::findAnimObject(
	const AsciiString &name )
{
	LivingWorldAnimObject *object = new LivingWorldAnimObject( name );
	m_animObjects.push_back( object );
	return object;
}

// ?parseLivingWorldAnimObject@@YAXPAVINI@@@Z
void parseLivingWorldAnimObject( INI *ini )
{
	const char *token = ini->getNextToken();
	if( !token )
		return;

	LivingWorldAnimObject *object = TheLivingWorldManager->findAnimObject( AsciiString( token ) );

	ini->initFromINI( object, LivingWorldAnimObject::m_fieldParseTable );
}
