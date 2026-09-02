// ?d_006ecfe0@@YAXXZ
// partial score=0.7 date=2026-09-02
class SubtitleResetTexture
{
public:
	void Release_Ref();
};

class SubtitleResetRenderer
{
public:
	void reset();
	void setTexture(SubtitleResetTexture *texture)
	{
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = texture;
		m_currentBatch = m_texture ? -1 : 0;
	}

private:
	char m_head[0x4C];
	SubtitleResetTexture *m_texture;
	int m_currentBatch;
};

class SubtitleResetTemporary
{
public:
	SubtitleResetTemporary() : m_texture(0) {}
	~SubtitleResetTemporary()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

private:
	SubtitleResetTexture *m_texture;
};

class SubtitleResetDisplayString
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28();
	virtual void reset();
};

class SubtitleManagerResetView
{
public:
	void reset();

private:
	char m_head[0x164];
	SubtitleResetRenderer *m_renderer;
	char m_middle[0x134];
	SubtitleResetDisplayString **m_stringsStart;
	SubtitleResetDisplayString **m_stringsFinish;
	SubtitleResetDisplayString **m_stringsEnd;
};

void SubtitleManagerResetView::reset()
{
	{
		SubtitleResetTemporary temporary;
		m_renderer->setTexture(0);
	}
	m_renderer->reset();

	for (SubtitleResetDisplayString **it = m_stringsStart; it != m_stringsFinish; ++it)
		(*it)->reset();
}
