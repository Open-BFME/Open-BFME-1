// cl: /O2 /EHsc
// Open-BFME5: virtual destructor of the 0x003B6680 class, retail 0x003B16B0
// 325 bytes. Installs vtable 0x010EC850 then destroys members +CC down to +4.
// Layout is the assignment sibling at 0x003B6680.

class BFMERetailAsciiString
{
	void releaseBuffer();
	void *m_data;

public:
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class AsciiString
{
private:
	void *m_data;
};

struct Gen003A99D0;
struct Gen003A9A90;
struct Gen003A9B60;
struct Gen003A9C30;
struct Gen003A9CF0;
struct Gen003A9DC0;
struct Gen003A9E90;
struct Gen003AA010;
struct Gen_t_003ab1b0_p12cd;
struct Gen003AA0D0;
struct Gen003AA1A0;
struct Gen003AA300;
struct Gen003AA3C0;
struct Gen_t_003ab0f0_p16cd;
struct Gen_t_003ab360_p12cd;

namespace _STL
{
struct Rva003B20C0Element;

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	~vector();
	vector &operator=(const vector &);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva003B6680
{
public:
	virtual ~Rva003B6680();

private:
	BFMERetailAsciiString m04;
	_STL::vector<Gen003A99D0> m08;
	_STL::vector<Gen003A9A90> m14;
	_STL::vector<Gen003A9B60> m20;
	_STL::vector<Gen003A9C30> m2c;
	_STL::vector<AsciiString> m38;
	_STL::vector<AsciiString> m44;
	BFMERetailAsciiString m50;
	_STL::vector<Gen003A9CF0> m54;
	_STL::vector<Gen003A9DC0> m60;
	_STL::vector<Gen003A9E90> m6c;
	_STL::vector<Gen003AA010> m78;
	_STL::vector<Gen003AA0D0> m84;
	_STL::vector<Gen003AA1A0> m90;
	_STL::vector<Gen003AA300> m9c;
	_STL::vector<Gen003AA3C0> ma8;
	_STL::vector<Gen_t_003ab0f0_p16cd> mb4;
	_STL::vector<Gen_t_003ab1b0_p12cd> mc0;
	_STL::vector<Gen_t_003ab360_p12cd> mcc;
	bool md8;
};

Rva003B6680::~Rva003B6680()
{
}
