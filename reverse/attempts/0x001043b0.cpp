// ?writeDict@DataChunkOutput@@QAEXABVDict@@@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char Byte;
typedef bool Bool;
typedef float Real;
typedef unsigned short WideChar;

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, FILE *);

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

template <typename Char>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<Char> &source);
	void set(const StringBase<Char> &source);
	void releaseBuffer() throw();

protected:
	BfmeStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
		return *this;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &source) : StringBase<WideChar>(source) {}
	~UnicodeString();
};

enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };

class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL = 0,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	Int getPairCount() const;
	NameKeyType getNthKey(Int n) const;
	DataType getNthType(Int n) const;
	Bool getNthBool(Int n) const;
	Int getNthInt(Int n) const;
	Real getNthReal(Int n) const;
	AsciiString getNthAsciiString(Int n) const;
	UnicodeString getNthUnicodeString(Int n) const;

private:
	struct DictPair;
	struct DictPairData;
	DictPairData *m_data;

	enum DictPairKeyType { DICTPAIRKEY_ILLEGAL = 0 };
	struct DictPair
	{
	private:
		DictPairKeyType m_key;
		void *m_value;
	public:
		DataType getType() const { return (DataType)(((UnsignedInt)m_key) & 0xff); }
		NameKeyType getName() const { return (NameKeyType)(((UnsignedInt)m_key) >> 8); }
	};
	struct DictPairData
	{
		UnsignedShort m_refCount;
		UnsignedShort m_numPairsAllocated;
		UnsignedShort m_numPairsUsed;
		DictPair *peek() { return (DictPair *)(this + 1); }
	};
};

inline Int Dict::getPairCount() const
{
	return m_data ? m_data->m_numPairsUsed : 0;
}

inline NameKeyType Dict::getNthKey(Int n) const
{
	if (!m_data || n < 0 || n >= m_data->m_numPairsUsed)
		return NAMEKEY_INVALID;
	return m_data->peek()[n].getName();
}

inline Dict::DataType Dict::getNthType(Int n) const
{
	if (!m_data || n < 0 || n >= m_data->m_numPairsUsed)
		return DICT_NONE;
	return m_data->peek()[n].getType();
}

class Mapping
{
public:
	virtual ~Mapping();
	Mapping *next;
	AsciiString name;
	UnsignedInt id;
};

class DataChunkTableOfContents
{
public:
	DataChunkTableOfContents();
	~DataChunkTableOfContents();
	Mapping *findMapping(const AsciiString &name);
	UnsignedInt allocateID(const AsciiString &name);

private:
	Mapping *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

class OutputStream;
class OutputChunk
{
public:
	virtual ~OutputChunk();
	OutputChunk *next;
	UnsignedInt id;
	Int filepos;
};

class DataChunkOutput
{
public:
	DataChunkOutput(OutputStream *pOut);
	~DataChunkOutput();
	void writeReal(Real value);
	void writeInt(Int value);
	void writeByte(Byte value);
	void writeAsciiString(const AsciiString &value);
	void writeUnicodeString(UnicodeString value);
	void writeDict(const Dict &dict);

protected:
	OutputStream *m_pOut;
	FILE *m_tmp_file;
	DataChunkTableOfContents m_contents;
	OutputChunk *m_chunkStack;
};

void DataChunkOutput::writeReal(Real value)
{
	::fwrite((const void *)&value, sizeof(Real), 1, m_tmp_file);
}

void DataChunkOutput::writeInt(Int value)
{
	::fwrite((const void *)&value, sizeof(Int), 1, m_tmp_file);
}

void DataChunkOutput::writeByte(Byte value)
{
	::fwrite((const void *)&value, sizeof(Byte), 1, m_tmp_file);
}

void DataChunkOutput::writeDict(const Dict &d)
{
	UnsignedShort len = d.getPairCount();
	::fwrite((const char *)&len, sizeof(UnsignedShort), 1, m_tmp_file);
	for (int i = 0; i < len; i++)
	{
		NameKeyType k = d.getNthKey(i);
		AsciiString kname = TheNameKeyGenerator->keyToName(k);

		Int keyAndType = m_contents.allocateID(kname);

		keyAndType <<= 8;
		Dict::DataType t = d.getNthType(i);
		keyAndType |= (t & 0xff);
		writeInt(keyAndType);

		switch (t)
		{
			case Dict::DICT_BOOL:
				writeByte(d.getNthBool(i) ? 1 : 0);
				break;
			case Dict::DICT_INT:
				writeInt(d.getNthInt(i));
				break;
			case Dict::DICT_REAL:
				writeReal(d.getNthReal(i));
				break;
			case Dict::DICT_ASCIISTRING:
				writeAsciiString(d.getNthAsciiString(i));
				break;
			case Dict::DICT_UNICODESTRING:
				writeUnicodeString(d.getNthUnicodeString(i));
				break;
			default:
				break;
		}
	}
}

UnsignedInt DataChunkTableOfContents::allocateID(const AsciiString &name)
{
	Mapping *m = findMapping(name);
	if (m)
		return m->id;
	m = new Mapping;
	m->id = m_nextID++;
	m->name = name;
	m->next = m_list;
	m_list = m;
	m_listLength++;
	return m->id;
}
