// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
// FileSystem::loadMusicFilesFromCD. ZH twin in FileSystem.cpp; retail
// 0x0069D0A0 walks TheCDManager drives and loadBigFilesFromDirectory(path, "Music.big").

#include "string_base.h"

#include "ascii_string.h"

class CDDriveInterface
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual AsciiString getPath() = 0;
};

class CDManagerInterface
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual int driveCount() = 0;
	virtual CDDriveInterface *getDrive(int index) = 0;
};

class ArchiveFileSystem
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual bool loadBigFilesFromDirectory(AsciiString dir, AsciiString fileMask, bool overwrite) = 0;
};

extern CDManagerInterface *TheCDManager;
extern ArchiveFileSystem *TheArchiveFileSystem;

class FileSystem
{
public:
	void loadMusicFilesFromCD();
};

void FileSystem::loadMusicFilesFromCD()
{
	if (!TheCDManager)
		return;

	AsciiString cdRoot;
	int dc = TheCDManager->driveCount();
	for (int i = 0; i < dc; ++i)
	{
		CDDriveInterface *cdi = TheCDManager->getDrive(i);
		if (!cdi)
			continue;

		cdRoot.set(cdi->getPath());
		if (TheArchiveFileSystem->loadBigFilesFromDirectory(cdRoot, "Music.big", 0))
			break;
	}
}
