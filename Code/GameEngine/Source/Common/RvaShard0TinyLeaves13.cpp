// cl: /DNDEBUG /MD /O2 /EHsc

// Anonymous carved leaves. Address-qualified names avoid unsupported owners;
// the EAX-zero body at 0x00170EE0 has the return ABI proved by its complete
// instruction stream even though its anonymous caller ignores that result.
int dup_00170ee0() { return 0; }
void dup_00232b60() {}
