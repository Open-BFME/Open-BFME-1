// ?rva00853610@INI@@QAEXVAsciiString@@W4INILoadType@@@Z
// partial score=0.68 date=2026-09-10
// Scratch-only reconstruction for the address-derived INI preload body at
// retail RVA 0x00853610.  This is deliberately outside Code/; it is used only
// by probe.py while the real source remains untouched until an exact result.
// cl: /O2 /GR- /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

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

class INILineBuffer
{
public:
	void rva009CC020(File *file);

	const char *getText(Int index) const;

	void *m_unknown0;
	void *m_unknown4;
	char *m_begin;
	char *m_end;
};

class BfmeSubDQB
{
public:
	void bfmeCallDQB(void *arg);
};

struct BfmeOutDQB
{
	int m_bfmeA;
	BfmeSubDQB m_bfmeSub;
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
	Gen_00852760 *m_bfmeTable;
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
	void rva00853610(AsciiString filename, INILoadType loadType);

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

void INI::rva00853610(AsciiString filename, INILoadType loadType)
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
	*(volatile File **)&m_file = 0;

	Int lineIndex = 0;
	if ((m_lines.m_end - m_lines.m_begin) & ~7)
	{
		do
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

				if (reinterpret_cast<const RvaStringBase<char> *>(&filename)->endsWith(
					"map.ini", 7))
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
				if (*hashText != 0)
				{
					do
					{
						shift = (*hashText + shift) & 0x1f;
						hash ^= (1u << shift);
						++hashText;
					}
					while (*hashText != 0);
				}

				BfmeOutDQB out;
				bfmeGoDQB(&out, reinterpret_cast<int *>(&hash), &firstToken);
				BfmeHashValue value((unsigned int)out.m_bfmeA,
					*(const BFMERetailAsciiString *)&out.m_bfmeSub);

				g_macroTable->resize(*g_macroCount + 1);
				Gen_00852760 *table =
					reinterpret_cast<Gen_00852760 *>(0x0130CE58);
				BfmeInsertResultF result = table->bfmeInsertUnique(&value);
				if (!result.m_bfmeInserted)
				{
					throw INIException(8,
						"%s:\nDuplicate MACRO names.\n%s.",
						filename.str(), name.str());
				}
			}

			++lineIndex;
		}
		while (lineIndex < (m_lines.m_end - m_lines.m_begin) / 8);
	}

	m_filename = filename;
	m_loadType = loadType;
}
