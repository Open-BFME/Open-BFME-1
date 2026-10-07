# AIMoveToStateSA destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x00182150 is `??_GAIMoveToStateSA@@UAEPAXI@Z`; the prior claim `??_GAIMoveToStateSA@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x00182180 is `??1AIMoveToStateSA@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GAIMoveToStateSA@@UAEPAXI@Z' 0x00182150` prints CONFIRMED (exact, p_false=3.39e-03) and the MAE spelling CONTRADICTED; `check '??1AIMoveToStateSA@@UAE@XZ' 0x00182180` prints CONFIRMED (exact, p_false=3.91e-04) and MAE/EAE CONTRADICTED. The class and identity are unchanged from the original evidence (constructor 0x00173620 installs dedicated vtable 0x01098FA8, slot zero ILT 0x0001B0CC -> 0x00182150, which calls ILT 0x0004B475 -> 0x00182180).

The correction preserves the start, extent, instructions and relocation targets.
