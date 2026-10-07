# DozerActionMoveToActionPosState destructors are public (UAE), not protected (MAE)

The 30-byte scalar-deleting destructor at RVA 0x002B80C0 is `??_GDozerActionMoveToActionPosState@@UAEPAXI@Z`; the prior claim `??_GDozerActionMoveToActionPosState@@MAEPAXI@Z` had the right class and member but the wrong access. Its complete destructor at 0x002B80F0 is `??1DozerActionMoveToActionPosState@@UAE@XZ`.

Evidence: retail's incremental-link thunk table orders thunks by decorated name. `python3 tools/ilt_oracle.py check '??_GDozerActionMoveToActionPosState@@UAEPAXI@Z' 0x002B80C0` prints CONFIRMED (exact, p_false=1.70e-03) and the MAE spelling CONTRADICTED; `check '??1DozerActionMoveToActionPosState@@UAE@XZ' 0x002B80F0` prints CONFIRMED (exact, p_false=1.96e-04) and MAE CONTRADICTED. The class and identity are unchanged from the original evidence (0x002B80C0 calls ILT 0x000188DB -> 0x002B80F0, a 5-byte tail jump to the State destructor).

The correction preserves the start, extent, instructions and relocation targets.
