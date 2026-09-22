// cl: /O2 /MD
//
// Address-qualified incremental-link tail thunks.  Their independently
// matched destinations establish the jump routes; the no-argument forwarding
// declarations preserve the real receiver and arguments on the caller stack.

extern void rva0000113BTarget(void);
extern void rva00006555Target(void);
extern void rva00007D06Target(void);

#pragma comment(linker, "/alternatename:?rva0000113BTarget@@YAXXZ=?Rva007849C0Clear@@YAXPAURva007849C0Owner@@@Z")
#pragma comment(linker, "/alternatename:?rva00006555Target@@YAXXZ=?end@?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QBE?AU?$_List_iterator@PAVDrawable@@U?$_Const_traits@PAVDrawable@@@_STL@@@2@XZ")
#pragma comment(linker, "/alternatename:?rva00007D06Target@@YAXXZ=?_M_lower_bound@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@ABEPAU?$_Rb_tree_node@VAsciiString@@@2@ABVAsciiString@@@Z")

void j_0000113B(void)
{
	rva0000113BTarget();
}

void j_00006555(void)
{
	rva00006555Target();
}

void j_00007D06(void)
{
	rva00007D06Target();
}
