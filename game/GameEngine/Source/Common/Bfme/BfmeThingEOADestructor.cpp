// cl: /O2
// BfmeThingEOA complete destructor at retail 0x0006B400 (5 bytes):
// ??_GBfmeThingEOA (0x0006E220) calls it through ILT 0x0001FF96; the body is
// one jmp into the base destructor 0x009D83D0 (??1Gen_009D83D0@@UAE@XZ) with
// no vptr re-seat of its own. novtable reproduces that; it lives apart from
// the ??_G TU because a novtable class there would not emit its ??_G.

class Gen_009D83D0
{
public:
    virtual ~Gen_009D83D0();
};

class __declspec(novtable) BfmeThingEOA : public Gen_009D83D0
{
public:
    virtual ~BfmeThingEOA();
};

BfmeThingEOA::~BfmeThingEOA()
{
}
