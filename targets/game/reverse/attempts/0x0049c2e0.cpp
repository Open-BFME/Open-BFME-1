// ?rvaSetField@Rva0049C2E0Owner@@QAEXHH@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc

// Retail 0x0049C2E0, 127 bytes, __thiscall(ret 8, 2 stack args p1,p2). No
// caller or vtable evidence names the owning class; landed neighbours
// (CommandButtonConstructor.cpp etc) are only address-adjacent. Two
// independent bit tests of this->m_18 select unrelated behaviour:
//  - bit 0x800000: this->m_10==0x22 or ==0x2e selects a "resolve p1 against
//    three cached slots" chain that writes this->m_148 (0x2e always takes
//    the same path as the 0x22 branch's continuation, jumping straight to
//    the second flag test's already-pushed-args tail).
//  - bit 0x3000000: looks p1 up via the already-landed GameLogic::findObjectByID
//    and passes the result plus p2 to a still-unresolved dump (0x0049BA80).
// Neither test true: return without writing anything.

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;

struct Rva00367E30Logic
{
	char m_prefix[0x0c];
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;   // 0x012F0898

class Rva0049C2E0Owner
{
public:
	void rvaSetField(Int p1, Int p2);
	void rvaNotifyObject(Object *object, Int p2);

private:
	char m_prefix10[0x10];
	Int m_10;
	char m_prefix18[0x18 - 0x14];
	Int m_18;
	char m_prefix70[0x70 - 0x1c];
	Int m_70;
	Int m_74;
	Int m_78;
	char m_prefix148[0x148 - 0x7c];
	Int m_148;
};

// ?rvaSetField@Rva0049C2E0Owner@@QAEXHH@Z
void Rva0049C2E0Owner::rvaSetField(Int p1, Int p2)
{
    if (m_18 & 0x800000) {
        switch (m_10) {
        case 0x22: {
            if (p1 == m_70) { p1=m_74; if(p1==3) p1=m_70; }
            else if (p1 == m_74) { p1=m_78; if(p1==3) p1=m_70; }
            else if(p1==m_78) p1=m_70;
            m_148=p1;
            return;
        }
        case 0x2e:
            rvaNotifyObject(((GameLogic *)TheBfmeGameLogic)->findObjectByID(p1), p2);
            return;
        default: return;
        }
    } else if (!(m_18 & 0x3000000)) return;
    rvaNotifyObject(((GameLogic *)TheBfmeGameLogic)->findObjectByID(p1), p2);
}
