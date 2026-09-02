// ?Rva009BEBB0Vp6DeblockBand@@YAXPAURva009BEBB0Vp6PostProc@@PAE1IIIPAI@Z
// partial score=0.13 date=2026-09-02
// Semantic reconstruction of the VP6 postprocessor's call-free SIMD band
// deblocker at retail 0x009BEBB0.  The original expands eight byte lanes into
// aligned word vectors and performs both edge directions in one unrolled body.
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /arch:SSE2

typedef unsigned char BfmeVp6Byte;
typedef unsigned int BfmeVp6Uint;

struct Rva009BEBB0Vp6PostProc
{
	BfmeVp6Byte m_unknown00[ 0x24 ];
	BfmeVp6Uint *m_fragmentQIndex;       // +0x24
	BfmeVp6Uint *m_fragmentVariances;    // +0x28
};

static __forceinline int rva009BEBB0Abs( int value )
{
	return value < 0 ? -value : value;
}

static __forceinline BfmeVp6Byte rva009BEBB0Clamp( int value )
{
	if( value < 0 )
		return 0;
	if( value > 255 )
		return 255;
	return (BfmeVp6Byte)value;
}

// Rebuild the eight centre samples of one ten-sample line.  Apart from doing
// eight lanes together, this is the arithmetic exposed by the retail SIMD
// stream: variance gates the low-pass path; a failed gate copies the centre
// samples unchanged.
static __forceinline BfmeVp6Uint rva009BEBB0FilterLine(
	const BfmeVp6Byte *source,
	int sourceStep,
	BfmeVp6Byte *destination,
	int destinationStep,
	BfmeVp6Uint qStep,
	unsigned short *samples )
{
	int i;
	int sum1 = 0;
	int sum2 = 0;
	int square1 = 0;
	int square2 = 0;

	for( i = 0; i < 10; ++i )
		samples[ i ] = source[ ( i - 5 ) * sourceStep ];

	for( i = 1; i <= 4; ++i )
	{
		int value = (int)samples[ i ] - 128;
		sum1 += value;
		square1 += value * value;
	}
	for( i = 5; i <= 8; ++i )
	{
		int value = (int)samples[ i ] - 128;
		sum2 += value;
		square2 += value * value;
	}

	BfmeVp6Uint variance1 =
		(BfmeVp6Uint)( square1 - ( sum1 >> 1 ) * ( ( sum1 + 1 ) >> 1 ) );
	BfmeVp6Uint variance2 =
		(BfmeVp6Uint)( square2 - ( sum2 >> 1 ) * ( ( sum2 + 1 ) >> 1 ) );
	BfmeVp6Uint limit = ( 3 * qStep * qStep ) >> 5;

	if( variance1 >= limit || variance2 >= limit ||
		rva009BEBB0Abs( (int)samples[ 4 ] - (int)samples[ 5 ] ) >= (int)qStep )
	{
		for( i = 1; i <= 8; ++i )
			destination[ ( i - 5 ) * destinationStep ] = (BfmeVp6Byte)samples[ i ];
		return variance1 + variance2;
	}

	int left = rva009BEBB0Abs( (int)samples[ 0 ] - (int)samples[ 1 ] ) < (int)qStep
		? samples[ 0 ] : samples[ 1 ];
	int right = rva009BEBB0Abs( (int)samples[ 8 ] - (int)samples[ 9 ] ) < (int)qStep
		? samples[ 9 ] : samples[ 8 ];
	int window = left * 3 + samples[ 1 ] + samples[ 2 ] + samples[ 3 ] + samples[ 4 ] + 4;

	for( i = 1; i <= 8; ++i )
	{
		int previous = i == 1 ? left : samples[ i - 1 ];
		int next = i == 8 ? right : samples[ i + 1 ];
		int value = ( ( window + samples[ i ] ) * 2 + previous - next ) >> 4;
		destination[ ( i - 5 ) * destinationStep ] = rva009BEBB0Clamp( value );
		window -= i < 4 ? left : samples[ i - 3 ];
		window += i < 4 ? samples[ i + 4 ] : right;
	}

	return variance1 + variance2;
}

// ?Rva009BEBB0Vp6DeblockBand@@YAXPAURva009BEBB0Vp6PostProc@@PAE1IIII@Z
void __cdecl Rva009BEBB0Vp6DeblockBand(
	Rva009BEBB0Vp6PostProc *postProc,
	BfmeVp6Byte *source,
	BfmeVp6Byte *destination,
	BfmeVp6Uint pitch,
	BfmeVp6Uint fragmentCount,
	BfmeVp6Uint firstFragment,
	BfmeVp6Uint *quantScale )
{
	// The retail frame is 0x104 bytes after 16-byte alignment.  These word
	// lanes preserve its ten-sample staging contract while keeping this body
	// portable C++ rather than an instruction lift.
	__declspec(align(16)) unsigned short samples[ 56 ];
	BfmeVp6Byte *sourcePtr = source;
	BfmeVp6Uint fragment = firstFragment;
	BfmeVp6Byte *destinationPtr = destination;
	BfmeVp6Uint endFragment = firstFragment + fragmentCount;

	while( fragment < endFragment )
	{
		BfmeVp6Uint qStep = quantScale[ postProc->m_fragmentQIndex[ fragment ] ];
		if( qStep > 3 )
		{
			BfmeVp6Uint acrossVariance = 0;
			BfmeVp6Uint downVariance = 0;
			int i;

			for( i = 0; i < 8; ++i )
				acrossVariance += rva009BEBB0FilterLine(
					sourcePtr + i, (int)pitch, destinationPtr + i, (int)pitch,
					qStep, samples );

			for( i = -4; i < 4; ++i )
				downVariance += rva009BEBB0FilterLine(
					sourcePtr + i * (int)pitch, 1,
					destinationPtr + i * (int)pitch, 1,
					qStep, samples );

			postProc->m_fragmentVariances[ fragment ] += acrossVariance;
			postProc->m_fragmentVariances[ fragment + fragmentCount ] += acrossVariance;
			postProc->m_fragmentVariances[ fragment ] += downVariance;
			postProc->m_fragmentVariances[ fragment + 1 ] += downVariance;
		}
		else
		{
			int row;
			for( row = -4; row < 4; ++row )
			{
				int column;
				for( column = 0; column < 8; ++column )
					destinationPtr[ row * (int)pitch + column ] =
						sourcePtr[ row * (int)pitch + column ];
			}
		}

		++fragment;
		sourcePtr += 8;
		destinationPtr += 8;
	}
}
