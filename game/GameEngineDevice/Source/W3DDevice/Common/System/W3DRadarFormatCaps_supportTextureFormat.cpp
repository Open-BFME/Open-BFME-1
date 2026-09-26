// cl: /DNDEBUG /MD /EHsc

// W3DRadarFormatCaps::supportTextureFormat, retail 0x0091B4F0. No calls: a
// bounds-checked byte table and then a switch on FourCC values.
//
// Formats 0 through 99 are answered straight out of the table at +0x13E - the
// bound is signed at both ends, which is the `jl' and the `jge'. Anything
// outside that range falls through to the five DXT codes, each with its own
// byte at +0x1A2 through +0x1A6, and anything else is false.
//
// The compare chain is MSVC's binary search over those five constants, not a
// jump table: it tests 'DXT3' first and splits.

typedef bool Bool;
typedef int Int;

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0
};

class W3DRadarFormatCaps
{
public:
	Bool supportTextureFormat( WW3DFormat format );

private:
	unsigned char m_unmodelled_00[ 0x13E ];
	Bool m_simpleFormats[ 100 ];			// +0x13E
	Bool m_dxt1;							// +0x1A2
	Bool m_dxt2;							// +0x1A3
	Bool m_dxt3;							// +0x1A4
	Bool m_dxt4;							// +0x1A5
	Bool m_dxt5;							// +0x1A6
};

// ?supportTextureFormat@W3DRadarFormatCaps@@QAE_NW4WW3DFormat@@@Z
Bool W3DRadarFormatCaps::supportTextureFormat( WW3DFormat format )
{
	if( (Int)format >= 0 && (Int)format < 100 )
		return m_simpleFormats[ (Int)format ];

	switch( (Int)format )
	{
		case 0x31545844:	return m_dxt1;
		case 0x32545844:	return m_dxt2;
		case 0x33545844:	return m_dxt3;
		case 0x34545844:	return m_dxt4;
		case 0x35545844:	return m_dxt5;
	}

	return false;
}
