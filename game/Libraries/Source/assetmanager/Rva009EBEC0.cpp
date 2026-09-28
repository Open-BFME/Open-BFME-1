// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x009EBEC0: return a counted AssetRegistry lookup by value.

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
	AssetReference &operator=( const AssetReference &that )
	{
		CountedAsset *object = that.m_object;
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
	CountedAsset *m_object;
};

class AssetRegistry
{
public:
	AssetReference Find_Asset( const char *name );
};

class AssetName
{
public:
	const char *Peek_Buffer() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}

private:
	const char *m_data;
};

extern AssetRegistry *g_theAssetRegistry;

AssetReference Rva009EBEC0( const AssetName &name )
{
	return g_theAssetRegistry
		? g_theAssetRegistry->Find_Asset( name.Peek_Buffer() )
		: AssetReference();
}
