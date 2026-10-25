// Retail 0x009EBDC0: return the registry's current counted asset.
// The dump's generated name is replaced by the recovered return-by-value ABI.

// Retail's AssetReference release calls TextureBaseClass::Release_Ref (0x009EB7A0).
class TextureBaseClass
{
public:
	void Release_Ref();
};

class CountedAsset;

class Rva009EBCE0AssetReference
{
	friend class AssetReference;
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

class AssetReference
{
public:
	AssetReference() : m_object( 0 ) {}
	AssetReference( const Rva009EBCE0AssetReference &that ) : m_object(static_cast<CountedAsset *>(that.m_object))
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
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

private:
	CountedAsset *m_object;
};

class AssetManagerImpl
{
public:
	AssetReference EnumAssets();
};

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

AssetReference Rva009EBDC0()
{
	// Retail state 1 destroys the lookup temporary through the handle at 5C640.
	// Preserve the canonical provider and the wrapper's public result type.
	typedef AssetReference (AssetManagerImpl::*CanonicalLookup)(void);
	typedef Rva009EBCE0AssetReference (AssetManagerImpl::*LookupView)(void);
	typedef char Rva009EEF10ResultWidth[sizeof(AssetReference) == sizeof(Rva009EBCE0AssetReference) ? 1 : -1];
	union { CanonicalLookup canonical; LookupView view; } lookup = { &AssetManagerImpl::EnumAssets };
	return g_theAssetRegistry
		? (((AssetManagerImpl *)g_theAssetRegistry)->*lookup.view)()
		: Rva009EBCE0AssetReference();
}
