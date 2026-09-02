// 038-fpsrender -- twice the render rate, simulation sub-step count untouched.
//
// WHY THIS EXISTS AND 037 DOES NOT SHIP.
//
// 037-fps60 doubles the sub-step count (6 -> 12) as well as the render rate.
// That does smooth unit motion, and its game speed and W3D animation clock both
// measure correct. But the sub-step count is a UNIT that subsystems count in,
// and an unknown number of them do. The W3D animation clock (33 ms per
// sub-step, at 0x012BB1CC) was found and compensated; the Heal spell was then
// observed running visibly fast in play, which is a special power -- a
// GameLogic module with client-side FX particle systems, neither of which is
// that clock. One counterexample found by eye in five minutes, after every
// instrument reported green.
//
// So doubling the sub-step count requires auditing everything that counts
// sub-steps, and there is no list of those. This arm refuses that entirely:
// the cycle stays at six steps and only the render rate moves.
//
// WHAT IT BUYS, measured: camera, cursor, UI and client-side effects at twice
// the rate. On the guest seat, present 29.9 -> 55.8 Hz.
// WHAT IT DOES NOT: unit motion. New images on the guest went 30.3 -> 33.7 only,
// because unit positions come from a simulation that has not changed. That is
// the price of not breaking the timing of everything else.
//
// SINGLE PLAYER gets retail's limit. With TheNetwork == 0 nothing gates the
// cycle, so the game's speed is the frame rate over six and raising the limit
// alone would run a skirmish at double speed. In a match the network paces the
// gated phase and the loop's spare iterations are spent re-attempting it, which
// is what makes the higher limit safe there and only there.

// NO ADAPTIVE BACKOFF, AND THAT IS A MEASURED DECISION.
//
// A judder report at 1680x1050 looked like the raised limit overrunning the
// machine: the reporter's clock read 0.799 against retail and the network frame
// rate 4.035/s against 5.0. Three arms differing only in this constant, run in
// real matches on that same desktop at 1600x900, say otherwise:
//
//     limit 38 (retail)  animation 0.926   network 4.684/s   p99 ~81 ms
//     limit 60           animation 0.942   network 4.755/s   p99 ~82 ms
//     limit 76           animation 0.917   network 4.629/s   p99 ~88 ms
//
// The simulation is late at RETAIL'S OWN LIMIT, and the ~85 ms hitches are the
// same size at every one. The frame limit does not cause either; that desktop
// does, and it does it to an unmodified game. A backoff to 38 would land on
// 0.926 -- no better than 60's 0.942 -- so it was removed rather than shipped.
//
// If this is revisited, the thing to measure is not the limit. It is what the
// machine is doing during those hitches, which the engine's own accounting says
// is not its work: 5 ms of frame work against an 85 ms gap.
enum { ENGINE_FPS_LIMIT = 0x08 };

#define TheNetwork (*(void **)0x012F7714)

extern "C" __declspec(dllexport) void __cdecl fpsrender_engine(void *engine) {
    if (engine != 0) {
        *(int *)((unsigned char *)engine + ENGINE_FPS_LIMIT) =
            TheNetwork != 0 ? FPS_LIMIT : FPS_LIMIT_RETAIL;
    }
}
