// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include <string.h>
#include <vector>

extern const char g_bfmeEmptyAscii[];

template <typename T> class StringBase
{
public:
	void clear();
	void set(const StringBase<T> &other);

private:
	friend class AsciiString;
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}
};

struct Rva00438670StringInfo
{
	AsciiString *label;
	void *info;
};

typedef _STL::vector<AsciiString> Rva00438670AsciiStringVector;

class GameTextManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual Rva00438670AsciiStringVector &getStringsWithLabelPrefix(AsciiString label);

private:
	unsigned char m_interfaceAndSubsystem[4];
	int m_textCount;
	unsigned char m_fileBuffers[0x7800];
	void *m_stringInfo;
	Rva00438670StringInfo *m_stringLUT;
	unsigned char m_initializedAndFlags[4];
	void *m_noStringList;
	int m_useStringFile;
	int m_language;
	unsigned char m_failed[4];
	void *m_mapStringInfo;
	Rva00438670StringInfo *m_mapStringLUT;
	int m_mapTextCount;
	Rva00438670AsciiStringVector m_asciiStringVec;
};

// ?getStringsWithLabelPrefix@GameTextManager@@UAEAAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z
Rva00438670AsciiStringVector &
GameTextManager::getStringsWithLabelPrefix(AsciiString label)
{
	m_asciiStringVec.clear();
	if (m_stringLUT)
	{
		for (int i = 0; i < m_textCount; ++i)
		{
			if (strstr(m_stringLUT[i].label->str(), label.str()) ==
				m_stringLUT[i].label->str())
			{
				m_asciiStringVec.push_back(*m_stringLUT[i].label);
			}
		}
	}
	if (m_mapStringLUT)
	{
		for (int i = 0; i < m_mapTextCount; ++i)
		{
			if (strstr(m_mapStringLUT[i].label->str(), label.str()) ==
				m_mapStringLUT[i].label->str())
			{
				m_asciiStringVec.push_back(*m_mapStringLUT[i].label);
			}
		}
	}
	return m_asciiStringVec;
}
