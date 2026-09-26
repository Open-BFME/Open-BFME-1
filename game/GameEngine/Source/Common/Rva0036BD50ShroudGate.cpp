// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x0036BD50 keeps the receiver address-qualified: its owner is the
// pointer stored four bytes before the module, with position at owner+0x38.
// The final helper receives the local player's index as a raw 32-bit value.

struct Coord3D { float x, y, z; };

struct Rva00367E30Logic {
    char pad[0x10C];
    int mode;
};
extern Rva00367E30Logic *TheBfmeGameLogic;

enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED };
class PartitionManager {
public:
    CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *position) const;
};
struct Rva002EEDA0ShroudManager;
extern Rva002EEDA0ShroudManager *Rva002EEDA0TheShroudManager;

struct Rva002EE330Player {
    char pad[0x24];
    int index;
};
struct Rva002EE330PlayerList {
    char pad[0xC];
    Rva002EE330Player *local;
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

struct Rva0036BD50Owner {
    char pad[0x38];
    Coord3D position;
};
class BfmeThing916C {
public:
    void bfmeGo916C(void *value);
};

class Rva0036BD50Module {
public:
    void check(int unused);
};

void Rva0036BD50Module::check(int)
{
    Rva00367E30Logic *logic = TheBfmeGameLogic;
    if (!logic)
        return;
    int mode = logic->mode;
    if (mode != 1 && mode != 5 && mode != 2)
        return;

    Rva0036BD50Owner *owner = *(Rva0036BD50Owner **)((char *)this - 4);
    PartitionManager *shroud = (PartitionManager *)Rva002EEDA0TheShroudManager;
    if (!shroud || !owner)
        return;
    Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
    if (!players || !players->local)
        return;
    int index = players->local->index;
    if (shroud->getShroudStatusForPlayer(index, &owner->position) == CELLSHROUD_FOGGED)
        ((BfmeThing916C *)owner)->bfmeGo916C((void *)index);
}
