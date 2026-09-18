// ?d_0034c0d0@@YAXXZ
// partial score=0.92 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>
#include <stdio.h>
#include <vector>

class File
{
public:
	virtual ~File();
	virtual bool open(const char *, int = 0);
	virtual void close();
	virtual int read(void *, int);
	virtual int write(const void *, int);
	virtual int seek(int, int);
	virtual void nextLine(char *, int);
	virtual bool scanInt(int &);
	virtual bool scanReal(float &);
	virtual bool scanString(void *);
	virtual bool print(const char *, ...);
	virtual int size();
	virtual int position();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
};

extern FileSystem *TheFileSystem;

class AsciiString;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	AsciiString getName() const;
	void writeINI(File &file, unsigned int flags) const;
};

}

class AsciiString
{
public:
	int compareNoCase(const AsciiString &other) const;
};

struct Q4Sort0034BFC0
{
	bool operator()(int left, int right) const;
};

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};
}

typedef _STL::hash_map<AsciiString, FXParticleSystem::ParticleSystemTemplate *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > TemplateMap;

class ParticleSystemManager
{
private:
	unsigned char m_pad[0x9c];
	TemplateMap m_templateMap;

public:
	TemplateMap &templates()
	{
		return m_templateMap;
	}
};

extern ParticleSystemManager *TheParticleSystemManager;

__declspec(noinline) void _writeOutINI()
{
	const int maxFileLength = 128;
	char buff[maxFileLength];
	File *saveFile = 0;
	int i = 0;

	do
	{
		if (saveFile)
		{
			saveFile->close();
			saveFile = 0;
		}
		sprintf(buff, "%s%d.%s", "Data\\INI\\FXParticleSystem", i, "BAK");
		saveFile = TheFileSystem->openFile(buff, 0x21);
		++i;
	} while (saveFile);

	saveFile = TheFileSystem->openFile(buff, 0x22);
	if (!saveFile)
		return;

	File *oldINI = TheFileSystem->openFile(
		"Data\\INI\\FXParticleSystem.ini", 0x21);
	if (oldINI)
	{
		char singleChar;
		while (oldINI->position() != oldINI->size())
		{
			oldINI->read(&singleChar, 1);
			saveFile->write(&singleChar, 1);
		}
		oldINI->close();
		oldINI = 0;
		saveFile->close();
		saveFile = 0;
	}

	File *newINI = TheFileSystem->openFile(
		"Data\\INI\\FXParticleSystem.ini", 0x22);
	if (!newINI)
		return;

	TemplateMap::iterator begin(TheParticleSystemManager->templates().begin());
	TemplateMap::iterator end(TheParticleSystemManager->templates().end());
	_STL::vector<int> templates;
	for (; begin != end; ++begin)
		templates.push_back(*(int *)&(*begin).second);

	_STL::sort(templates.begin(), templates.end(), Q4Sort0034BFC0());
	int *first = templates.begin();
	int *last = templates.end();
	if (first != last)
	{
		((FXParticleSystem::ParticleSystemTemplate *)*first)->writeINI(*newINI, 0);
		for (int *it = first + 1;
			it != last; ++it)
		{
			newINI->write("\n", 1);
			((FXParticleSystem::ParticleSystemTemplate *)*it)->writeINI(*newINI, 0);
		}
	}

	newINI->close();
}
