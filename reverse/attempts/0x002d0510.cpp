// ?advance@Rva002D0510Behavior@@QAEHXZ
// partial score=0.85 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x002D0510, 41 bytes. Owning class identity not recovered;
// the shape is a reload-gate decrement: while a reload timer at +0x2C is
// running, the ammo counter at +0x14 is held at zero; otherwise it counts
// down to zero one call at a time. Always returns a nonzero int result.
// Control flow, both field offsets and the always-1 return are all
// byte-verified correct (probe.py agrees on every branch target).
//
// Two remaining diffs, both encoding-only:
//   1. Retail's outer reload-timer guard is `ja` (unsigned >); every source
//      spelling tried here (`> 0`, `!(== 0)`, an early-return restructure)
//      that keeps the INNER shape below also flips the inner test back to a
//      plain `je`, so the two do not land together in this toolchain.
//   2. Retail decrements the ammo field with `dec dword ptr [ecx+0x14]`
//      (memory operand) after only TESTING it; this toolchain always keeps
//      the just-loaded value in eax and does register-dec + store instead.
//      Tried: a `volatile int` field (forces an extra reload instead of a
//      memory-operand dec), a local pointer, a __forceinline `decrement(int*)`
//      helper matching the "shader resource cleanup" family lever -- none
//      produced a bare memory-operand dec.
//   3. Retail's inner zero-test is `sete al` / `test al,al` / `je` (7 bytes)
//      instead of the natural `test eax,eax` / `je` (2 bytes) this toolchain
//      always emits for `if (x != 0)` here, regardless of an added bool
//      local (optimized back to the same je) -- looks like a source shape
//      this reconstruction has not found yet, not a pure register pick.
//
// Next agent: try a TU cl: flag change (see docs/lessons.md "a
// register-allocation wall moves on a TU flag, never on a source rewrite")
// before more source rewrites of the inner test.

class Rva002D0510Behavior
{
public:
	int advance();

private:
	unsigned char m_pad00[0x14];
	int m_ammo;
	unsigned char m_pad18[0x2C - 0x14 - 4];
	unsigned int m_reloadTimer;
};

int Rva002D0510Behavior::advance()
{
	if (m_reloadTimer == 0)
	{
		if (m_ammo != 0)
		{
			--m_ammo;
			return 1;
		}
	}

	m_ammo = 0;
	return 1;
}
