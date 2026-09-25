// ?bfmeAddXB@BfmeBaseXB@@QAEXPAVBfmeItemXB@@@Z
// The matched BfmeHolderXB::bfmeOnXB caller reaches this body through ILT 0x0000E633.
// Retail ends at ret 4 at +0x19C, for a total size of 415 bytes.
// The constructor call at ILT 0x000089E0 names LivingWorldAnimObject, as its vtable and snapshot-name literal confirm.
// Retail body 0x0060A1D0 names BfmeSubDGE::bfmeRunDGE.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Source /Ireference/shims/stringinline

#include "StringInline.h"

#include "Common/System/xfer.h"

class BfmeItemXB;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

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
	Coord3DBase m_position;
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

class Rva00612640PointerRange
{
public:
	LivingWorldAnimObject **begin() const { return m_begin; }
	unsigned int size() const
	{
		return static_cast<unsigned int>( m_end - m_begin );
	}

private:
	LivingWorldAnimObject **m_begin;
	LivingWorldAnimObject **m_end;
};

class BfmeBaseXB
{
public:
	void bfmeAddXB( BfmeItemXB *item );

private:
	unsigned char m_prefix[ 0x258 ];
	Rva00612640PointerRange m_range006258;
};

void BfmeBaseXB::bfmeAddXB( BfmeItemXB *item )
{
	Xfer *xfer = reinterpret_cast<Xfer *>( item );
	{
		Xfer::Version version;
		unsigned char set = 1;
		version.data[ 0 ] = set;
		version.data[ 1 ] = set;
		*xfer == version;
	}

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

	{
		int count;
		count = 0;
		for( unsigned int i = 0; i < m_range006258.size(); ++i )
			if( m_range006258.begin()[ i ]->m_xfer )
				++count;

		*xfer == count;
	}
	for( unsigned int i = 0; i < m_range006258.size(); ++i )
		if( m_range006258.begin()[ i ]->m_xfer )
			m_range006258.begin()[ i ]->DoXfer( *xfer );
}
