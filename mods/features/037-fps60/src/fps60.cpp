// 037-fps60 -- twice the simulation sub-steps, twice the render rate, same
// network frame.
//
// THIS IS NOT THE FIX THE SPIKE SET OUT TO BUILD, and the reason is the whole
// finding. The plan was one extra INTERPOLATED draw in the frame limiter's
// idle wait, on the premise that retail interpolates unit transforms between
// 5 Hz logic frames. Retail does no such thing. GameEngine::update drives a
// six-step cycle -- phases 2,3,4,5,6 ungated and then phase 1 gated on the
// network -- and calls GameLogic::update on every one of them. So the
// simulation itself runs at six steps per 200 ms network frame: 30 Hz. There
// is no interpolator to reuse and nothing for an extra draw to draw. An extra
// draw would present the frame that was already presented.
//
// 036-fpsprobe measured exactly that. On the host, presents run at the FPS
// limit (38.5 Hz) while the simulation steps six times per 5 Hz network frame,
// so 1 - 6/7.68 = 21.8% of frames should already be duplicates; the cells over
// the units read 22%. On the guest, presents come 6.07 per network frame --
// one per sub-step -- and its duplicate rate is ~0%. Retail already renders
// more often than it simulates, and the surplus frames are already repeats.
//
// So the way to 60 Hz motion is to simulate more often, not to draw more
// often: twelve sub-steps per network frame instead of six, and a render rate
// that can complete them inside the same 200 ms. Both halves are required and
// neither works alone -- twelve sub-steps at the retail 38 Hz cannot finish
// inside a network frame and the game would be paced by the loop instead of by
// the network, which is a game-speed change in the other direction.
//
// WHAT THIS DOES NOT ESTABLISH. Whether a sub-step advances the world by a
// fixed amount or by an amount derived from the step count. If it is fixed,
// twelve steps move everything twice as far per network frame and the game
// runs at double speed while the network frame rate -- the obvious gate --
// stays at a reassuring 5.0/s. That is why the arm is measured on how long
// units take to walk a fixed path, and not on the logic rate alone.
//
// The step count is two immediates the build pokes; this payload carries the
// other half, the render rate. No CRT and no loader: see modbuild.py.

// GameEngine::m_framesPerSecondLimit, at this+0x08. Proven by
// getFramesPerSecondLimit (RVA 0x0006B600, four bytes, `mov eax,[ecx+8]; ret`)
// and by the frame limiter's own `fild dword ptr [ebx+8]` at RVA 0x0006BEF7,
// which is the value it divides 1000 by to get a frame budget in milliseconds.
//
// Written on every call rather than once: the value comes from GlobalData,
// which is re-read across a reset, and a one-shot would silently lapse back to
// the retail rate mid-session -- which is the shape of bug that produces an
// arm that measures retail and is labelled as the fix.
enum { ENGINE_FPS_LIMIT = 0x08 };

// ---- and the animation clock, which the sub-step change breaks -------------
// WW3D::SyncTime is advanced by this many milliseconds per SIMULATION SUB-STEP
// (VA 0x012BB1CC, read at RVA 0x006F40E8). Retail holds 33, and 30 sub-steps a
// second times 33 ms is 990 ms of animation per real second -- measured at
// 0.990x. Double the sub-step count and every torch, banner, idle loop and
// walk cycle plays at twice speed: measured at 2.068x before this store
// existed.
//
// The correction wants 16.5, which is not an integer, so it ALTERNATES 16 and
// 17. Writing either one alone lands 3% off retail; alternating averages 16.5
// and lands on it. Three percent is not visible, but a constant that is
// knowably wrong when a correct one costs three lines is not worth shipping.
//
// Written every frame rather than poked once: there is a runtime setter for
// this field at RVA 0x006FB9C0, reached through a vtable slot, so a one-shot
// poke can be overwritten without warning.
#define TheAnimationMsPerStep (*(int *)0x012BB1CC)

static int s_odd;

extern "C" __declspec(dllexport) void __cdecl fps60_engine(void *engine) {
    if (engine != 0) {
        *(int *)((unsigned char *)engine + ENGINE_FPS_LIMIT) = FPS_LIMIT;
    }
    s_odd = !s_odd;
    TheAnimationMsPerStep = s_odd ? ANIM_MS_LOW : ANIM_MS_HIGH;
}
