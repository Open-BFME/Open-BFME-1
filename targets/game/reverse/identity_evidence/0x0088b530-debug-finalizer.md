# Debug assertion/crash finalizer at RVA 0x0088B530

The former `?AssertBegin@Debug@@SAAAV1@PBDH0@Z` claims a static three-argument method returning Debug&. Retail instead preserves ECX as the Debug receiver, reads one stack argument as a reporting mode, returns false in AL, and ends with `ret 4` at +0x277. The other paths converge there or terminate the process. The full 948-byte extent includes the seven-entry switch table at +0x398; the following bytes are int3 padding.

Receiver fields agree with landed Debug::CheckBegin: current output type +0x9CF4, recursion count +0x9DF8, current frame +0x9DFC, and frame file/line/hits/status +0x0C/+0x10/+0x14/+0x18. The body emits hit counts, adds a stack trace, flushes, presents assertion/crash dialogs, clears the current frame, releases the shared diagnostic lock, and decrements the recursion count. Zero Hour debug_debug.cpp AssertDone supplies the same core finalization flow but lacks BFME's mode argument and extended dialog decisions.

The exact historical member name and mode enum are unproved. `Debug::finishAssert0088B530(int)` retains its address instead of guessing a semantic decoration. Debug ownership is supported by the receiver layout and calls to Debug::AddPatternEntry plus the shared Debug stream interface.

The single inline `int 3` is the intentional debugger breakpoint, not a byte lift: VC7.1's __debugbreak intrinsic moves the flag store after the breakpoint; an inline trap preserves retail's store-before-break ordering. All other instructions are compiled from C++ control flow and standard string operations.
