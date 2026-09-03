// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMapDir@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// Identity correction from invented ?bfmeGoDNE@BfmeThingDNE@@. Retail 33B at
// 0x0044FF90 is the sibling of landed getMapExtension (0x0044FFC0, "map"):
// construct the hidden return from the "Maps" literal and ret 4. Matched
// callers getUserMapDir and writeCacheINI reach it through ILT 0x000079F5.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	AsciiString getMapDir() const;
};

AsciiString MapCache::getMapDir() const
{
	return AsciiString("Maps");
}
