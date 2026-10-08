# 0x0037EFB0 is ~ExperienceScalarTable

The 128-byte destructor at RVA 0x0037EFB0, previously matched under the address-derived placeholder `??1Gen_0037EFB0@@QAE@XZ`, is `??1ExperienceScalarTable@@QAE@XZ`.

Evidence: the matched scalar-deleting destructor `??_GExperienceScalarTable@@QAEPAXI@Z` (0x0037FB90; the class is proven by its exact named constructor 0x0037EF50 and the ExperienceLevelSystem ownership path) calls its complete destructor through ILT 0x00016E6E, which is `jmp 0x0037EFB0`. `python3 tools/ilt_oracle.py check '??1ExperienceScalarTable@@QAE@XZ' 0x0037EFB0` prints CONFIRMED (exact, p_false=1.96e-04).

The correction preserves the start, extent, instructions and relocation targets.
