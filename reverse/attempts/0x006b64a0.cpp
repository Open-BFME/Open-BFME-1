// ?canPlayNow@SoundManager@@QAE_NPAVAudioEventRTS@@@Z
// partial score=0.2 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// SoundManager::canPlayNow at retail RVA 0x006B64A0 (404B). BLOCKED past the
// initial distance-cull guard: see notes below and reverse/re_attempts.log.
// This records the shape found via tools/dis_retail.py 0x006B64A0 against
// the ZH twin (reference/.../GameSounds.cpp SoundManager::canPlayNow) for
// the next attempt; it compiles but is not byte-exact.
//
// Confirmed against retail bytes:
//  - event->isPositionalAudio() is the already-pinned ILT at 0x0000F380
//    (?isPositionalAudio@AudioEventRTS@@QBE_NXZ); bl is preloaded with 8
//    (the ST_GLOBAL bit) for the BitTest(m_type, ST_GLOBAL) at
//    eventInfo+0x38, and eventInfo+0x34 is compared against literal 4
//    (AP_CRITICAL). All three conditions failing false skips straight to
//    the violatesVoice call at +0xf3 -- there is no early "return false"
//    for this block, matching ZH's `if (positional && !global && !critical)
//    { ...distance/shroud... }` with nothing after it but the next `if`.
//  - the distance cull is NOT `Coord3D::length()` then compare: retail
//    first does an early `fcomp` of eventInfo->m_maxDistance (+0x18)
//    against a float cached at [this+0xc]+0x7c (unidentified, likely a
//    cached listener/global audio-range value) BEFORE resolving the
//    event's own position, then only after that gate calls the pinned
//    resolveOwnerPosition (0x00029AE1) and a virtual at this-vtable+0x10c
//    (likely SoundManager/AudioManager::getListenerPosition, returning a
//    pointer) to do the real squared-distance-vs-m_maxDistance^2 compare
//    inline (three fsub + cross fmul/fadd terms + fcompp, no sqrt).
//  - BLOCKED: violatesVoice/isInterrupting/doesViolateLimit/
//    isPlayingLowerPriority/isPlayingAlready are called through this's own
//    vtable at unusually high slot numbers (0x10c=67, 0x188=98), meaning
//    SoundManager's vtable has 90+ entries and none of those slot->name
//    mappings are pinned yet (checked reverse/symbols.csv: only canPlayNow
//    itself is pinned for this RVA). Reconstructing the exact vtable
//    ordering needs those siblings converted/pinned first.

typedef int Int;
typedef bool Bool;

class Coord3D
{
public:
	float x, y, z;
};

class AudioEventInfo
{
public:
	char m_pad[0x18];
	float m_maxDistance;   // +0x18
	char m_pad3[0x34 - 0x1c];
	int m_priority;        // +0x34
	unsigned int m_type;    // +0x38
};

class AudioEventRTS
{
public:
	Bool isPositionalAudio() const;
	void resolveOwnerPosition(Coord3D *pos, Bool *found);

	char m_pad[8];
	AudioEventInfo *m_eventInfo; // +8
};

// SoundManager's vtable reaches at least slot 98 (0x188/4); the real
// ordering/names of slots 0..97 are not pinned. Pad with placeholders so
// this compiles; slot 67 and 98 are the two calls this body makes.
class SoundManager
{
public:
#define PAD(n) virtual void pad##n() {}
	PAD(000) PAD(001) PAD(002) PAD(003) PAD(004) PAD(005) PAD(006) PAD(007)
	PAD(008) PAD(009) PAD(010) PAD(011) PAD(012) PAD(013) PAD(014) PAD(015)
	PAD(016) PAD(017) PAD(018) PAD(019) PAD(020) PAD(021) PAD(022) PAD(023)
	PAD(024) PAD(025) PAD(026) PAD(027) PAD(028) PAD(029) PAD(030) PAD(031)
	PAD(032) PAD(033) PAD(034) PAD(035) PAD(036) PAD(037) PAD(038) PAD(039)
	PAD(040) PAD(041) PAD(042) PAD(043) PAD(044) PAD(045) PAD(046) PAD(047)
	PAD(048) PAD(049) PAD(050) PAD(051) PAD(052) PAD(053) PAD(054) PAD(055)
	PAD(056) PAD(057) PAD(058) PAD(059) PAD(060) PAD(061) PAD(062) PAD(063)
	PAD(064) PAD(065) PAD(066)
	virtual const Coord3D *getListenerPosition(void); // slot 67 (0x10c)
	PAD(068) PAD(069) PAD(070) PAD(071) PAD(072) PAD(073) PAD(074) PAD(075)
	PAD(076) PAD(077) PAD(078) PAD(079) PAD(080) PAD(081) PAD(082) PAD(083)
	PAD(084) PAD(085) PAD(086) PAD(087) PAD(088) PAD(089) PAD(090) PAD(091)
	PAD(092) PAD(093) PAD(094) PAD(095) PAD(096) PAD(097)
	virtual Bool isPlayingLowerPriority(AudioEventRTS *event); // slot 98 (0x188)
#undef PAD

	Bool violatesVoice(AudioEventRTS *event);
	Bool isInterrupting(AudioEventRTS *event);

	Bool canPlayNow(AudioEventRTS *event);

private:
	char m_pad_4[0xc - 4];
	void *m_pad_c; // +0xc, cached pointer whose +0x7c is a float compared against m_maxDistance
};

Bool SoundManager::canPlayNow(AudioEventRTS *event)
{
	if (event->isPositionalAudio())
	{
		AudioEventInfo *info = event->m_eventInfo;
		if (!(info->m_type & 8) && info->m_priority != 4)
		{
			// early distance gate: retail compares m_maxDistance against a
			// cached float at [this+0xc]+0x7c before resolving the event's
			// own position -- unidentified source value, left as 0.0f here.
			float cachedRange = *(float *)((char *)m_pad_c + 0x7c);
			if (info->m_maxDistance >= cachedRange)
			{
				Coord3D pos;
				Bool found = false;
				event->resolveOwnerPosition(&pos, &found);
				if (found)
				{
					const Coord3D *listener = getListenerPosition();
					float dx = listener->x - pos.x;
					float dy = listener->y - pos.y;
					float dz = listener->z - pos.z;
					if (dx * dx + dy * dy + dz * dz >= info->m_maxDistance * info->m_maxDistance)
						return false;
				}
			}
		}
	}

	if (violatesVoice(event))
	{
		if (isInterrupting(event))
			return true;
		return false;
	}

	if (isPlayingLowerPriority(event))
		return true;

	return false;
}
