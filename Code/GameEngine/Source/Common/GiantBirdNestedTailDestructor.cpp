// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: GiantBirdNestedTail owns a vector of 0xb8-byte records.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class GiantBirdNestedCoord3D
{
public:
	~GiantBirdNestedCoord3D();

private:
	float m_x;
	float m_y;
	float m_z;
};

class GiantBirdNestedRecord
{
private:
	unsigned char m_prefix[0x2c];
	GiantBirdNestedCoord3D m_spots[10];
	unsigned char m_between[0x0c];
	AsciiString m_name;
	unsigned char m_tail[4];
};

class GiantBirdNestedTail
{
public:
	~GiantBirdNestedTail();

private:
	_STL::vector<GiantBirdNestedRecord> m_records;
};

template class _STL::vector<GiantBirdNestedRecord>;

GiantBirdNestedTail::~GiantBirdNestedTail()
{
}
