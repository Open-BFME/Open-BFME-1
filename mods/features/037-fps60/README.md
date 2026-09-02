# 037-fps60 — DO NOT SHIP: confirmed broken

`UNSHIPPED`. Kept because it is the runnable proof of the most expensive lesson
here, and because its addresses are recorded nowhere else.

Two byte pokes plus `038`'s detour: the sub-step immediates at `0x0006E986` and
`0x0006E9D9` go 6 → 12, and the frame limit goes 38 → 76 so twelve sub-steps
still fit a network frame (76/12 = 38/6). The payload also rewrites the
animation constant every frame — alternating 16 and 17, because the correction
wants 16.5 and the field is an integer — rather than poking it once, since there
is a runtime setter at `0x006FB9C0` reached through a vtable slot that would
overwrite a one-shot silently. Reads `GameLogic+0x3C` and `GameEngine+0x38`.

**The defect.** It smooths unit motion and breaks the timing of everything
authored in frames — `Lifetime` 2,735 times, `SystemLifetime` 1,965,
`BurstDelay` 1,517 across 724 ini files. Game speed measured correct three ways,
network frame correct, desync flag zero, animation clock compensated to 1.256×
against retail's 1.269× — and the Heal spell still ran visibly fast in play.

**The lesson.** The sub-step count is a UNIT that subsystems count in, and there
is no list of which ones do. One clock was found, fixed, measured, and
generalised to all of them. A special power is a GameLogic module with
client-side FX particle systems and reads neither. Nothing in a 470-line
backbuffer probe could see the difference, because every metric there is about
how OFTEN the screen changes, never how FAST a thing plays.

Raising the sub-step count is a closed route. `docs/fps60.md` has the rest.
