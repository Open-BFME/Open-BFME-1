// cl: /DNDEBUG /MD
// Address-derived global identity already used by Rva001FC2F0Get.cpp.
// Retail VA 0x012ADC38 is four-byte aligned and holds 0xFFFFFFFF.
// The gate constructor 0x001FCEC0 and the two 15-byte getter bodies
// 0x001FC2F0/0x001FC310 each read this location as one unsigned DWORD.
// No semantic global name is proven; see identity_evidence/001fcec0.md.
unsigned int g_sentinel012ADC38 = 0xFFFFFFFFU;
