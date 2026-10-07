# DozerActionPickActionPosState destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x002B8080 is `??_GDozerActionPickActionPosState@@UAEPAXI@Z`; the prior claim `??_GDozerActionPickActionPosState@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x002B80B0 is `??1DozerActionPickActionPosState@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GDozerActionPickActionPosState@@UAEPAXI@Z' 0x002B8080` prints CONFIRMED (exact, p_false=1.70e-03) and the MAE spelling CONTRADICTED; `check '??1DozerActionPickActionPosState@@UAE@XZ' 0x002B80B0` prints CONFIRMED (exact, p_false=5.22e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (0x002B8080 calls ILT 0x00010AB4 -> 0x002B80B0, a 5-byte tail jump to the State destructor).

The correction preserves the start, extent, instructions and relocation targets.
