// ?parseMod@@YAHQAPADH@Z
// partial score=0.82 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

extern "C" char *(__cdecl *__imp__strchr)(const char *, int);

struct Rva000624F0Stat
{
	unsigned char m_head[6];
	unsigned short st_mode;
	unsigned char m_tail[0x1c];
};

struct Rva000624F0StatHolder
{
	unsigned char m_pad[4];
	Rva000624F0Stat m_stat;
};

extern "C" int __cdecl _stat(const char *, Rva000624F0Stat *);

template <class T> class StringBase
{
protected:
	T *m_data;
	void concat(const T *text, int length);
};

class BFMERetailAsciiString : public StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &text);
	~BFMERetailAsciiString(void);

	const char *str(void) const
	{
		return m_data != 0 ? m_data + 8 : (const char *)0x0107388b;
	}

	void format(BFMERetailAsciiString format, ...);
	void set(const BFMERetailAsciiString &text);
	bool startsWith(const char *text) const;
	bool endsWith(const char *text) const;
	__forceinline void concat(char text)
	{
		volatile char separator[4];
		separator[0] = text;
		StringBase<char>::concat((const char *)separator, 1);
	}
};

class GlobalData
{
public:
	BFMERetailAsciiString getPath_UserData(void) const;

private:
	unsigned char m_pad0[0xdc0];
public:
	BFMERetailAsciiString m_modDir;
	BFMERetailAsciiString m_modBIG;
};

extern GlobalData *TheWritableGlobalData;
extern GlobalData *TheGlobalData;

class FileSystem
{
public:
	bool doesFileExist(const char *path) const;
};

extern FileSystem *TheLocalFileSystem;

extern bool byte_134CB4C;

int __cdecl parseMod(char *args[], int num)
{
	byte_134CB4C = 1;
	if (TheWritableGlobalData != 0 && num > 1)
	{
		Rva000624F0StatHolder statHolder;
		BFMERetailAsciiString modPath(args[1]);
		if ((*__imp__strchr)(modPath.str(), ':') || modPath.startsWith("/") || modPath.startsWith("\\"))
		{
		}
		else
		{
			char *argument = args[1];
			modPath.format("%s%s", TheGlobalData->getPath_UserData().str(), argument);
		}

		if (!TheLocalFileSystem->doesFileExist(modPath.str()))
			return 2;

		if (_stat(modPath.str(), &statHolder.m_stat) != 0)
			return 2;

		if (statHolder.m_stat.st_mode & 0x4000)
		{
			if (!modPath.endsWith("\\") && !modPath.endsWith("/"))
				modPath.concat('\\');
			TheWritableGlobalData->m_modDir.set(modPath);
		}
		else
		{
			TheWritableGlobalData->m_modBIG.set(modPath);
		}
		return 2;
	}
	return 1;
}
