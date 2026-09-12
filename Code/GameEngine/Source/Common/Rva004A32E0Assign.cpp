// cl: /O2 /Ob0

// Raw twelve-byte prefix and canonical StringBase/STLport views for retail assignment
// 0x004A32E0.  The body has a thiscall source reference and returns *this;
// its prefix, BfmeNarrowString, and STLport vector calls are all direct retail
// helper routes.  No class owner is asserted beyond the recovered layout.

// Only the twelve-byte prefix and no-op assignment call are established.
struct Rva004A32E0Prefix { unsigned char storage[12]; };
class Rva004A32E0CallReceiver {};
extern void j_00048725();
extern void j_0000efde();

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &);

private:
	void *m_data;
};

typedef StringBase<char> BfmeNarrowString;

class AsciiString
{
public:
    AsciiString(const AsciiString &);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &);
private:
	StringBase<char> m_data;
};

struct Gen_t_000bc4b0_p4pod
{
	int m_value;
};

struct S4Poly000BC2E0
{
    S4Poly000BC2E0(const S4Poly000BC2E0 &);
    S4Poly000BC2E0 &operator=(const S4Poly000BC2E0 &);
	int m_storage[27];
	virtual ~S4Poly000BC2E0();
};

struct SixWords
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

struct TenWords
{
	int m_words[10];
};


// The target's +0x138 member is only proven to be a 12-byte vector-shaped
// slot. Keep its owner neutral and call the existing ILT with the observed
// receiver/source ABI, without declaring a gameplay pointee type.
struct RvaVector12
{
	void *m_first;
	void *m_last;
	void *m_end;
};

// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// These three operator bodies already have retail owners. Keep the vendored
// container types and call those specializations without re-emitting a second
// allocator/copy/destructor family in this translation unit.
namespace _STL {
template <> vector<AsciiString> &vector<AsciiString>::operator=(const vector<AsciiString> &);
template <> vector<Gen_t_000bc4b0_p4pod> &vector<Gen_t_000bc4b0_p4pod>::operator=(const vector<Gen_t_000bc4b0_p4pod> &);
template <> vector<S4Poly000BC2E0> &vector<S4Poly000BC2E0>::operator=(const vector<S4Poly000BC2E0> &);
}


class Rva004A32E0Record
{
	Rva004A32E0Prefix m_prefix;
	BfmeNarrowString m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	_STL::vector<AsciiString> m_28;
	int m_34;
	int m_38;
	BfmeNarrowString m_3C;
	BfmeNarrowString m_40;
	_STL::vector<AsciiString> m_44;
	_STL::vector<AsciiString> m_50;
	BfmeNarrowString m_5C;
	BfmeNarrowString m_60;
	BfmeNarrowString m_64;
	BfmeNarrowString m_68;
	int m_6C;
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
	int m_80;
	_STL::vector<Gen_t_000bc4b0_p4pod> m_84;
	int m_90;
	_STL::vector<AsciiString> m_94;
	int m_A0;
	int m_A4;
	_STL::vector<S4Poly000BC2E0> m_A8;
	_STL::vector<S4Poly000BC2E0> m_B4;
	_STL::vector<S4Poly000BC2E0> m_C0;
	_STL::vector<S4Poly000BC2E0> m_CC;
	_STL::vector<S4Poly000BC2E0> m_D8;
	_STL::vector<S4Poly000BC2E0> m_E4;
	_STL::vector<S4Poly000BC2E0> m_F0;
	_STL::vector<S4Poly000BC2E0> m_FC;
	_STL::vector<S4Poly000BC2E0> m_108;
	_STL::vector<S4Poly000BC2E0> m_114;
	_STL::vector<S4Poly000BC2E0> m_120;
	_STL::vector<S4Poly000BC2E0> m_12C;
	RvaVector12 m_138;
	int m_144;
	int m_148;
	unsigned char m_14C;
	unsigned char m_14D;
	unsigned char m_14E;
	unsigned char m_14F;
	unsigned char m_150;
	unsigned char m_151;
	unsigned char m_152;
	unsigned char m_153;
	int m_154;
	unsigned char m_158;
	SixWords m_15C;
	unsigned char m_174;
	unsigned char m_175;
	int m_178;
	int m_17C;
	unsigned char m_180;
	BfmeNarrowString m_184;
	TenWords m_188;
	TenWords m_1B0;

public:
	Rva004A32E0Record &operator=(const Rva004A32E0Record &);
};

Rva004A32E0Record &Rva004A32E0Record::operator=(const Rva004A32E0Record &other)
{
    union PrefixCall {
        void (*address)();
        void *(Rva004A32E0CallReceiver::*method)(const Rva004A32E0Prefix &);
    } prefixCall;
    prefixCall.address = j_00048725;
    (((Rva004A32E0CallReceiver *)&m_prefix)->*prefixCall.method)(other.m_prefix);
	m_0C.set(other.m_0C);
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C.set(other.m_3C);
	m_40.set(other.m_40);
	m_44 = other.m_44;
	m_50 = other.m_50;
	m_5C.set(other.m_5C);
	m_60.set(other.m_60);
	m_64.set(other.m_64);
	m_68.set(other.m_68);
	m_6C = other.m_6C;
	m_70 = other.m_70;
	m_74 = other.m_74;
	m_78 = other.m_78;
	m_7C = other.m_7C;
	m_80 = other.m_80;
	m_84 = other.m_84;
	m_90 = other.m_90;
	m_94 = other.m_94;
	m_A0 = other.m_A0;
	m_A4 = other.m_A4;
	m_A8 = other.m_A8;
	m_B4 = other.m_B4;
	m_C0 = other.m_C0;
	m_CC = other.m_CC;
	m_D8 = other.m_D8;
	m_E4 = other.m_E4;
	m_F0 = other.m_F0;
	m_FC = other.m_FC;
	m_108 = other.m_108;
	m_114 = other.m_114;
	m_120 = other.m_120;
	m_12C = other.m_12C;
    union PointerVectorCall {
        void (*address)();
        void *(Rva004A32E0CallReceiver::*method)(const RvaVector12 &);
    } vectorCall;
    vectorCall.address = j_0000efde;
    (((Rva004A32E0CallReceiver *)&m_138)->*vectorCall.method)(other.m_138);
	m_144 = other.m_144;
	m_148 = other.m_148;
	m_14C = other.m_14C;
	m_14D = other.m_14D;
	m_14E = other.m_14E;
	m_14F = other.m_14F;
	m_150 = other.m_150;
	m_151 = other.m_151;
	m_152 = other.m_152;
	m_153 = other.m_153;
	m_154 = other.m_154;
	m_158 = other.m_158;
	m_15C = other.m_15C;
	m_174 = other.m_174;
	m_175 = other.m_175;
	m_178 = other.m_178;
	m_17C = other.m_17C;
	m_180 = other.m_180;
	m_184.set(other.m_184);
	m_188 = other.m_188;
	m_1B0 = other.m_1B0;
	return *this;
}
