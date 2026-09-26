// Two more three-way splits, arms retracted alongside.
//
// 0x00360880 compares the float at +0x08 of one argument against the same
// field of the other. Neither argument is this and ecx is never read, so it is
// __stdcall. test ah,0x41 reads C0 and C3 together, so the true case is a
// strict greater.
//
// 0x004655B0 reads a function pointer at +0x1EC and, when it is set, calls it
// with this and both arguments through a cdecl frame the caller cleans -- the
// same shape as 0x00477D30 one argument wider. A null pointer is the only way
// it answers false.
//
// Both return int: mov eax,1 and xor eax,eax, not the two-byte al forms.

typedef float Real;

class BfmeFloatAt8
{
public:
	char m_bfmeHead[0x08];
	Real m_bfmeValue;						// +0x08
};

// ?Gen_00360880@@YGHPBVBfmeFloatAt8@@0@Z
int __stdcall Gen_00360880(const BfmeFloatAt8 *first, const BfmeFloatAt8 *second)
{
	if (first->m_bfmeValue > second->m_bfmeValue)
		return 1;

	return 0;
}

class Gen_004655b0;

typedef void (__cdecl *BfmeTwoArgHandler)(Gen_004655b0 *owner, void *first, void *second);

class Gen_004655b0
{
public:
	int bfmeDispatch(void *first, void *second);

private:
	char m_bfmeHead[0x1EC];
	BfmeTwoArgHandler m_bfmeHandler;				// +0x1EC
};

// ?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z
int Gen_004655b0::bfmeDispatch(void *first, void *second)
{
	if (m_bfmeHandler)
	{
		m_bfmeHandler(this, first, second);

		return 1;
	}

	return 0;
}
