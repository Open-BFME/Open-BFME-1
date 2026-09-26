// cl: /DNDEBUG /MD /EHsc

// Open-BFME: the retail ILT at 0x00024E0B forwards to the matched body at
// 0x00601B50. The caller and targets/game/reverse/symbols.csv identify the target method.

typedef int Int;

enum BodyDamageType
{
	BODY_DAMAGE_TYPE_UNKNOWN = 0
};

class AsciiString
{
	void *m_data;
};

class TerrainRoadType
{
public:
	void friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString s );
};

class Rva00024E0BTerrainRoadTypeSetDamageToFXStringThunk
{
public:
	void forward( BodyDamageType state, Int index, AsciiString s );
};

void Rva00024E0BTerrainRoadTypeSetDamageToFXStringThunk::forward(
	BodyDamageType state, Int index, AsciiString s )
{
	((TerrainRoadType *)this)->friend_setDamageToFXString( state, index, s );
}
