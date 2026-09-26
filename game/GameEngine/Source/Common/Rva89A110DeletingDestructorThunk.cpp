__declspec(dllimport) void __cdecl operator delete(void *, unsigned int);

struct Rva89A110DeletingDestructorThunk
{
	void destroyBody();
	void *destroyAndMaybeDelete(unsigned int flags);
};

void *Rva89A110DeletingDestructorThunk::destroyAndMaybeDelete(unsigned int flags)
{
	destroyBody();
	if (flags & 1) {
		operator delete(this, 8);
	}
	return this;
}
