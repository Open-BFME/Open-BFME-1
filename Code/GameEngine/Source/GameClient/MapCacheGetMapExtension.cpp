// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMapExtension@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp

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
	AsciiString getMapExtension() const;
};

AsciiString MapCache::getMapExtension() const
{
	return AsciiString("map");
}
