// cl: /O2
// Open-BFME: BfmeThingEOA scalar-deleting destructor, retail 0x0006E220
// (30 bytes). Constructor 0x0006B190 installs vtable 0x01075B08; slot zero
// reaches this wrapper through ILT 0x0000B2D5. Its complete destructor routes
// through ILT 0x0001FF96 and tail thunk 0x0006B400 to base dtor 0x009D83D0.

class BfmeThingEOA
{
public:
    __declspec(noinline) virtual ~BfmeThingEOA();
};

BfmeThingEOA::~BfmeThingEOA()
{
}
