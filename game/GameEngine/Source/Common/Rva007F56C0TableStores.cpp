// cl: /DNDEBUG /MD /O2
// Padding-proven boundaries. Retail explicitly installs these table addresses;
// these opaque member names make no unsupported constructor identity claim.
extern const void *Rva0112B5F0[];
extern const void *Rva0112B680[];
struct Rva007F56C0 { const void **offset00; Rva007F56C0 *body(); };
Rva007F56C0 *Rva007F56C0::body() { offset00 = Rva0112B5F0; return this; }
struct Rva007F56D0 { const void **offset00; Rva007F56D0 *body(); };
Rva007F56D0 *Rva007F56D0::body() { offset00 = Rva0112B680; return this; }
struct Rva007F56E0 { const void **offset00; void body(); };
void Rva007F56E0::body() { offset00 = Rva0112B5F0; }
