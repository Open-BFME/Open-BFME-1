template<int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
    int countInverseIntersection(const BitFlags<Bits> &) const;
};

class BitFlagsHFCountInverseIntersectionShim
{
public:
    int run(const BitFlagsHFCountInverseIntersectionShim &) const;
};

template<int Bits>
int BitFlags<Bits>::countInverseIntersection(const BitFlags<Bits> &other) const
{
    return ((const BitFlagsHFCountInverseIntersectionShim *)this)->run(
        *(const BitFlagsHFCountInverseIntersectionShim *)&other);
}

template int BitFlags<117>::countInverseIntersection(const BitFlags<117> &) const;
