// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ?setWaypointName@MapObject@@QAEXVAsciiString@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp

// Open-BFME5: MapObject::setWaypointName
// Retail: Dict global setAsciiString(name) then assign result into this+0x24.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	unsigned int m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	AsciiString *setAsciiString(AsciiString name);
};

extern Dict g_theWaypointNameDict;

class AsciiStringField
{
public:
	void set(AsciiString *src);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapObject.h
class MapObject
{
public:
	void setWaypointName(AsciiString name);

private:
	char m_pad[0x24];
	AsciiStringField m_name;
};

// ?setWaypointName@MapObject@@QAEXVAsciiString@@@Z
void MapObject::setWaypointName(AsciiString name)
{
	AsciiString *result = g_theWaypointNameDict.setAsciiString(name);
	m_name.set(result);
}
