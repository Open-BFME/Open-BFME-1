// cl: /DNDEBUG /DWIN32 /MD /O2

// LuaScriptEngine callback: CurDrawableGetCurrentTargetDistance.

#include <math.h>

typedef float Real;

struct lua_State;

extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

struct BfmePt951
{
	float m_bfmeX;
	float m_bfmeY;
};

// Layout as in BfmeConv951.cpp, whose matched bfmeGapB951 (0x0015BE50) this
// callback reaches through ILT 0x000158B1.
class BfmeGap951
{
public:
	float bfmeGapB951(const BfmePt951 *other) const;
private:
	int m_bfmeGap[14];
	float m_bfmeX;
	float m_bfmeY;
	int m_bfmeGap2[31];
	float m_bfmeRadius;
};

struct LuaTargetRecord : public BfmeGap951
{
	char m_targetPad[0x2A8 - sizeof(BfmeGap951)];
	BfmePt951 m_targetPosition;
};

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	LuaTargetRecord *m_target;
};

struct LuaDrawableLink
{
	char m_ownerPad[0x0C];
	LuaTargetOwner *m_owner;
};

struct LuaDrawableState
{
	char m_drawablePad[0x78];
	LuaDrawableLink *m_drawable;
};

extern LuaDrawableState *g_obj12F060C;

int CurDrawableGetCurrentTargetDistance(lua_State *state)
{
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0) {
			if (owner->m_target != 0) {
				lua_pushnumber(state, sqrt(owner->m_target->bfmeGapB951(&owner->m_target->m_targetPosition)));
				return 1;
			}
		}
	}
	lua_pushnil(state);
	return 1;
}
