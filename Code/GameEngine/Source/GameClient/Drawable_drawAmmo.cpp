// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?drawAmmo@Drawable@@AAEXXZ  retail 0x00414BE0 478 bytes
//
// BFME's no-argument Drawable ammo-pip pass, reached from the group-3/4 icon
// dispatch in Drawable::drawIconUI.  The Zero Hour twin
// (reference/.../GameClient/Drawable.cpp Drawable::drawAmmo) takes the health
// bar region as an argument; this build reads the cached health-bar origin out
// of the Drawable instead and passes an extra draw mode to Display::drawImage.
//
// The engine singletons are referenced through their pinned decorated symbols
// rather than literal addresses: a literal-address deref aliases the
// address-taken Coord3D local, which pushed every global load out of retail's
// schedule.  `scale` is the SCALE_ICONS_WITH_ZOOM_ML-off branch of the twin --
// it folds to 1.0f, but it is what puts the bounding-sphere load ahead of the
// screen-offset load at +0x125.

typedef unsigned char Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Image
{
	unsigned char m_unreconstructed_00[0x24];
	Int m_imageWidth;
	Int m_imageHeight;
};

class Player
{
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	Real getBoundingSphereRadius() const
	{
		return *(const Real *)((const char *)this + 0x14);
	}
};

class Object
{
public:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0xac - 0x44];
	GeometryInfo m_geometryInfo;

	Player *getControllingPlayer() const;
	bool getAmmoPipShowingInfo(Int &numTotal, Int &numFull) const;
	const Coord3D *getPosition() const
	{
		return &m_position;
	}
	const GeometryInfo &getGeometryInfo() const
	{
		return m_geometryInfo;
	}
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68();
	virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80();
	virtual void slot81(); virtual void slot82();
	virtual Int getMousedOverDrawableID() const;
};

class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68();
	virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80();
	virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86();
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen);
};

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52();
	virtual void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_0000[0x1c0];
	Coord3D m_ammoPipWorldOffset;
	unsigned char m_unreconstructed_01cc[0x1d8 - 0x1cc];
	Coord2D m_ammoPipScreenOffset;
	unsigned char m_unreconstructed_01e0[0xa8d - 0x1e0];
	Bool m_showObjectHealth;
};

struct Rva002EE330PlayerList
{
	unsigned char m_unreconstructed_00[0x0c];
	Player *m_localPlayer;
};

extern GlobalData *TheWritableGlobalData;
extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern Display *TheDisplay;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

#define TheGlobalData TheWritableGlobalData
#define ThePlayerList Rva002EE330ThePlayers

// 0x012F12D4 / 0x012F12D8 carry no ledger pin: address-derived, kept literal.
#define s_fullAmmo (*(const Image **)0x012f12d4)
#define s_emptyAmmo (*(const Image **)0x012f12d8)

class Drawable
{
	Object *getObject() const
	{
		return *(Object **)((char *)this + 0xfc);
	}

	Int getID() const
	{
		return *(Int *)((char *)this + 0x100);
	}

private:
	void drawAmmo();
};

// ?drawAmmo@Drawable@@AAEXXZ
void Drawable::drawAmmo()
{
	Object *obj = getObject();

	if (!TheGlobalData->m_showObjectHealth)
		return;

	if (!*(Bool *)((char *)this + 0x3ac))
	{
		InGameUI *ui = TheInGameUI;
		if (!ui)
			return;
		Int drawableID = getID();
		if (ui->getMousedOverDrawableID() != drawableID)
			return;
	}

	Player *localPlayer = ThePlayerList->m_localPlayer;
	if (obj->getControllingPlayer() != localPlayer)
		return;

	Int numTotal;
	Int numFull;
	if (!obj->getAmmoPipShowingInfo(numTotal, numFull))
		return;

	if (!s_fullAmmo)
		return;
	const Image *emptyAmmo = s_emptyAmmo;
	if (!emptyAmmo)
		return;

	// SCALE_ICONS_WITH_ZOOM_ML is off in this build.
	Real scale = 1.0f;
	Int boxWidth = (Int)((Real)emptyAmmo->m_imageWidth * scale);
	Int boxHeight = (Int)((Real)emptyAmmo->m_imageHeight * scale);

	ICoord2D screenCenter;
	Coord3D pos = {
		obj->m_position.x,
		obj->m_position.y,
		obj->m_position.z
	};
	pos.x += TheGlobalData->m_ammoPipWorldOffset.x;
	pos.y += TheGlobalData->m_ammoPipWorldOffset.y;
	pos.z += TheGlobalData->m_ammoPipWorldOffset.z +
		obj->getGeometryInfo().getMaxHeightAbovePosition();
	if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0)
		return;

	Real bounding = obj->getGeometryInfo().getBoundingSphereRadius() * scale;
	Int posx = *(Int *)((char *)this + 0x3c4);
	Int posy = screenCenter.y +
		(Int)(TheGlobalData->m_ammoPipScreenOffset.y * bounding);

	for (Int i = 0; i < numTotal; ++i)
	{
		const Image *image = s_fullAmmo;
		if (i >= numFull)
			image = s_emptyAmmo;
		Display *display = TheDisplay;
		display->drawImage(image,
			(Real)posx, (Real)(posy + 1),
			(Real)(posx + boxWidth), (Real)(posy + 1 + boxHeight), -1, 2);
		posx += boxWidth + 1;
	}
}
