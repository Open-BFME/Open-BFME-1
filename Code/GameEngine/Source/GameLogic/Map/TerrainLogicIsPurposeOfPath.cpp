// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?isPurposeOfPath@TerrainLogic@@UAE_NPAVWaypoint@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// TerrainLogic::isPurposeOfPath, retail 0x001AAAC0.
//
// This BFME body compares a waypoint's three path labels with the supplied
// label.  The retail parameter is a by-value AsciiString, and each returned
// label is destroyed through the established StringBase<char> body.

typedef bool Bool;

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed_06;
};

class AsciiString;

class AsciiStringCompareShim
{
public:
	__declspec(nothrow) int compare(const AsciiString &other) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public AsciiStringCompareShim
{
public:
	~AsciiString();

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_numChars == 0;
	}

	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	AsciiString getPathLabel1(void) const;
	AsciiString getPathLabel2(void) const;
	AsciiString getPathLabel3(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual Bool isPurposeOfPath(Waypoint *pWay, AsciiString label);
};

Bool TerrainLogic::isPurposeOfPath(Waypoint *pWay, AsciiString label)
{
	if (label.isEmpty() || pWay == 0)
		return false;

	Bool match = false;
	if (label.compare(pWay->getPathLabel1()) == 0)
		match = true;
	if (label.compare(pWay->getPathLabel2()) == 0)
		match = true;
	if (label.compare(pWay->getPathLabel3()) == 0)
		match = true;

	return match;
}
