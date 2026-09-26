// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x00699E90 is the vector-deleting wrapper for the 0x40-byte
// Rva00699D60AudioOwner object.  The wrapper's scalar-destructor call goes
// through the existing 0x0002D902 thunk to the matched 0x00699D60 body.
// Keep this ABI slice storage-only: the separately matched destructor owns
// the real member cleanup, while the byte width is fixed by the retail
// __ehvec_dtor operand (0x40).
void operator delete[](void *block);

class Rva00699D60AudioOwner
{
public:
	~Rva00699D60AudioOwner(void);

private:
	unsigned char m_storage[0x40];
};

Rva00699D60AudioOwner *MakeRva00699D60AudioOwnerArray(void)
{
	return new Rva00699D60AudioOwner[2];
}

void DeleteRva00699D60AudioOwnerArray(Rva00699D60AudioOwner *array)
{
	delete[] array;
}
