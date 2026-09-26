// cl: /DNDEBUG /MD /EHsc
// BFME's real-coordinate animation draw with an explicit opacity byte.

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

class Image;

struct Anim2DTemplateFrameView
{
	unsigned char m_pad00[0x0c];
	const Image * const *m_images;
	UnsignedShort m_numFrames;
};

class Display
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9c();
	virtual void slota0(); virtual void slota4(); virtual void slota8(); virtual void slotac();
	virtual void beginImageDraw();
	virtual void slotb4(); virtual void slotb8(); virtual void slotbc();
	virtual void slotc0(); virtual void slotc4(); virtual void slotc8(); virtual void slotcc();
	virtual void slotd0();
	virtual void drawImageCore(const Image *, Real, Real, Real, Real, Int, Int);
	virtual void slotd8();
	virtual void endImageDraw();
};

extern Display *TheDisplay;

class Rva005BA910Anim2D;
class Anim2D
{
	friend class Rva005BA910Anim2D;
protected:
	void tryNextFrame();
};

class Rva005BA910Anim2D
{
public:
	void draw(Real x, Real y, UnsignedByte opacity);
private:
	void *m_vtable;
	UnsignedShort m_currentFrame;
	unsigned char m_pad06[6];
	Anim2DTemplateFrameView *m_template;
	UnsignedByte m_status;
	unsigned char m_pad11[15];
	void *m_collectionSystem;
	unsigned char m_pad24[8];
	Int m_width;
	Int m_height;
};


void Rva005BA910Anim2D::draw(Real x, Real y, UnsignedByte opacity)
{
	UnsignedShort frame = m_currentFrame;
	Anim2DTemplateFrameView *animation = m_template;
	const Image *image;
	if (frame < animation->m_numFrames)
		image = animation->m_images[frame];
	else
		image = 0;

	Real y1 = y + m_height;
	Real x1 = x + m_width;
	Display *display = TheDisplay;
	TheDisplay->beginImageDraw();
	unsigned int color = opacity;
	color = (color << 8) | opacity;
	color = (color << 8) | opacity;
	color = (color << 8) | opacity;
	display->drawImageCore(image, x, y, x1, y1, color, 3);
	display->endImageDraw();
	if (m_collectionSystem == 0 && !(m_status & 1))
		((Anim2D *)this)->tryNextFrame();
}
