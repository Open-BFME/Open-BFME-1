# Complete GUI transition extents

Both old23B claims end inside reachable instructions. Direct retail decoding
and independently created Ghidra functions agree on the complete extents:

- RVA0059E0E0, MainMenuMediumScaleUpTransition::reverse: old end cuts
  MOV ECX,[ESI+44] at59E0F5. Second call reaches GameWindow::winHide through
  ILT27F2A ->478390. POP ESI;RET ends59E100; INT3 starts59E101:33 bytes.
- RVA005A02B0, TextOnFrameTransition::init: old end cuts TEST AL,AL at5A02C6.
  Hidden arm endsRET4 at5A02DA. Visible arm reads receiver+10, passes that
  integer to virtual slot8, updates flags, thenRET4 at5A02F5. INT3 starts
  5A02F8:72 bytes. Hidden query uses ILT3A5B7 ->478410.

GeneralsMD GameWindowTransitionsStyles.cpp supplies both named twins and the
same flag/window operations. The existing names are retained. The complete
reverse comparison reveals exactly one wrong displacement: reference grow
window+3C versus retail+44. The same TU already uses the independently matched
BfmeMediumScaleUpTransitionFields view for update; reuse it unchanged.

The init twin uses a fixed zero enum for its update argument, but BFME reads
its configurable m_startFrame at+10. The existing TextOnFrameTransition shim
and matched update already carry that field at+10; use it. No shared header,
callee pin, assembly, or guessed identity is added. Each repaired extent is
verified separately with add_match, then all source claims pass together.
