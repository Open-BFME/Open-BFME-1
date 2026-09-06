// ?setShouldPlay@Eva@@QAE_NW4EvaMessage@@PBUCoord3D@@@Z
// partial score=0.4 date=2026-09-06
// cl: /O2

// Eva::setShouldPlay(EvaMessage, const Coord3D *) at retail 0x004233A0.
// BFME replaced ZH's single `m_shouldPlay[msg] = TRUE;` with a bounds-checked
// pair of per-message vectors: 28-byte EvaCheckInfo "defs" records at
// this+0xC/+0x10 and 24-byte EvaCheck "checks" records at this+0x4C/+0x50
// (see reverse/symbols.csv pin on this RVA), then forwards to the already
// matched per-message trigger callee at 0x004223F0
// (Code/GameEngine/Source/GameClient/EvaCheck_trigger.cpp):
//   checks[msg].trigger(&defs[msg], pos)
// This TU is self-contained: it defines local EvaCheck/EvaCheckInfo/Coord3D
// types sized only to reproduce the pointer arithmetic and mangled names the
// callee already pins, and a local `Eva` class padded to the retail offsets
// this body actually touches. The real Code/GameEngine/Source/GameClient/Eva.cpp
// is left untouched.

typedef bool Bool;

enum EvaMessage
{
	EvaMessage_Invalid = -1
};

struct Coord3D
{
	float x, y, z;
};

// Only the size (28 B) matters here; the real field contents are read by the
// already-matched trigger() callee, not by this function.
struct EvaCheckInfo
{
	unsigned char pad[28];
};

// Only the size (24 B) matters here for this function's own indexing.
struct EvaCheck
{
	unsigned char pad[24];

	Bool trigger(const EvaCheckInfo *info, const Coord3D *pos);
};

class Eva
{
public:
	Bool setShouldPlay(EvaMessage messageToPlay, const Coord3D *pos);

private:
	unsigned char m_head[0xC];
	EvaCheckInfo * volatile m_defsBegin;		// +0xC
	EvaCheckInfo * volatile m_defsEnd;			// +0x10
	unsigned char m_mid[0x4C - 0x14];
	EvaCheck * volatile m_checksBegin;			// +0x4C
	EvaCheck * volatile m_checksEnd;			// +0x50
};

Bool Eva::setShouldPlay(EvaMessage messageToPlay, const Coord3D *pos)
{
	if (messageToPlay == EvaMessage_Invalid)
		return false;

	if (messageToPlay >= 0)
	{
		if ((unsigned)messageToPlay < (unsigned)(m_checksEnd - m_checksBegin))
		{
			if ((int)(m_defsEnd - m_defsBegin) == (int)(m_checksEnd - m_checksBegin))
			{
				return m_checksBegin[messageToPlay].trigger(&m_defsBegin[messageToPlay], pos);
			}
		}
	}

	return false;
}
