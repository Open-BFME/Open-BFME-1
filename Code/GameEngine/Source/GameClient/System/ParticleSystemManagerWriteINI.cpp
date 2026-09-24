// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
// Keep the disputed retail iterator helper under its address-derived name.
#define _M_skip_to_next Rva003442B0_skipToNext
#include <hash_map>
#undef _M_skip_to_next
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

#include "ascii_string.h"

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	AsciiString getName() const;
	void writeINI(File &file, unsigned int flags) const;
};

}

struct Q4Sort0034BFC0
{
 Q4Sort0034BFC0() {}
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
class CommandButton;
// Retail passes the iterator in ECX and stores the returned node from EAX.
// Both STLport iterators hold the current node and hashtable pointers.
typedef _STL::hash_map<AsciiString, const CommandButton *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > CommandButtonMap;


extern void j_000360f2();
extern void j_0003496e();
namespace _STL {
template<> __forceinline void __insertion_sort<int*, Q4Sort0034BFC0>(int* first, int* last, Q4Sort0034BFC0 cmp) {
 ((void (*)(int*,int*,Q4Sort0034BFC0))j_000360f2)(first,last,cmp);
}
template<> __forceinline void __unguarded_insertion_sort_aux<int*,int,Q4Sort0034BFC0>(int* first,int* last,int* value,Q4Sort0034BFC0 cmp) {
 ((void (*)(int*,int*,int*,Q4Sort0034BFC0))j_0003496e)(first,last,value,cmp);
}
}

struct Gen_t_00341960_m4pod { int a[1]; };

class ParticleSystemManager
{
private:
	unsigned char m_pad[0x9c];
	TemplateMap m_templateMap;

public:
	TemplateMap::iterator beginParticleSystemTemplate() { return m_templateMap.begin(); }
	TemplateMap::iterator endParticleSystemTemplate() { return m_templateMap.end(); }
	TemplateMap &templates()
	{
		return m_templateMap;
	}
};

extern ParticleSystemManager *TheParticleSystemManager;

// The FXParticleSystem.ini and .BAK literals identify the writer.
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

	_STL::vector<Gen_t_00341960_m4pod> templates;
	TemplateMap::iterator begin(TheParticleSystemManager->beginParticleSystemTemplate());
	TemplateMap::iterator end(TheParticleSystemManager->endParticleSystemTemplate());
	for (; begin != end; ++(*(CommandButtonMap::iterator *)&begin))
		templates.push_back(*(Gen_t_00341960_m4pod *)&(*begin).second);

	_STL::sort((int*)templates.begin(), (int*)templates.end(), Q4Sort0034BFC0());
	int *first = (int*)templates.begin();
	int *last = (int*)templates.end();
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
