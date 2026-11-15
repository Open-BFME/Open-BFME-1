// cl: /EHsc
// Open-BFME: the BFME2 three-string AnimSet copy constructor and destructor.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class GenericObjectCreationNugget
{
public:
    struct AnimSet
    {
        AnimSet(const AnimSet &source);
        ~AnimSet();

        AsciiString m_animInitial;
        AsciiString m_animFlying;
        AsciiString m_animFinal;
    };
};

GenericObjectCreationNugget::AnimSet::AnimSet(const AnimSet &source)
    : m_animInitial(source.m_animInitial),
      m_animFlying(source.m_animFlying),
      m_animFinal(source.m_animFinal)
{
}

GenericObjectCreationNugget::AnimSet::~AnimSet()
{
}
