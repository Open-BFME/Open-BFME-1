// Retail 0x009EBDC0: return the registry's current counted asset.
// The dump's generated name is replaced by the recovered return-by-value ABI.

// Retail's AssetReference release calls TextureBaseClass::Release_Ref (0x009EB7A0).
class TextureBaseClass
{
public:
	void Release_Ref();
};

class CountedAsset;

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
	return g_theAssetRegistry
		? ((AssetManagerImpl *)g_theAssetRegistry)->EnumAssets()
		: AssetReference();
}
