# 0x00609DA0: bfmeRunESM takes a two-float position and a float output

The 107-byte body at `0x00609DA0` was claimed as
`?bfmeRunESM@BfmeHostESM@@QAEDHHPAPAX@Z`, a placeholder
`char (int a, int b, void **out)`. The class and method placeholder names are
kept. The parameter types are corrected to
`char (BfmeCoordESM pos, float *height)`, which decorates as
`?bfmeRunESM@BfmeHostESM@@QAEDUBfmeCoordESM@@PAM@Z`. BfmeCoordESM is a
two-float struct with an inline (x, y) constructor, a throw() copy
constructor and no destructor.

## Evidence

1. **Retail caller 0x006176A0 (`BfmeSinkAM::registerItem`) at +0x11C..+0x19A.**
   - It loads `pos->y` and `pos->x` with `fld`, reserves the argument area
     with `sub esp,8`, and stores both with `fstp` straight into it.
   - It records the argument address (`mov [esp+0x20],esp`), which is the `$T`
     store MSVC 7.1 emits for an in-place constructed class argument. Two ints
     would be pushed with `mov`/`push`.
   - It passes `&height` and later reads the result with `fld` and adds a
     float member to it, so the output is a `float *`.
   - That caller byte-matches only with a copy-constructible (x, y) float
     class. With no copy constructor the pair goes through registers and
     loses the `$T` slot. With a destructor it is built as a separate
     temporary and destroyed.
2. **The callee has no EH frame,** so its own parameter type has no
   destructor. It still builds a BfmePairESM, which declares one, in-place in
   bfmeDoESM's argument slot. That is the `$T` store at +0x46, which the old
   source reached by constructing the pair from the two int parameters. So
   the parameter and the pair are different types.
3. **The corrected source still byte-matches** retail 0x00609DA0 (107 B,
   exact modulo relocations). BfmePairESM now holds the two floats it is built
   from; the member copies still compile to `mov`.

No other matched C++ source references the old decorated name.
