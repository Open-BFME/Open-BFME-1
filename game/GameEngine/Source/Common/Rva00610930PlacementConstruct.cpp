// cl: /DNDEBUG /MD
// Placement-construct helper, RVA 0x00610930, 19 bytes:
//   mov ecx,[esp+4]; test ecx,ecx; je ret; mov eax,[esp+8]; push eax;
//   call ILT 0x00018ACA; ret
// STLport's _Construct shape (null-checked placement new), constructing the
// 16-byte linked node whose constructor is the matched 0x0060FB70
// (BfmeNodeAS::BfmeNodeAS, reached through ILT 0x00018ACA) from its second
// argument. Its ?dup_ row used to borrow MoneyVectorPushBack.cpp's
// _Construct<Money>, whose call reaches Money's copy constructor instead.
// Identity not recovered: the helper is named for its address, and the
// callee keeps the name its matched row carries.

struct BfmeSpecAS;

class BfmeNodeAS
{
public:
	BfmeNodeAS(const BfmeSpecAS *spec);

private:
	int m_fields[4];
};

inline void *operator new(unsigned int, void *place)
{
	return place;
}

void Rva00610930Construct(BfmeNodeAS *node, const BfmeSpecAS *spec)
{
	new (node) BfmeNodeAS(spec);
}
