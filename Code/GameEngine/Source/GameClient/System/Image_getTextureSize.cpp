// cl: /O2

struct ICoord2D
{
	int x;
	int y;
};

class Image
{
public:
	const ICoord2D *getTextureSize() const;
};

const ICoord2D *Image::getTextureSize() const
{
	return (const ICoord2D *)((const unsigned char *)this + 0x0C);
}
