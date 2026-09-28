// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00745B10 (977 bytes): the constructor of the 0x24E4-byte owner
// whose matched destructor is 0x007461B0 (Rva00745B10OwnerDestructor.cpp);
// the niladic factory 0x006FBE60 allocates it.  It builds the View base
// (0x0045B8C0), the second base at +0xB4 and SubsystemInterface at +0xFC,
// installs the owner vtables 0x011217A0 / 0x01121790 / 0x01121764, and then
// initialises the members in declaration order.  Vtable 0x011217A0's slot 0
// is the matched W3DView scalar-deleting destructor, so the owner is BFME's
// W3DView; the class keeps the matched destructor's address-token name here.
//
// Shape notes, each measured against retail:
// - The camera move infos (+0x1AC, +0x1E0, +0x208, +0x22C, +0x258) are plain
//   structs holding a ParabolicEase; the owner value-initialises them, which
//   clears each block before the ease constructor runs (as Zero Hour's
//   TRotateCameraInfo etc. hold their ease).
// - Coord3D/Coord2D members zero through inline constructors; those
//   boundaries fix where retail schedules the ease arguments, the EH state
//   stores and the +0x23D8 address it keeps in EDI.
// - The body inlines Rva0073B8C0::setInt23BC(0) (Bfme/Rva0073B8C0Set.cpp),
//   the same object's message-0x451 setter.
// - Scaling +0x23D8.x through a const reference and .y directly reproduces
//   retail's x87 operand order (coordinate first, then the +0xA0 scale).
#include <vector>
#include <string.h>
#include "ascii_string.h"

typedef float Real;
struct Coord2D { Real x, y; Coord2D() : x(0), y(0) {} };
struct Coord3D { Real x, y, z; Coord3D() : x(0), y(0), z(0) {} };

class ParabolicEase
{
public:
	explicit ParabolicEase(Real easeInTime = 0.0f, Real easeOutTime = 0.0f)
		{ setEaseTimes(easeInTime, easeOutTime, 1.0f); }
	void setEaseTimes(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

// Camera move infos: plain data ending in (or holding) an ease; the owner
// value-initialises them, which clears them before the ease constructor runs.
struct Rva00745B10Info1AC
{
	char m_head[0x14];
	ParabolicEase ease;
	char m_tail[0x14];
};

template <int HEAD>
struct Rva00745B10EasedInfo
{
	char m_head[HEAD];
	ParabolicEase ease;
};

struct Rva00745B10Tail2434
{
	Rva00745B10Tail2434() : m_2434(1.0f), m_2438(false), m_2439(false) {}
	Real m_2434;
	bool m_2438, m_2439;
};

struct Rva00745B10Block2450
{
	Rva00745B10Block2450() : m_2490(0) {}
	char m_gap2450[0x2490 - 0x2450];
	int m_2490;
	char m_gap2494[0x24ac - 0x2494];
};


class Rva007461B0RefCounted
{
public:
	virtual void Delete_This() = 0;
	int NumRefs;
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30();
	virtual GameMessage *appendMessage(int type);	// +0x34
};
extern MessageStream *TheMessageStream;

// Camera path member at +0x280 (CameraPath_ctor.cpp).
class Rva00740AE0
{
public:
	Rva00740AE0();
	~Rva00740AE0();
private:
	void *m_body[(0x22f4 - 0x280) / 4];
};

class BfmeThingIC
{
public:
	BfmeThingIC();
	~BfmeThingIC();
private:
	char m_body[0x60];
};

class Rva00459D20
{
public:
	Rva00459D20();
	~Rva00459D20();
private:
	char m_body[8];
};

class Rva006DF550
{
public:
	Rva006DF550();
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40();
	virtual void rva006DF550Slot44();					// +0x44
	virtual void rva006DF550Slot48(struct Coord3D *a, Real *b);	// +0x48
private:
	char m_body[0x2c - 4];
};

struct Gen_t_00745890_p24cd
{
	char m_body[24];
};

class View
{
public:
	View();
	virtual ~View();
	char m_pad04[0x28 - 4];
	Real m_28;						// +0x28
	char m_pad2c[0x70 - 0x2c];
	Real m_70;						// +0x70
	char m_pad74[0xa0 - 0x74];
	Real m_a0;						// +0xa0
	char m_pada4[0xb4 - 0xa4];
};

class Rva007461B0BaseS
{
public:
	Rva007461B0BaseS() {}
	virtual ~Rva007461B0BaseS() {}
	char m_pad04[0x2c - 4];
	struct Zero { int v; Zero() : v(0) {} } m_2c;	// +0xe0 in the owner
	char m_pad30[0x48 - 0x30];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	char *m_name;
};

class Rva00745B10Owner : public View, public Rva007461B0BaseS, public SubsystemInterface
{
public:
	Rva00745B10Owner();
	virtual ~Rva00745B10Owner();

	void setInt23BC(int arg)
	{
		if (arg != m_int23BC)
		{
			if (TheMessageStream)
			{
				GameMessage *msg = TheMessageStream->appendMessage(0x451);
				msg->appendIntegerArgument(arg);
				return;
			}
			m_int23BC = arg;
		}
	}

private:
	Rva007461B0RefCounted *m_104;
	Rva007461B0RefCounted *m_108;
	int m_10c;
	int m_110;
	bool m_114;
	bool m_115;
	int m_118, m_11c;
	Coord3D m_120;
	Coord3D m_12c;
	int m_138;
	char m_gap13c[0x1a4 - 0x13c];
	ParabolicEase m_1a4;
	Rva00745B10Info1AC m_1ac;
	bool m_byte1DC;
	Rva00745B10EasedInfo<0x1c> m_1e0;
	bool m_byte204;
	Rva00745B10EasedInfo<0x18> m_208;
	bool m_byte228;
	Rva00745B10EasedInfo<0x20> m_22c;
	bool m_byte254;
	Rva00745B10EasedInfo<0x1c> m_258;
	bool m_byte27C;
	bool m_flag27D;
	Rva00740AE0 m_280;
	BfmeThingIC m_22f4;
	int m_int2354;
	BfmeThingIC m_2358;
	bool m_byte23B8;
	int m_int23BC;
	bool m_23c0;
	int m_23c4;
	bool m_23c8;
	_STL::vector<Gen_t_00745890_p24cd> m_23cc;
	Coord3D m_23d8;
	Coord2D m_23e4;
	Real m_23ec, m_23f0, m_23f4;
	Real m_23f8;
	char m_gap23fc[0x240c - 0x23fc];
	bool m_240c;
	int m_2410, m_2414, m_2418, m_241c, m_2420, m_2424;
	bool m_2428, m_2429, m_242a;
	AsciiString m_242c;
	AsciiString m_2430;
	Rva00745B10Tail2434 m_2434;
	int m_int243C, m_int2440, m_int2444;
	Rva00459D20 m_2448;
	Rva00745B10Block2450 m_2450;
	int m_24ac;
	bool m_24b0;
	int m_24b4;
	Rva006DF550 m_24b8;
};

Rva00745B10Owner::Rva00745B10Owner()
	: m_104(0), m_108(0), m_10c(15), m_110(9), m_114(false), m_115(false), m_118(0), m_11c(0), m_138(0),
	  m_1ac(), m_byte1DC(false), m_1e0(), m_byte204(false), m_208(), m_byte228(false), m_22c(), m_byte254(false), m_258(),
	  m_byte27C(false), m_flag27D(false),
	  m_int2354(0),
	  m_byte23B8(false), m_int23BC(0), m_23c0(false), m_23c4(0), m_23c8(true),
	  m_23ec(0), m_23f0(0), m_23f4(0),
	  m_23f8(10.0f),
	  m_240c(false), m_2410(0), m_2414(0), m_2418(0), m_241c(0), m_2420(0), m_2424(0),
	  m_2428(false), m_2429(false), m_242a(false),
	  m_int243C(0), m_int2440(0), m_int2444(0),
	  m_24ac(0), m_24b0(false), m_24b4(0)
{
	m_24b8.rva006DF550Slot44();
	m_24b8.rva006DF550Slot48(&m_23d8, &m_28);
	{
		const Real &scale = m_a0;
		m_23d8.x *= scale;
	}
	m_23d8.y *= m_a0;
	m_23cc.reserve(50);
	m_70 = 1.0f;
	setInt23BC(0);
}
