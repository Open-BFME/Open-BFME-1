// [BFME 2 donor] Declaration reconciled against original B1 comutil.obj.
// The actual16B class publicly inherits the SDK's16B tagVARIANT at0; no own
// fields or vtable. Only the two consumed APIs are declared, without defaults.
// No Microsoft COM implementation header or private flat variant view is used.
#ifndef BFME_COM_VARIANT_NATIVE_H
#define BFME_COM_VARIANT_NATIVE_H
#include <oaidl.h>
class _variant_t : public tagVARIANT {
public:
 _variant_t(long,unsigned short);
 ~_variant_t();
};
typedef char VariantNativeBaseSize[sizeof(tagVARIANT)==16?1:-1];
typedef char VariantNativeSize[sizeof(_variant_t)==16?1:-1];
#endif
