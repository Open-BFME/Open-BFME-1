// cl: /DNDEBUG /MD /EHsc
// The retail body at 0x0001E902 is a five-byte incremental-link jump to the
// matched SupplyWarehouseDockUpdate constructor at 0x002CF800. The address-
// derived thunk keeps the separate call-site identity without adding another
// naked byte lift.

extern void rva0001e902Target(void);

#pragma comment(linker, "/alternatename:?rva0001e902Target@@YAXXZ=??0SupplyWarehouseDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z")

void Rva0001E902SupplyWarehouseCtorThunk(void)
{
    rva0001e902Target();
}
