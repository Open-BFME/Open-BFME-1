// ?d_004588d0@@YAXXZ
// partial score=0.99 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O2

#include <string.h>

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

class Gen00458270
{
public:
	float sample(unsigned int frame);
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Shadow
{
public:
	virtual void _bfme_slot_00(void) = 0;
	virtual void _bfme_slot_04(void) = 0;
	virtual void release(void) = 0;

	unsigned char m_pad04[4];
	Coord3D m_position;
	unsigned char m_pad14[0x0c];
	unsigned int m_localAngleBits;

	void setColor(int value);
};

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
	virtual void _bfme_slot_00(void) = 0;
	virtual ~ProjectedShadowManager();
	virtual Shadow *addDecal(RenderObjClass *, ShadowTypeInfo *);
	virtual Shadow *addDecal(ShadowTypeInfo *);
};

extern ProjectedShadowManager *TheProjectedShadowManager;
extern const float BfmeZeroRange;

class RadiusDecal
{
public:
	const void *m_template;
	Shadow *m_decal;
	bool m_empty;

	void clear(void);
};

class Rva004588D0RadiusDecalTemplate
{
public:
	void create(float, float, float, unsigned int, int, RadiusDecal &, float);

private:
	AsciiString m_name;
	AsciiString m_secondName;
	int m_shadowType;
	float m_minOpacity;
	float m_maxOpacity;
	float m_opacityThrobTime;
	unsigned int m_color;
	bool m_onlyVisibleToOwningPlayer;
	unsigned char m_pad1d[3];
	float m_minRadius;
	float m_maxRadius;
	unsigned int m_maxSelectedUnits;
	float m_rotationsPerMinute;
};

// ?create@Rva004588D0RadiusDecalTemplate@@QAEXMMMIHAAVRadiusDecal@@M@Z
void Rva004588D0RadiusDecalTemplate::create(
	float x,
	float y,
	float z,
	unsigned int selectedUnits,
	int color,
	RadiusDecal &result,
	float extra)
{
	if (m_name.isEmpty())
		return;

	if (selectedUnits == 0)
		return;

	if (m_minRadius == BfmeZeroRange)
		return;

	if (m_maxRadius == BfmeZeroRange)
		return;

	result.clear();
	result.m_empty = false;

	ShadowTypeInfo decalInfo;
	decalInfo.m_unmodelled9c = 20.0f;
	decalInfo.m_unmodelleda0 = false;
	strcpy(decalInfo.m_ShadowName, m_name.str());
	strcpy(decalInfo.m_ShadowName + 64, m_secondName.str());
	decalInfo.allowUpdates = false;
	decalInfo.allowWorldAlign = true;
	decalInfo.m_type = m_shadowType;
	float radius = ((Gen00458270 *)this)->sample(selectedUnits);
	decalInfo.m_sizeX = radius;
	decalInfo.m_sizeY = radius;
	decalInfo.m_unmodelled9c = extra;
	decalInfo.m_offsetX = 0.0f;
	decalInfo.m_offsetY = 0.0f;

	result.m_decal = TheProjectedShadowManager->addDecal(&decalInfo);
	if (result.m_decal == 0)
		return;

	result.m_decal->m_localAngleBits = 0;
	result.m_decal->setColor(color);
	*(Coord3D *)&result.m_decal->m_position = *(const Coord3D *)&x;
	result.m_template = this;
}
