#ifndef RVA0093DD20_COPY_H
#define RVA0093DD20_COPY_H

// Copies the two-byte field at 0 and four-byte field at 4, in that order.
// Bytes 2 and 3 are untouched. A null destination does not access source.
// The byte-storage contract requires no alignment or original value type.
// Otherwise both pointers must address at least eight bytes of storage, with
// the destination writable. This operation does not construct a typed object.
void __cdecl Rva0093DD20Copy(unsigned char *destination,
	const unsigned char *source);

#endif
