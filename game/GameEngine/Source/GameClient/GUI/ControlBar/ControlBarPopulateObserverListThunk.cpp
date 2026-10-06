// cl: /O2 /MD
// Incremental-link thunk 0x00036BA1 for ControlBar::populateObserverList, whose
// body (0x004A9CD0) is game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarObserver.cpp.
// Claimed by address, as the ILT convention says. Under /O2 a tail call with
// no arguments is exactly `E9 rel32`, and `this` passes through in ecx. A free
// function cannot name a member, so the extern carries the mangled name itself.

extern "C" void __identifier("?populateObserverList@ControlBar@@QAEXXZ")(void);

void j_00036ba1(void)
{
	__identifier("?populateObserverList@ControlBar@@QAEXXZ")();
}
