// readable body of ?draw@Drawable@@QAEXPAVView@@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?freeBlock@MemoryPool@@: Code/GameEngine/Source/Common/System/GameMemory.cpp
template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
    int countInverseIntersection(const BitFlags &) const;
};

class BitFlagsCountInverseIntersectionShim
{
public:
    int run(const BitFlagsCountInverseIntersectionShim &) const;
};

template <int Bits>
int BitFlags<Bits>::countInverseIntersection(const BitFlags<Bits> &other) const
{
    return ((const BitFlagsCountInverseIntersectionShim *)this)->run(
        *(const BitFlagsCountInverseIntersectionShim *)&other);
}

template int BitFlags<17>::countInverseIntersection(const BitFlags<17> &) const;
