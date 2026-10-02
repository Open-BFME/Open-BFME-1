// 25-byte forwarder with member and two arguments

class AsciiString;
struct BannerThingCounts;

class BannerThingCounter
{
public:
	void add(BannerThingCounts *counts, const AsciiString &name, int count);
};

class Rva0049AB20
{
public:
	void forward( int arg1, int arg2 );

	char            m_pad00[ 0x8 ];
	BannerThingCounter *m_subObject;
	BannerThingCounts  *m_param;
};

void Rva0049AB20::forward( int arg1, int arg2 )
{
	m_subObject->add(m_param, *(const AsciiString *)arg1, arg2);
}
