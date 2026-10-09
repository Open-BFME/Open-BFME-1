// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O2 /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: RadiusDecalTemplate::createRadiusDecal (Zero Hour RadiusDecal.cpp).
// ?createRadiusDecal@RadiusDecalTemplate@@QBEXABUCoord3D@@MPBVPlayer@@AAVRadiusDecal@@@Z

#include <string.h>

extern const char g_bfmeEmptyAscii[];

#include "ascii_string.h"

// This caller inlines the witnessed null/length test.
template <> inline bool StringBase<char>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}

#include "../../../Libraries/Include/Lib/Coord3D.h"

// BFME layout as this body writes it: the decal position is a Coord3D at +0x08,
// the angle at +0x20 and a flag byte at +0x64.  The layout witness names Shadow+0x08
// from W3DVolumetricShadow bodies, so the span here stays an offset placeholder.
class Shadow
{
public:
	virtual void _bfme_slot_00(void) = 0;
	virtual void _bfme_slot_04(void) = 0;
	virtual void release(void) = 0;

	unsigned char m_pad04[4];
	Coord3D m_unmodelled08;
	unsigned char m_pad14[0x0c];
	float m_localAngle;
	unsigned char m_pad24[0x40];
	bool m_unmodelled64;

	void setColor(int value);

	void setAngle(float angle)
	{
		m_localAngle = angle;
	}

	void setPosition(const Coord3D &position)
	{
		m_unmodelled08 = position;
	}
};

// BFME keeps a second 64-byte texture name after the Zero Hour one.
struct ShadowTypeInfo
{
	char m_ShadowName[128];
	int m_type;
	bool allowUpdates;
	bool allowWorldAlign;
	unsigned char m_pad86[2];
	float m_sizeX;
	float m_sizeY;
	float m_offsetX;
	float m_offsetY;
	float m_unmodelled98;
	float m_unmodelled9c;
	bool m_unmodelleda0;
};

class RenderObjClass;

class ProjectedShadowManager
{
public:
	virtual ~ProjectedShadowManager();
	virtual void _bfme_slot_04(void) = 0;
	virtual Shadow *addDecal(RenderObjClass *, ShadowTypeInfo *, int, int);
	virtual Shadow *addDecal(ShadowTypeInfo *);
};

extern ProjectedShadowManager *TheProjectedShadowManager;

class Player
{
public:
	unsigned char m_pad00[0x24];
	int m_playerIndex;
	unsigned char m_pad28[0x19c];
	unsigned int m_unmodelled1c4;

	int getPlayerIndex(void) const
	{
		return m_playerIndex;
	}

	unsigned int getPlayerColor(void) const
	{
		return m_unmodelled1c4;
	}
};

class PlayerList
{
public:
	unsigned char m_pad00[0x0c];
	Player *m_local;

	Player *getLocalPlayer(void) const
	{
		return m_local;
	}
};

extern PlayerList *ThePlayerList;

class RadiusDecalTemplate;

class RadiusDecal
{
public:
	const RadiusDecalTemplate *m_template;
	Shadow *m_decal;
	bool m_empty;

};

// RadiusDecal::clear (retail 0x00458310) is defined once in RadiusDecal.cpp;
// retail inlines it here, so expand it through a TU-static helper that emits
// no external copy.
static __forceinline void clearRadiusDecal(RadiusDecal &decal)
{
	decal.m_template = 0;
	if (decal.m_decal)
		decal.m_decal->release();
	decal.m_decal = 0;
	decal.m_empty = true;
}

class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &, float, const Player *, RadiusDecal &) const;

private:
	AsciiString m_name;
	AsciiString m_secondName;
	int m_shadowType;
	float m_minOpacity;
	float m_maxOpacity;
	float m_opacityThrobTime;
	unsigned int m_color;
	bool m_onlyVisibleToOwningPlayer;
};

// ?createRadiusDecal@RadiusDecalTemplate@@QBEXABUCoord3D@@MPBVPlayer@@AAVRadiusDecal@@@Z
void RadiusDecalTemplate::createRadiusDecal(
	const Coord3D &pos, float radius, const Player *owningPlayer, RadiusDecal &result) const
{
	clearRadiusDecal(result);

	if (owningPlayer == 0)
		return;

	if (m_name.isEmpty() || radius <= 0.0f)
		return;

	result.m_empty = false;

	if (!m_onlyVisibleToOwningPlayer
		|| owningPlayer->getPlayerIndex() == ThePlayerList->getLocalPlayer()->getPlayerIndex())
	{
		ShadowTypeInfo decalInfo;
		decalInfo.m_type = m_shadowType;
		decalInfo.m_unmodelled9c = 20.0f;
		decalInfo.m_unmodelleda0 = false;
		decalInfo.allowUpdates = false;
		decalInfo.allowWorldAlign = true;
		strcpy(decalInfo.m_ShadowName, m_name.str());
		strcpy(decalInfo.m_ShadowName + 64, m_secondName.str());
		decalInfo.m_sizeX = radius * 2;
		decalInfo.m_sizeY = radius * 2;

		result.m_decal = TheProjectedShadowManager->addDecal(&decalInfo);
		if (result.m_decal)
		{
			result.m_decal->setAngle(0.0f);
			result.m_decal->setColor(m_color == 0 ? owningPlayer->getPlayerColor() : m_color);
			result.m_decal->setPosition(pos);
			if (radius > 110.0f)
				result.m_decal->m_unmodelled64 = true;
			result.m_template = this;
		}
	}
}
