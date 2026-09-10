// ?createRadiusDecal@RadiusDecalTemplate@@QBEXABUCoord3D@@MPBVPlayer@@AAVRadiusDecal@@@Z
// partial score=0.92 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include <string.h>

// BFME's AsciiString is the eight-byte-header StringBase view: length is at
// +0x04 and the characters begin at +0x08.  Keep the accessors inline here so
// the retail body remains a manual length/data check rather than an out-of-line
// call to a different StringBase owner.
extern const char g_bfmeEmptyAscii[];

class AsciiString
{
private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_data[1];
	};

	Header *m_data;

public:
	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str(void) const
	{
		return m_data ? m_data->m_data : g_bfmeEmptyAscii;
	}
};

// These are the BFME layouts used by the retail body at 0x00458C80.  The
// vendored Zero Hour Shadow.h has a 64-byte name and cannot describe BFME's
// 128-byte decal record, so keep this view private to this translation unit.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Shadow
{
public:
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
		float m_unmodelled_98;
		float m_unmodelled_9C;
		bool m_unmodelled_A0;
	};

	virtual void _bfme_slot_00(void) = 0;
	virtual void _bfme_slot_04(void) = 0;
	virtual void release(void) = 0;

	unsigned char m_pad04[4];
	Coord3D m_position;
	unsigned char m_pad14[0x0C];
	float m_localAngle;
	unsigned char m_pad24[0x40];
	bool m_unmodelled_64;

	void setColor(int value);

	void setAngle(float angle)
	{
		m_localAngle = angle;
	}

	void setPosition(const Coord3D &position)
	{
		m_position = position;
	}
};

class RenderObjClass;

class ProjectedShadowManager
{
public:
	virtual void _bfme_slot_00(void) = 0;
	virtual ~ProjectedShadowManager();
	virtual Shadow *addDecal(RenderObjClass *, Shadow::ShadowTypeInfo *);
	virtual Shadow *addDecal(Shadow::ShadowTypeInfo *);
};

extern ProjectedShadowManager *TheProjectedShadowManager;
extern const float BfmeZeroRange;
extern const float g_010F6388; // retail float at VA 0x010F6388; field identity unresolved

class Player
{
public:
	unsigned char m_pad00[0x24];
	int m_playerIndex;
	unsigned char m_pad28[0x19C];
	unsigned int m_playerColor;

	int getPlayerIndex(void) const
	{
		return m_playerIndex;
	}

	unsigned int getPlayerColor(void) const
	{
		return m_playerColor;
	}
};

class Rva002EE330PlayerList
{
public:
	unsigned char m_pad00[0x0C];
	Player *m_localPlayer;

	Player *getLocalPlayer(void) const
	{
		return m_localPlayer;
	}
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class RadiusDecalTemplate;

class RadiusDecal
{
public:
	const RadiusDecalTemplate *m_template;
	Shadow *m_decal;
	bool m_empty;
	int m_bfmeExtra;

	void clear(void)
	{
		m_template = 0;
		if (m_decal)
			m_decal->release();
		m_decal = 0;
		m_empty = true;
	}
};

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
	unsigned int m_unmodelled_20;
	unsigned int m_unmodelled_24;
	unsigned int m_unmodelled_28;
	unsigned int m_unmodelled_2C;
};

// ?createRadiusDecal@RadiusDecalTemplate@@QBEXABUCoord3D@@MPBVPlayer@@AAVRadiusDecal@@@Z
void RadiusDecalTemplate::createRadiusDecal(
	const Coord3D &pos, float radius, const Player *owningPlayer, RadiusDecal &result) const
{
	result.clear();

	if (!owningPlayer)
		return;

	if (m_name.isEmpty() || radius <= BfmeZeroRange)
		return;

	result.m_empty = false;

	if (!m_onlyVisibleToOwningPlayer
		|| owningPlayer->getPlayerIndex() == Rva002EE330ThePlayers->getLocalPlayer()->getPlayerIndex())
	{
		Shadow::ShadowTypeInfo decalInfo;
		decalInfo.m_type = m_shadowType;
		decalInfo.m_unmodelled_9C = 20.0f;
		decalInfo.m_unmodelled_A0 = false;
		decalInfo.allowUpdates = false;
		decalInfo.allowWorldAlign = true;
		strcpy(decalInfo.m_ShadowName, m_name.str());
		strcpy(decalInfo.m_ShadowName + 64, m_secondName.str());
		decalInfo.m_sizeX = radius * 2.0f;
		decalInfo.m_sizeY = radius * 2.0f;

		result.m_decal = TheProjectedShadowManager->addDecal(&decalInfo);
		if (!result.m_decal)
			return;

		result.m_decal->setAngle(0.0f);
		result.m_decal->setColor(
			m_color == 0 ? (int)owningPlayer->getPlayerColor() : (int)m_color);
		result.m_decal->setPosition(pos);
		if (radius > g_010F6388)
			result.m_decal->m_unmodelled_64 = true;
		result.m_template = this;
	}
}
