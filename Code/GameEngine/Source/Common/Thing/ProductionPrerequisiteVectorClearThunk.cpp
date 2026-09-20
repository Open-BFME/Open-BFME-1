// cl: /O2 /MD

// Retail RVA 0x0001FE92 is a five-byte tail jump to the matched
// ProductionPrerequisite vector clear body at RVA 0x003AFE10.
extern void rva0001fe92Target(void);

#pragma comment(linker, "/alternatename:?rva0001fe92Target@@YAXXZ=?_M_clear@?$vector@VProductionPrerequisite@@V?$allocator@VProductionPrerequisite@@@_STL@@@_STL@@IAEXXZ")

// ?j_0001FE92@@YAXXZ
void j_0001FE92(void)
{
	rva0001fe92Target();
}
