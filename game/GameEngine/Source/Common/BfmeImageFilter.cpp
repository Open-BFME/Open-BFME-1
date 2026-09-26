// cl: /EHsc
#include <excpt.h>

// ?bfmeProbeSse2@@YAHXZ
int __cdecl bfmeProbeSse2(void)
{
	unsigned int code;
	__try {
		__asm { xorpd xmm0, xmm0 }
	} __except ((code = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)) {
		return 0;
	}
	return 1;
}
