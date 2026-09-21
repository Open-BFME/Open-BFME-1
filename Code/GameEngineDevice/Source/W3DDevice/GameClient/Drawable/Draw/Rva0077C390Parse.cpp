// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0077C390 is the BFME model-condition sub-block parser.  Its
// temporary is the 108-byte record consumed by the adjacent STLport vector
// body at 0x0077BFB0: the bone, offset and weighted model list come first,
// followed by the two 304-bit condition masks.

#include <bitset>

typedef int Int;

template <typename T>
class StringBase
{
public:
	struct Header
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}

	~StringBase();

private:
	StringBase() : m_data(0) {}
	Header *m_data;

	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString();

	bool isEmpty() const
	{
		return ((const StringBase<char> *)this)->isEmpty();
	}
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva0077C390Model
{
	AsciiString name;
	Int probability;
};

namespace _STL
{
template <typename T>
class allocator;

template <typename T, typename Allocator = allocator<T> >
class vector
{
public:
	vector() : m_start(0), m_finish(0), m_endOfStorage(0) {}
	~vector();
	void push_back(const T *value);

	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

template <int NUMBITS>
class BitFlags
{
public:
	void clear()
	{
		m_bits.reset();
	}

	void set(Int bitIndex)
	{
		m_bits._Unchecked_set(bitIndex);
	}

	void clearBit(Int bitIndex)
	{
		m_bits._Unchecked_reset(bitIndex);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> Rva0076A580ModelConditionFlags;

void parseModelConditionFlags(
	class INI *ini,
	Rva0076A580ModelConditionFlags *all,
	Rva0076A580ModelConditionFlags *positive);

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_message;
};

class Rva00770F40
{
public:
	AsciiString bone;
	Coord3D offset;
	_STL::vector<Rva0077C390Model> models;

	~Rva00770F40();
};

struct Rva0077BFB0Element : public Rva00770F40
{
	public:
	Rva0076A580ModelConditionFlags all;
	Rva0076A580ModelConditionFlags positive;
};

class Rva0077C390Owner
{
public:
	char m_prefix[8];
	_STL::vector<Rva0077BFB0Element> modelConditions;
};

class Rva0077C390
{
public:
	static void parse(INI *ini, void *instance, void *store,
		const void *userData);
};

// ?parse@Rva0077C390@@SAXPAVINI@@PAX1PBX@Z
void Rva0077C390::parse(INI *ini, void *instance, void *, const void *)
{
	if (instance == 0)
		return;

	Rva0077BFB0Element info;
	info.offset.x = 0;
	info.offset.y = 0;
	info.offset.z = 0;
	parseModelConditionFlags(ini, &info.all, &info.positive);
	ini->initFromINI(&info, (const FieldParse *)0x01124420);

	if (info.bone.isEmpty())
		throw INIException(3,
			"*** ASSET ERROR: you must specify then bone name");

	Rva0077C390Model *first = info.models.m_start;
	if (first == info.models.m_finish)
		throw INIException(3,
			"*** ASSET ERROR: you must specify at least one model name");
	Int totalProbability = 0;
	Int unassignedCount = 0;
	for (Rva0077C390Model *model = first; model != info.models.m_finish; ++model)
	{
		if (model->probability <= 0)
			++unassignedCount;
		else
			totalProbability += model->probability;
	}

	if (totalProbability > 100)
		throw INIException(3,
			"*** ASSET ERROR: combined probability may not be higher than 100 (it's %i)",
			totalProbability);

	if (totalProbability + unassignedCount > 100)
		throw INIException(3,
			"*** ASSET ERROR: can't auto-assign probabilities, specified probabilities must be %i or less",
			100 - unassignedCount);

	if (unassignedCount != 0)
	{
		Int remainder = 100 - totalProbability;
		Int share = remainder / unassignedCount;
		for (Rva0077C390Model *model = first; model != info.models.m_finish; ++model)
		{
			if (model->probability <= 0)
			{
				--unassignedCount;
				if (unassignedCount == 0)
					model->probability = remainder;
				else
				{
					model->probability = share;
					remainder -= share;
				}
				totalProbability += model->probability;
			}
		}
	}

	if (totalProbability > 100)
		throw INIException(3,
			"*** ASSET ERROR: combined probability must be 100 (it's %i)",
			totalProbability);

	((Rva0077C390Owner *)instance)->modelConditions.push_back(&info);
}
