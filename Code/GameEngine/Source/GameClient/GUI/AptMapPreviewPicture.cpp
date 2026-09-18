// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
//
// AptMapPreview::picture, retail 0x005204F0, 156 bytes.
// AptMapPreview::initGadgets at 0x00521AE0 pushes the selector string
// "AptMapPreview::Picture" at 0x00521B6C and loads this body's ILT thunk
// 0x0000AFAB twenty bytes later, which is what names it.
//
// The APT movie calls this every frame to paint the cached map picture into
// the rectangle it hands over. AptMapPreviewImages.cpp at 0x00520E70
// already witnesses the two fields this reads, the owned Image at +0x34 and
// the ownership flag at +0x38.

extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(
	const void *address, unsigned long size );

class Image;

#include "basetype.h"

// The BFME display vtable, as BfmeOverlay1293_bfmeDraw1293.cpp witnesses it:
// slot 44 opens a two-dimensional batch and slot 55 closes it. Slot 53 is the
// image draw that Zero Hour spells drawImage, widened to floats.
class Display
{
public:
	virtual void reserved00(); virtual void reserved01();
	virtual void reserved02(); virtual void reserved03();
	virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07();
	virtual void reserved08(); virtual void reserved09();
	virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13();
	virtual void reserved14(); virtual void reserved15();
	virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19();
	virtual void reserved20(); virtual void reserved21();
	virtual void reserved22(); virtual void reserved23();
	virtual void reserved24(); virtual void reserved25();
	virtual void reserved26(); virtual void reserved27();
	virtual void reserved28(); virtual void reserved29();
	virtual void reserved30(); virtual void reserved31();
	virtual void reserved32(); virtual void reserved33();
	virtual void reserved34(); virtual void reserved35();
	virtual void reserved36(); virtual void reserved37();
	virtual void reserved38(); virtual void reserved39();
	virtual void reserved40(); virtual void reserved41();
	virtual void reserved42(); virtual void reserved43();
	virtual void bfmeBeginBatch();
	virtual void reserved45(); virtual void reserved46();
	virtual void reserved47(); virtual void reserved48();
	virtual void reserved49(); virtual void reserved50();
	virtual void reserved51(); virtual void reserved52();
	virtual void drawImage( const Image *image, float startX, float startY,
		float endX, float endY, int color, int mode );
	virtual void reserved54();
	virtual void bfmeEndBatch();
};

extern Display * const TheDisplay;

// Layout witnessed by AptMapPreviewImages.cpp at 0x00520E70.
class AptMapPreview
{
public:
	void picture( const Coord2D *origin, const Coord2D *extent,
		void *unusedA, void *unusedB );

private:
	char m_unmodelled[ 0x34 ];
	const Image *m_picture;
	bool m_pictureOwned;
};

void AptMapPreview::picture( const Coord2D *origin, const Coord2D *extent,
	void *unusedA, void *unusedB )
{
	(void)unusedA;
	(void)unusedB;

	if ( m_picture == 0 )
		return;
	if ( IsBadReadPtr( m_picture, 0x34 ) )
	{
		m_picture = 0;
		return;
	}

	float bottom = extent->y + origin->y;
	float right = origin->x + extent->x;
	float top = origin->y;
	float left = origin->x;
	const Image *image = m_picture;
	Display *device = TheDisplay;
	TheDisplay->bfmeBeginBatch();
	device->drawImage( image, left, top, right, bottom, -1, 2 );
	device->bfmeEndBatch();
}
