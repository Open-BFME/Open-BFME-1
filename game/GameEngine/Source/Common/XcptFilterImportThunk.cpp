// cl: /DNDEBUG /MD /EHs-c-
// MSVCR71.dll _XcptFilter import stub at 0x009F7EEC: FF 25 [IAT].

// Retail's IAT slot 0x01359258 is MSVCR71's _XcptFilter (imports.csv), so the
// slot is __imp___XcptFilter. C cannot declare that import beside its own
// _XcptFilter definition, so the slot is read as a pointer; C linkage adds
// the leading underscore.
extern "C" int (__cdecl *__identifier("_imp___XcptFilter"))(unsigned long code, void *info);

extern "C" int __cdecl _XcptFilter(unsigned long code, void *info)
{
	return __identifier("_imp___XcptFilter")(code, info);
}
