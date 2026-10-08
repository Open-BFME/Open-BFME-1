# RiderChangeContain destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x0022A510 is `??_GRiderChangeContain@@UAEPAXI@Z`; the prior claim `??_GRiderChangeContain@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x0022A540 (reached through ILT 0x0001CA80) is `??1RiderChangeContain@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GRiderChangeContain@@UAEPAXI@Z' 0x0022A510` prints CONFIRMED (exact, p_false=1.30e-03) and the MAE spelling CONTRADICTED; `check '??1RiderChangeContain@@UAE@XZ' 0x0022A540` prints CONFIRMED (exact, p_false=1.96e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (constructor 0x00229FB0 installs dedicated vtable 0x010ACAF0, slot zero ILT 0x000310AC -> 0x0022A510, which calls ILT 0x0001CA80 -> 0x0022A540, a 5-byte tail jump through ILT 0x0004AB47 to the SiegeEngineContain destructor 0x0022B870).

The correction preserves the start, extent, instructions and relocation targets.
