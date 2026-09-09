// cl: /DNDEBUG /MD /EHsc

// BFME's body does not walk the ZH Texture_Hash directly.  It selects the
// texture asset stream, repeatedly obtains a counted AssetReference, and
// invalidates each returned texture through the virtual slot at +0x30.
// Rva009EBBC0 and Rva009EBDC0 are the already matched registry helpers at
// 0x009EBBC0 and 0x009EBDC0.  The small declarations below preserve the
// WW3D2 counted-texture ABI without importing the drifted ZH container types.

class TextureClass
{
public:
	void Add_Ref()
	{
		++*(unsigned short *)((char *)this + 4);
	}

	void Release_Ref();

	virtual void VTableSlot00();
	virtual void VTableSlot01();
	virtual void VTableSlot02();
	virtual void VTableSlot03();
	virtual void VTableSlot04();
	virtual void VTableSlot05();
	virtual void VTableSlot06();
	virtual void VTableSlot07();
	virtual void VTableSlot08();
	virtual void VTableSlot09();
	virtual void VTableSlot10();
	virtual void VTableSlot11();
	virtual void Invalidate();
};

class DummyPtrType;

class AssetReference
{
public:
	AssetReference() : m_object(0) {}

	AssetReference(const AssetReference &that) : m_object(that.m_object)
	{
		if (m_object)
			m_object->Add_Ref();
	}

	~AssetReference()
	{
		if (m_object)
			m_object->Release_Ref();
	}

	AssetReference &operator=(const AssetReference &that)
	{
		if (that.m_object)
			that.m_object->Add_Ref();
		if (m_object)
			m_object->Release_Ref();
		m_object = that.m_object;
		return *this;
	}

	operator const DummyPtrType *() const
	{
		return (DummyPtrType *)m_object;
	}

	TextureClass *operator->() const
	{
		return m_object;
	}

	TextureClass *m_object;
};

void Rva009EBBC0(int asset_type);
AssetReference Rva009EBDC0();

class __declspec(novtable) WW3D
{
public:
	static void _Invalidate_Textures();
};

// ?_Invalidate_Textures@WW3D@@SAXXZ
void WW3D::_Invalidate_Textures()
{
	Rva009EBBC0(0x544558);
	AssetReference texture;
	bool has_texture;
	for (;;)
	{
		has_texture = (texture = Rva009EBDC0()) != 0;
		if (has_texture && texture)
			texture->Invalidate();
		if (!has_texture)
			break;
	}
}
