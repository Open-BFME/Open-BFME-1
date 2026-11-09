// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include

typedef int Int;
typedef float Real;
typedef unsigned long UnsignedInt;

extern Real g_bfmeDefaultBU;

extern const Real g_rva01075350;
extern "C" Real g_bfmeUint32Scale;

#include "texture.h"
// BFME RectClass has four floats; WWMath/rect.h defines the unrelated TRect.
// Render2DClass is the older BFME batch layout witnessed by Add_Quad at 0x006E7210.
class RectClass
{
public:
	RectClass() {}
	RectClass(Real left, Real top, Real right, Real bottom) :
		Left(left), Top(top), Right(right), Bottom(bottom) {}
	Real Left;
	Real Top;
	Real Right;
	Real Bottom;
};



class Rva006ECD30TextureRef
{
public:
    TextureBaseClass *m_value;
    ~Rva006ECD30TextureRef() { if (m_value) m_value->Release_Ref(); }
    __forceinline Rva006ECD30TextureRef &operator=(const Rva006ECD30TextureRef &other)
    {
        if (other.m_value) other.m_value->Add_Ref();
        if (m_value) m_value->Release_Ref();
        m_value = other.m_value;
        return *this;
    }
};

class Render2DClass
{
public:
	unsigned char m_unmodelled00[0x4c];
	Rva006ECD30TextureRef m_texture;
	UnsignedInt m_textureSet;
	unsigned char m_texturingEnabled;

public:
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		UnsignedInt color0, UnsignedInt color1,
		UnsignedInt color2, UnsignedInt color3);

};

class Image
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual bool slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual const Rva006ECD30TextureRef &slot24();

	unsigned char m_unmodelled04[8];
	Int m_0c;
	Int m_10;
	Int m_14;
	Int m_18;
	Int m_1c;
	Real m_20;
};

class W3DDisplay
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void rva006ECD30(Image *image, Real x0, Real y0,
		Real x1, Real y1, Int color);

private:
	unsigned char m_unmodelled04[0x160];
	Render2DClass *m_render2D;
};

// RVA 0x006ECD30, 384 bytes. Slot 54 of W3DDisplay; method identity unknown.
void W3DDisplay::rva006ECD30(Image *image, Real startX, Real startY,
	Real endX, Real endY, Int color)
{
	Render2DClass *render;
	Real textureScale = g_bfmeDefaultBU /
		(Real)(UnsignedInt)image->m_18;
	m_render2D->m_texturingEnabled = 1;
	textureScale = 0.5f * textureScale;

	const Rva006ECD30TextureRef &textureRef = image->slot24();
    render = m_render2D;
    if (textureRef.m_value != render->m_texture.m_value)
    {
        render->m_texture = textureRef;
        render->m_textureSet = render->m_texture.m_value ? (UnsignedInt)-1 : 0;
    }

	Real imageRatio;
	if (image->slot18())
		imageRatio = (Real)(UnsignedInt)image->m_10 /
			(Real)(UnsignedInt)image->m_18;
	else
		imageRatio = 0.0f;

	RectClass uv(textureScale, textureScale,
		(image->slot18() ?
			(Real)(UnsignedInt)image->m_0c /
				(Real)(UnsignedInt)image->m_14 : g_rva01075350) -
			textureScale,
		imageRatio - textureScale);

	Real opacity = image->m_20;
	Int c0 = (color & 0x00ffffff) | ((Int)(opacity * (Real)(UnsignedInt)((color >> 24) & 0xff)) << 24);
	Int c1 = (color & 0x00ffffff) | ((Int)(opacity * (Real)(UnsignedInt)((color >> 24) & 0xff)) << 24);
	RectClass screen(startX, startY, endX, endY);
	m_render2D->Add_Quad(screen, uv, c0, c0, c1, c1);
}
