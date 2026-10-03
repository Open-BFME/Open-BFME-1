class AsciiString;

class BfmeSrcCR
{
public:
	void *m_bfmeHeadCR;
};

// The 0x70-byte stack request is an AudioEventRTS: retail builds it with the
// plain-int overload (0x000B2CC0, reached through the ILT 0x0001EC13) and
// releases it through the scalar destructor ILT 0x00026F35 -> 0x000B31F0.
// Only the reference is passed, so spelling it with its real name and its real
// const-reference parameter type reproduces retail's two pushes.
//
// LINK BLOCKER (re-measured 2026-10-03, byte-neutral): the scalar destructor
// call is a thiscall member call, so its name must be a `??1X@@..@XZ`.  Retail's
// body there is the NON-virtual destructor, so the only byte-matching spelling
// here is ??1AudioEventRTS@@QAE@XZ -- and NO object defines it.  Ledger row
// functions.csv:6852 *names* that symbol (0x000B31F0, this object) but its
// object-symbol= column says ??1AudioEventRTS@@UAE@XZ, which is what
// AudioEventRTSCopyAndLifetime.o actually emits (its class has a virtual dtor).
// Measured alternative, also byte-identical apart from one relocation:
// `virtual ~AudioEventRTS();` plus m_bfmePadCR[0x6C] (the vptr takes the first
// 4 of the 0x70-byte frame) makes this object reference the *defined*
// ??1AudioEventRTS@@UAE@XZ.  Its compiled body is then byte-for-byte retail's
// except that one call, and the resolver reports exactly:
//   retail calls 0x00026F35 -> body 0x000B31F0 ...;
//   candidates [0x0002671F, 0x000CFA40, 0x00BFC1BE, 0x00C095FA, 0x00C09856]
// so it needs a symbols.csv pin for ??1AudioEventRTS@@UAE@XZ at 0x00026F35.
// Note the existing pin at symbols.csv:4751 is at 0x0002671F, whose thunk is
// `e9 1c930a00` -> 0x000CFA40, i.e. NOT this destructor (0x00026F35's thunk is
// `e9 b6c20800` -> 0x000B31F0): that pin looks stale and is what shadows the
// right address.  Either way the fix needs a ledger edit, so the byte-matching
// non-virtual spelling is kept here.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int timeOfDay);
	~AudioEventRTS();

	unsigned char m_bfmePadCR[0x70];
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00CR();
	virtual void bfmeSlot01CR();
	virtual void bfmeSlot02CR();
	virtual void bfmeSlot03CR();
	virtual void bfmeSlot04CR();
	virtual void bfmeSlot05CR();
	virtual void bfmeSlot06CR();
	virtual void bfmeSlot07CR();
	virtual void bfmeSlot08CR();
	virtual void bfmeSlot09CR();
	virtual void bfmeSlot10CR();
	virtual void bfmeSlot11CR();
	virtual void bfmeSlot12CR();
	virtual void bfmeSlot13CR();
	virtual void bfmeSlot14CR();
	virtual void bfmeSlot15CR();
	virtual void bfmeSlot16CR();
	virtual void bfmeSendCR(AudioEventRTS *req);
};

// Retail's global at 0x012ED668 is `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. Only the name has to be canonical for the link;
// this TU keeps its own TU-local view of the pointee and casts at the use.
class AudioManager;

extern AudioManager *TheAudio;

void __stdcall bfmeQueueCR(BfmeSrcCR *src)
{
	if (src->m_bfmeHeadCR != 0)
	{
		AudioEventRTS req(*(const AsciiString *)src, 1);

		((Rva005A00B0AudioClient *)TheAudio)->bfmeSendCR(&req);
	}
}
