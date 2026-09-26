// BFME PlayerTemplate image-name layout, recovered from the retail INI field
// table at 0x00C849D0..0x00C84A00. The retained Zero Hour header is twelve
// bytes short here, which previously made these identical-shaped getters land
// under the neighboring field names.

class AsciiString;
class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

class PlayerTemplate
{
public:
	const Image *getHeadWaterMarkImage() const;
	const Image *getFlagWaterMarkImage() const;
	const Image *getSideIconImage() const;
	const Image *getEnabledImage() const;
};

static const AsciiString &bfmeImageNameAt(const PlayerTemplate *self, unsigned int offset)
{
	return *reinterpret_cast<const AsciiString *>(
		reinterpret_cast<const char *>(self) + offset);
}

const Image *PlayerTemplate::getHeadWaterMarkImage() const
{
	return TheMappedImageCollection->findImageByName(bfmeImageNameAt(this, 0xd4));
}

const Image *PlayerTemplate::getFlagWaterMarkImage() const
{
	return TheMappedImageCollection->findImageByName(bfmeImageNameAt(this, 0xd8));
}

const Image *PlayerTemplate::getSideIconImage() const
{
	return TheMappedImageCollection->findImageByName(bfmeImageNameAt(this, 0xe0));
}

const Image *PlayerTemplate::getEnabledImage() const
{
	return TheMappedImageCollection->findImageByName(bfmeImageNameAt(this, 0xdc));
}
