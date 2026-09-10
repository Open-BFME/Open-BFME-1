// ?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBUCoord3D@@W4WorldAnimationOptions@@MM@Z
// partial score=0.7 date=2026-09-10
// ?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBUCoord3D@@W4WorldAnimationOptions@@MM@Z
// Full useful ABI attempt for retail 0x00443720..0x00443848 (296 bytes).
// The live TU used the same local views and body below. Retail allocates the
// 0x34-byte Anim2D block with global new, then calls the proven constructor
// ILT; the list is the retail InGameUI member at this+0x12c0 and reaches its
// proven ILT. These view classes do not claim retail identity.
// Remaining mismatch: clean MSVC orders the EH frame differently, allocates
// different callee-saved registers, and leaves the local aliases unresolved.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef float Real;

enum WorldAnimationOptions { WORLD_ANIM_NO_OPTIONS = 0 };
enum { LOGICFRAMES_PER_SECOND = 30 };

struct Coord3D { Real x; Real y; Real z; };
class Anim2DTemplate;
class Anim2DCollection;
class Anim2D;

class WorldAnimationData
{
public:
	Anim2D *m_anim;
	Coord3D m_worldPos;
	UnsignedInt m_expireFrame;
	WorldAnimationOptions m_options;
	Real m_zRisePerSecond;
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	UnsignedByte m_pad[0x3C];
	UnsignedInt m_frame;
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;
extern void j_00015b09();
extern void j_0002f2a7();

class BfmeAnim2DAllocView
{
public:
	BfmeAnim2DAllocView(Anim2DTemplate *, Anim2DCollection *);
	~BfmeAnim2DAllocView();
	UnsignedByte m_body[0x34];
};

class BfmeWorldAnimationListView
{
public:
	void push_front(WorldAnimationData *const &);
};

#pragma comment(linker, "/alternatename:??0BfmeAnim2DAllocView@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z=?j_00015b09@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeAnim2DAllocView@@QAE@XZ=??1Anim2D@@MAE@XZ")
#pragma comment(linker, "/alternatename:?push_front@BfmeWorldAnimationListView@@QAEXABQAVWorldAnimationData@@@Z=?j_0002f2a7@@YAXXZ")

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *, const Coord3D *,
		WorldAnimationOptions, Real, Real);

private:
	UnsignedByte m_pad[0x12C0];
};

void InGameUI::addWorldAnimation(Anim2DTemplate *animTemplate,
	const Coord3D *pos, WorldAnimationOptions options,
	Real durationInSeconds, Real zRisePerSecond)
{
	if (animTemplate == 0 || pos == 0 || durationInSeconds <= 0.0f)
		return;

	WorldAnimationData *wad = new WorldAnimationData;
	if (wad == 0)
		return;

	BfmeAnim2DAllocView *animView = new BfmeAnim2DAllocView(
		animTemplate, TheAnim2DCollection);
	Anim2D *anim = reinterpret_cast<Anim2D *>(animView);
	wad->m_anim = anim;
	wad->m_expireFrame = TheGameLogic->getFrame()
		+ (UnsignedInt)(durationInSeconds * (Real)LOGICFRAMES_PER_SECOND);
	wad->m_options = options;
	wad->m_worldPos = *pos;
	wad->m_zRisePerSecond = zRisePerSecond;

	reinterpret_cast<BfmeWorldAnimationListView *>(
		reinterpret_cast<UnsignedByte *>(this) + 0x12c0)->push_front(wad);
}
