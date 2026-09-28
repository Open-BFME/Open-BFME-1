// ?prepFile@INI@@IAEXVAsciiString@@W4INILoadType@@@Z
// partial score=0.82 date=2026-09-27
// cl: /DNDEBUG /O2 /GR- /EHsc /MD /Iinputs/reference/shims/ini
// Reconstruction of INI::prepFile (GeneralsMD INI.h:389) at retail 0x00853610; BFME adds the #define MACRO pre-pass. Scratch shape for probe.py; the landed body belongs in game/GameEngine/Source/Common/INI/INI_stl.cpp (stlport TU: the body calls the _STL hashtable at 0x00852340/0x00852760 and StringBase).
#include "Common/INIException.h"

template <typename T> struct RvaStringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class RvaStringBase
{
	friend class AsciiString;

public:
	bool endsWith(const T *text, int length) const;
	void set(const RvaStringBase<T> &other);

private:
	RvaStringBase() : m_data(0) {}
	RvaStringBase(const T *text);
	RvaStringBase(const RvaStringBase<T> &other);
	~RvaStringBase();

	RvaStringInlineData<T> *m_data;
};

class AsciiString : private RvaStringBase<char>
{
	friend class RvaStringBase<char>;

public:
	AsciiString() : RvaStringBase<char>() {}
	AsciiString(const char *text) : RvaStringBase<char>(text) {}
	AsciiString(const AsciiString &other) : RvaStringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data != 0 ? m_data->m_text : "";
	}

	void set(const AsciiString &other)
	{
		RvaStringBase<char>::set(other);
	}

	AsciiString &operator=(const AsciiString &other)
	{
		RvaStringBase<char>::set(other);
		return *this;
	}
};

typedef int Int;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &other);
	~BFMERetailAsciiString();

	bool startsWith(const char *text, int length) const;
	bool endsWith(const char *text, int length) const;
	bool nextToken(BFMERetailAsciiString *out, const char *delimiters);

	const char *str() const
	{
		return m_data != 0 ? (const char *)m_data + 8 : "";
	}

	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

	void *m_data;
};

class File
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
};

extern FileSystem *TheFileSystem;

struct INILine
{
	const char *m_text;
	Int m_unknown4;
};

class INILineBuffer
{
public:
	void rva009CC020(File *file);

	const char *getText(Int index) const;

	void *m_unknown0;
	void *m_unknown4;
	INILine *m_begin;
	INILine *m_end;
};

struct BfmeOutDQB
{
	int m_bfmeA;
	BFMERetailAsciiString m_bfmeSub;
};

extern BfmeOutDQB *bfmeGoDQB(BfmeOutDQB *out, int *src, void *arg);

struct BfmeHashValue
{
	BfmeHashValue(unsigned int key, const BFMERetailAsciiString &value)
		: m_bfmeKey(key), m_bfmeSecond(value)
	{
	}

	~BfmeHashValue() {}

	unsigned int m_bfmeKey;
	BFMERetailAsciiString m_bfmeSecond;
};

class Gen_00852760;
struct BfmeHashNode;

struct BfmeInsertResultF
{
	BfmeHashNode *m_bfmeNode;
	unsigned int m_bfmePad;
	bool m_bfmeInserted;
};

class Gen_00852760
{
public:
	BfmeInsertResultF bfmeInsertUnique(const BfmeHashValue *value);
};

class Rva00852340Table
{
public:
	void resize(unsigned int count);
};

class INI
{
public:

protected:
	void prepFile(AsciiString filename, INILoadType loadType);

	File *m_file;
	AsciiString m_filename;
	INILoadType m_loadType;
	char m_padding[0x828];
	INILineBuffer m_lines;
};

static Rva00852340Table *const g_macroTable =
	reinterpret_cast<Rva00852340Table *>(0x0130CE58);
static unsigned int *const g_macroCount =
	reinterpret_cast<unsigned int *>(0x0130CE68);

void INI::prepFile(AsciiString filename, INILoadType loadType)
{
	if (m_file != 0)
	{
		throw INIException(6, "INI::load, cannot open file '%s', file already open\n",
			filename.str());
	}

	m_file = TheFileSystem->openFile(filename.str(), 1);
	if (m_file == 0)
	{
		throw INIException(7, "INI::load, cannot open file '%s'\n",
			filename.str());
	}

	m_lines.rva009CC020(m_file);
	m_file->close();
	m_file = 0;

	Int lineIndex = 0;
	for (; lineIndex < (m_lines.m_end - m_lines.m_begin); lineIndex++)
	{
		const char *rawLine = m_lines.getText(lineIndex);
		BFMERetailAsciiString line(rawLine);

		if (line.startsWith("#define", 7))
		{
			*(char *)rawLine = 0;

			BFMERetailAsciiString firstToken;
			line.nextToken(&firstToken, 0);
			BFMERetailAsciiString name;
			line.nextToken(&name, 0);

			if (filename.endsWith("map.ini", 7))
			{
				throw INIException(8,
					"%s:\nMACROs not allowed in map.ini.\n%s.",
					filename.str(), name.str());
			}

			const char *nameText = name.str();
			while (*nameText != 0)
			{
				if (*nameText > 'a' && *nameText < 'z')
				{
					throw INIException(8,
						"%s:\nMACRO names must use UPPERCASE letters.\n%s.",
						filename.str(), name.str());
				}
				++nameText;
			}

			line.nextToken(&firstToken, 0);
			if (firstToken.isEmpty())
			{
				throw INIException(8,
					"%s:\nError parsing MACRO.\n%s has no value",
					filename.str(), name.str());
			}

			unsigned int hash = 0;
			unsigned int shift = 0;
			const char *hashText = name.str();
			while (*hashText != 0)
			{
				shift = (*hashText + shift) & 0x1f;
				hash ^= (1u << shift);
				++hashText;
			}

			bool inserted;
			{
				BfmeOutDQB out;
				bfmeGoDQB(&out, reinterpret_cast<int *>(&hash), &firstToken);
				BfmeHashValue value((unsigned int)out.m_bfmeA,
					*(const BFMERetailAsciiString *)&out.m_bfmeSub);
				g_macroTable->resize(*g_macroCount + 1);
				inserted = reinterpret_cast<Gen_00852760 *>(0x0130CE58)
					->bfmeInsertUnique(&value).m_bfmeInserted;
			}
			if (!inserted)
			{
				throw INIException(8,
					"%s:\nDuplicate MACRO names.\n%s.",
					filename.str(), name.str());
			}
		}
	}

	m_filename = filename;
	m_loadType = loadType;
}
