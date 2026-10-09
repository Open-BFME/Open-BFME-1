// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// Retail RVA 0x009EBCE0: complete 211-byte counted registry lookup.
// The caller supplies hidden aggregate storage and one explicit name.
// The original registry/helper names are not independently established.

#include "../WWVegas/WW3D2/texture.h"

class AssetReference
{
public:
	AssetReference() : m_object( 0 ) {}
	AssetReference( const AssetReference &that ) : m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	~AssetReference()
	{
		if ( m_object )
		{
			((TextureBaseClass *)m_object)->Release_Ref();
		}
	}

	void *m_object;
};

class Rva009EBCE0AssetReference
{
public:
	Rva009EBCE0AssetReference() : m_object( 0 ) {}
	Rva009EBCE0AssetReference( const Rva009EBCE0AssetReference &that )
		: m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	Rva009EBCE0AssetReference( const AssetReference &that )
		: m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	~Rva009EBCE0AssetReference()
	{
		if ( m_object )
		{
			((TextureBaseClass *)m_object)->Release_Ref();
		}
	}

private:
	void *m_object;
};

class AssetManagerImpl
{
public:
	AssetReference Find_Asset( const char *name );
};

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype( const char *name )
{
	if ( !name )
	{
		return Rva009EBCE0AssetReference();
	}

	return g_theAssetRegistry
		? ((AssetManagerImpl *)g_theAssetRegistry)->Find_Asset( name )
		: AssetReference();
}
