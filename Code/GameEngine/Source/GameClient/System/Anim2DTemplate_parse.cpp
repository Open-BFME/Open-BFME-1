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

// The parser pair is kept in its own TU so the neighboring Anim2D.cpp compiler
// labels stay stable. BFME retains the formatted INIException path in release.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
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

// ?parseNumImages@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
void Anim2DTemplate::parseNumImages(INI *ini, void *instance, void *store, const void *userData)
{
	UnsignedInt numFrames;
	ini->parseUnsignedInt(ini, instance, &numFrames, userData);

	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	Int minimumFrames = 1;
	if (numFrames < minimumFrames) {
		throw INIException(3, "Anim2DTemplate::parseNumImages - Invalid animation '%s', animations must have '%d' or more frames defined\n",
			animTemplate->getName().str(), minimumFrames);
	}

	animTemplate->allocateImages((UnsignedShort)numFrames);
}

// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z
void Anim2DTemplate::storeImage(const Image *image)
{
	if (image == NULL) {
		return;
	}

	for (Int i = 0; i < m_numFrames; ++i) {
		if (m_images[i] == NULL) {
			m_images[i] = image;
			return;
		}
	}

	throw INIException(3, "Anim2DTemplate::storeImage - Unable to store image '%s' into animation '%s' because the animation is setup to only support '%d' image frames\n",
		image->getName().str(), getName().str(), m_numFrames);
}
