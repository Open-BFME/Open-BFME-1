// ?d_001eed80@@YAXXZ
// partial score=0.26 date=2026-09-26

// checkForAutoHeal(Object *, void *) at retail 0x001EED80, 66 bytes.
// The vendored callback declares void (?checkForAutoHeal@@YAXPAVObject@@PAX@Z),
// but retail ends with MOV EAX,1 on both paths. BFME's player iterator treats
// visitor EAX as a continue/stop result: the candidate therefore returns int
// (?checkForAutoHeal@@YAHPAVObject@@PAX@Z), always continuing traversal.
// Same-TU static predicate is included below. Retail passes scan data in EAX
// and testObj in EBX without stack arguments. The callback candidate probes
// 66/66 bytes with 44 non-relocation differences and two relocation-layout
// mismatches; it pushes EDI and holds the scan data there instead of ESI.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1

#include "0x001ee670.cpp"

int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (rva001EE670EligibleForAutoHeal(helper, testObj))
		helper->m_objectList->push_back(testObj);
	return 1;
}
