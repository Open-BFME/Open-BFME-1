// ?parseImageSequence@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// partial score=0.82 date=2026-09-10
// Bounded semantic probe for Anim2DTemplate::parseImageSequence at 0x005BB150.
// This variant keeps the proven retail ILT routes for the two late calls.
class Anim2DTemplateImageStoreView
{
public:
	void storeImage(const Image *image);
};

#pragma comment(linker, "/alternatename:?storeImage@Anim2DTemplateImageStoreView@@QAEXPBVImage@@@Z=?j_0001cf0d@@YAXXZ")

class Anim2DImageCollectionView
{
public:
	const Image *findImageByName(const AsciiString &name);
};

#pragma comment(linker, "/alternatename:?findImageByName@Anim2DImageCollectionView@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")

void Anim2DTemplate::parseImageSequence(INI *ini, void *instance,
	void *store, const void *userData)
{
	const Image *image;
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;

	if (animTemplate->getNumFrames() == NUM_FRAMES_INVALID) {
		throw INIException(3,
			"Anim2DTemplate::parseImageSequence - You must specify the number of animation frames for animation '%s' *BEFORE* specifying the image sequence name\n",
			animTemplate->getName().str());
	}

	AsciiString imageBaseName = ini->getNextAsciiString();
	AsciiString imageName;
	for (UnsignedInt i = 0; i < animTemplate->getNumFrames(); ++i) {
		imageName.format("%s%03d", imageBaseName.str(), i);
		image = ((Anim2DImageCollectionView *)TheMappedImageCollection)->findImageByName(imageName);
		if (image == NULL) {
			throw INIException(3,
				"Anim2DTemplate::parseImageSequence - Image '%s' not found for animation '%s'.  Check the number of images specified in INI and also make sure all the actual images exist.\n",
				imageName.str(), animTemplate->getName().str());
		}
		((Anim2DTemplateImageStoreView *)animTemplate)->storeImage(image);
	}
}
