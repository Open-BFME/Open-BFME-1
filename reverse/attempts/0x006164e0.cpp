// ?rva006164e0@BfmeLivingWorldManager@@QAEXXZ
// partial score=0.46 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x006164E0, 1010 bytes.  Manager fields and both spawned object layouts are address-derived.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Lib/BaseType.h"
#include "StringInline.h"

extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

class WWMath
{
public:
	static float Random_Float();
};

class StringBaseNarrowBG_Rva0060BBD0
{
protected:
	StringBaseNarrowBG_Rva0060BBD0(const char *text);
	StringBaseNarrowBG_Rva0060BBD0(const StringBaseNarrowBG_Rva0060BBD0 &other);
	~StringBaseNarrowBG_Rva0060BBD0();
	char *m_data;
};

class AsciiStringBG_Rva0060BBD0 : public StringBaseNarrowBG_Rva0060BBD0
{
public:
	AsciiStringBG_Rva0060BBD0(const char *text)
		: StringBaseNarrowBG_Rva0060BBD0(text) {}
	AsciiStringBG_Rva0060BBD0(const AsciiStringBG_Rva0060BBD0 &other)
		: StringBaseNarrowBG_Rva0060BBD0(other) {}
	~AsciiStringBG_Rva0060BBD0() {}
};

class RenderObjClass
{
public:
#define RENDER_SLOT(n) virtual void renderSlot##n();
	RENDER_SLOT(000) RENDER_SLOT(001) RENDER_SLOT(002) RENDER_SLOT(003)
	RENDER_SLOT(004) RENDER_SLOT(005) RENDER_SLOT(006) RENDER_SLOT(007)
	RENDER_SLOT(008) RENDER_SLOT(009) RENDER_SLOT(010) RENDER_SLOT(011)
	RENDER_SLOT(012) RENDER_SLOT(013) RENDER_SLOT(014) RENDER_SLOT(015)
	RENDER_SLOT(016) RENDER_SLOT(017) RENDER_SLOT(018) RENDER_SLOT(019)
	RENDER_SLOT(020) RENDER_SLOT(021) RENDER_SLOT(022) RENDER_SLOT(023)
	RENDER_SLOT(024) RENDER_SLOT(025) RENDER_SLOT(026) RENDER_SLOT(027)
	RENDER_SLOT(028) RENDER_SLOT(029) RENDER_SLOT(030) RENDER_SLOT(031)
	RENDER_SLOT(032) RENDER_SLOT(033) RENDER_SLOT(034) RENDER_SLOT(035)
	RENDER_SLOT(036) RENDER_SLOT(037) RENDER_SLOT(038) RENDER_SLOT(039)
	RENDER_SLOT(040) RENDER_SLOT(041) RENDER_SLOT(042) RENDER_SLOT(043)
	RENDER_SLOT(044) RENDER_SLOT(045) RENDER_SLOT(046) RENDER_SLOT(047)
	RENDER_SLOT(048) RENDER_SLOT(049) RENDER_SLOT(050) RENDER_SLOT(051)
	RENDER_SLOT(052) RENDER_SLOT(053) RENDER_SLOT(054) RENDER_SLOT(055)
	RENDER_SLOT(056) RENDER_SLOT(057) RENDER_SLOT(058) RENDER_SLOT(059)
	RENDER_SLOT(060) RENDER_SLOT(061) RENDER_SLOT(062) RENDER_SLOT(063)
	RENDER_SLOT(064) RENDER_SLOT(065) RENDER_SLOT(066) RENDER_SLOT(067)
	RENDER_SLOT(068) RENDER_SLOT(069) RENDER_SLOT(070) RENDER_SLOT(071)
	RENDER_SLOT(072) RENDER_SLOT(073) RENDER_SLOT(074) RENDER_SLOT(075)
	RENDER_SLOT(076) RENDER_SLOT(077) RENDER_SLOT(078) RENDER_SLOT(079)
	RENDER_SLOT(080) RENDER_SLOT(081) RENDER_SLOT(082) RENDER_SLOT(083)
	RENDER_SLOT(084) RENDER_SLOT(085) RENDER_SLOT(086) RENDER_SLOT(087)
	RENDER_SLOT(088) RENDER_SLOT(089) RENDER_SLOT(090) RENDER_SLOT(091)
	RENDER_SLOT(092) RENDER_SLOT(093) RENDER_SLOT(094) RENDER_SLOT(095)
	RENDER_SLOT(096) RENDER_SLOT(097) RENDER_SLOT(098) RENDER_SLOT(099)
#undef RENDER_SLOT
	virtual void renderSlot100(bool value);
};

void Rva00739B30(RenderObjClass *object, bool geometry);
void __cdecl bfmeReportGN(void *object, void *red, void *green, void *blue);

class Rva0060BEB0Object
{
public:
	virtual RenderObjClass *createRenderObject(AsciiString name);
	Rva0060BEB0Object(AsciiString name);

	char m_pad04[4];
	RenderObjClass *m_renderObject;
	char m_pad0c[0x1c];
	int m_field28;
	char m_pad2c[0x60];
	int m_field8c;
	Coord3D m_field94;
	char m_padA0[4];
	int m_fieldA0;
	int m_fieldA4;
	int m_fieldA8;
};

class Rva0060BBD0
{
public:
	virtual RenderObjClass *createRenderObject(AsciiString name);
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c(Coord3D position);
	Rva0060BBD0(AsciiStringBG_Rva0060BBD0 name);

	char m_pad04[4];
	RenderObjClass *m_renderObject;
	char m_pad0c[0x18];
	int m_field24;
	char m_gap28[4];
	int m_field2c;
	int m_field30;
	int m_field34;
	int m_field38;
	int m_field3c;
	int m_field40;
	int m_field44;
	int m_field48;
	char m_pad4c[0x30];
	unsigned char m_field7c;
	char m_pad7d[0x23];
};

class BfmeThingDY
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	void bfmeSetRectDY(int left, int right, int top, int bottom, int value);
};

class BfmeAnimationHolder
{
public:
	void applyScalePayload(float scale);
};

class Gen_00609320
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28(RenderObjClass *object);
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeItemAM;

class BfmeLivingWorldManager
{
public:
	void rva006164e0();
	void rva00616240(BfmeItemAM *item, int which, int second);

private:
	char m_pad00[0x28];
	float m_field28;
	char m_pad2c[0x94];
	AsciiString m_nameC0;
	char m_padC4[0x10];
	Coord3D m_coordD4;
	int m_fieldE0;
	int m_fieldE4;
	char m_padE8[0x14];
	AsciiString m_nameFC;
	int m_field100;
	int m_field104;
	float m_field108;
	float m_field10c;
	int m_field110;
	float m_field114;
	float m_field118;
	int m_field11c;
	int m_field120;
	char m_pad124[0x1c];
	float m_field140;
	char m_pad144[0xfc];
	_STL::vector<Rva0060BBD0 *> m_primary;
	_STL::vector<Rva0060BEB0Object *> m_secondary;
};

static float retailFloat(unsigned int address)
{
	return *reinterpret_cast<const float *>(address);
}

void BfmeLivingWorldManager::rva006164e0()
{
	int batchSize = 1;
	int remaining;
	if (m_fieldE4 > 0)
	{
		remaining = m_fieldE4;
		do
		{
			int index = 0;
			while (index < batchSize)
			{
				char buffer[60];
				sprintf(buffer, "doomRays%02d", index);
				Rva0060BEB0Object *object = new Rva0060BEB0Object(AsciiString(buffer));
				if (object->createRenderObject(m_nameC0) != 0)
				{
					Rva00739B30(object->m_renderObject, false);
					bfmeReportGN(object->m_renderObject, (object->m_field28 = 1, 0), 0, 0);
						object->m_renderObject->renderSlot100(true);
					object->m_field94 = m_coordD4;
					object->m_field8c = m_fieldE0;
					g_bfmeStateDF->slot28(object->m_renderObject);
					m_secondary.push_back(object);
				}
				++index;
			}
			batchSize += batchSize;
		}
		while (--remaining != 0);
	}

	remaining = 0;
	while (remaining < m_field104)
	{
		char buffer[64];
		sprintf(buffer, "doomCloud%02d", remaining);
		Rva0060BBD0 *object = new Rva0060BBD0(AsciiStringBG_Rva0060BBD0(buffer));
		if (object->createRenderObject(m_nameFC) != 0)
		{
			Rva00739B30(object->m_renderObject, false);
			Coord3D position;
			position.x = WWMath::Random_Float() * (m_field10c - m_field108) + m_field108;
			position.y = WWMath::Random_Float() * (m_field118 - m_field114) + m_field114;
			position.z = m_field28;
			int offset = (int)(WWMath::Random_Float() * (float)m_field120 * retailFloat(0x01095f98));
			object->slot1c(position);
			object->m_field7c = 1;
			object->m_renderObject->renderSlot100(false);
			int left = offset + (int)((WWMath::Random_Float() * retailFloat(0x01116b88) + retailFloat(0x01080bbc)) * batchSize);
			int right = offset + (int)((WWMath::Random_Float() * retailFloat(0x01116b84) + retailFloat(0x01094a60)) * batchSize);
			int bottom = offset + (int)((WWMath::Random_Float() * retailFloat(0x01116b80) + retailFloat(0x0109f748)) * batchSize);
			reinterpret_cast<BfmeThingDY *>(object)->bfmeSetRectDY(offset, left, right, bottom, 1);
			reinterpret_cast<BfmeAnimationHolder *>(object)->applyScalePayload(m_field140);
			g_bfmeStateDF->slot28(object->m_renderObject);
			m_primary.push_back(object);
			rva00616240(reinterpret_cast<BfmeItemAM *>(object), 3, 0);
		}
		++remaining;
	}
}
