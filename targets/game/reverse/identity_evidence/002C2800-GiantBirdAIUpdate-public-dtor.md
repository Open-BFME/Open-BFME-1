# GiantBirdAIUpdate destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x002C2800 is `??_GGiantBirdAIUpdate@@UAEPAXI@Z`; the prior claim `??_GGiantBirdAIUpdate@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor, reached through ILT 0x00030792, is the already matched `??1GiantBirdAIUpdate@@UAE@XZ` at 0x002C2720.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GGiantBirdAIUpdate@@UAEPAXI@Z' 0x002C2800` prints CONFIRMED (exact, p_false=1.30e-03) and the MAE spelling CONTRADICTED; `check '??1GiantBirdAIUpdate@@UAE@XZ' 0x002C2720` prints CONFIRMED (exact, p_false=1.96e-04) and the MAE spelling CONTRADICTED.

The correction preserves the start, extent, instructions and relocation targets.
