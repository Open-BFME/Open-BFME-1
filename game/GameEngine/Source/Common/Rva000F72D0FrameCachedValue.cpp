// cl: /DNDEBUG /MD /EHsc

// TU-local view of the canonical GameLogic (GameLogic.cpp); the real class is
// only forward declared here, so every field read casts through this view.
class GameLogicFrameSlice
{
public:
	unsigned char m_unmodelled_000[0x3c];
	unsigned int m_frame;
};

class GameLogic;

extern GameLogic *TheGameLogic;

// The frame check calls retail 0x0004154C, the incremental-link thunk that
// jumps to the body at 0x0004F67B0 (no ledger row yet, no name proven). The
// thunk is a real definition in game/gen_small/thunks_031.cpp, so referencing
// it links and encodes the call site exactly as retail did.
void j_0004154c();

// MSVC 7.1 rejects __thiscall in a free-function-pointer typedef, so the call
// goes through a pointer-to-member view: that keeps the retail ECX/stack ABI.
struct RefreshView
{
	void refresh(float range);
};
typedef void (RefreshView::*RefreshCall)(float);

class Rva000F72D0FrameCachedValue
{
public:
	float value(float range);

private:
	unsigned char m_unmodelled_000[0xf4];
	float m_value;
	unsigned int m_frame;
};

float Rva000F72D0FrameCachedValue::value(float range)
{
	if (m_frame < ((GameLogicFrameSlice *)TheGameLogic)->m_frame)
	{
		union { void (*asFunction)(void); RefreshCall asMember; } refreshCast;
		refreshCast.asFunction = j_0004154c;
		(reinterpret_cast<RefreshView *>(this)->*refreshCast.asMember)(range);
	}
	return m_value;
}
