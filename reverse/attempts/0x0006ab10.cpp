// ?set@Rva0006AB10Curve@@QAEXMMHH@Z
// partial score=0.95 date=2026-09-11
// cl: /DNDEBUG /MD /O2 /EHsc-
// Retail 0x0006AB10 inserts a function-curve point into the sorted vector.

struct Rva0006AA90Element
{
	float m_key;
	struct Value
	{
		float m_real;
		int m_inTangent;
		int m_outTangent;
	} m_value;
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
};

void Rva0006AB10Curve::set(float time, float value, int inTangent,
	int outTangent)
{
	Rva0006AB10SetLocals locals;
	locals.m_values.m_real = value;
	locals.m_values.m_inTangent = inTangent;
	locals.m_values.m_outTangent = outTangent;
	locals.m_point.m_value.m_real = locals.m_values.m_real;
	locals.m_point.m_key = time;
	locals.m_point.m_value.m_inTangent = locals.m_values.m_inTangent;
	locals.m_point.m_value.m_outTangent = locals.m_values.m_outTangent;
	Rva0006AA90InsertResult *inserted = m_points.insertUnique(
		&locals.m_result, locals.m_point);
	inserted->m_second;
	m_current = m_points.m_finish;
}
