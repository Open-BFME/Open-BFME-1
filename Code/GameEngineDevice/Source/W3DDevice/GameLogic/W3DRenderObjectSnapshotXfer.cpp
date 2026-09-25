// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?xfer@W3DRenderObjectSnapshot@@MAEXPAVXfer@@@Z
// Retail 0x006BD380, slot 3 of the W3DRenderObjectSnapshot vtable 0x0111D024 through ILT 0x0002DC45.

#include <string.h>

typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;

struct Vector4
{
	float m_values[ 4 ];

	Vector4 &operator=( const Vector4 &that )
	{
		m_values[ 0 ] = that.m_values[ 0 ];
		m_values[ 1 ] = that.m_values[ 1 ];
		m_values[ 2 ] = that.m_values[ 2 ];
		m_values[ 3 ] = that.m_values[ 3 ];
		return *this;
	}
};

struct Matrix3D
{
	Vector4 Row[ 3 ];

	Matrix3D &operator=( const Matrix3D &that )
	{
		Row[ 0 ] = that.Row[ 0 ];
		Row[ 1 ] = that.Row[ 1 ];
		Row[ 2 ] = that.Row[ 2 ];
		return *this;
	}
};

struct XferVersion
{
	XferVersion( UnsignedByte version ) : m_version( version ), m_currentVersion( version ) {}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	UnsignedByte m_pad[ 2 ];
};

class RetailLayoutString
{
public:
	void set( const char *text, Int length );

protected:
	void *m_text;
};

class BFMERetailAsciiString : private RetailLayoutString
{
public:
	BFMERetailAsciiString() { m_text = 0; }
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str( void ) const
	{
		return m_text ? (const char *)m_text + 8 : (const char *)0x0107388B;
	}

	void set( const char *text, Int length )
	{
		RetailLayoutString::set( text, length );
	}

private:
	void releaseBuffer( void );
};

class Xfer
{
public:
	virtual void slot00( void );
	virtual Bool isLoading( void );
	virtual Bool isSaving( void );
	virtual void slot03( void );
	virtual void slot04( void );
	virtual void slot05( void );
	virtual void slot06( void );
	virtual void slot07( void );
	virtual void slot08( void );
	virtual void slot09( void );
	virtual void xferVersion( XferVersion *version );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual void slot13( void );
	virtual void slot14( void );
	virtual void slot15( void );
	virtual void slot16( void );
	virtual void slot17( void );
	virtual void slot18( void );
	virtual void slot19( void );
	virtual void slot20( void );
	virtual void slot21( void );
	virtual void slot22( void );
	virtual void slot23( void );
	virtual void slot24( void );
	virtual void slot25( void );
	virtual void xferAsciiString( BFMERetailAsciiString *value );
	virtual void slot27( void );
	virtual void slot28( void );
	virtual void slot29( void );
	virtual void xferInt( Int *value );
	virtual void slot31( void );
	virtual void slot32( void );
	virtual void slot33( void );
	virtual void slot34( void );
	virtual void xferBool( Bool *value );
};

#define BFME_RENDER_SLOT( n ) virtual void slot##n( void );

class RenderObjClass
{
public:
	virtual void Delete_This( void );
	virtual void slot01( void );
	virtual RenderObjClass *Clone( void ) const;
	virtual Int Class_ID( void ) const;
	BFME_RENDER_SLOT( 04 )
	BFME_RENDER_SLOT( 05 )
	virtual const char *Get_Name( void ) const;
	BFME_RENDER_SLOT( 07 )
	BFME_RENDER_SLOT( 08 )
	BFME_RENDER_SLOT( 09 )
	BFME_RENDER_SLOT( 10 )
	BFME_RENDER_SLOT( 11 )
	BFME_RENDER_SLOT( 12 )
	BFME_RENDER_SLOT( 13 )
	BFME_RENDER_SLOT( 14 )
	BFME_RENDER_SLOT( 15 )
	virtual void Remove( void );
	BFME_RENDER_SLOT( 17 )
	BFME_RENDER_SLOT( 18 )
	BFME_RENDER_SLOT( 19 )
	virtual const Matrix3D &Get_Transform( void ) const;
	virtual void Set_Transform( const Matrix3D &transform );
	BFME_RENDER_SLOT( 22 )
	BFME_RENDER_SLOT( 23 )
	BFME_RENDER_SLOT( 24 )
	BFME_RENDER_SLOT( 25 )
	BFME_RENDER_SLOT( 26 )
	virtual Int Get_Num_Sub_Objects( void ) const;
	BFME_RENDER_SLOT( 28 )
	virtual RenderObjClass *Get_Sub_Object( Int index ) const;
	BFME_RENDER_SLOT( 30 )
	virtual RenderObjClass *Get_Sub_Object_By_Name( const char *name, Int *index ) const;
	BFME_RENDER_SLOT( 32 )
	BFME_RENDER_SLOT( 33 )
	BFME_RENDER_SLOT( 34 )
	virtual void Set_User_Data( void *data, Bool recursive = false );
	BFME_RENDER_SLOT( 36 )
	BFME_RENDER_SLOT( 37 )
	BFME_RENDER_SLOT( 38 )
	BFME_RENDER_SLOT( 39 )
	BFME_RENDER_SLOT( 40 )
	BFME_RENDER_SLOT( 41 )
	BFME_RENDER_SLOT( 42 )
	BFME_RENDER_SLOT( 43 )
	BFME_RENDER_SLOT( 44 )
	BFME_RENDER_SLOT( 45 )
	BFME_RENDER_SLOT( 46 )
	BFME_RENDER_SLOT( 47 )
	BFME_RENDER_SLOT( 48 )
	BFME_RENDER_SLOT( 49 )
	BFME_RENDER_SLOT( 50 )
	BFME_RENDER_SLOT( 51 )
	BFME_RENDER_SLOT( 52 )
	BFME_RENDER_SLOT( 53 )
	BFME_RENDER_SLOT( 54 )
	BFME_RENDER_SLOT( 55 )
	BFME_RENDER_SLOT( 56 )
	BFME_RENDER_SLOT( 57 )
	BFME_RENDER_SLOT( 58 )
	BFME_RENDER_SLOT( 59 )
	BFME_RENDER_SLOT( 60 )
	BFME_RENDER_SLOT( 61 )
	BFME_RENDER_SLOT( 62 )
	BFME_RENDER_SLOT( 63 )
	BFME_RENDER_SLOT( 64 )
	BFME_RENDER_SLOT( 65 )
	BFME_RENDER_SLOT( 66 )
	BFME_RENDER_SLOT( 67 )
	BFME_RENDER_SLOT( 68 )
	BFME_RENDER_SLOT( 69 )
	BFME_RENDER_SLOT( 70 )
	BFME_RENDER_SLOT( 71 )
	BFME_RENDER_SLOT( 72 )
	BFME_RENDER_SLOT( 73 )
	BFME_RENDER_SLOT( 74 )
	BFME_RENDER_SLOT( 75 )
	BFME_RENDER_SLOT( 76 )
	BFME_RENDER_SLOT( 77 )
	BFME_RENDER_SLOT( 78 )
	BFME_RENDER_SLOT( 79 )
	BFME_RENDER_SLOT( 80 )
	BFME_RENDER_SLOT( 81 )
	BFME_RENDER_SLOT( 82 )
	BFME_RENDER_SLOT( 83 )
	BFME_RENDER_SLOT( 84 )
	BFME_RENDER_SLOT( 85 )
	BFME_RENDER_SLOT( 86 )
	BFME_RENDER_SLOT( 87 )
	BFME_RENDER_SLOT( 88 )
	BFME_RENDER_SLOT( 89 )
	BFME_RENDER_SLOT( 90 )
	BFME_RENDER_SLOT( 91 )
	BFME_RENDER_SLOT( 92 )
	BFME_RENDER_SLOT( 93 )
	BFME_RENDER_SLOT( 94 )
	BFME_RENDER_SLOT( 95 )
	virtual Int Is_Not_Hidden_At_All( void );
	BFME_RENDER_SLOT( 97 )
	BFME_RENDER_SLOT( 98 )
	BFME_RENDER_SLOT( 99 )
	virtual void Set_Hidden( Int onoff );
	BFME_RENDER_SLOT( 101 )
	BFME_RENDER_SLOT( 102 )
	BFME_RENDER_SLOT( 103 )
	BFME_RENDER_SLOT( 104 )
	BFME_RENDER_SLOT( 105 )
	BFME_RENDER_SLOT( 106 )
	BFME_RENDER_SLOT( 107 )
	BFME_RENDER_SLOT( 108 )
	BFME_RENDER_SLOT( 109 )
	BFME_RENDER_SLOT( 110 )
	BFME_RENDER_SLOT( 111 )
	BFME_RENDER_SLOT( 112 )
	BFME_RENDER_SLOT( 113 )
	BFME_RENDER_SLOT( 114 )
	BFME_RENDER_SLOT( 115 )
	BFME_RENDER_SLOT( 116 )
	BFME_RENDER_SLOT( 117 )
	BFME_RENDER_SLOT( 118 )
	BFME_RENDER_SLOT( 119 )
	BFME_RENDER_SLOT( 120 )
	BFME_RENDER_SLOT( 121 )
	BFME_RENDER_SLOT( 122 )
	BFME_RENDER_SLOT( 123 )
	BFME_RENDER_SLOT( 124 )
	BFME_RENDER_SLOT( 125 )
	BFME_RENDER_SLOT( 126 )
	BFME_RENDER_SLOT( 127 )
	BFME_RENDER_SLOT( 128 )
	BFME_RENDER_SLOT( 129 )
	BFME_RENDER_SLOT( 130 )

	unsigned int m_refCount;
	unsigned char m_pad08[ 8 ];
	unsigned int Bits;
	unsigned char m_pad14[ 4 ];
	Matrix3D m_transform;
	unsigned char m_pad48[ 4 ];
	unsigned int m_objectColor;

	void Release_Ref( void )
	{
		if( --m_refCount == 0 )
			Delete_This();
	}

	void Set_Sub_Object_Transforms_Dirty( Bool onoff )
	{
		if( onoff )
			Bits |= 0x00200000;
		else
			Bits &= 0xFFDFFFFF;
	}
};

#undef BFME_RENDER_SLOT

class HLodClass : public RenderObjClass
{
public:
	void Friend_Set_Hierarchy_Valid( Bool valid )
	{
		m_hierarchyValid = valid;
	}

private:
	unsigned char m_pad50[ 0xA8 ];
	unsigned char m_hierarchyValid;
};

class Snapshot
{
public:
	virtual void anchor( void );
};

class W3DRenderObjectSnapshot : public Snapshot
{
protected:
	virtual void xfer( Xfer *xfer );

public:
	RenderObjClass *m_robj;
	W3DRenderObjectSnapshot *m_next;
};

extern void BfmeParticleSystemXferMatrix( Xfer &xfer, void *value );

void W3DRenderObjectSnapshot::xfer( Xfer *const xfer )
{
	XferVersion version( 1 );
	xfer->xferVersion( &version );
	RenderObjClass *transformObject = m_robj;

	Matrix3D transform;
	transformObject->Get_Transform();
	transform = transformObject->m_transform;
	BfmeParticleSystemXferMatrix( *xfer, &transform );
	if( xfer->isLoading() )
		m_robj->Set_Transform( transform );

	Int subObjectCount = m_robj->Get_Num_Sub_Objects();
	xfer->xferInt( &subObjectCount );

	Bool visible;
	RenderObjClass *subObject;
	BFMERetailAsciiString subObjectName;
	for( Int i = 0; i < subObjectCount; ++i )
	{
		if( xfer->isSaving() )
		{
			subObject = m_robj->Get_Sub_Object( i );
			const char *name = subObject->Get_Name();
			Int length = name ? (Int)strlen( name ) : 0;
			subObjectName.set( name, length );
			xfer->xferAsciiString( &subObjectName );
		}
		else
		{
			xfer->xferAsciiString( &subObjectName );
			subObject = m_robj->Get_Sub_Object_By_Name( subObjectName.str(), 0 );
		}

		if( subObject )
			visible = subObject->Is_Not_Hidden_At_All() != 0;
		xfer->xferBool( &visible );
		if( subObject && xfer->isLoading() )
			subObject->Set_Hidden( !visible );

		if( subObject )
		{
			subObject->Get_Transform();
			transform = subObject->m_transform;
		}
		BfmeParticleSystemXferMatrix( *xfer, &transform );
		if( subObject && xfer->isLoading() )
			subObject->Set_Transform( transform );

		if( subObject && subObject->Class_ID() == 0x19 )
			((HLodClass *)subObject)->Friend_Set_Hierarchy_Valid( true );

		if( subObject )
			subObject->Release_Ref();
	}

	m_robj->Set_Sub_Object_Transforms_Dirty( false );
}
