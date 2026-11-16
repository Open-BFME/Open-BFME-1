// cl: /O2

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

class Image
{
public:
	const ICoord2D *getTextureSize() const;
};

const ICoord2D *Image::getTextureSize() const
{
	return (const ICoord2D *)((const unsigned char *)this + 0x0C);
}
