// ?init@?$basic_ios@GV?$char_traits@G@_STL@@@_STL@@IAEXPAV?$basic_streambuf@GV?$char_traits@G@_STL@@@2@@Z
// partial score=0.55 date=2026-09-06
// Open-BFME7: wchar_t (G) twin of the landed char body
// ?init@?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@IAEXPAV?$basic_streambuf@DV?$char_traits@D@_STL@@@2@@Z
// at 0x0053F8D0 (Code/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_init.cpp).
//
// Structural match up to +0x33 confirmed (probe): xor/cmp/sete/mov-esi-ecx/
// mov-ecx-[esi+0x14]/store-streambuf-at+0x58/test-eax-ecx all identical in
// both instantiations, so the class layout and the leading rdbuf(sb) inline
// are already right when compiled from the same twin TU.
//
// THE ONE REAL DIFFERENCE: the char body reaches the guarded cleanup hook
// through a REAL out-of-line call, `call 0x0083E8F0` (?process@@YAXXZ,
// already landed clean in Code/GameEngine/Source/Common/Gen_0083E8F0.cpp:
// g_call((void*)0x0112EBAC, (char*)g_global + 0x40)). The wchar body inlines
// that exact same two-push sequence directly against the g_call function
// pointer at VA 0x013593C8 and the g_global pointer at VA 0x013592F0,
// skipping the process() wrapper entirely -- almost certainly an MSVC
// call-site-count inlining decision (process() has only the one caller on
// the wchar path), not a source difference. Reproducing this exactly needs
// either an explicit template specialization of this exact mangled name (risk:
// ODR conflict against the twin TU's implicit instantiation of the same
// (wchar_t, char_traits<wchar_t>) basic_ios if both land in the same link) or
// a compiler flag/ordering trick that makes MSVC inline process() here too;
// neither was tried to a working state in the ~25 minutes spent.
//
// SECOND BLOCKER: the wchar body's imbue()-equivalent callee, 0x0083F880, is
// itself still an unclaimed dump (?d_0083f880@@YAXXZ) -- the char twin's
// matching callee (thunk 0x0001F2C1) is already landed, but this sibling for
// wchar is not, so even a correct init() body would still call into an
// un-landed dependency.
//
// globals: g_call (VA 0x013593C8, ?g_call@@3P6AXPAX0@ZA), g_global
// (VA 0x013592F0, ?g_global@@3PAXA) -- both already in reverse/symbols.csv.
// Next step for whoever draws this: try `template<> void
// _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::init(...)` in a
// throwaway probe (not committed) to see whether the ODR conflict is real at
// link time or only a probe-time link artifact, and land 0x0083F880 first so
// its callee is a real symbol rather than a dump reference.
