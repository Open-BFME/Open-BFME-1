// ?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NW4PickType@@@Z
// partial score=0.78 date=2026-09-09
// ?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NW4PickType@@@Z
// BFME reconstruction scratch for retail 0x00745370, full boundary 793 bytes.
//
// This is deliberately kept out of Code/: 0x007129F0 and 0x008F7440 are
// address-derived callees whose class names are not proven.  The concrete
// lever here is the BFME W3DView ABI and the retail control flow: the five
// pick-registry keys, DrawableInfo's +4 drawable, the visibility gate, the
// terrain/shroud filter, and the GameClient notification tail.  It is not a
// claim that either unknown address has the facade name below.

#include "Common/GlobalData.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameLogic/TerrainLogic.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DView.h"
#include "WW3D2/Coltype.h"

// These two local facades are address-derived only.  Their declarations keep
// the thiscall register and stack layout visible while their identity remains
// intentionally unresolved for a later owner-backed conversion.
class RetailPickRegistryAt007129F0
{
public:
	bool query(void **out, int one, unsigned int key);
};

class RetailTerrainQueryAt001A6280
{
public:
	struct Result
	{
		unsigned char pad00[0x0c];
		void *field0c;
		unsigned char pad10[0x1c];
		unsigned char flag2c;
		unsigned char flag2d;
	};
	Result *query(void *out);
};

extern RetailPickRegistryAt007129F0 *g_bfmeGlobPB;
extern RetailTerrainQueryAt001A6280 *TheTerrainLogic007;
extern PartitionManager *TheShroudManager007;
extern GameClient *TheGameClient007;

// The retail body calls these through the existing ILT thunks.  The aliases
// are intentionally absent here: this file is a source-shape handoff, not a
// new identity or a production pin.
extern "C" int retailShroudStatus007(void *shroud, int player, void *terrain);
extern "C" void retailNotifyPick007(GameClient *client, unsigned int id);

static Drawable *bfmeSpecialPick(PickType pickType)
{
	if ((pickType & 0x100) == 0 || g_bfmeGlobPB == 0)
		return 0;

	void *specialRaw = 0;
	if (g_bfmeGlobPB->query(&specialRaw, 1, 0x184) && specialRaw == 0)
		g_bfmeGlobPB->query(&specialRaw, 1, 0x104);
	if (specialRaw == 0)
		g_bfmeGlobPB->query(&specialRaw, 1, 0x84);
	if (specialRaw == 0)
		g_bfmeGlobPB->query(&specialRaw, 1, 0x14);
	if (specialRaw == 0)
		g_bfmeGlobPB->query(&specialRaw, 0, (unsigned int)pickType);
	RenderObjClass *special = (RenderObjClass *)specialRaw;

	if (special == 0)
		return 0;

	DrawableInfo *info = (DrawableInfo *)special->Get_User_Data();
	Drawable *draw = info ? info->m_drawable : 0;
	if (draw)
		draw = (Drawable *)(long)draw->bfmeVisibilityGate();
	return draw;
}

Drawable *pickDrawableBFMEAttempt(W3DView *view, const ICoord2D *screen,
	Bool forceAttack, PickType pickType)
{
	RenderObjClass *renderObj = 0;
	Drawable *draw = 0;

	if (screen == 0)
		return 0;

	GameWindow *window = 0;
	if (TheWindowManager)
		window = TheWindowManager->getWindowUnderCursor(screen->x, screen->y);
	while (window)
	{
		if (!BitTest(window->winGetStatus(), WIN_STATUS_SEE_THRU))
			return 0;
		window = window->winGetParent();
	}

	Vector3 rayStart, rayEnd;
	view->getPickRay(screen, &rayStart, &rayEnd);
	LineSegClass lineseg;
	lineseg.Set(rayStart, rayEnd);
	CastResultStruct result;
	if (forceAttack)
		result.ComputeContactPoint = true;
	RayCollisionTestClass raytest(lineseg, &result, COLL_TYPE_ALL, false, false);

	// Retail checks the BFME pick registry before the normal scene result.
	// The registry can supply a render object whose DrawableInfo is then
	// filtered by the proven Drawable visibility-gate call.
	if (pickType & 0x100)
	{
		if ((draw = bfmeSpecialPick(pickType)) != 0)
			return draw;
	}

	if (W3DDisplay::m_3DScene->castRay(raytest, false, (Int)pickType))
		renderObj = raytest.CollidedRenderObj;

	// 0x001A6280 is the retail terrain query.  Its class ownership is not
	// proven, so keep the call as a neutral address-derived facade in scratch.
	if (renderObj == 0 && TheTerrainLogic007)
	{
		RetailTerrainQueryAt001A6280::Result *terrainResult =
			TheTerrainLogic007->query(&raytest);
		if (terrainResult == 0 || terrainResult->field0c == 0)
			return 0;
		int player = 0;
		if (ThePlayers && ThePlayers->getLocalPlayer())
			player = ThePlayers->getLocalPlayer()->getPlayerIndex();
		if (TheShroudManager007 &&
			retailShroudStatus007(TheShroudManager007, player, terrainResult) == 4)
			return 0;
		// The retail tail emits one of four notification ids based on the
		// two result bytes at +0x2c/+0x2d.
		unsigned int id = 0x05f5e0fe;
		if (terrainResult->flag2c)
			id = terrainResult->flag2d ? 0x05f5e0ff : 0x05f5e0fc;
		else if (terrainResult->flag2d)
			id = 0x05f5e0fd;
		if (TheGameClient007)
			retailNotifyPick007(TheGameClient007, id);
	}

	if (renderObj)
	{
		DrawableInfo *info = (DrawableInfo *)renderObj->Get_User_Data();
		if (info)
			draw = info->m_drawable;
	}
	return draw;
}
