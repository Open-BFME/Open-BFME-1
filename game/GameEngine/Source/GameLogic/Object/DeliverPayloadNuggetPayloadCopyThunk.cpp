// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Retail RVA 0x000097CD jumps to the matched Payload copy body at 0x0036D980.
// The symbol pin and ObjectCreationList.cpp callers identify this as the
// DeliverPayloadNugget Payload STLport copy specialization.

extern void rva000097CDTarget(void);

#pragma comment(linker, "/alternatename:?rva000097CDTarget@@YAXXZ=??$__copy@PAUPayload@DeliverPayloadNugget@@PAU12@H@_STL@@YAPAUPayload@DeliverPayloadNugget@@PAU12@00ABUrandom_access_iterator_tag@0@PAH@Z")

void Rva000097CDDeliverPayloadCopyThunk(void)
{
	rva000097CDTarget();
}
