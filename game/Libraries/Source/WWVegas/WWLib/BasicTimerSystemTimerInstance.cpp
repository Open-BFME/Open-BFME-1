// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// Emits BasicTimerClass<SystemTimerClass> (vtable, destructor and scalar
// deleting destructor) from the native timer.h. Retail carries the 31-byte
// deleting-destructor shape at several addresses (?dup_007e7630 among them,
// identity among the twins unproven), and gen_asm dumps take this vtable by
// name. Both used to come only from the pristine Zero Hour _timer.cpp, which
// also defines Zero Hour's FrameTimer/TickCount globals.

#include "_timer.h"

template class BasicTimerClass<SystemTimerClass>;
