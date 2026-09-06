// cl: /O2 /Oy /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef unsigned long DWORD;

struct BfmeOSVersionInfo
{
	DWORD dwOSVersionInfoSize;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	DWORD dwBuildNumber;
	DWORD dwPlatformId;
	char szCSDVersion[128];
};

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(BfmeOSVersionInfo *info);
extern "C" void *__cdecl memset(void *, int, unsigned int);

class BfmeStrVM0
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int v31();
	virtual int v32();
	virtual int v33();
	virtual int v34();
	virtual int v35();
	virtual int v36();
	virtual int v37();
	virtual int v38();
	virtual int v39();
	virtual int v40();
	virtual int v41();
	virtual int v42();
	virtual int v43();
	virtual int v44();
	virtual int v45();
	virtual int v46();
	virtual int v47();
	virtual int v48();
	virtual int v49();
	virtual int v50();
	virtual int v51();
	virtual int v52();
	virtual int v53();
	virtual int v54();
	virtual int v55();
	virtual int v56();
	virtual bool bfmeGateVM0(AsciiString, int, int, int);
	virtual int v58();
	virtual int v59();
	virtual bool bfmePredVM0();
	void bfmeGoVM0(int);
	bool bfmeCheckVM0(AsciiString name, int flags);
};

bool BfmeStrVM0::bfmeCheckVM0(AsciiString name, int flags)
{
	BfmeOSVersionInfo osvi;
	memset(&osvi, 0, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionExA(&osvi);
	if (osvi.dwPlatformId == 1)
		return false;
	if (bfmeGateVM0(name, flags & ~8, -1, -1))
	{
		if (!bfmePredVM0())
			goto success;
		bfmeGoVM0(3);

		success:
		return true;
	}
	return false;
}
