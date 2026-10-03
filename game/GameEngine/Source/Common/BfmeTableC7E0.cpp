// cl: /DNDEBUG /MD /O2
// Zero-initialised .data globals at retail 0x0134C7E0 and 0x0134C800: the two
// tables bfmeGo7820 (0x009A7820) passes to its 8x8 block helpers; BfmeGo79D0
// also reads the first. Declared as int by those callers.
int g_bfmeTableC7E0;
int g_bfmeTableC800;
