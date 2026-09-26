// ?drawImageCore@W3DDisplay@@UAEXPAVImage@@MMMMH@Z
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef unsigned long UnsignedInt;

extern Real g_bfmeDefaultBU;
#define g_bfmeK1253 (*(Real *)0x0107533c)
extern const Real BfmeZeroRange;
extern "C" Real g_bfmeUint32Scale;

class TextureClass
{
public:
	unsigned char m_unmodelled00[4];
	unsigned short m_refCount;
	void Release_Ref();
};

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

class Render2DClass
{
public:
	unsigned char m_unmodelled00[0x4c];
	TextureClass *m_texture;
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
	virtual TextureClass **slot24();

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
	virtual void drawImageCore(Image *image, Real x0, Real y0,
		Real x1, Real y1, Int color);

private:
	unsigned char m_unmodelled04[0x160];
	Render2DClass *m_render2D;
};

// ?drawImageCore@W3DDisplay@@UAEXPAVImage@@MMMMH@Z
void W3DDisplay::drawImageCore(Image *image, Real x0, Real y0,
	Real x1, Real y1, Int color)
{
	Render2DClass *render;
	Real textureScale = g_bfmeDefaultBU /
		(Real)(UnsignedInt)image->m_18;
	m_render2D->m_texturingEnabled = 1;
	textureScale = g_bfmeK1253 * textureScale;

	TextureClass ** const textureRef = image->slot24();
	render = m_render2D;
	if (*textureRef != render->m_texture)
	{
		if (*textureRef)
			++(*textureRef)->m_refCount;
		if (render->m_texture)
			render->m_texture->Release_Ref();
		render->m_texture = *textureRef;
		render->m_textureSet = render->m_texture ?
			(UnsignedInt)-1 : 0;
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
				(Real)(UnsignedInt)image->m_14 : BfmeZeroRange) -
			textureScale,
		imageRatio - textureScale);

	Real opacity = image->m_20;
	Int alpha = (color >> 24) & 0xff;
	color = (color & 0x00ffffff) |
		((Int)(opacity * (Real)alpha) << 24);
	RectClass screen(x0, y0, x1, y1);
	m_render2D->Add_Quad(screen, uv, color, color, color, color);
}
