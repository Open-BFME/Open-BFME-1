// [BFME 2 donor] One shared canonical declaration adapted from authored ComError.h.
// B1 original comraise/invkerr CodeView proves16B, vptr0, HRESULT4, IErrorInfo*8
// and char* allocation12. Project field names remain result/info/message; native
// names are m_hresult/m_perrinfo/m_pszMsg. This declares only the four consumed
// APIs; no claim of a complete14-method surface or inferred defaults is made.
// SDK supplies interface declarations only. No implementation header is used.
// The generated data skeleton is completed with evidenced API declarations;
// no implementation body is defined here.
#ifndef CANONICAL__COM_ERROR_H
#define CANONICAL__COM_ERROR_H
#include <oaidl.h>

class _com_error {
public:
 _com_error(long,IErrorInfo*,bool);
 _com_error(const _com_error&);
 virtual ~_com_error();
 static long WCodeToHRESULT(unsigned short);
private:
 long result;
 IErrorInfo *info;
 char *message;
};
typedef char ComErrorNativeSize[sizeof(_com_error)==16?1:-1];
#endif
