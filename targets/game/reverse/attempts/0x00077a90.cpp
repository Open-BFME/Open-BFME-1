// ?grow@Rva00077a90@@QAEXPAUInputArg@@@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Od /Ob0
// stlport
// The two retail marker blocks require inline assembly.
#include <map>
#include <set>

struct Rva00077a90Record {
    unsigned int field0[2];
    unsigned int field8;
    unsigned int fieldc;
    unsigned int field10;
    unsigned int field14;
    unsigned int field18;
    unsigned int field1c;
    unsigned int field20;
    unsigned int *field24;
    unsigned int field28;
    unsigned int field2c;
};

struct InputArg {
    Rva00077a90Record *field0;
    unsigned int **field4;
};

class BfmeTreeYN;
class BfmeTreeYK;
class BfmeTreeYM;
class BfmeTreeYL;
BfmeTreeYN *bfmeTreeYN();
BfmeTreeYK *bfmeTreeYK();
BfmeTreeYM *bfmeTreeYM();
BfmeTreeYL *bfmeTreeYL();

typedef _STL::set<unsigned int> Rva00077a90Set;
typedef _STL::map<unsigned int, Rva00077a90Record *> Rva00077a90RecordMap;
typedef _STL::map<unsigned int, unsigned int> Rva00077a90WordMap;

class Rva00077a90 { public: void grow(InputArg *arg); };

// ?grow@Rva00077a90@@QAEXPAUInputArg@@@Z
void Rva00077a90::grow(InputArg *arg)
{
    __asm {
        push eax
        mov eax, 0CFCECDCCh
        mov eax, 0477A9Fh
        mov eax, 0
        mov eax, 0
        mov eax, 0CFCECDCCh
        pop eax
    }

    unsigned int **array;
    Rva00077a90Record *base = arg->field0;
    Rva00077a90Set::iterator found = ((Rva00077a90Set *)bfmeTreeYN())->find(base->field8);
    if (found == ((Rva00077a90Set *)bfmeTreeYN())->end()) {
        array = arg->field4;
        *array = new unsigned int[base->field28];
        (*array)[base->field2c] = base->field1c;
        base->field24 = &(*array)[base->field2c];
        _STL::pair<unsigned int, Rva00077a90Record *> recordPair(base->field8, base);
        ((Rva00077a90RecordMap *)bfmeTreeYK())->insert(recordPair);
        {
            _STL::pair<unsigned int, unsigned int> firstPair(base->field10, base->field8);
            ((Rva00077a90WordMap *)bfmeTreeYM())->insert(firstPair);
        }
        _STL::pair<unsigned int, unsigned int> secondPair(base->field14, base->field8);
        ((Rva00077a90WordMap *)bfmeTreeYL())->insert(secondPair);
    }

    __asm {
        push eax
        mov eax, 0CFCECDCCh
        mov eax, 0477A9Fh
        mov eax, 0
        mov eax, 0
        mov eax, 0CECDCCCBh
        pop eax
    }
}
