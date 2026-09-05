// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// FileSystem::loadMusicFilesFromCD. ZH twin in FileSystem.cpp; retail
// 0x0069D0A0 walks TheCDManager drives and loadBigFilesFromDirectory(path, "Music.big").

#include "string_base.h"

class AsciiString
{
public:
	AsciiString()
	{
		m_data = 0;
	}

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
	}

private:
	char *m_data;
};

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
