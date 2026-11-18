// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern void (__cdecl *TheBfmeFree)(void *block, unsigned int bytes);

// Base-destructor stub (gen_small ?m@Gen_0089a140@@QAEXXZ at 0x89A140).
struct Gen_0089a140 { void m(); };

struct Rva89A110DeletingDestructorThunk
{
	void *destroyAndMaybeDelete(unsigned int flags);
};

void *Rva89A110DeletingDestructorThunk::destroyAndMaybeDelete(unsigned int flags)
{
	((Gen_0089a140 *)this)->m();
	if (flags & 1) {
		TheBfmeFree(this, 8);
	}
	return this;
}
