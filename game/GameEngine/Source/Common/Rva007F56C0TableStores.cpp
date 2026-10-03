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

// Table-backed deleting wrappers; independent table-store witnesses above.
void __cdecl operator delete(void *);
extern int g_bfmeVftBVHW[];
struct Rva007F6E60
{
    const void **offset00;
    void *method(unsigned flags);
};
struct Rva00801650
{
    int *offset00;
    void *method(unsigned flags);
};
void *Rva007F6E60::method(unsigned flags)
{
    offset00 = Rva0112B5F0;
    if (flags & 1) operator delete(this);
    return this;
}
void *Rva00801650::method(unsigned flags)
{
    offset00 = g_bfmeVftBVHW;
    if (flags & 1) operator delete(this);
    return this;
}
