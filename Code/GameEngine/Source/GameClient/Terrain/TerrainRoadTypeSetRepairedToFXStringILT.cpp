// cl: /DNDEBUG /MD /EHsc

// The retail ILT at 0x0001C693 forwards to TerrainRoadType's matched
// friend_setRepairedToFXString body at 0x00601CC0.

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
	void friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString s );
};

class Rva0001C693TerrainRoadTypeSetRepairedToFXStringThunk
{
public:
	void forward( BodyDamageType state, Int index, AsciiString s );
};

void Rva0001C693TerrainRoadTypeSetRepairedToFXStringThunk::forward(
	BodyDamageType state, Int index, AsciiString s )
{
	((TerrainRoadType *)this)->friend_setRepairedToFXString( state, index, s );
}
