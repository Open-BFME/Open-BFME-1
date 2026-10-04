// cl: /O2 /MD
// Retail RVA 0x000481E9 is a five-byte incremental-link tail jump to the
// matched vector clear body at 0x00771D00. The address-derived wrapper keeps
// the thunk identity because two vector names share this retail address.
// The jump targets _STL::NuggetInsertOverflowShim::clear directly: the free
// alias plus its linker fallback directive are gone, and the union below is
// the incremental-link-thunk idiom the compiler folds into one rel32 to that
// name (no `this` setup, because the retail thunk is a bare jmp).

namespace _STL
{
class NuggetInsertOverflowShim
{
public:
	void clear();
};
}

void j_000481e9(void)
{
	typedef _STL::NuggetInsertOverflowShim Shim;
	union { void (Shim::*call)(); void (*fn)(); } u;
	u.call = &Shim::clear;
	u.fn();
}
