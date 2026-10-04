// Readonly floats read by the pathfinder radius/center conversion
// (PathfindGetRadiusAndCenter and its Rva003DF250/003E3D20/003E5E40/FindSafePath
// siblings). Retail .rdata: VA 0x010977E0 holds 00 00 A0 41 (20.0f) and VA
// 0x01095F98 holds 9A 99 99 3E (0.3f). The third operand, 10.0f at VA
// 0x01075C74, is already defined as g_bfmeDirectionWeight1285. No EA names are
// proven, so these keep address-derived spellings.
extern const float g_Rva010977E0 = 20.0f;
float g_Rva01095F98 = 0.3f;
