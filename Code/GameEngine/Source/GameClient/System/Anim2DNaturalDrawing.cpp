// cl: /DNDEBUG /MD /EHsc
// readable body of ?draw@Anim2D@@QAEXHH@Z: natural-size Anim2D drawing

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

class Image;

struct ICoord2D
{
	Int x;
	Int y;
};

class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void drawImageCore(const Image *image, Real x0, Real y0,
		Real x1, Real y1, Int color, Int mode);
	virtual void unused54();
	virtual void endImageDraw();
};

extern Display *TheDisplay;
#define g_bfmeScaleB3 (*(Real *)0x01084068)

inline Int GameMakeColor(UnsignedByte red, UnsignedByte green,
	UnsignedByte blue, UnsignedByte alpha)
{
	return ((unsigned int)alpha << 24) | ((unsigned int)red << 16) |
		((unsigned int)green << 8) | blue;
}

inline void drawImage(Display *display, const Image *image, Real x0, Real y0,
	Real x1, Real y1, Int color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, x0, y0, x1, y1, color, mode);
	display->endImageDraw();
}

struct BfmeAnim2DTemplate
{
	unsigned char m_unreconstructed_00[0x0c];
	const Image * const *m_images;
	UnsignedShort m_numFrames;
};

struct BfmeImageFields
{
	unsigned char m_unreconstructed_00[0x24];
	ICoord2D m_imageSize;
};

class Anim2D
{
public:
	void draw(Int x, Int y);
protected:
	void tryNextFrame();
private:
	void *m_vtable;
	UnsignedShort m_currentFrame;
	unsigned char m_unreconstructed_06[0x02];
	Int m_lastUpdateFrame;
	BfmeAnim2DTemplate *m_template;
	UnsignedByte m_status;
	unsigned char m_unreconstructed_11[0x0b];
	Real m_alpha;
	void *m_collectionSystem;
};

void Anim2D::draw(Int x, Int y)
{
	UnsignedShort currentFrame = m_currentFrame;
	BfmeAnim2DTemplate *animTemplate = m_template;
	const Image *image;
	if (currentFrame < animTemplate->m_numFrames)
		image = animTemplate->m_images[currentFrame];
	else
		image = 0;

	Real alphaValue = m_alpha;
	alphaValue *= g_bfmeScaleB3;
	register Int alpha = alphaValue;
	Int color = GameMakeColor(255, 255, 255, alpha);
	const ICoord2D *imageSize = &((const BfmeImageFields *)image)->m_imageSize;
	drawImage(TheDisplay, image, (Real)x, (Real)y,
		(Real)(x + imageSize->x), (Real)(y + imageSize->y), color, 2);

	if (m_collectionSystem == 0 && (m_status & 1) == 0)
		tryNextFrame();
}
