// The carved boundary at 0x00336700 contains only a retail ret.
// The existing thunk table names its address-derived body b_00336700.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD

void b_00336700() { }
