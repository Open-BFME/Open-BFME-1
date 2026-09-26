// cl: /DNDEBUG /MD /EHsc
// The carved body at retail RVA 0x001EE7E0 has one pointer argument and ret 4.
// Its boundary ends immediately before the int3 padding, so an empty stdcall
// body reproduces the complete three-byte extent.

void __stdcall Rva001EE7E0Ret4(void *)
{
}
