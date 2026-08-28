// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// IAT form of sprintf: call dword ptr [__imp__sprintf]
extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);
static inline int do_sprintf(char *b, const char *f, const char *a, const char *c)
{
	return (*__imp__sprintf)(b, f, a, c);
}

// The two names were swapped here, which is what put
// ?TheLocalFileSystem@@ at two bases in the DIR32 consistency check: this file
// called 0x0134CC50 TheLocalFileSystem while FileSystem::createDirectory and
// Win32BIGFile::getFileInfo call 0x0134D060 that. 0x0134CC50 is the archive
// system -- FileSystem::openFile reaches it through vtable slot 5 and the local
// one through slot 2, so they are different interfaces.
//
// The slot layouts stay attached to their call sites, because those are what the
// emitted offsets come from; only the names move. Retail checks the archive
// first and the local second, which is also now what the code reads like.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchiveFileSystem {
public:
	virtual ~ArchiveFileSystem() {}
	virtual void A1() = 0;
	virtual void A2() = 0;
	virtual void A3() = 0;
	virtual void A4() = 0;
	virtual void A5() = 0;
	virtual void A6() = 0;
	virtual void A7() = 0;
	// slot 8 = +0x20
	virtual bool doesFileExist(const char *filename) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem {
public:
	virtual ~LocalFileSystem() {}
	virtual void L1() = 0;
	virtual void L2() = 0;
	virtual void L3() = 0;
	// slot 4 = +0x10
	virtual bool doesFileExist(const char *filename) const = 0;
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern LocalFileSystem *TheLocalFileSystem;
// retail global path prefix used by sprintf("%s\\%s", prefix, filename)
extern char byte_134CA48[];

class FileSystem {
public:
	bool doesFileExist(const char *filename) const;
};

// ?doesFileExist@FileSystem@@QBE_NPBD@Z
bool FileSystem::doesFileExist(const char *filename) const
{
	char buf[0x200];
	do_sprintf(buf, "%s\\%s", byte_134CA48, filename);
	if (TheArchiveFileSystem->doesFileExist(buf))
		return true;
	if (TheArchiveFileSystem->doesFileExist(filename))
		return true;
	if (TheLocalFileSystem->doesFileExist(buf))
		return true;
	if (TheLocalFileSystem->doesFileExist(filename))
		return true;
	return false;
}
