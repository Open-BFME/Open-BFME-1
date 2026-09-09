// ?bfmeGoZF@BfmeSubZF@@QAEXPAX00PAUBfmeStateZF@@@Z
//
// The named BfmeOwnerZF::bfmeSendZF caller forwards four stack arguments to
// BfmeSubZF at +0x1cc through ILT 0x00008fbc.  That ILT targets this body's
// retail span at 0x00458aa0.  The local views below keep the BFME RadiusDecal
// fields private to this TU; no shared header layout is asserted here.
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

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

struct BfmeStateZF
{
	const void *m_template;
	Shadow *m_decal;
	bool m_empty;
	unsigned char m_pad0c[4];
};

class BfmeSubZF
{
public:
	void bfmeGoZF(void *a, void *b, void *c, BfmeStateZF *state);

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
	unsigned int m_unmodelled28;
	float m_unmodelled2c;
};

void BfmeSubZF::bfmeGoZF(void *a, void *b, void *c, BfmeStateZF *state)
{
	const BfmeSubZF *self = this;

	if (self->m_name.isEmpty())
		return;

	if (a == 0)
		return;

	if (self->m_minRadius == BfmeZeroRange)
		return;

	if (self->m_maxRadius == BfmeZeroRange)
		return;

	RadiusDecal *result = reinterpret_cast<RadiusDecal *>(state);
	result->clear();
	result->m_empty = false;

	Coord3D position;
	ShadowTypeInfo decalInfo;
	decalInfo.m_unmodelled9c = 20.0f;
	decalInfo.m_unmodelleda0 = false;
	strcpy(decalInfo.m_ShadowName, self->m_name.str());
	strcpy(decalInfo.m_ShadowName + 64, self->m_secondName.str());
	decalInfo.allowUpdates = true;
	decalInfo.allowWorldAlign = true;
	decalInfo.m_type = self->m_shadowType;
	decalInfo.m_sizeX = self->m_maxRadius;
	decalInfo.m_sizeY = self->m_maxRadius;
	decalInfo.m_offsetX = 0.0f;
	decalInfo.m_offsetY = 0.0f;

	result->m_decal = TheProjectedShadowManager->addDecal(&decalInfo);
	if (result->m_decal == 0)
		return;

	result->m_decal->m_localAngleBits = reinterpret_cast<unsigned int>(b);
	result->m_decal->setColor(*reinterpret_cast<const int *>(c));
	position.x = reinterpret_cast<const Coord3D *>(a)->x + decalInfo.m_offsetX;
	position.y = reinterpret_cast<const Coord3D *>(a)->y + decalInfo.m_offsetY;
	position.z = reinterpret_cast<const Coord3D *>(a)->z;
	result->m_decal->m_position = position;
	result->m_template = self;
}
