// ?bfmeAddXB@BfmeBaseXB@@QAEXPAVBfmeItemXB@@@Z
// partial score=0.7 date=2026-09-19
// ?bfmeAddXB@BfmeBaseXB@@QAEXPAVBfmeItemXB@@@Z
// Retail 0x00612640 (415 bytes).  BfmeHolderXB::bfmeOnXB reaches this body
// through ILT 0x0000E633.  The argument is the game's Xfer interface: its
// version, IsLoading, and integer slots are +0x28, +0x04, and +0x78.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Source

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

#include "Common/System/xfer.h"

class BfmeItemXB;

struct BfmeCoord3DXB
{
	float x;
	float y;
	float z;
};

class LivingWorldAnimObject
{
public:
	LivingWorldAnimObject( const AsciiString &name );
	virtual ~LivingWorldAnimObject();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer( Xfer &xfer );

	int m_zero04;
	int m_zero08;
	AsciiString m_model;
	bool m_hasAnim;
	bool m_xfer;
	unsigned char m_pad12[ 2 ];
	float m_orientAngle;
	AsciiString m_name;
	BfmeCoord3DXB m_position;
};

struct Rva00612430Item;

class Rva00612430Owner
{
public:
	Rva00612430Item *find( const AsciiString &name );
};

class BfmeSubDGE
{
public:
	void bfmeRunDGE( void *data );
};

class BfmeBaseXB
{
public:
	void bfmeAddXB( BfmeItemXB *item );

private:
	unsigned char m_prefix[ 0x258 ];
	LivingWorldAnimObject **m_begin;
	LivingWorldAnimObject **m_end;
};

void BfmeBaseXB::bfmeAddXB( BfmeItemXB *item )
{
	Xfer *xfer = reinterpret_cast<Xfer *>( item );
	Xfer::Version version;
	unsigned char set = 1;
	version.data[ 0 ] = set;
	version.data[ 1 ] = set;
	*xfer == version;

	if( xfer->IsLoading() )
	{
		int count;
		*xfer == count;
		for( int i = 0; i < count; ++i )
		{
			LivingWorldAnimObject object( AsciiString( "loadObject" ) );
			object.DoXfer( *xfer );
			BfmeSubDGE *target = reinterpret_cast<BfmeSubDGE *>(
				reinterpret_cast<Rva00612430Owner *>( this )->find( object.m_name ) );
			if( target )
				target->bfmeRunDGE( &object.m_position );
		}
		return;
	}

	int count = 0;
	for( unsigned int i = 0; i < static_cast<unsigned int>( m_end - m_begin ); ++i )
		if( m_begin[ i ]->m_xfer )
			++count;

	*xfer == count;
	for( unsigned int i = 0; i < static_cast<unsigned int>( m_end - m_begin ); ++i )
		if( m_begin[ i ]->m_xfer )
			m_begin[ i ]->DoXfer( *xfer );
}
