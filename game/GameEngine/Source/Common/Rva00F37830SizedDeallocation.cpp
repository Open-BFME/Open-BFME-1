// cl: /DNDEBUG /MD /EHsc
// Retail VA 0x01337830 is a loader-zero sized-deallocation callback cell,
// not an import slot. Existing matched callers and DIR32 pins agree on
// its address and cdecl (void *, unsigned int) contract.
void (__cdecl *TheBfmeFree)(void *, unsigned int) = 0;
