// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// Retail 0x009EBEC0: return a counted AssetManagerImpl lookup by value.

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
			m_object->Release_Ref();
		}
	}
	AssetReference &operator=( const AssetReference &that )
	{
		TextureBaseClass *object = that.m_object;
		if ( object )
		{
			++*(unsigned short *)((char *)object + 4);
		}
		if ( m_object )
		{
			m_object->Release_Ref();
		}
		m_object = object;
		return *this;
	}

private:
	TextureBaseClass *m_object;
};

class AssetManagerImpl
{
public:
	AssetReference Find_Asset( const char *name );
};

class AssetName
{
public:
	const char *Peek_Buffer() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	const char *m_data;
};

// Retail VA 0x0134FAAC is a zero-filled four-byte pointer. The matched
// Add_Prototype wrapper (RVA 0x009EBA40) and symbols.csv pin use this name
// and type; the guarded load at RVA 0x009EB940 also reads a DWORD.
// The recorded global (?g_theAssetRegistry@@3PAVAssetRegistry@@A) keeps its
// opaque pointee tag; callers cast it to the AssetManagerImpl it holds.
class AssetRegistry;
AssetRegistry *g_theAssetRegistry = 0;

AssetReference Rva009EBEC0( const AssetName &name )
{
	return g_theAssetRegistry
		? ((AssetManagerImpl *)g_theAssetRegistry)->Find_Asset( name.Peek_Buffer() )
		: AssetReference();
}
