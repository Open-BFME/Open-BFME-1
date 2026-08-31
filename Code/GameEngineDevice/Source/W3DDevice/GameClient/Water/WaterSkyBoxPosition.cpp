// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// Clean reconstruction of the small water-renderer sky-box position helper.

#include "vector3.h"

class RenderObjClass
{
public:
    Vector3 Get_Position(void) const;
};

class WaterSkyBoxPositionAccessor
{
public:
    Vector3 getSkyBoxPosition(void) const;

private:
    unsigned char m_prefix[0x250];
    RenderObjClass *m_skyBox;
};

Vector3 WaterSkyBoxPositionAccessor::getSkyBoxPosition(void) const
{
    Vector3 position;

    if (m_skyBox)
        position = m_skyBox->Get_Position();

    return Vector3(position.X, position.Y, position.Z);
}
