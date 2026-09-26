// cl: /O2
// BFME Image size accessor, retail 0x005BA130.

struct ICoord2D
{
	int x;
	int y;
};

class Image
{
public:
	const ICoord2D *getImageSize() const;
};

const ICoord2D *Image::getImageSize() const
{
	return (const ICoord2D *)((const unsigned char *)this + 0x24);
}
