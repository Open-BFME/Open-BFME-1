# Apt Math.random at 0x008A51B0

The retail function starts after the `int3` at 0x008A51AF and ends with `ret`
at 0x008A51D8. Its direct calls reach the matched RNG body at 0x008D3C00 and
the matched Apt float factory at 0x008A4CD0.

After the RNG call, retail stores EAX in a stack word and executes `fild` on
that word. It tests EAX and, only for a negative signed interpretation, adds
the float at 0x01075358. That float is 4294967296.0 (`00 00 80 4f`). It then
multiplies unconditionally by the float at 0x011366D8, which is 2^-32
(`00 00 80 2f`). This is an unsigned 32-bit to float conversion followed by
scaling. The old bank's `float f = (float)(int)r; if (r < 0) f *= scale` has a
different computation and compiled to 44 bytes rather than the retail 41.

The byte-exact source keeps the RNG word unsigned and passes its scaled value
directly to the float factory. The `name_regression` finding `f ->
Rva008A4EA0MakeFloat` is token alignment across removal of that incorrect
local, not a rename of the factory: the factory declaration and call occur in
both sources, and the function identity `aptMathRandom` is preserved.
