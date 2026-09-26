// Retail 0x009EBDC0: return the registry's current counted asset.
// The dump's generated name is replaced by the recovered return-by-value ABI.

class CountedAsset
{
public:
	void Release_Ref();
};

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

private:
	CountedAsset *m_object;
};

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset();
};

extern AssetRegistry *g_theAssetRegistry;

AssetReference Rva009EBDC0()
{
	return g_theAssetRegistry
		? g_theAssetRegistry->Get_Current_Asset()
		: AssetReference();
}
