// 050-ratiocont -- a continuous client-frame ratio for BFME's own drawable
// interpolation, plus real-time animation clock steering.
//
// Installed at the entry of GameEngine::_bfme_updateClientSubsystems (retail
// RVA 0x0006B910, GameEngine vtable slot +0x80) by
// build/astra_ratiocont_patch.py, on top of D:\BFME1\lotrbfme-astra.exe.
//
// WHY
//   docs/interp-seams.md (target 5/6) established that a moving unit's
//   locomotor runs once per 200 ms logic frame, and that what the player sees
//   between logic frames is the engine's OWN interpolation of drawable
//   transforms driven by GameEngine::m_clientFrameRatio (+0x38).  Retail sets
//   that ratio to phase/6 after each admitted phase, so under the Astra pacing
//   cave it moves in 33 ms steps while the loop renders at 60 Hz: every other
//   frame is a duplicate.  Writing a ratio that advances continuously with the
//   wall clock -- (phase + fractionOfCurrentStep) / 6 -- lets the engine's own
//   interpolation land on a fresh position every rendered frame.  No render
//   object is touched, nothing is restored, and no extra latency is added.
//
//   The ratio is written at the start of the client update, which is where the
//   drawable update reads it (GameEngine::update writes retail's value only
//   after the client update returns, so the retail write does not overwrite
//   this one before it is consumed).
//
//   The animation clock is steered exactly as in 049 revision 2: [0x012BB1CC]
//   is set each client frame to the animation-ms deficit against real time,
//   so WW3D::SyncTime advances at 1.0x whatever the frame rate.  In any state
//   where the pacing cave is inactive (menus, multiplayer, mode 5) the payload
//   leaves the ratio alone and puts the constant back to retail's 33.

typedef unsigned int Unsigned;
typedef float Real;
typedef __int64 Int64;

extern "C" const int _fltused = 0;

enum { RETAIL_ANIMATION_MS = 33 };
#define MAX_ANIMATION_CATCHUP_MS 40.0f

#define TheAnimationMsPerStep (*(int *)0x012BB1CC)
#define WW3DSyncTime (*(Unsigned *)0x0133F420)

// Astra pacing cave state block (see D:\BFME1\lotrbfme-astra-notes.txt).
#define PaceActive (*(int *)0x01416400)
#define PaceLastCounter (*(Int64 *)0x01416404)
#define PaceAccumulated (*(Int64 *)0x0141640C)
#define PaceFrequency (*(Int64 *)0x01416414)
#define PaceInterval (*(Int64 *)0x0141641C)
#define PaceFrequencyReady (*(int *)0x01416424)

typedef int (__stdcall *CounterFn)(Int64 *);
#define QueryPerformanceCounterSlot (*(CounterFn *)0x01358EB4)

enum
{
    ENGINE_CLIENT_FRAME_PERIOD = 0x30,
    ENGINE_CLIENT_FRAME_RATIO = 0x38
};

static Int64 s_lastDrawTicks;
static int s_haveDrawTicks;
static Real s_desiredMs;
static Real s_actualMs;
static Unsigned s_lastSyncTime;
static int s_haveSyncTime;

static Real to_real(int value)
{
    return (Real)value;
}

#ifndef NO_ANIM_STEER
// Round-to-nearest without _ftol (see 049 for the derivation).
static int round_real(Real value)
{
    union Bits
    {
        Real real;
        int bits;
    } u;
    u.real = value + 12582912.0f;
    return u.bits - 0x4B400000;
}

static void steer_animation_clock(int paceOn, Int64 now)
{
    if (!paceOn)
    {
        TheAnimationMsPerStep = RETAIL_ANIMATION_MS;
        s_haveDrawTicks = 0;
        s_haveSyncTime = 0;
        return;
    }

    Int64 frequency = PaceFrequency;
    Int64 elapsedTicks = 0;
    if (s_haveDrawTicks)
    {
        elapsedTicks = now - s_lastDrawTicks;
        if (elapsedTicks < 0)
            elapsedTicks = 0;
        if (elapsedTicks > frequency)
            elapsedTicks = frequency;
    }
    s_lastDrawTicks = now;
    s_haveDrawTicks = 1;

    Real elapsedMs = (Real)elapsedTicks * 1000.0f / (Real)frequency;

    Unsigned sync = WW3DSyncTime;
    if (!s_haveSyncTime || sync < s_lastSyncTime || sync - s_lastSyncTime > 1000u)
    {
        s_desiredMs = 0.0f;
        s_actualMs = 0.0f;
        s_haveSyncTime = 1;
    }
    else
    {
        s_actualMs += to_real((int)(sync - s_lastSyncTime));
        s_desiredMs += elapsedMs;
    }
    s_lastSyncTime = sync;

    Real deficit = s_desiredMs - s_actualMs;
    if (deficit > MAX_ANIMATION_CATCHUP_MS)
    {
        s_desiredMs = s_actualMs + MAX_ANIMATION_CATCHUP_MS;
        deficit = MAX_ANIMATION_CATCHUP_MS;
    }
    if (deficit < 1.0f)
        deficit = 1.0f;

    if (s_actualMs > 1000000.0f)
    {
        s_actualMs -= 1000000.0f;
        s_desiredMs -= 1000000.0f;
    }

    TheAnimationMsPerStep = round_real(deficit);
}
#endif

extern "C" __declspec(dllexport) void __cdecl ratiocont_client(void *engine)
{
    Int64 now = 0;
    int haveNow = 0;
    CounterFn counter = QueryPerformanceCounterSlot;
    if (counter != 0 && counter(&now) != 0)
        haveNow = 1;

    int paceOn = 0;
    if (haveNow && PaceActive != 0 && PaceFrequencyReady != 0 &&
        PaceInterval > 0 && PaceFrequency > 0)
        paceOn = 1;

#ifndef NO_ANIM_STEER
    steer_animation_clock(paceOn, now);
#endif

    if (!paceOn || engine == 0)
        return;

    // +0x30 holds the last admitted phase (1..6), or 7 while a phase-1 admit
    // is pending; retail's ratio during this client update would be phase/6.
    int period = *(int *)((unsigned char *)engine + ENGINE_CLIENT_FRAME_PERIOD);
    Real ratio = 1.0f;
    if (period >= 1 && period <= 6)
    {
        Int64 interval = PaceInterval;
        Int64 since = now - PaceLastCounter;
        if (since < 0)
            since = 0;
        if (since > interval)
            since = interval;
        Real fraction = (Real)(PaceAccumulated + since) / (Real)interval;
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 1.0f)
            fraction = 1.0f;
        ratio = (to_real(period) + fraction) / 6.0f;
    }
    if (ratio < 0.0f)
        ratio = 0.0f;
    if (ratio > 1.0f)
        ratio = 1.0f;
    *(Real *)((unsigned char *)engine + ENGINE_CLIENT_FRAME_RATIO) = ratio;
}
