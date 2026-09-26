// ?Replace_Texture@MeshClass@@QAEXABVBfmeHandleCX@@0@Z
// partial score=0.83 date=2026-09-11
// cl: /DNDEBUG /MD /O2 /Ob2

class TextureClass
{
public:
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}

	void Release_Ref();
};

class BfmeHandleCX
{
public:
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.m_ptr != 0)
			other.m_ptr->Add_Ref();
		if (m_ptr != 0)
			m_ptr->Release_Ref();
		m_ptr = other.m_ptr;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const
	{
		return m_ptr == other.m_ptr;
	}

	TextureClass *m_ptr;
};

class Gen_007A0340
{
public:
	BfmeHandleCX bfmeGet(int index) const;
};

class TextureVector
{
public:
	void *m_vptr;
	int m_unused;
	BfmeHandleCX *m_vector;
	int m_max;
	int m_pad;
	int m_count;

	BfmeHandleCX &operator[](int index) { return m_vector[index]; }

};

class MaterialInfoClass
{
public:
	void Add_Ref()
	{
		++m_refs;
	}

	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}

	virtual void Delete_This();

	int Texture_Count() const { return m_textures.m_count; }

	BfmeHandleCX Get_Texture(int index) const;

	void Replace_Texture(int index, const BfmeHandleCX &texture)
	{
		m_textures[index] = texture;
	}

	public:
	int m_refs;
	char m_padding08[0x14];
	TextureVector m_textures;
};

class MeshModelClass
{
public:
	void Add_Ref()
	{
		++m_refs;
	}

	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}

	virtual void Delete_This();
	void Replace_Texture(const BfmeHandleCX &oldTexture, const BfmeHandleCX &newTexture);

private:
	int m_refs;
};

class MeshClassVirtuals
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual MaterialInfoClass *getMaterialInfo();
};

class MeshClass : public MeshClassVirtuals
{
public:
	void Replace_Texture(const BfmeHandleCX &oldTexture, const BfmeHandleCX &newTexture);

private:
	char m_padding04[0xc4];
	MeshModelClass *m_model;
};

// ?Replace_Texture@MeshClass@@QAEXABVBfmeHandleCX@@0@Z
void MeshClass::Replace_Texture(const BfmeHandleCX &oldTexture, const BfmeHandleCX &newTexture)
{
	if (m_model != 0)
		m_model->Add_Ref();
	MeshModelClass *model = m_model;

	MaterialInfoClass *material = getMaterialInfo();
	for (int index = 0; index < material->Texture_Count(); ++index)
	{
		TextureClass *tex_ptr = material->Get_Texture(index).m_ptr;
		TextureClass *old_ptr = oldTexture.m_ptr;
		bool matched = old_ptr == tex_ptr;
		if (tex_ptr != 0)
			tex_ptr->Release_Ref();
		if (matched)
		{
			model->Replace_Texture(oldTexture, newTexture);
			material->Replace_Texture(index, newTexture);
		}
	}

	material->Release_Ref();
	if (model != 0)
		model->Release_Ref();
}
