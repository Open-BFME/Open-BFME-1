// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/GameEngine/Source/Common
// stlport
//
// W3DRadar::renderObjectListRva006C43F0, retail 0x006C43F0, 1296 bytes (ret 0Ch).
// Zero Hour's W3DRadar::renderObjectList walks the radar object list and plots
// each visible object into the radar texture; this is BFME's version of that
// body (readable reference:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp).
// Its only caller, 0x006C4A50, calls it twice, for the object list and for the
// local object list, as Zero Hour's W3DRadar::draw does.
//
// Why this name carries its address:
// - BFME's third parameter is a packed Color, not Zero Hour's Bool calcHero. It
//   goes straight to the colour multiplier Rva006C0890(Color, Color) as a full
//   dword. A bool parameter forces a movzx and 325 byte diffs.
// - ilt_oracle contradicts every renderObjectList decoration tried: the
//   W3DRadar, Radar and Rva006C4A50Owner classes; QAE/IAE/AAE/UAE/MAE/EAE; const
//   and non-const list and texture views; and _N/H/I/Bool for the third
//   parameter.
// So the role is supported but the decorated name is not.
//
// Shape notes:
// - The two KindOf tests read ThingTemplate's 192-bit mask at +0xC8 through the
//   inline BitFlags<192>::test chain, as Zero Hour's ThingTemplate::isKindOf
//   does. The open-coded mask spelling emits the same test instructions but
//   swaps two reloads after the first circle loop (+0x394).
// - rva006C42B0, rva006C2A20, rva006C2DD0 and rva006C1D00 are TU-private
//   copies of bodies whose ledger rows live in W3DRadar.cpp,
//   W3DRadarAlphaBlob6x6.cpp, W3DRadarBlendBlip2x2.cpp and
//   W3DRadarScanlineEndpoints.cpp. Keeping them static and visible lets MSVC
//   choose the private register conventions retail uses at each call.
//   Handoff: targets/game/reverse/attempt_support/20261107-006c43f0-kindof-bitflags-reload-order.md
#define BFME_STLP_NODE_ALLOC 1
#define Matrix4x4 Matrix4
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Radar.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/GameClient.h"
#include "GameClient/Color.h"
#include "discrete_circle.h"
#include <algorithm>

inline const ThingTemplate *Thing::getTemplate() const {
 return m_template;
}
class SurfaceClass {
public:
 void *Lock(int *pitch, int left, int top, int right, int bottom);
 void Unlock();
 void DrawPixel(unsigned x, unsigned y, unsigned color);
};
class W3DRadarResetSurface {
public:
 ~W3DRadarResetSurface();
private:
 void *m_surface;
};
class W3DRadarResetTexture {
public:
 W3DRadarResetSurface getSurfaceLevel();
 void *texture;
};
class Rva000DF7F0 { public: int inactive() const; };
class CastleBehavior { public: float rva0036F2D0(const Player *player); };
unsigned rva00107A50MakeColor(void *colorData);
int Rva006C0890(int color, int modulation);
extern int g_Va012F7F44;

inline Bool legalRadarPoint(int x, int y) {
 if (x < 0 || y < 0 || x >= 128 || y >= 128) return false;
 return true;
}
class BFMEObjectStealthQuery : public Object
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

// The private caller supplies Object in ESI and Color storage in EBX.
// TU visibility allows MSVC to select those registers.
static __declspec(noinline) Bool rva006C42B0(
	const Object *object, Color *color)
{
	const BFMEObjectStealthQuery *stealthQuery =
		static_cast<const BFMEObjectStealthQuery *>(object);
	if (!stealthQuery->isStealthedAndUndetected(NULL))
		return TRUE;

	if (object->getControllingPlayer() != ThePlayerList->getLocalPlayer() &&
		!object->testStatus(OBJECT_STATUS_DETECTED))
	{
		return FALSE;
	}

	UnsignedByte red;
	UnsignedByte green;
	UnsignedByte blue;
	UnsignedByte alpha;
	GameGetColorComponents(*color, &red, &green, &blue, &alpha);

	const UnsignedInt framesForTransition = 60;
	const UnsignedInt halfTransition = framesForTransition / 2;
	const UnsignedInt alphaRange = 191;
	UnsignedInt frame = TheGameClient->getFrame() % framesForTransition;
	if (frame >= halfTransition)
		alpha = (UnsignedByte)(255 - ((frame - halfTransition) * alphaRange) / halfTransition);
	else
		alpha = (UnsignedByte)(64 + (frame * alphaRange) / halfTransition);

	*color = GameMakeColor(red, green, blue, alpha);
	return TRUE;
}

Color Rva006C13E0(Color *color, Color source, UnsignedByte alpha);

class SurfaceLock006C13D0
{
public:
	SurfaceLock006C13D0(SurfaceClass *surface, void *&bits, int *pitch,
		int left, int top, int right, int bottom) : m_surface(surface)
	{
		bits = m_surface->Lock(pitch, left, top, right, bottom);
	}
	~SurfaceLock006C13D0() { m_surface->Unlock(); }

private:
	SurfaceClass *m_surface;
};

static __declspec(noinline) void rva006C2A20(SurfaceClass *surface, Int width, Int height,
	Int x, Int y, Color color, const UnsignedByte *alpha)
{
	Int blobLeft = x - 3;
	Int blobTop = y - 3;
	Int blobRight = x + 3;
	Int blobBottom = y + 3;
	Int left = (blobLeft > 0) ? blobLeft : 0;
	Int startY = (blobTop > 0) ? blobTop : 0;
	Int right = (blobRight < width) ? blobRight : width;
	Int endY = (blobBottom < height) ? blobBottom : height;

	int pitch;
	void *bits;
	SurfaceLock006C13D0 lock(surface, bits, &pitch, left, startY, right, endY);
	if (bits)
	{
		Int row;
		Int col;
		for (row = startY; row < y && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			for (col = left; col < x && col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
		if (y < endY)
		for (row = std::max(y, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			for (col = left; col < x && col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
	}
}

class SurfaceLock006C2DD0
{
public:
	SurfaceLock006C2DD0(SurfaceClass *surface, void *&bits, int *pitch,
		int left, int top, int right, int bottom)
		: m_surface(surface)
	{
		bits = surface->Lock(pitch, left, top, right, bottom);
	}
	~SurfaceLock006C2DD0() { m_surface->Unlock(); }

	SurfaceClass *m_surface;
};

static __declspec(noinline) void rva006C2DD0(SurfaceClass *surface, int width, int height, int x, int y,
	int color, const unsigned char alpha[][2])
{
	int x0 = x - 2;
	int x1 = x + 2;
	int y0 = y - 2;
	int y1 = y + 2;
	int left = __max(x0, 0);
	int top = __max(y0, 0);
	int right = __min(x1, width);
	int bottom = __min(y1, height);
	int pitch;
	void *bits;
	SurfaceLock006C2DD0 lock(surface, bits, &pitch, left, top, right, bottom);
	if (bits == NULL)
		return;

	int i, j, dy;

	// upper half: rows above the centre, alpha rows counting in from the edge
	for (j = top; j < y && j < bottom; ++j)
	{
		int *row = (int *)((char *)bits + (j - top) * pitch);
		dy = j - y0;
		for (i = left; i < x && i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}

	if (y >= bottom)
		return;

	// lower half: the same table mirrored
	for (j = std::max(y, top); j < bottom; ++j)
	{
		dy = y1 - j - 1;
		int *row = (int *)((char *)bits + (j - top) * pitch);
		for (i = left; i < x && i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}
}


static __declspec(noinline) void rva006C1D00(int xStart, int xEnd, int y, SurfaceClass *surface) {
 if (legalRadarPoint(xStart,y)) surface->DrawPixel(xStart, y, g_Va012F7F44);
 if (legalRadarPoint(xEnd,y)) surface->DrawPixel(xEnd, y, g_Va012F7F44);
}
static const unsigned char s_blipAlpha006C2DD0[2][2] = {{0, 0x4a}, {0x4a, 0xff}};
static const unsigned char s_blobAlpha006C2A20[9] = {0x03,0x24,0x45,0x24,0x4f,0x4f,0x45,0x4f,0x4f};
// BFME ThingTemplate keeps its 192-bit KindOf mask at +0xC8 (word 2 = +0xD0, word 3 = +0xD4).
// The test goes through the inline BitFlags<192>::test -> bitset::test chain, as
// Zero Hour ThingTemplate::isKindOf does; the open-coded mask spelling emits the
// same instructions but leaves the loop-exit reloads at +0x394 in the wrong order.
struct BfmeTemplateKindView {
 char m_pad[0xc8];
 BitFlags<192> m_kindof;
 inline Bool isKindOf(Int t) const { return m_kindof.test(t); }
};
// W3DRadar.cpp: BFME inserts two KindOf entries before AIRCRAFT, making DISGUISER bit 89.
static const Int BFME_KINDOF_DISGUISER = 89;
// Bit 119 (word +0xD4, 0x00800000) selects the CastleBehavior path; its name is unproven.
static const Int BFME_KINDOF_BIT119 = 119;
class W3DRadar {
protected:
 void renderObjectListRva006C43F0(const RadarObject *listHead, W3DRadarResetTexture *texture, Color modulation);
 template<class T> __forceinline T &at(int offset) { return *(T*)((char*)this + offset); }
};
// ?renderObjectListRva006C43F0@W3DRadar@@IAEXPBVRadarObject@@PAVW3DRadarResetTexture@@H@Z
void W3DRadar::renderObjectListRva006C43F0(const RadarObject *listHead, W3DRadarResetTexture *texture, Color modulation) {
 if (listHead == NULL || texture->texture == NULL) return;
 W3DRadarResetSurface surface = texture->getSurfaceLevel();
 SurfaceClass *surfaceClass = (SurfaceClass*)&surface;
 Player *player = ThePlayerList->getLocalPlayer();
 int playerIndex = 0;
 if (player) playerIndex = player->getPlayerIndex();
 float radarWidth = 128.0f / (at<float>(0x1448) - at<float>(0x143c));
 float radarHeight = 128.0f / (at<float>(0x144c) - at<float>(0x1440));
 for (const RadarObject *rObj = (const RadarObject*)listHead; rObj; rObj = *(const RadarObject**)((const char*)rObj + 8)) {
  if (rObj->isTemporarilyHidden()) continue;
  const Object *obj = *(const Object**)((const char*)rObj + 4);
  Bool disguised = ((const BfmeTemplateKindView *)obj->getTemplate())->isKindOf(BFME_KINDOF_BIT119);
  Bool skip = obj->getShroudedStatus(playerIndex) > OBJECTSHROUD_PARTIAL_CLEAR;
  if (!disguised) {
   if (skip) continue;
   if (obj->getRadarPriority() == RADAR_PRIORITY_LOCAL_UNIT_ONLY && obj->getControllingPlayer() != ThePlayerList->getLocalPlayer() && (unsigned char)((Rva000DF7F0*)ThePlayerList)->inactive()) continue;
  }
  ICoord2D radarPoint;
  radarPoint.x = radarWidth * obj->getPosition()->x;
  radarPoint.y = radarHeight * obj->getPosition()->y;
  Color c;
  if (!skip) c = *(const Color*)((const char*)rObj + 0xc);
  else {
   if (!at<int>(0x14ac)) {
    Player *field14 = *(Player**)((char*)ThePlayerList + 0x14);
    if (!field14) continue;
    void *colorData = *(void**)((char*)field14 + 0x1c4);
    at<int>(0x14ac) = rva00107A50MakeColor(colorData);
   }
   c = at<int>(0x14ac);
  }
  c = Rva006C0890(c, modulation);
  if (((const BfmeTemplateKindView *)obj->getTemplate())->isKindOf(BFME_KINDOF_DISGUISER)) {
   if (!rva006C42B0(obj, &c)) continue;
   UnsignedByte red, green, blue, alpha;
   GameGetColorComponents(c, &red, &green, &blue, &alpha);
   red = (UnsignedByte)(red + ((255-red)>>1));
   green = (UnsignedByte)(green + ((255-green)>>1));
   blue = (UnsignedByte)(blue + ((255-blue)>>1));
   int lightColor = GameMakeColor(red, green, blue, alpha);
   rva006C2A20(surfaceClass, at<int>(0x14a4), at<int>(0x14a8), radarPoint.x, radarPoint.y, c, s_blobAlpha006C2A20);
   rva006C2DD0(surfaceClass, at<int>(0x14a4), at<int>(0x14a8), radarPoint.x, radarPoint.y, lightColor, s_blipAlpha006C2DD0);
  } else if (disguised) {
   static NameKeyType castleKey = TheNameKeyGenerator->nameToKey("CastleBehavior");
   CastleBehavior *castle = (CastleBehavior*)obj->findUpdateModule(castleKey);
   if (!castle) continue;
   DiscreteCircle circle(radarPoint.x, radarPoint.y, (int)(castle->rva0036F2D0(obj->getControllingPlayer()) * radarWidth * 0.5f + 2.0f));
   g_Va012F7F44 = c;
   int yDoubled = radarPoint.y * 2;
   const VecHorzLine &edges = circle.getEdges();
   VecHorzLine::const_iterator longest = edges.begin();
   for (VecHorzLine::const_iterator it = edges.begin(); it != edges.end(); ++it) {
    rva006C1D00(it->xStart, it->xEnd, it->yPos, surfaceClass);
    rva006C1D00(it->xStart, it->xEnd, yDoubled - it->yPos, surfaceClass);
    if (longest->yPos < it->yPos) longest = it;
   }
   for (int x = longest->xStart + 1; x < longest->xEnd; ++x) {
    if (legalRadarPoint(x,longest->yPos)) surfaceClass->DrawPixel(x, longest->yPos, c);
    if (legalRadarPoint(x,yDoubled-longest->yPos)) surfaceClass->DrawPixel(x, yDoubled - longest->yPos, c);
   }
  } else {
   if (!rva006C42B0(obj, &c)) continue;
   if (legalRadarPoint(radarPoint.x,radarPoint.y)) surfaceClass->DrawPixel(radarPoint.x,radarPoint.y,c);
   --radarPoint.x;
   if (legalRadarPoint(radarPoint.x,radarPoint.y)) surfaceClass->DrawPixel(radarPoint.x,radarPoint.y,c);
   --radarPoint.y;
   if (legalRadarPoint(radarPoint.x,radarPoint.y)) surfaceClass->DrawPixel(radarPoint.x,radarPoint.y,c);
   ++radarPoint.x;
   if (legalRadarPoint(radarPoint.x,radarPoint.y)) surfaceClass->DrawPixel(radarPoint.x,radarPoint.y,c);
  }
 }
}
