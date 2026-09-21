// cl: /O2 /MD
// Retail RVA 0x000481E9 is a five-byte incremental-link tail jump to the
// matched vector clear body at 0x00771D00. The address-derived wrapper keeps
// the thunk identity because two vector names share this retail address.

extern void rva000481e9Target(void);

#pragma comment(linker, "/alternatename:?rva000481e9Target@@YAXXZ=?clear@NuggetInsertOverflowShim@_STL@@QAEXXZ")

void j_000481e9(void)
{
	rva000481e9Target();
}
