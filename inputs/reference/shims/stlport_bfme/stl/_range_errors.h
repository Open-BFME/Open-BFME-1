// BFME's STLport range-error hooks: inline no-ops.
//
// tools/build.py puts this directory ahead of inputs/vendor/stlport for every
// `// stlport` TU, so it shadows the pristine stl/_range_errors.h (which stays
// unmodified). The vendored header cannot give retail's shape under any
// configuration macro: with STLport's own iostreams it declares the five
// __stl_throw_* functions extern (bodies in STLport's library sources, not here),
// and otherwise it defines them inline as `throw ex(string(msg))` or
// `puts(msg), abort()`. Each of those leaves the message string and a call or
// a throw behind. Retail has none of them:
//   - _String_base<char>::_M_throw_out_of_range (0x006434C0) and
//     _M_throw_length_error (0x000A34E0) are a bare `ret`; their 30 callers are
//     the /Od string block at 0x0082C000-0x00832000;
//   - "basic_string", "bitset" and "deque" do not occur in the image, so no
//     range check anywhere passes its message on;
//   - out_of_range and length_error each have a type descriptor referenced only
//     by their own RTTI (complete object locator, base class descriptor): no
//     catchable type, so nothing throws them.
// So BFME built these hooks as inline functions that do nothing. No body is
// added here that retail lacks: an inline function emits nothing unless a TU
// fails to inline it, and then only a COMDAT the linker discards with its caller.
// The same shape shows where the check was inlined: in the body the matched
// basic_string<char>::_M_range_initialize(const char*, const char*) forwards
// to (0x002D8760, still an address-named row) the length-error branch jumps
// straight to the continuation, and the BitFlags<192> one-index constructor
// (0x000C4B00) sets its bit with no bound test.
// Not _STLP_DECLSPEC: retail imports no STLport DLL (a /MD TU without
// _STLP_USE_STATIC_LIB would otherwise reference __imp_ copies).
//
// A TU opts out with `// stlport-range-errors: vendored` (tools/build.py). On
// 2026-09-29, 25 matched functions in 17 TUs byte-matched only with the
// vendored extern call: it keeps a callee (BitFlags constructors,
// basic_string::_M_range_initialize) too large to inline, standing in for
// something else retail's callee had (for _M_range_initialize, STLport's
// node allocator where those TUs compile a plain operator new). Each opt-out
// is debt: fix that other shape, then drop the line.
#ifndef _STLP_RANGE_ERRORS_H
#define _STLP_RANGE_ERRORS_H

_STLP_BEGIN_NAMESPACE
inline void _STLP_CALL __stl_throw_range_error(const char*) {}
inline void _STLP_CALL __stl_throw_out_of_range(const char*) {}
inline void _STLP_CALL __stl_throw_length_error(const char*) {}
inline void _STLP_CALL __stl_throw_invalid_argument(const char*) {}
inline void _STLP_CALL __stl_throw_overflow_error(const char*) {}
_STLP_END_NAMESPACE

#endif /* _STLP_RANGE_ERRORS_H */
