// cl: /O2 /MD
// Retail RVA 0x000481E9 is a five-byte incremental-link tail jump to the
// matched vector clear body at 0x00771D00. The address-derived wrapper keeps
// the thunk identity because two vector names share this retail address.
// The jump targets the existing address-qualified vector clear provider.
// A zero-stack-slot declaration preserves ECX across the bare tail jump;
// the receiving thiscall body consumes the original caller's receiver.

extern "C" void __identifier("?_M_clear@?$vector@URva0013B8F0Element@@V?$allocator@URva0013B8F0Element@@@_STL@@@_STL@@IAEXXZ")();

void j_000481e9(void)
{
	__identifier("?_M_clear@?$vector@URva0013B8F0Element@@V?$allocator@URva0013B8F0Element@@@_STL@@@_STL@@IAEXXZ")();
}
