// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AssaultTransportAIUpdateBase::call_0002105d, retail 0x002B4320,
// 124 bytes.
//
// Lives entirely inside AssaultTransportAIUpdateIface5's opaque
// this+0x344..+0x398 blob (see AssaultTransportAIUpdateCtorThunk.cpp, which
// declares this method but leaves the body unnamed). Clears a fixed
// 10-element table -- a dword array at +0x344, then two parallel byte
// arrays at +0x36c and +0x376 -- up to whatever count is currently held at
// +0x398 (the ctor sets that count to 10 before calling this, so on
// construction the whole table is wiped), then unconditionally zeroes six
// scalar dwords at +0x380..+0x394, three scalar bytes at +0x39c..+0x39e,
// and the count itself.

typedef int Int;
typedef unsigned char Byte;
typedef unsigned int UnsignedInt;

class AssaultTransportAIUpdateBase
{
protected:
	void call_0002105d( void );

public:
	Byte m_pad000[0x344];
	Int m_arrDword[10];		// +0x344 .. +0x36c
	Byte m_arrByte1[10];		// +0x36c .. +0x376
	Byte m_arrByte2[10];		// +0x376 .. +0x380
	UnsignedInt m_380;
	UnsignedInt m_384;
	UnsignedInt m_388;
	UnsignedInt m_38c;
	UnsignedInt m_390;
	UnsignedInt m_394;
	Int m_398;
	Byte m_39c;
	Byte m_39d;
	Byte m_39e;
};

// ?call_0002105d@AssaultTransportAIUpdateBase@@IAEXXZ
void AssaultTransportAIUpdateBase::call_0002105d( void )
{
	Int count = m_398;
	if( count > 0 )
	{
		for( Int i = 0; i < m_398; ++i )
		{
			m_arrDword[i] = 0;
			m_arrByte1[i] = 0;
			m_arrByte2[i] = 0;
		}
	}

	m_398 = 0;
	m_380 = 0;
	m_384 = 0;
	m_388 = 0;
	m_38c = 0;
	m_390 = 0;
	m_394 = 0;
	m_39c = 0;
	m_39d = 0;
	m_39e = 0;
}
