// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
//
// Drawable::drawContained, retail RVA 0x00414E40, 833 bytes (plain `ret`).
// tools/ilt_oracle.py CONFIRMS ?drawContained@Drawable@@AAEXXZ at its ILT
// 0x00012E2C: like drawEnthusiastic, BFME's version takes no health-bar
// region and reads the drawable's own region at +0x3C4. The body follows
// Zero Hour's (GameClient/Drawable.cpp) with BFME's changes: the container
// owner may also be the local player, getContainerPipsToShow reports two pip
// rows (total, full and infantry counts each) instead of counting infantry
// here, worldToScreen reports success as zero, and the pips are drawn with
// the recorded s_contestPipFull / s_contestPipEmpty images through the float
// drawImage, the second row two pixels below the first.

#include "Lib/Coord3D.h"

typedef int Int;
typedef float Real;
typedef unsigned int Color;
typedef unsigned int DrawableID;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image
{
public:
	Int getImageWidth() const { return m_imageSize.x; }
	Int getImageHeight() const { return m_imageSize.y; }
private:
	unsigned char m_unmodelled_00[0x24];
	ICoord2D m_imageSize;					// +0x24
};

class Player;

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_unmodelled_00[0x0C];
	Player *m_local;						// +0x0C
};
extern PlayerList *ThePlayerList;

class GlobalData
{
public:
	unsigned char m_unmodelled_000[0x1CC];
	Coord3D m_containerPipWorldOffset;		// +0x1CC
	unsigned char m_unmodelled_1D8[0x08];
	struct { Real x, y; } m_containerPipScreenOffset;	// +0x1E0
	unsigned char m_unmodelled_1E8[0xA8D - 0x1E8];
	bool m_showObjectHealth;				// +0xA8D
};
// Retail 0x012ED5C8 is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows.csv,
// Common/GlobalData.cpp); TheGlobalData was only a pin.
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

class InGameUI
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual DrawableID getMousedOverDrawableID() const;
};
extern InGameUI *TheInGameUI;

class View
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14c();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual Int worldToScreen(const Coord3D *w, ICoord2D *s);
};
extern View *TheTacticalView;

class Display
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);
};
extern Display *TheDisplay;

class ContainModuleInterface
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	// Slot +0xCC: a player the container answers for (unidentified).
	virtual Player *rva00414E40Slot0CC() const;
	virtual void w0d0();
	virtual void w0d4();
	virtual void w0d8();
	virtual void w0dc();
	virtual void w0e0();
	virtual void w0e4();
	virtual void w0e8();
	virtual void w0ec();
	virtual void w0f0();
	virtual void w0f4();
	virtual void w0f8();
	virtual void w0fc();
	virtual void w100();
	virtual void w104();
	virtual void w108();
	virtual void w10c();
	virtual void w110();
	virtual void w114();
	virtual void w118();
	virtual void w11c();
	virtual void w120();
	virtual void w124();
	virtual void w128();
	virtual void w12c();
	virtual void w130();
	virtual void w134();
	virtual void w138();
	virtual bool getContainerPipsToShow(Int &numTotal, Int &numFull, Int &numInfantry,
		Int &numTotal2, Int &numFull2, Int &numInfantry2);
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
private:
	unsigned char m_unmodelled_00[0x14];
	Real m_boundingSphereRadius;			// +0x14
};

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_pos; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	ContainModuleInterface *getContain() const { return m_contain; }
private:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_pos;							// +0x38
	unsigned char m_unmodelled_044[0xAC - 0x44];
	GeometryInfo m_geometryInfo;			// +0xAC
	unsigned char m_unmodelled_0C4[0x1FC - 0xC4];
	ContainModuleInterface *m_contain;		// +0x1FC
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Drawable
{
public:
	const Object *getObject() const { return m_object; }
	DrawableID getID() const { return m_id; }
	bool isSelected() const { return m_selected; }

private:
	void drawContained();

	static const Image *s_emptyContainer;
	static const Image *s_contestPipFull;
	static const Image *s_contestPipEmpty;

	unsigned char m_unmodelled_000[0xFC];
	Object *m_object;						// +0x0FC
	DrawableID m_id;						// +0x100
	unsigned char m_unmodelled_104[0x3AC - 0x104];
	bool m_selected;						// +0x3AC
	unsigned char m_unmodelled_3AD[0x3C4 - 0x3AD];
	IRegion2D m_healthBarRegion;			// +0x3C4
};

#define REAL_TO_INT(x) ((Int)(x))
#define INT_TO_REAL(x) ((Real)(x))

inline Color GameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void Drawable::drawContained()
{
	const Object *obj = getObject();

	ContainModuleInterface *container = obj->getContain();
	if (!container)
		return;

	if (!(
				TheGlobalData->m_showObjectHealth &&
				(isSelected() || (TheInGameUI && (TheInGameUI->getMousedOverDrawableID() == getID()))) &&
				(obj->getControllingPlayer() == ThePlayerList->getLocalPlayer() ||
				 container->rva00414E40Slot0CC() == ThePlayerList->getLocalPlayer())
			))
		return;

	Int numTotal;
	Int numFull;
	Int numInfantry;
	Int numTotal2;
	Int numFull2;
	Int numInfantry2;
	if (!container->getContainerPipsToShow(numTotal, numFull, numInfantry,
			numTotal2, numFull2, numInfantry2))
		return;

	// if empty, don't show nothin'
	if (numFull == 0)
		return;

	Real scale = 1.0f;
	Int boxWidth  = REAL_TO_INT(s_emptyContainer->getImageWidth() * scale);
	Int boxHeight = REAL_TO_INT(s_emptyContainer->getImageHeight() * scale);
	const Int SPACING = 1;

	ICoord2D screenCenter;
	// Copied member by member: retail loads the three words straight from the
	// object, where a whole-struct copy goes through the returned pointer.
	Coord3D pos;
	pos.x = obj->getPosition()->x;
	pos.y = obj->getPosition()->y;
	pos.z = obj->getPosition()->z;
	pos.x += TheGlobalData->m_containerPipWorldOffset.x;
	pos.y += TheGlobalData->m_containerPipWorldOffset.y;
	pos.z += TheGlobalData->m_containerPipWorldOffset.z + obj->getGeometryInfo().getMaxHeightAbovePosition();
	if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0)
		return;

	Real bounding = obj->getGeometryInfo().getBoundingSphereRadius() * scale;

	Int posx = m_healthBarRegion.lo.x;
	Int posy = screenCenter.y + REAL_TO_INT(TheGlobalData->m_containerPipScreenOffset.y * bounding);

	for (Int i = 0; i < numTotal; ++i)
	{
		const Color INFANTRY_COLOR = GameMakeColor(0, 255, 0, 255);
		const Color NON_INFANTRY_COLOR = GameMakeColor(0, 0, 255, 255);
		if (i < numFull)
			TheDisplay->drawImage(s_contestPipFull, INT_TO_REAL(posx), INT_TO_REAL(posy),
				INT_TO_REAL(posx + boxWidth), INT_TO_REAL(posy + boxHeight),
				(i < numInfantry) ? INFANTRY_COLOR : NON_INFANTRY_COLOR, 2);
		else
			TheDisplay->drawImage(s_contestPipEmpty, INT_TO_REAL(posx), INT_TO_REAL(posy + 1),
				INT_TO_REAL(posx + boxWidth), INT_TO_REAL(posy + 1 + boxHeight), 0xFFFFFFFF, 2);
		posx += boxWidth + SPACING;
	}

	if (numFull2 > 0)
	{
		posx = m_healthBarRegion.lo.x;
		posy += boxHeight + 2;
		for (Int i = 0; i < numTotal2; ++i)
		{
			const Color INFANTRY_COLOR = GameMakeColor(0, 255, 0, 255);
			const Color NON_INFANTRY_COLOR = GameMakeColor(0, 0, 255, 255);
			if (i < numFull2)
				TheDisplay->drawImage(s_contestPipFull, INT_TO_REAL(posx), INT_TO_REAL(posy),
					INT_TO_REAL(posx + boxWidth), INT_TO_REAL(posy + boxHeight),
					(i < numInfantry2) ? INFANTRY_COLOR : NON_INFANTRY_COLOR, 2);
			else
				TheDisplay->drawImage(s_contestPipEmpty, INT_TO_REAL(posx), INT_TO_REAL(posy + 1),
					INT_TO_REAL(posx + boxWidth), INT_TO_REAL(posy + 1 + boxHeight), 0xFFFFFFFF, 2);
			posx += boxWidth + SPACING;
		}
	}
}
