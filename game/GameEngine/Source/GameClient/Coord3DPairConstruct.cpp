// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

struct ICoord2D { int x, y; };
struct Coord3D { float x, y, z; };

namespace _STL
{
template <class T, class U>
struct pair
{
    T first;
    U second;
};

template <class T, class U>
void _Construct(T *, const U &);

class Coord3DPairConstructShim
{
public:
    static void construct(pair<ICoord2D, Coord3D> *p, const pair<ICoord2D, Coord3D> &v);
};

template <class T, class U>
void _Construct(T *p, const U &v)
{
    Coord3DPairConstructShim::construct((pair<ICoord2D, Coord3D> *)p, *(const pair<ICoord2D, Coord3D> *)&v);
}

template void _Construct<pair<ICoord2D, Coord3D>, pair<ICoord2D, Coord3D> >(pair<ICoord2D, Coord3D> *, const pair<ICoord2D, Coord3D> &);
}
