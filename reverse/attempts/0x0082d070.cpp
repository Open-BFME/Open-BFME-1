// ?d_0082d070@@YAXXZ
// partial score=0.96 date=2026-08-30
// cl: /Od
struct BfmeTagA82D070 { char m_dummy; };
struct BfmeTagB82D070 { char m_dummy; };
struct Rva0082C6E0Value;
Rva0082C6E0Value *rva0082C6E0CopyValues(Rva0082C6E0Value *first, Rva0082C6E0Value *last, Rva0082C6E0Value *dest);
Rva0082C6E0Value *bfmeCopy82D070(Rva0082C6E0Value *first, Rva0082C6E0Value *last, Rva0082C6E0Value *dest)
{
	BfmeTagA82D070 one;
	BfmeTagB82D070 two;
	BfmeTagA82D070 sourceOne;
	BfmeTagB82D070 sourceTwo;

	sourceOne = BfmeTagA82D070();
	one = sourceOne;
	sourceTwo = BfmeTagB82D070();
	two = sourceTwo;

	return rva0082C6E0CopyValues(first, last, dest);
}
