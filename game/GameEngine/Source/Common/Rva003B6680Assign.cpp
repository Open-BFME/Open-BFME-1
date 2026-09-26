// cl: /O2
// Open-BFME5: memberwise assignment at retail 0x003B6680, 297 bytes.
// vptr at +0, UnicodeString::set at +4 and +50, then 17 twelve-byte members
// whose operator= ILTs land on already-matched vector assigns, then a bool
// at +D8. +60 is vector<Rva003B20C0Element> (0x003B6180, 36-byte virtual
// dtor). That callee must be in the ledger before this row can resolve.
// names follow the ICF-owner already claimed at each ILT target; they are
// not a claim that this class is W3DModelDraw or ThingTemplate.

class UnicodeString
{
public:
	void set(const UnicodeString &other);
	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

private:
	void *m_data;
};

class AsciiString
{
private:
	void *m_data;
};

namespace ModelConditionInfo { struct HideShowSubObjInfo; }
struct Gen_t_003b5310_p40cd;
struct Gen_t_003b5480_p48cd;
struct Gen_t_003b55d0_p32cd;
struct Gen_t_003b56f0_p12cd;
struct Gen_t_003b4920_p32cd;
struct Gen_t_003b4a40_p16cd;
struct Gen_t_003b4b60_p16cd;
struct Gen_t_003b5c60_p12cd;
class Open2Elem3B5860;
class Open2Elem3B59D0;
class W3DAnimationInfo;

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec;
};

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
	Rva003B6680 &operator=(const Rva003B6680 &other);

private:
	UnicodeString m04;
	_STL::vector<ModelConditionInfo::HideShowSubObjInfo> m08;
	_STL::vector<Gen_t_003b5310_p40cd> m14;
	_STL::vector<Gen_t_003b5480_p48cd> m20;
	_STL::vector<Gen_t_003b55d0_p32cd> m2c;
	_STL::vector<AsciiString> m38;
	_STL::vector<AsciiString> m44;
	UnicodeString m50;
	_STL::vector<Gen_t_003b56f0_p12cd> m54;
	_STL::vector<_STL::Rva003B20C0Element> m60;
	_STL::vector<Open2Elem3B5860> m6c;
	_STL::vector<Gen_t_003b4920_p32cd> m78;
	_STL::vector<ProductionPrerequisite> m84;
	_STL::vector<Open2Elem3B59D0> m90;
	_STL::vector<Gen_t_003b4a40_p16cd> m9c;
	_STL::vector<Gen_t_003b4b60_p16cd> ma8;
	_STL::vector<W3DAnimationInfo> mb4;
	_STL::vector<ProductionPrerequisite::PrereqUnitRec> mc0;
	_STL::vector<Gen_t_003b5c60_p12cd> mcc;
	bool md8;
};

Rva003B6680 &Rva003B6680::operator=(const Rva003B6680 &other)
{
	m04 = other.m04;
	m08 = other.m08;
	m14 = other.m14;
	m20 = other.m20;
	m2c = other.m2c;
	m38 = other.m38;
	m44 = other.m44;
	m50 = other.m50;
	m54 = other.m54;
	m60 = other.m60;
	m6c = other.m6c;
	m78 = other.m78;
	m84 = other.m84;
	m90 = other.m90;
	m9c = other.m9c;
	ma8 = other.ma8;
	mb4 = other.mb4;
	mc0 = other.mc0;
	mcc = other.mcc;
	md8 = other.md8;
	return *this;
}
