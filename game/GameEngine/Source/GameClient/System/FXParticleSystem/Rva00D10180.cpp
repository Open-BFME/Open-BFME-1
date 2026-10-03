// cl: /DNDEBUG /MD /EHsc
// Five contiguous retail pointer tables, VA 01110180..01110244.
// GeneralsMD ParticleSys.h preserves their order; BFME's actual elements
// differ in the first two tables. Each table ends in a null pointer.
// Addresses remain in the names because semantic ownership is unproven.

extern const char *const g_rva01110180Names[] = {
    "NONE", "ADDITIVE", "ADDITIVE_ALPHA_TEST", "ALPHA", "ALPHA_TEST",
    "MULTIPLY", "ADDITIVE_NO_DEPTH_TEST", "ALPHA_NO_DEPTH_TEST",
    "W3D_DIFFUSE", "W3D_ALPHA", "W3D_EMISSIVE", 0
};

extern const char *const g_rva011101B0Names[] = {
    "NONE", "PARTICLE", "DRAWABLE", "STREAK", "VOLUME_PARTICLE",
    "SMUDGE", "TERRAIN_PARTICLE", 0
};

extern const char *const g_rva011101D0Names[] = {
    "NONE", "ORTHO", "SPHERICAL", "HEMISPHERICAL", "CYLINDRICAL",
    "OUTWARD", 0
};

extern const char *const g_rva011101ECNames[] = {
    "NONE", "POINT", "LINE", "BOX", "SPHERE", "CYLINDER", 0
};

extern const char *const g_rva01110208Names[] = {
    "NONE", "WEAPON_EXPLOSION", "SCORCHMARK", "DUST_TRAIL", "BUILDUP",
    "DEBRIS_TRAIL", "UNIT_DAMAGE_FX", "DEATH_EXPLOSION", "SEMI_CONSTANT",
    "CONSTANT", "WEAPON_TRAIL", "AREA_EFFECT", "CRITICAL", "ALWAYS_RENDER", 0
};
