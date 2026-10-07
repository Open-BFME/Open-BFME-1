# AIUncontrollableCower destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x00182320 is `??_GAIUncontrollableCower@@UAEPAXI@Z`; the prior claim `??_GAIUncontrollableCower@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x00182350 is `??1AIUncontrollableCower@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GAIUncontrollableCower@@UAEPAXI@Z' 0x00182320` prints CONFIRMED (exact, p_false=3.26e-03) and the MAE spelling CONTRADICTED; `check '??1AIUncontrollableCower@@UAE@XZ' 0x00182350` prints CONFIRMED (exact, p_false=6.52e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (vtable 0x010991D0 slot zero via ILT 0x0000C38D -> 0x00182320, which calls ILT 0x00007E0A -> 0x00182350).

The correction preserves the start, extent, instructions and relocation targets.
