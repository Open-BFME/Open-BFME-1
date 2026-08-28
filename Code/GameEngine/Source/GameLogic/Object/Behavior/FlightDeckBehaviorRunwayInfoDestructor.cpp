// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FlightDeckBehavior::RunwayInfo's destructor, retail 0x002BC7A0,
// 90 bytes. The body carried only a machine byte-dump row; the symbols.csv pin
// fronts it from the ILT at 0x00036241, which the _Destroy range loop over this
// element type calls.
//
// Two members go, in reverse declaration order: an AsciiString at +0xB0 first,
// then ten Coord3Ds at +0x2C through the eh vector destructor iterator, which
// takes the base, the twelve-byte stride, the count and the element's own
// destructor. The size of the class is the 0xB8 that the already-ledgered
// _Destroy range thunk and the vector destructor over this element both pin
// from their strides.
//
// The frame stores this before the first destruction because the iterator call
// needs an unwind record, and the unwind slot goes 0 then -1 across the two.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	~Coord3D();						// ILT 0x0001364C

private:
	float m_bfmeX, m_bfmeY, m_bfmeZ;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	struct RunwayInfo
	{
		~RunwayInfo(void);

		unsigned char m_bfmeHeadA[0x2C];
		Coord3D m_bfmeSpots[10];			// +0x2C
		unsigned char m_bfmeHeadB[0xB0 - 0xA4];
		AsciiString m_bfmeName;				// +0xB0
		unsigned char m_bfmeTail[0xB8 - 0xB4];
	};
};

// ??1RunwayInfo@FlightDeckBehavior@@QAE@XZ
FlightDeckBehavior::RunwayInfo::~RunwayInfo(void)
{
}
