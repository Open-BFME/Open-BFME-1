// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Retail 0x007B4620, 636 bytes. The W3DProjectedShadowManager constructor
// 0x007AF5A0 installs vtable 0x01128404, whose slot 1 (+0x04) routes through
// ILT 0x00035FD5 to this body; nothing else reaches it. No caller, string or
// Zero Hour virtual names the slot, so the method keeps its address.
//
// Once per call it walks the decal list (+0x08) and then the shadow list
// (+0x04). Timed decals (type 0x400 or 0x800) past their end frame are
// collected and released; the rest have their opacity faded in and out
// against the client frame, using the frame and opacity values
// Shadow::rva00459960 stores at +0x38 .. +0x54.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "Lib/BaseType.h"

class ClientFrameSubsystem
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual UnsignedInt getFrame(void);
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;

// Field names follow Shadow::rva00459960 (ShadowRva00459960.cpp), which writes
// +0x38 .. +0x54; +0x34 is the type mask Shadow::setOpacity tests.
//
// Slot 2 is release: the W3DProjectedShadow vtable 0x01128428 (installed by
// constructor 0x007B3C70) routes it through ILT 0x0003486F to 0x007B13D0,
// which hands `this` to the manager singleton 0x01306DF0 -- the body of Zero
// Hour's inline W3DProjectedShadow::release. Slots 0 and 1 stay unnamed.
class Shadow
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void release(void);
	void setOpacity(Int value);

	unsigned char m_pad04[0x30];
	UnsignedInt m_type;
	UnsignedInt m_value38;
	UnsignedInt m_value3C;
	UnsignedInt m_value40;
	UnsignedInt m_value44;
	UnsignedInt m_value48;
	UnsignedInt m_value4C;
	UnsignedInt m_value50;
	UnsignedInt m_value54;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadow : public Shadow
{
public:
	unsigned char m_pad58[0x7C];
	W3DProjectedShadow *m_next;		// +0xD4
};

class W3DProjectedShadowManager
{
public:
	virtual ~W3DProjectedShadowManager();
	virtual void rva007B4620(void);

private:
	W3DProjectedShadow *m_shadowList;	// +0x04
	W3DProjectedShadow *m_decalList;	// +0x08
};

void W3DProjectedShadowManager::rva007B4620(void)
{
	_STL::list<W3DProjectedShadow *> expired;
	UnsignedInt frame = TheGameClientClientUpdate->getFrame();

	for (Int i = 0; i <= 1; ++i)
	{
		for (W3DProjectedShadow *shadow = i ? m_shadowList : m_decalList; shadow; shadow = shadow->m_next)
		{
			if (shadow->m_type == 0x400 || shadow->m_type == 0x800)
			{
				if (shadow->m_value3C <= frame)
					expired.push_back(shadow);
				else
				{
					UnsignedInt value38 = shadow->m_value38;
					UnsignedInt value40 = shadow->m_value40;
					UnsignedInt value44 = shadow->m_value44;
					UnsignedInt value48 = shadow->m_value48;
					UnsignedInt value4C = shadow->m_value4C;
					UnsignedInt value50 = shadow->m_value50;
					UnsignedInt value54 = shadow->m_value54;
					if (frame < value38)
						shadow->setOpacity(0);
					else if (frame < value44)
					{
						double opacity = value40;
						Real t = (Real)(frame - value38) / (Real)(value44 - value38);
						opacity += t * (value48 - opacity);
						shadow->setOpacity(fast_float2long_round(ceil(opacity)));
					}
					else if (frame < value4C)
						shadow->setOpacity(value48);
					else if (frame < value50)
					{
						double opacity = value48;
						Real t = (Real)(frame - value4C) / (Real)(value50 - value4C);
						opacity += t * (value54 - opacity);
						shadow->setOpacity(fast_float2long_round(ceil(opacity)));
					}
					else
						shadow->setOpacity(value54);
				}
			}
		}
	}

	for (_STL::list<W3DProjectedShadow *>::iterator it = expired.begin(); it != expired.end(); ++it)
		(*it)->release();

	expired.clear();
}
