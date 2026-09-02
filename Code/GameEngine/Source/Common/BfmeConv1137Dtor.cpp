// cl: /DNDEBUG /MD /EHsc

class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeTexHold1137
{
public:
	~BfmeTexHold1137(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

private:
	TextureClass *m_texture;
};

class MaterialPassClass
{
public:
	virtual ~MaterialPassClass(void);
};

class BfmeB1137 : public MaterialPassClass
{
public:
	virtual ~BfmeB1137(void);

private:
	unsigned char m_unmodelled[0x54];
	BfmeTexHold1137 m_tex0;
	BfmeTexHold1137 m_tex1;
	BfmeTexHold1137 m_tex2;
	BfmeTexHold1137 m_tex3;
};

// ??1BfmeB1137@@UAE@XZ
BfmeB1137::~BfmeB1137(void)
{
}
