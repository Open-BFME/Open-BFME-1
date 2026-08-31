// cl: /DNDEBUG /MD /EHsc
// Drawable::setEmoticon, retail 0x004149E0, 218 bytes.
//
// This is the Zero Hour source body with BFME's measured Drawable layout.  The
// matched AIGroup::groupSetEmoticon caller supplies the real identity, while
// the retail body fixes m_iconInfo at +0x2E0 and ICON_EMOTICON at slot eleven.

typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString;
class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *, Anim2DCollection *);
	virtual ~Anim2D();
	void deleteInstance() { delete this; }

private:
	unsigned char m_unmodelled[0x30];
};

class DrawableIconInfo
{
public:
	Anim2D *m_icon[14];
	UnsignedInt m_keepTillFrame[14];

	void killIcon(Int t)
	{
		if (m_icon[t])
		{
			m_icon[t]->deleteInstance();
			m_icon[t] = 0;
			m_keepTillFrame[t] = 0;
		}
	}
};

class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

class Drawable
{
public:
	DrawableIconInfo *getIconInfo();
	void clearEmoticon();
	void setEmoticon(const AsciiString &name, Int duration);
	void killIcon(Int t) { if (m_iconInfo) m_iconInfo->killIcon(t); }

private:
	unsigned char m_unmodelled[0x2E0];
	DrawableIconInfo *m_iconInfo;
};

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;

inline void Drawable::clearEmoticon()
{
	if (!m_iconInfo)
		return;

	killIcon(11);
}

void Drawable::setEmoticon(const AsciiString &name, Int duration)
{
	clearEmoticon();
	Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(name);
	if (animTemplate)
	{
		if (getIconInfo()->m_icon[11] == 0)
		{
			getIconInfo()->m_icon[11] = new Anim2D(animTemplate, TheAnim2DCollection);
			getIconInfo()->m_keepTillFrame[11] = duration >= 0 ? TheGameLogic->m_frame + duration : 0x3FFFFFFF;
		}
	}
}
