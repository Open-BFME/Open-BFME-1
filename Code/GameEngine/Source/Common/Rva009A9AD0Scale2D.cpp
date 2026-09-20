// VPx Scale2D conversion recovered from the retail codec body at RVA 0x009A9AD0.
// Callback bodies at 0x009A9980 and 0x009A9A20 use the witnessed Scale1D ABI.
// cl: /DNDEBUG /MD /O2

#include <string.h>

typedef unsigned char Byte;
typedef void (__cdecl *Scale1D)( const Byte *, int, unsigned int, unsigned int,
	Byte *, int, unsigned int, unsigned int );

extern void __cdecl Rva009A9980( const Byte *, int, unsigned int, unsigned int,
	Byte *, int, unsigned int, unsigned int );
extern void __cdecl Rva009A9A20( const Byte *, int, unsigned int, unsigned int,
	Byte *, int, unsigned int, unsigned int );
extern void __cdecl bfmeCopyColAA90( Byte *, int, int, int,
	Byte *, int, int, int );

void Rva009A9AD0Scale2D(
	Byte *source,
	int sourcePitch,
	unsigned int sourceWidth,
	unsigned int sourceHeight,
	Byte *dest,
	int destPitch,
	unsigned int destWidth,
	unsigned int destHeight,
	Byte *tempArea,
	Byte tempAreaHeight,
	unsigned int hscale,
	unsigned int hratio,
	unsigned int vscale,
	unsigned int vratio,
	unsigned int interlaced )
{
	unsigned int i, j, k;
	unsigned int bands;
	unsigned int destBandHeight;
	unsigned int sourceBandHeight;
	Scale1D scaleVertical = Rva009A9980;
	Scale1D scaleHorizontal = Rva009A9980;
	Scale1D scaleTwoToOne = (Scale1D)bfmeCopyColAA90;
	if( hscale == 2 && hratio == 1 )
		scaleHorizontal = scaleTwoToOne;
	if( vscale == 2 && vratio == 1 )
		scaleVertical = interlaced ? scaleTwoToOne : Rva009A9A20;

	if( sourceHeight == destHeight )
	{
		for( k = 0; k < destHeight; ++k )
		{
			scaleHorizontal( source, 1, hscale, sourceWidth + 1,
				dest, 1, hratio, destWidth );
			source += sourcePitch;
			dest += destPitch;
		}
		return;
	}

	if( destHeight > sourceHeight )
	{
		destBandHeight = tempAreaHeight - 1;
		sourceBandHeight = destBandHeight * sourceHeight / destHeight;
	}
	else
	{
		sourceBandHeight = tempAreaHeight - 1;
		destBandHeight = sourceBandHeight * vratio / vscale;
	}

	scaleHorizontal( source, 1, hscale, sourceWidth + 1,
		tempArea, 1, hratio, destWidth );
	bands = ( destHeight + destBandHeight - 1 ) / destBandHeight;

	for( k = 0; k < bands; ++k )
	{
		for( i = 1; i < sourceBandHeight + 1; ++i )
		{
			if( k * sourceBandHeight + i < sourceHeight )
				scaleHorizontal( source + i * sourcePitch, 1, hscale, sourceWidth + 1,
					tempArea + i * destPitch, 1, hratio, destWidth );
			else
				memcpy( tempArea + i * destPitch,
					tempArea + ( i - 1 ) * destPitch, destPitch );
		}

		for( j = 0; j < destWidth; ++j )
			scaleVertical( &tempArea[j], destPitch, vscale, sourceBandHeight + 1,
				&dest[j], destPitch, vratio, destBandHeight );

		memcpy( tempArea, tempArea + sourceBandHeight * destPitch, destPitch );
		source += sourceBandHeight * sourcePitch;
		dest += destBandHeight * destPitch;
	}
}
