// The adjacent 0x00459D20 constructor, 0x00459F00 reset, 0x00459F70
// STLport vector resize, and 0x00459B10 sampler describe one flat scalar
// field: a float vector at +0x00, two extents at +0x0C/+0x10, a scale at
// +0x14, a state at +0x18, and a ready byte at +0x1C.  The owning class has
// no vtable load in this body, so its exact public identity remains unknown.

#include <stdlib.h>

typedef unsigned short R3HeightSample;

namespace _STL
{
template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	void resize( unsigned int count, Type value );
	Type &operator[]( unsigned int index ) { return m_begin[ index ]; }
	Type *m_begin;
	Type *m_finish;
	Type *m_end;
};
}
class GenKey
{
public:
	int fetch( bool *found );
	int m_a;
	int m_b;
};

class GenTable
{
public:
	float lookup( int key );
};

class R3FieldGlobals
{
public:
	char m_padding[ 0xE68 ];
	float m_default;
};

extern GenKey GenKey0012A79E0;
extern GenKey GenKey0012A79F0;
extern GenKey GenKey0012A79F8;
extern GenTable GenTable0012ED5E0;
extern R3FieldGlobals *R3FieldGlobals0012ED5C8;

extern float R3FieldZero01075350;
extern float R3FieldSampleScale010F653C;
extern float R3FieldSlope1096CF4;
extern float R3FieldDiagonal10861AC;
extern float g_bfmeDefaultBU;
extern float g_bfmeDirectionWeight1285;
extern "C" __declspec(dllimport) double __cdecl BfmeFloorER( double value );

__forceinline int Rva0045A000FloatToInt( float value )
{
	int result;
	__asm
	{
		fld value
		fistp result
	}
	return result;
}

class Rva0045A000
{
public:
	void initialize( const R3HeightSample *source, int unused,
		int sourceWidth, int sourceHeight, int state );
	float sample( float x, float y );

	_STL::vector<float, _STL::allocator<float> > m_data;
	int m_width;
	int m_height;
	float m_scale;
	int m_state;
	bool m_ready;
};

void Rva0045A000::initialize( const R3HeightSample *source, int unused,
	int sourceWidth, int sourceHeight, int state )
{
	bool found;
	float setting = GenTable0012ED5E0.lookup(
		GenKey0012A79E0.fetch( &found ) );
	if( !found )
		setting = R3FieldGlobals0012ED5C8->m_default;
	if( setting == R3FieldZero01075350 )
		return;

	float low = GenTable0012ED5E0.lookup(
		GenKey0012A79F0.fetch( &found ) );
	if( !found )
		low = -9999999.0f;
	float high = GenTable0012ED5E0.lookup(
		GenKey0012A79F8.fetch( &found ) );
	if( !found )
		high = 9999999.0f;
	if( high < low )
	{
		float temporary = high;
		high = low;
		low = temporary;
	}

	m_width = ( sourceWidth + 3 ) / 4;
	m_height = ( sourceHeight + 3 ) / 4;
	m_scale = 40.0f;
	m_data.resize( m_width * m_height, 0.0f );

	for( int outputX = 0; outputX < m_width; ++outputX )
	{
		for( int outputY = 0; outputY < m_height; ++outputY )
		{
			float value = R3FieldZero01075350;
			for( int x = outputX * 4; x < outputX * 4 + 4; ++x )
			{
				for( int y = outputY * 4; y < outputY * 4 + 4; ++y )
				{
					if( x < sourceWidth && y < sourceHeight )
					{
						float sample = source[ y * sourceWidth + x ] *
							R3FieldSampleScale010F653C;
						if( sample < low )
							sample = low;
						else if( sample > high )
							sample = high;
						if( value < sample )
							value = sample;
					}
				}
			}
			m_data[ outputY * m_width + outputX ] = value;
		}
	}

	int outputX2;
	int outputY2;
	int x;
	int y;
	bool changed = false;
	int passes = m_width;
	if( m_height > passes )
		passes = m_height;
	do
	{
		changed = false;
		for( outputX2 = 0; outputX2 < m_width; ++outputX2 )
		{
			for( outputY2 = 0; outputY2 < m_height; ++outputY2 )
			{
				for( x = outputX2 - 1; x < outputX2 + 2; ++x )
				{
					if( x < 0 || x >= m_width )
						continue;
					for( y = outputY2 - 1; y < outputY2 + 2; ++y )
					{
						if( y >= 0 && y < m_height )
						{
							float delta = setting;
							delta *= m_scale;
							delta *= R3FieldSlope1096CF4;
							if( x != outputX2 && y != outputY2 )
								delta *= R3FieldDiagonal10861AC;
							float candidate = m_data[ y * m_width + x ] - delta;
							float *current = &m_data[ outputY2 * m_width + outputX2 ];
							if( candidate > *current )
							{
								*current = candidate;
								changed = true;
							}
						}
					}
					}
			}
		}
		--passes;
	}
	while( changed && passes > 0 );

	m_state = state;
	m_ready = true;
}

float Rva0045A000::sample( float x, float y )
{
	if( !m_ready )
		return R3FieldZero01075350;

	float scale = g_bfmeDefaultBU / m_scale;
	float offset = (float)m_state * g_bfmeDirectionWeight1285;
	register float scaledX = (x + offset) * scale;
	register float scaledY = (y + offset) * scale;
	float xFloor = (float)BfmeFloorER( (double)scaledX );
	register int xIndex = Rva0045A000FloatToInt( xFloor );
	float yFloor = (float)BfmeFloorER( (double)scaledY );
	register int yIndex = Rva0045A000FloatToInt( yFloor );
	float xFraction = scaledX - (float)xIndex;
	float yFraction = scaledY - (float)yIndex;

	if( xIndex < 0 )
		xIndex = 0;
	if( yIndex < 0 )
		yIndex = 0;

	if( xIndex > m_width - 1 )
		xIndex = m_width - 1;
	if( yIndex > m_height - 1 )
		yIndex = m_height - 1;
	if( xIndex > m_width - 2 || yIndex > m_height - 2 )
		return m_data[ yIndex * m_width + xIndex ];

	int index = yIndex * m_width + xIndex;
	float p0 = m_data[ index ];
	float p2 = m_data[ index + m_width + 1 ];
	if( yFraction > xFraction )
	{
		float p3 = m_data[ index + m_width ];
		float height = (1.0f - yFraction) * (p0 - p3) +
			xFraction * (p2 - p3);
		height = height + p3;
		return height;
	}
	{
		float p1 = m_data[ index + 1 ];
		float height = (1.0f - xFraction) * (p0 - p1) +
			yFraction * (p2 - p1);
		height = height + p1;
		return height;
	}
}
