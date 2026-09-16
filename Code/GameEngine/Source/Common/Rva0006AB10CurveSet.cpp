// ?set@Rva0006AB10Curve@@QAEXMMHH@Z
// Rva0006AB10Curve::set inserts a function-curve point into the sorted vector.
// The existing Rva0006AB90FunctionCurve callers and the 0x00030053 insert thunk
// establish this method's identity and argument types.
// cl: /DNDEBUG /MD /O2 /EHsc-

struct Rva0006AA90Element
{
	float m_key;
	struct Value
	{
		Value() {}

		Value(float real, int inTangent, int outTangent)
			: m_real(real), m_inTangent(inTangent), m_outTangent(outTangent) {}

		float m_real;
		int m_inTangent;
		int m_outTangent;
	} m_value;

	Rva0006AA90Element(float key, const volatile Value &value)
		: m_key(key)
	{
		m_value.m_real = value.m_real;
		m_value.m_inTangent = value.m_inTangent;
		m_value.m_outTangent = value.m_outTangent;
	}
};

struct Rva0006AA90InsertResult
{
	Rva0006AA90Element *m_first;
	volatile bool m_second;
};

class Rva0006AA90Vector
{
public:
	Rva0006AA90InsertResult insertUnique(const Rva0006AA90Element &value);
	Rva0006AA90InsertResult *insertUnique(volatile Rva0006AA90InsertResult *result,
		const Rva0006AA90Element &value);

	Rva0006AA90Element *m_start;
	Rva0006AA90Element *m_finish;
	Rva0006AA90Element *m_end;
	unsigned char m_padding;
	unsigned char m_flag;
	unsigned char m_reserved[2];
};

#pragma comment(linker, "/alternatename:?insertUnique@Rva0006AA90Vector@@QAEPAURva0006AA90InsertResult@@PCU2@ABURva0006AA90Element@@@Z=?j_00030053@@YAXXZ")

class Rva0006AB10Curve
{
public:
	void set(float time, float value, int inTangent, int outTangent);

	int m_field0;
	int m_field4;
	Rva0006AA90Vector m_points;
	Rva0006AA90Element *m_current;
};

struct Rva0006AB10SetLocals
{
	Rva0006AA90InsertResult m_result;
	volatile Rva0006AA90Element::Value m_values;
	Rva0006AA90Element m_point;

	Rva0006AB10SetLocals(float time, float value, int inTangent, int outTangent)
		: m_values(value, inTangent, outTangent), m_point(time, m_values) {}
};

void Rva0006AB10Curve::set(float time, float value, int inTangent,
	int outTangent)
{
	Rva0006AB10SetLocals locals(time, value, inTangent, outTangent);
	Rva0006AA90InsertResult *inserted = m_points.insertUnique(
		&locals.m_result, locals.m_point);
	inserted->m_second;
	m_current = m_points.m_finish;
}
