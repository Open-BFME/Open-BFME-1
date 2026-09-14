// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define DEFINE_SHADOW_NAMES
// stlport

// ?update@RadiusDecal@@QAEXXZ
// TU-local BFME mirror for the retail RadiusDecal update body at 0x004585F0.

#include "PreRTS.h"

class GameClient
{
public:
	virtual void pad00(void) = 0;
	virtual void pad04(void) = 0;
	virtual void pad08(void) = 0;
	virtual void pad0C(void) = 0;
	virtual void pad10(void) = 0;
	virtual void pad14(void) = 0;
	virtual void pad18(void) = 0;
	virtual void pad1C(void) = 0;
	virtual void pad20(void) = 0;
	virtual void pad24(void) = 0;
	virtual void pad28(void) = 0;
	virtual void pad2C(void) = 0;
	virtual void pad30(void) = 0;
	virtual void pad34(void) = 0;
	virtual void pad38(void) = 0;
	virtual void pad3C(void) = 0;
	virtual void pad40(void) = 0;
	virtual void pad44(void) = 0;
	virtual void pad48(void) = 0;
	virtual void pad4C(void) = 0;
	virtual void pad50(void) = 0;
	virtual void pad54(void) = 0;
	virtual void pad58(void) = 0;
	virtual void pad5C(void) = 0;
	virtual void pad60(void) = 0;
	virtual void pad64(void) = 0;
	virtual UnsignedInt getFrame(void) = 0;
};

class Shadow
{
public:
	void setOpacity(Int value);
};

struct Rva004585F0ShadowFields
{
	UnsignedByte pad00[0x20];
	Real value20;
	UnsignedByte pad24[0x10];
	volatile UnsignedInt value34;
};

struct Rva004585F0TemplateLayout
{
	UnsignedByte pad00[0x0C];
	Real minOpacity;
	Real maxOpacity;
	Real opacityThrobTime;
	UnsignedByte pad18[0x10];
	volatile UnsignedInt templateValue28;
	Real templateValue2C;
};

struct Rva004585F0WritableGlobalData
{
	UnsignedByte pad00[0x60];
	volatile UnsignedByte flag60;
};

class Rva004585F0LookAtTranslator
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual Int slot01(void) = 0;
};

struct Rva004585F0GameLogicLayout
{
	UnsignedByte pad00[0x3C];
	Int frame;
	UnsignedByte pad40[0x52];
	volatile UnsignedByte drawIconUI;
};

class Rva004585F0RadiusDecal
{
public:
	void update();

	Rva004585F0TemplateLayout *m_template;
	Shadow *m_decal;
	Bool m_empty;
	Real bfmeExtra;
};

#define RVA004585F0_GAME_LOGIC (*(Rva004585F0GameLogicLayout **)0x012F0898)
#define RVA004585F0_GAME_CLIENT (*(GameClient **)0x012F1464)
#define RVA004585F0_ZERO (*(const Real *)0x01075350)
#define RVA004585F0_UINT32_SCALE (*(const Real *)0x01075358)
#define RVA004585F0_ONE (*(const Real *)0x01075334)
#define RVA004585F0_HALF (*(const Real *)0x0107533C)
#define RVA004585F0_TWO_PI (*(const Real *)0x01087B10)
#define RVA004585F0_SCALE (*(const Real *)0x01084068)
#define RVA004585F0_THROB_SCALE (*(const Real *)0x010F638C)
#define RVA004585F0_FIRST_FACTOR (*(volatile Real *)0x012B5628)
#define RVA004585F0_SECOND_FACTOR (*(volatile Real *)0x010F6394)
#define RVA004585F0_POSITION_SCALE (*(const Real *)0x0108882C)
#define RVA004585F0_WRITABLE_DATA (*(Rva004585F0WritableGlobalData **)0x012ED5C8)
#define RVA004585F0_LOOK_AT_TRANSLATOR (*(Rva004585F0LookAtTranslator **)0x012F4C84)

extern "C" __declspec(dllimport) double bfmeMathVE(double);
extern Real bfmeSinVNB(Real);

// ?update@RadiusDecal@@QAEXXZ
void Rva004585F0RadiusDecal::update()
{
	if (bfmeExtra == RVA004585F0_ZERO)
	{
		UnsignedInt frame = RVA004585F0_GAME_LOGIC->frame;
		bfmeExtra = frame;
	}

	if (m_decal == NULL)
		goto update_extra;

	if (m_template == NULL)
		goto update_extra;

	UnsignedInt frame = RVA004585F0_GAME_CLIENT->getFrame();
	Real throbTime = (Real)bfmeMathVE(
		m_template->opacityThrobTime * RVA004585F0_THROB_SCALE);
	UnsignedInt cycle;
	__asm fld throbTime
	__asm fistp cycle
	UnsignedInt divisorValue = cycle;
	UnsignedInt minimum = 1;
	UnsignedInt *divisor;
	if (divisorValue > 1)
		divisor = &divisorValue;
	else
		divisor = &minimum;
	UnsignedInt phase = frame % *divisor;
	Real percent = RVA004585F0_HALF *
		(bfmeSinVNB((Real)phase * RVA004585F0_TWO_PI / (Real)*divisor)
			+ RVA004585F0_ONE);

	Int opacity;
	if (RVA004585F0_GAME_LOGIC->drawIconUI)
	{
		opacity = (Int)(((m_template->maxOpacity - m_template->minOpacity) * percent
			+ m_template->minOpacity) * RVA004585F0_SCALE);
	}
	else
	{
		opacity = 0;
	}

	{
		Bool specialShadow =
			((Rva004585F0ShadowFields *)m_decal)->value34 == 0x1000;
		UnsignedInt templateValue = m_template->templateValue28;
		if (templateValue > 0 || specialShadow)
			goto set_opacity;
		if (RVA004585F0_WRITABLE_DATA->flag60
			&& RVA004585F0_LOOK_AT_TRANSLATOR->slot01())
		{
			opacity = 0;
		}
	}

set_opacity:
	m_decal->setOpacity(opacity);
	if (m_template->templateValue2C != RVA004585F0_ZERO)
	{
		UnsignedInt clientFrame;
		Real scale;
		Real frameAsReal;
		scale = RVA004585F0_FIRST_FACTOR;
		scale *= RVA004585F0_SECOND_FACTOR;
		scale *= m_template->templateValue2C;
		scale *= RVA004585F0_POSITION_SCALE;
		clientFrame = RVA004585F0_GAME_CLIENT->getFrame();
		frameAsReal = (Real)clientFrame;
		if (clientFrame < 0)
			frameAsReal += RVA004585F0_UINT32_SCALE;
		((Rva004585F0ShadowFields *)m_decal)->value20 = frameAsReal * scale;
	}

update_extra:
	bfmeExtra = (Real)RVA004585F0_GAME_CLIENT->getFrame();
}
