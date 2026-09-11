// cl: /EHsc
// Open-BFME: GeometryRecord destructor, retail 0x000FD020.
//
// GeometryRecord is the 0x10-byte element of GeometryInfo's record vector.
// Its AsciiString member begins at +0x0C, so normal C++ destruction adjusts
// the receiver to that member and tail-calls the shared string release path.

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
	~GeometryRecord();
};

GeometryRecord::~GeometryRecord()
{
}
