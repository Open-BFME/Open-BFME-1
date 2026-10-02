// cl: /O2 /Ob0 /MD /EHs-c-

typedef bool Bool;

// Retail 0x012F7FE0: BaseHeightMapRenderObjClass *TheTerrainRenderObject
// (W3DDevice/GameClient/BaseHeightMap.h). The member-thunk receiver is the
// same pointer; the class stays opaque here, so the cast carries the call.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class BfmeA1087
{
};

extern void d_0002f6fd(void);

class Rva006BE410TerrainQueryForwarder
{
public:
	Bool query( float first, float second );
};

Bool Rva006BE410TerrainQueryForwarder::query( float first, float second )
{
	typedef Bool (BfmeA1087::*MemberThunk)( float, float );
	union
	{
		void (*function)(void);
		MemberThunk member;
	} thunk;
	thunk.function = d_0002f6fd;
	return ((BfmeA1087 *)TheTerrainRenderObject->*thunk.member)( first, second );
}
