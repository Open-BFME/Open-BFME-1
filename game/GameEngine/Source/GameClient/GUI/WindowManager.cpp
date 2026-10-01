// cl: /DNDEBUG /MD /EHsc
// FILE: WindowManager.cpp -- the WindowManager singleton retail keeps at
// VA 0x012F19E8. The class's functions live in the WindowManager*.cpp files
// beside this one.
//
// TYPE (proven from retail bytes): ??0WindowManager@@QAE@XZ (RVA 0x0046E5E0)
// ends with `if (!global) global = this;` on 0x012F19E8 -- the only store into
// it in .text -- and ??1WindowManager@@UAE@XZ (RVA 0x0046D8E0) clears it; every
// consumer loads it as a WindowManager `this` (WindowManager_invokeCallbackWithArg,
// Q2NamedScriptCallbacks, R2GuardedTailCalls, the SubsystemInterface slot calls).
// NAME (unproven): no EA string or caller names the variable. It is not EA's
// TheWindowManager, which the "TheWindowManager" string puts on 0x012F1B40 as a
// GameWindowManager. So the name keeps the address.

class WindowManager;

WindowManager *g_rva012F19E8WindowManager = 0;
