// cl: /DNDEBUG /MD /EHsc
// readable body of ?setEmoticon@Drawable@@QAEXABVAsciiString@@H@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?setDrawableHidden@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
//
// Two setters for what a drawable shows: the emoticon above it at 0x004149E0
// and whether it is drawn at all at 0x0041A230. Both walk out of the same
// object and both had their own file and their own partial Drawable to do it,
// one describing 0x2E0 anonymous bytes before the icon info, the other 0x150
// before the draw-module array and another 0x25C before the hidden flag.
//
// The merged layout is those two statements laid over each other, and they do
// not overlap: the draw-module array is at +0x150, the icon info at +0x2E0 and
// the hidden flag at +0x3B0, with the runs between them still unexplained but
// now named for where they end rather than for how long they are.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
	virtual void setHidden(bool hidden);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	DrawableIconInfo *getIconInfo();
	// The whole of clearEmoticon: slot eleven, and only if there is an icon
	// info to clear it out of.
	void clearEmoticon() { if (m_iconInfo) killIcon(11); }
	void setEmoticon(const AsciiString &name, Int duration);
	void setDrawableHidden(bool hidden);
	void killIcon(Int t) { if (m_iconInfo) m_iconInfo->killIcon(t); }

private:
	void updateHiddenStatus();

	char m_pad000[0x150];
	DrawModule **m_drawModules;				// this+0x150
	char m_pad154[0x2E0 - 0x154];
	DrawableIconInfo *m_iconInfo;				// this+0x2E0
	char m_pad2E4[0x3B0 - 0x2E4];
	bool m_hidden;						// this+0x3B0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;

// ?setEmoticon@Drawable@@QAEXABVAsciiString@@H@Z
// Retail 0x004149E0, 218 bytes. Slot eleven is the emoticon icon. A duration
// below zero means it never expires -- the keep-till frame is pushed out to
// 0x3FFFFFFF rather than a flag being set.
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

// ?setDrawableHidden@Drawable@@QAEX_N@Z
// Retail 0x0041A230, 74 bytes. Every draw module is told, and only unhiding
// re-derives the status the other flags imply.
void Drawable::setDrawableHidden(bool hidden)
{
	if (m_hidden != hidden)
	{
		for (DrawModule **module = m_drawModules; *module; ++module)
			(*module)->setHidden(hidden);

		m_hidden = hidden;
		if (!hidden)
			updateHiddenStatus();
	}
}
