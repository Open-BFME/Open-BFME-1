// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// drawSkinnyBorder at RVA 0079BCA0, 2304 bytes.
// The original W3DControlBar counterpart supplies the FrameT/B/L/R and four
// corner-image tiling. BFME wraps the float-coordinate display slot D4 with
// B0/DC. The shared Display header still declares the ZH integer virtual ABI,
// so this translation-unit view preserves the observed slots without changing it.
// Direct contracts use the canonical StringBase and existing ImageCollection.
// Evidence: targets/game/reverse/identity_evidence/0079bca0-skinny-border.md.
#include "ascii_string.h"
typedef int Int;
class Image;
class ImageCollection {public: const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
class Display;
extern Display *TheDisplay;
class Rva0079BCA0DisplayView {public:
 virtual void slot00()=0;
 virtual void slot04()=0;
 virtual void slot08()=0;
 virtual void slot0C()=0;
 virtual void slot10()=0;
 virtual void slot14()=0;
 virtual void slot18()=0;
 virtual void slot1C()=0;
 virtual void slot20()=0;
 virtual void slot24()=0;
 virtual void slot28()=0;
 virtual void slot2C()=0;
 virtual void slot30()=0;
 virtual void slot34()=0;
 virtual void slot38()=0;
 virtual void slot3C()=0;
 virtual void slot40()=0;
 virtual void slot44()=0;
 virtual void slot48()=0;
 virtual void slot4C()=0;
 virtual void slot50()=0;
 virtual void slot54()=0;
 virtual void slot58()=0;
 virtual void slot5C()=0;
 virtual void slot60()=0;
 virtual void slot64()=0;
 virtual void slot68()=0;
 virtual void slot6C()=0;
 virtual void slot70()=0;
 virtual void slot74()=0;
 virtual void slot78()=0;
 virtual void slot7C()=0;
 virtual void slot80()=0;
 virtual void slot84()=0;
 virtual void slot88()=0;
 virtual void slot8C()=0;
 virtual void slot90()=0;
 virtual void slot94()=0;
 virtual void slot98()=0;
 virtual void slot9C()=0;
 virtual void slotA0()=0;
 virtual void slotA4()=0;
 virtual void slotA8()=0;
 virtual void slotAC()=0;
 virtual void slotB0()=0;
 virtual void slotB4()=0;
 virtual void slotB8()=0;
 virtual void slotBC()=0;
 virtual void slotC0()=0;
 virtual void slotC4()=0;
 virtual void slotC8()=0;
 virtual void slotCC()=0;
 virtual void slotD0()=0;
 virtual void slotD4(const Image*,float,float,float,float,int,int)=0;
 virtual void slotD8()=0;
 virtual void slotDC()=0;
 inline void drawImage(const Image*image, int x,int y,int ex,int ey,int color=-1,int mode=2) {
 slotB0(); slotD4(image,float(x),float(y),float(ex),float(ey),color,mode); slotDC();
 }
};
inline Rva0079BCA0DisplayView *SkinnyDisplay() {return (Rva0079BCA0DisplayView*)TheDisplay;}
void drawSkinnyBorder( Int x, Int y, Int width, Int height)
{

	enum
	{
		BORDER_CORNER_SIZE	= 5,
		BORDER_LINE_SIZE		= 5,
	};
	Int Offset = 2;
	Int OffsetLower = 5;

	// save original x, y
	Int originalX = x;
	Int originalY = y;
	Int maxX = x + width;
	Int maxY = y + height;
	Int x2, y2;			// used for simultaneous drawing of line pairs
	Int size = 5;
	Int halfSize = size / 2;
	const Image *image1, *image2;
	// Draw Horizontal Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	y = originalY - Offset;
	y2 = maxY - OffsetLower;
	x2 = maxX - (OffsetLower + BORDER_LINE_SIZE);
	image1 = TheMappedImageCollection->findImageByName("FrameT");
	image2 = TheMappedImageCollection->findImageByName("FrameB");
	for( x=(originalX + 3); x <= x2; x += BORDER_LINE_SIZE )
	{

		SkinnyDisplay()->drawImage( image1,
													 x, y, x + size, y + size );
		SkinnyDisplay()->drawImage( image2,
													 x, y2, x + size, y2 + size );

	}

	x2 = maxX - 5;//BORDER_CORNER_SIZE;

	// x == place to draw remainder if any
	if( (x2 - x) >= (BORDER_LINE_SIZE / 2) )
	{
		
		//Blit Half piece
		SkinnyDisplay()->drawImage( image1,
													 x, y, x + halfSize, y + size );
		SkinnyDisplay()->drawImage( image2,
													 x, y2, x + halfSize, y2 + size );

		x += (BORDER_LINE_SIZE / 2);

	}

	// x2 - x ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( x < x2 )
	{
		x -= ((BORDER_LINE_SIZE / 2) - (((x2 - x) + 1) & ~1));

		//Blit Half piece
		SkinnyDisplay()->drawImage(image1,
													 x, y, x + halfSize, y + size );
		SkinnyDisplay()->drawImage( image2,
													 x, y2, x + halfSize, y2 + size );

	}

	// Draw Vertical Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	image1 = TheMappedImageCollection->findImageByName("FrameL");
	image2 = TheMappedImageCollection->findImageByName("FrameR");

	x = originalX - Offset;
	x2 = maxX - OffsetLower;
	y2 = maxY - (OffsetLower + BORDER_LINE_SIZE);

	for( y=(originalY + 3); y <= y2; y += BORDER_LINE_SIZE )
	{

		SkinnyDisplay()->drawImage( image1,
													 x, y, x + size, y + size );
		SkinnyDisplay()->drawImage( image2,
													 x2, y, x2 + size, y + size );

	}

	y2 = maxY - OffsetLower;//BORDER_CORNER_SIZE;

	// y == place to draw remainder if any
	if( (y2 - y) >= (BORDER_LINE_SIZE / 2) )
	{

		//Blit Half piece
		SkinnyDisplay()->drawImage( image1,
													 x, y, x + size, y + halfSize );
		SkinnyDisplay()->drawImage( image2,
													 x2, y, x2 + size, y + halfSize );

		y += (BORDER_LINE_SIZE / 2);
	}

	// y2 - y ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( y < y2 )
	{
		y -= ((BORDER_LINE_SIZE / 2) - (((y2 - y) + 1) & ~1));

		//Blit Half piece
		SkinnyDisplay()->drawImage( image1,
													 x, y, x + size, y + halfSize );
		SkinnyDisplay()->drawImage( image2,
													 x2, y, x2 + size, y + halfSize );

	}

	// Draw Corners
	x = originalX - 2;//BORDER_CORNER_SIZE ;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerUL");
	SkinnyDisplay()->drawImage( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerUR");
	SkinnyDisplay()->drawImage(image1,
												 x, y, x + size, y + size );
	x = originalX - 2;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerLL");
	SkinnyDisplay()->drawImage( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerLR");
	SkinnyDisplay()->drawImage(image1,
												 x, y, x + size, y + size );


}
