// ?Rva009A9AD0Scale2D@@YAXPAEHIH0HII0EIIIII@Z
// partial score=0.84 date=2026-09-16
// Clean reconstruction of the VPx Scale2D helper at retail RVA 0x009A9AD0.
// cl: /DNDEBUG /MD /O2

#include <string.h>

typedef unsigned char Byte;
typedef void (__cdecl *Scale1D)( const Byte *, int, unsigned int, unsigned int,
	Byte *, int, unsigned int, unsigned int );

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
	int i, j, k;
	int bands;
	int destBandHeight;
	int sourceBandHeight;
	Scale1D scaleVertical = (Scale1D)0x00DA9980;
	Scale1D scaleHorizontal = (Scale1D)0x00DA9980;
	Scale1D scaleTwoToOne = (Scale1D)0x00DA9A90;
	if( hscale == 2 && hratio == 1 )
		scaleHorizontal = scaleTwoToOne;
	if( vscale == 2 && vratio == 1 )
		scaleVertical = interlaced ? scaleTwoToOne : (Scale1D)0x00DA9A20;

	if( sourceHeight == destHeight )
	{
		for( k = 0; k < (int)destHeight; ++k )
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
			if( k * sourceBandHeight + i < (int)sourceHeight )
				scaleHorizontal( source + i * sourcePitch, 1, hscale, sourceWidth + 1,
					tempArea + i * destPitch, 1, hratio, destWidth );
			else
				memcpy( tempArea + i * destPitch,
					tempArea + ( i - 1 ) * destPitch, destPitch );
		}

		for( j = 0; j < (int)destWidth; ++j )
			scaleVertical( &tempArea[j], destPitch, vscale, sourceBandHeight + 1,
				&dest[j], destPitch, vratio, destBandHeight );

		memcpy( tempArea, tempArea + sourceBandHeight * destPitch, destPitch );
		source += sourceBandHeight * sourcePitch;
		dest += destBandHeight * destPitch;
	}
}
