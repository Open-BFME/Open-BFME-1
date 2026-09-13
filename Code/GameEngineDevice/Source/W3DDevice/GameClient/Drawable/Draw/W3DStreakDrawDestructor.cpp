// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DStreakDraw destructor at retail 0x0077D510.

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();

private:
	unsigned char m_pad[8];
};

class StreakDrawBase : public Rva0002B8C8TailBase
{
public:
	virtual ~StreakDrawBase() {}
};

class BFME3DScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void Add_Render_Object(void *object);
	virtual void Remove_Render_Object(void *object);
};

class W3DDisplay
{
public:
	static BFME3DScene *m_3DScene;
};

class BfmeStreakObject
{
public:
	virtual void Delete_This();
	int m_numRefs;

	void Release_Ref()
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}
};

class TextureClass
{
public:
	void Release_Ref();
};

class BFMETextureRef
{
public:
	TextureClass *m_texture;

	~BFMETextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

class W3DStreakDraw : public StreakDrawBase
{
public:
	virtual ~W3DStreakDraw();

private:
	BfmeStreakObject *m_streak;
	BFMETextureRef m_texture;
};

// ??1W3DStreakDraw@@UAE@XZ
W3DStreakDraw::~W3DStreakDraw()
{
	if (m_streak)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_streak);
		if (m_streak)
		{
			m_streak->Release_Ref();
			m_streak = 0;
		}
	}
}
