// ?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBUCoord3D@@W4WorldAnimationOptions@@MM@Z
// partial score=0.68 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// InGameUI::addWorldAnimation — retail 0x00443720 (296B).
// ZH walk: reject null template/pos or non-positive duration, NEW WorldAnimationData
// (0x1C, inline-zeroed), new Anim2D(template, TheAnim2DCollection), fill fields,
// push_front onto this+0x12C0.
//
// Wall: ours 294B. Retail EH is push -1 / push handler / mov eax,fs:[0];
// ours is mov eax,fs:[0] / push -1 / push 0. Retail ebp=template, ebx=pos,
// edi=0 CSE, esi=wad. Do not edit InGameUI.h (vtable shim breaks
// disregardDrawable @ slot 0xC8).

typedef unsigned int UnsignedInt;
typedef float Real;

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0
};

enum
{
	LOGICFRAMES_PER_SECOND = 30
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collection);
};

class WorldAnimationData
{
public:
	Anim2D *m_anim;
	Coord3D m_worldPos;
	UnsignedInt m_expireFrame;
	WorldAnimationOptions m_options;
	Real m_zRisePerSecond;
};

class WorldAnimationList
{
public:
	void push_front(WorldAnimationData *const &wad);
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
		WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond);

private:
	unsigned char m_pad[0x12C0];
	WorldAnimationList m_worldAnimationList;
};

// ?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBUCoord3D@@W4WorldAnimationOptions@@MM@Z
void InGameUI::addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
	WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond)
{
	if (animTemplate == 0 || pos == 0 || durationInSeconds <= 0.0f)
		return;

	WorldAnimationData *wad = new WorldAnimationData;
	if (wad == 0)
		return;
	wad->m_anim = 0;
	wad->m_worldPos.x = 0;
	wad->m_worldPos.y = 0;
	wad->m_worldPos.z = 0;
	wad->m_expireFrame = 0;
	wad->m_options = WORLD_ANIM_NO_OPTIONS;
	wad->m_zRisePerSecond = 0;

	Anim2D *anim = new Anim2D(animTemplate, TheAnim2DCollection);
	wad->m_anim = anim;
	wad->m_expireFrame = TheGameLogic->getFrame() + (UnsignedInt)(durationInSeconds * (Real)LOGICFRAMES_PER_SECOND);
	wad->m_options = options;
	wad->m_worldPos = *pos;
	wad->m_zRisePerSecond = zRisePerSecond;
	m_worldAnimationList.push_front(wad);
}
