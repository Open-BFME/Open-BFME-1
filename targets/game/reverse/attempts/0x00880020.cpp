// ?parseAdditionalGeometry@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.7679 date=2026-10-31
// cl: /O2 /G7 /DNDEBUG /MD /EHs-c-
// BANK (s514 a1): 168/168 B, 39 diffs, all at +0x07..+0x40: retail saves ESI/EDI after the two INI calls (interleaved with the fst stores), ours at entry. /G7 is what fixes the size and every byte from +0x41 (cmp ecx,[esi+8] memory operand, store order); /G6 gives 170 B/115 diffs. A real branch between getNextToken and scanIndexList (or after it) moves the saves exactly like retail, so retail had a block boundary there; code-free candidates tried and inert: empty if, __assume, switch default, do-while(0), for+break, goto label, inline/forceinline INI member wrapper, inline addShape, placement-new buffer, EH on with throw() callees, volatile ini param (BFME 2 donor), volatile/double default load, dimension loop, flags /Ob0-2 /Ox /Ow /GS /Og-Oi-Ot-Oy.
#include <new>

extern float g_bfmeDefaultBU;

class INI
{
public:
	static int scanIndexList(const char *token, const char *const *values);
	const char *getNextToken(const char *seps = 0);
};

template <typename T>
class StringBase
{
private:
	void releaseBuffer();
	T *m_data;
	friend class AsciiString;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString() { releaseBuffer(); }
};

struct BfmeFalseBE
{
};

struct BfmeElemBE
{
	char m_data[36];
	void copyFrom(const BfmeElemBE &src);
};

class BfmeVecBE
{
public:
	void overflow(BfmeElemBE *pos, const BfmeElemBE &value,
		const BfmeFalseBE &, unsigned fill, bool atEnd);
	void append(const BfmeElemBE &value, const BfmeFalseBE &tag)
	{
		if (_M_finish != _M_end_of_storage)
		{
			if (_M_finish)
				_M_finish->copyFrom(value);
			++_M_finish;
		}
		else
			overflow(_M_finish, value, tag, 1, true);
	}

	BfmeElemBE *_M_start;
	BfmeElemBE *_M_finish;
	BfmeElemBE *_M_end_of_storage;
};

struct GeometryShapeDimensions
{
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	GeometryShapeDimensions()
	{
		float value = g_bfmeDefaultBU;
		m_height = value;
		m_majorRadius = value;
		m_minorRadius = value;
	}
};

struct GeometryShapeRecord
{
	int m_type;
	GeometryShapeDimensions m_dimensions;
	float m_x, m_y, m_z;
	AsciiString m_name;
	unsigned char m_enabled;
	GeometryShapeRecord(int type) : m_type(type), m_dimensions(), m_x(0), m_y(0), m_z(0), m_enabled(1) {}
};

extern const char *const GeometryNames[];

class GeometryInfo
{
public:
	static void parseAdditionalGeometry(INI *ini, void *instance, void *store, const void *userData);

private:
	void calcBoundingStuff();
	char m_pad[0x2c];
	BfmeVecBE m_shapes;
};

void GeometryInfo::parseAdditionalGeometry(INI *ini, void *, void *store, const void *)
{
	GeometryShapeRecord shape(INI::scanIndexList(ini->getNextToken(), GeometryNames));
	GeometryInfo *geometry = static_cast<GeometryInfo *>(store);
	BfmeFalseBE &tag = *new (&ini) BfmeFalseBE;
	geometry->m_shapes.append(*reinterpret_cast<const BfmeElemBE *>(&shape), tag);
	geometry->calcBoundingStuff();
}
