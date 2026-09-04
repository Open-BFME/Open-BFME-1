// ?parseImageSequence@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// partial score=0.82 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring8outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/Image.h"
#include "GameLogic/GameLogic.h"

// BFME keeps the release parser's formatted exception path.  The reference
// header is unavailable in this tree, so this TU carries the ABI-sized shell
// used by the neighboring parseNumImages/storeImage reconstruction.
class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	Int m_code;
	const char *m_message;
};

// ?parseImageSequence@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
void Anim2DTemplate::parseImageSequence(INI *ini, void *instance, void *store, const void *userData)
{
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	if (animTemplate->getNumFrames() == NUM_FRAMES_INVALID) {
		throw INIException(3,
			"Anim2DTemplate::parseImageSequence - You must specify the number of animation frames for animation '%s' *BEFORE* specifying the image sequence name\n",
			animTemplate->getName().str());
	}

	AsciiString imageBaseName = ini->getNextAsciiString();
	AsciiString imageName;
	const Image *image;
	for (Int i = 0; i < animTemplate->getNumFrames(); ++i) {
		imageName.format("%s%03d", imageBaseName.str(), i);
		image = TheMappedImageCollection->findImageByName(imageName);
		if (image == NULL) {
			throw INIException(3,
				"Anim2DTemplate::parseImageSequence - Image '%s' not found for animation '%s'.  Check the number of images specified in INI and also make sure all the actual images exist.\n",
				imageName.str(), animTemplate->getName().str());
		}
		animTemplate->storeImage(image);
	}
}
