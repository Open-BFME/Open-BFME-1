// ?Rva002E6420ObjectApplyCondition@@YAHPAUlua_State@@@Z
// partial score=0.92 date=2026-09-06
// Retail 123B, ours 123B (same size). Lua binding int f(lua_State*), always
// returns 0: id1=Rva00990030Lookup(state,1), guard (!id1 && lua_type(state,1)!=1);
// id2=Rva00990030Lookup(state,2), guard (!id2 && lua_type(state,1)!=1) (note:
// retail re-checks lua_type index 1, NOT 2, on this second guard -- verified
// byte for byte, not a transcription slip); then TheGameLogic->bfmeFind1011(id1)
// and ->bfmeFind1011(id2); if both objects resolve, object1->
// bfmeApplySpecialModelCondition(5, object2, 1) (pinned 0x1191E). Everything
// through the two guards and both bfmeFind1011 calls' argument setup matches
// byte for byte; only 8 bytes differ (offsets +0x49..+0x61), and only in
// WHICH callee-saved register (esi vs edi) holds TheGameLogic vs which holds
// the object1 result across the second bfmeFind1011 call -- both variants are
// semantically identical, this toolchain's allocator just colors them the
// other way around. WALL: tried caching TheGameLogic in a local (required to
// get the size right at all -- direct TheGameLogic->bfmeFind1011() calls twice
// gave 125B with a totally different shape), tried reordering the two
// bfmeFind1011 calls, tried `register` hints on both locals -- none changed
// the esi/edi coloring for this pair. Next lever to try: split into two
// TU-local static helpers each taking GameLogic* explicitly, so the compiler's
// call-site argument evaluation order for `helper(gl, id)` (args pushed before
// the pointer is loaded, matching retail's push-then-clobber-edi pattern) is
// forced rather than inferred from a member-call expression `gl->bfmeFind1011(id)`.
// t=25min model=sonnet score=0.92

struct lua_State;
extern "C" int lua_type( lua_State *state, int index );

unsigned Rva00990030Lookup( lua_State *range, int index );

class Object
{
public:
	char m_unreconstructed00[ 4 ];
};

class GameLogic
{
public:
	Object *bfmeFind1011( int id );
};

extern GameLogic *TheGameLogic;

class Rva002E6420Object : public Object
{
public:
	void bfmeApplySpecialModelCondition( int a, const void *b, int c );
};

int Rva002E6420ObjectApplyCondition( lua_State *state )
{
	unsigned id1 = Rva00990030Lookup( state, 1 );
	if( !id1 && lua_type( state, 1 ) != 1 )
		return 0;
	unsigned id2 = Rva00990030Lookup( state, 2 );
	if( !id2 && lua_type( state, 1 ) != 1 )
		return 0;
	GameLogic *gl = TheGameLogic;
	Rva002E6420Object *object1 = (Rva002E6420Object *)gl->bfmeFind1011( id1 );
	Rva002E6420Object *object2 = (Rva002E6420Object *)gl->bfmeFind1011( id2 );
	if( object1 && object2 )
		object1->bfmeApplySpecialModelCondition( 5, object2, 1 );
	return 0;
}
