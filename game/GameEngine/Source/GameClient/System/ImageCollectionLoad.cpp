// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
// ImageCollection::load, retail 0x005D23A0, 600 bytes.
//
// Identity. The name is the one the Open-BFME5 lift carried, and the body
// corroborates it rather than contradicting it. It is the Zero Hour method
// Image.cpp:315 declares on ImageCollection, with BFME's additions: three
// directories Zero Hour does not load (AptImages, ParticleTextures,
// TransitionImages) alongside its two (TextureSize_%d, HandCreated), and the
// two "%sINI\MappedImages" strings built from GlobalData::getPath_UserData. It
// sits inside the ImageCollection method cluster whose other members are
// already matched under that class -- findImageByName at 0x005D2CF0 and
// addImage at 0x005D3410, both in game/GameEngine/Source/GameClient/System/
// Image.cpp -- and it takes exactly the one int argument, closes with
// `ret 4`, and reads no member: the identity check's suspicion that `this` is
// unused is true, which is also why this translation unit can declare the
// class without a layout. Its one direct caller, ?d_0042f5a0, is anonymous, so
// nothing names the symbol from outside; the class name rests on that cluster
// and the Zero Hour twin.
//
// The body never reads `this` -- ecx is overwritten by the first INI
// construction and no member of ImageCollection is touched -- so this
// translation unit declares the class it is a method of without a layout.
// It cannot: the class's own header is the Zero Hour GameClient/Image.h, whose
// AsciiString has a FOUR-byte string header and whose GlobalData::getPath_UserData
// is an inline `const AsciiString&`, while retail calls that accessor out of
// line (0x000106EA -> 0x00083D70) returning by value and builds its strings
// through the out-of-line StringBase<char> constructor at 0x00888BC0. The BFME
// declarations in game/GameEngine/Include (ascii_string.h, Common/Recorder.h,
// Common/INI/INI.h) are the ones whose codegen matches; that is the same
// header set game/GameEngine/Source/Common/CommandLine_parseMod.cpp builds its
// matched body against, and it is why this body is a TU of its own rather
// than a member of the Zero Hour-header Image.cpp.

#include <stdio.h>
#include <string.h>
#include "windows.h"				// WIN32_FIND_DATA, FindFirstFile, INVALID_HANDLE_VALUE, TRUE
#include "ascii_string.h"
#include "Common/Recorder.h"		// GlobalData, TheGlobalData, getPath_UserData
#include "Common/INI/INI.h"		// BFME's INI, whose loadDirectory takes five arguments

// Retail inlines StringBase<char>::str() as `m_data ? m_data->data : ""`, and
// its header is eight bytes wide, so the character data is at +8.
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int Int;

class ImageCollection
{
public:
	void load(Int textureSize);
};

// The class lives in Zero Hour's GameClient/Image.h; this body touches none of
// it (see the header comment), so the declaration above carries no members and
// claims no layout.
void ImageCollection::load( Int textureSize )
{
	char buffer[ _MAX_PATH ];
	INI ini;
	// first load in the user created mapped image files if we have them.
	WIN32_FIND_DATA findData;
	AsciiString userDataPath;
	if(TheGlobalData)
	{
		userDataPath.format("%sINI\\MappedImages\\*.ini",TheGlobalData->getPath_UserData().str());
		if(FindFirstFile(userDataPath.str(), &findData) != INVALID_HANDLE_VALUE)
		{
			userDataPath.format("%sINI\\MappedImages",TheGlobalData->getPath_UserData().str());
			ini.loadDirectory(userDataPath, TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
		}
	}

	// construct path to the mapped images folder of the correct texture size
	sprintf( buffer, "Data\\INI\\MappedImages\\TextureSize_%d", textureSize );

	// load all the ini files in that directory
	ini.loadDirectory( AsciiString( buffer ), TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
	ini.loadDirectory( "Data\\INI\\MappedImages\\HandCreated", TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
	ini.loadDirectory( "Data\\INI\\MappedImages\\AptImages", TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
	ini.loadDirectory( "Data\\INI\\MappedImages\\ParticleTextures", TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
	ini.loadDirectory( "Data\\INI\\MappedImages\\TransitionImages", TRUE, INI_LOAD_OVERWRITE, NULL, 0 );
}  // end load
