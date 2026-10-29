// The separately stored BFME 1 base-check fallback read at VA 0x010E1F40.
// Retail .rdata is 00 00 C8 41 (25.0f). Keep an external definition in a
// data-only TU so the existing caller retains its observed memory load.
// The original source identity of this constant is unproven.
extern const float g_010E1F40 = 25.0f;
