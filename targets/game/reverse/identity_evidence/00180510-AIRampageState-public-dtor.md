# AIRampageState destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x00180510 is `??_GAIRampageState@@UAEPAXI@Z`; the prior claim `??_GAIRampageState@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x00180540 is `??1AIRampageState@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GAIRampageState@@UAEPAXI@Z' 0x00180510` prints CONFIRMED (exact, p_false=1.70e-03) and the MAE spelling CONTRADICTED; `check '??1AIRampageState@@UAE@XZ' 0x00180540` prints CONFIRMED (exact, p_false=3.91e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (constructor 0x001719F0 installs dedicated vtable 0x010984D8, slot zero ILT 0x0003F07B -> 0x00180510, which calls ILT 0x00040967 -> 0x00180540).

The correction preserves the start, extent, instructions and relocation targets.
