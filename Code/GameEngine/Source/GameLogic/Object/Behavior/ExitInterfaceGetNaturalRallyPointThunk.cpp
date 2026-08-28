// cl: /DNDEBUG /MD /EHsc

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class ExitInterface
{
public:
    virtual bool getNaturalRallyPoint(Coord3D &, bool) const;
};

// ?getNaturalRallyPoint@ExitInterface@@UBE_NAAUCoord3D@@_N@Z
bool ExitInterface::getNaturalRallyPoint(Coord3D &point, bool) const
{
    unsigned int *components = reinterpret_cast<unsigned int *>(&point);
    components[2] = 0;
    components[1] = 0;
    components[0] = 0;
    return false;
}
