# AIAttackMeleeHordeWaitPathState destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x0017F6C0 is `??_GAIAttackMeleeHordeWaitPathState@@UAEPAXI@Z`; the prior claim `??_GAIAttackMeleeHordeWaitPathState@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x0017F6F0 is `??1AIAttackMeleeHordeWaitPathState@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GAIAttackMeleeHordeWaitPathState@@UAEPAXI@Z' 0x0017F6C0` prints CONFIRMED (exact, p_false=4.57e-03) and the MAE spelling CONTRADICTED; `check '??1AIAttackMeleeHordeWaitPathState@@UAE@XZ' 0x0017F6F0` prints CONFIRMED (exact, p_false=4.57e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (0x0017F6C0 calls ILT 0x0002200C -> 0x0017F6F0, a 5-byte tail jump to the State destructor).

The correction preserves the start, extent, instructions and relocation targets.
