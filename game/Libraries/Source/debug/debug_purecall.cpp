// cl: /DNDEBUG /MD /EHsc
// CRT _purecall override at RVA 0x0088C500.
// Identity: targets/game/reverse/identity_evidence/20261003-purecall-binding-audit.md
class BfmeAwakenLog {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual BfmeAwakenLog *slot38(const char *);
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C(int);
};
class BfmeAwakenDebug { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual BfmeAwakenLog *slot6C(int,int);
};
// Existing owned pointer cell; the original singleton class type is unproven.
extern void *g_Rva00F36E5C;

void _bfme_debugRecordCallsite(int kind);

extern "C" int __cdecl _purecall(void)
{
    _bfme_debugRecordCallsite(1);
    reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot60();
    BfmeAwakenLog *log = reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot6C(0, 0);
    log = log->slot38("Pure virtual function called.");
    log->slot4C(1);
    return 0;
}
