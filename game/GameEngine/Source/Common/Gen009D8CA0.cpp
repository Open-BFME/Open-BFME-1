// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the three-argument layout constructor at retail RVA 0x009D8CA0.
class Gen009D8CA0
{
public:
	Gen009D8CA0(int first, int second, int third);
	virtual void slot0();
private:
	int m_first;
	int m_third;
	int m_second;
	bool m_flag;
	unsigned char m_pad[3];
	int m_valueA;
	int m_valueB;
	int m_index;
};
Gen009D8CA0::Gen009D8CA0(int first, int second, int third) :
	m_first(first), m_third(third), m_second(second), m_flag(false),
	m_valueA(0), m_valueB(0), m_index(-1)
{
}
