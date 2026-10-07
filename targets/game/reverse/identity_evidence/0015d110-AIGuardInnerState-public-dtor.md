# AIGuardInnerState destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x0015D110 is `??_GAIGuardInnerState@@UAEPAXI@Z`; the prior claim `??_GAIGuardInnerState@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x0015D140 is `??1AIGuardInnerState@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GAIGuardInnerState@@UAEPAXI@Z' 0x0015D110` prints CONFIRMED (exact, p_false=1.70e-03) and the MAE spelling CONTRADICTED; `check '??1AIGuardInnerState@@UAE@XZ' 0x0015D140` prints CONFIRMED (exact, p_false=7.83e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (0x0015D110 calls ILT 0x000434CD -> 0x0015D140, a 5-byte tail jump to the State destructor).

The correction preserves the start, extent, instructions and relocation targets.
