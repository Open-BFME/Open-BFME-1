// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class BFMERopeDrawable
{
public:
    const Coord3D *getPosition() const;
};

class BFMERopeDrawableGetPositionShim
{
public:
    const Coord3D *get() const;
};

// ?j_0004b12d@@YAXXZ
const Coord3D *BFMERopeDrawable::getPosition() const
{
    return ((const BFMERopeDrawableGetPositionShim *)this)->get();
}
