// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The primary vftable 0x011217A0 places this method at slot 112.
// Its body allocates the named camera record constructed at 0x00741830.

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "ascii_string.h"

class Rva00741830
{
public:
	Rva00741830(const AsciiString &, const Coord3D &, Real, Real, Real,
		Real, Real, Real);

private:
	unsigned m_zero;
	AsciiString m_name;
	Coord3D m_position;
	Real m_values[6];
	unsigned char m_flag;
};

#define BFME_SLOT(n) virtual void slot##n() = 0;
#define BFME_REAL_SLOT(n) virtual Real slot##n() = 0;

class Rva00745B10Owner
{
public:
	BFME_SLOT(0)   BFME_SLOT(1)   BFME_SLOT(2)   BFME_SLOT(3)
	BFME_SLOT(4)   BFME_SLOT(5)   BFME_SLOT(6)   BFME_SLOT(7)
	BFME_SLOT(8)   BFME_SLOT(9)   BFME_SLOT(10)  BFME_SLOT(11)
	BFME_SLOT(12)  BFME_SLOT(13)  BFME_SLOT(14)  BFME_SLOT(15)
	BFME_SLOT(16)  BFME_SLOT(17)  BFME_SLOT(18)  BFME_SLOT(19)
	BFME_SLOT(20)  BFME_SLOT(21)  BFME_SLOT(22)  BFME_SLOT(23)
	BFME_SLOT(24)  BFME_SLOT(25)  BFME_SLOT(26)  BFME_SLOT(27)
	BFME_SLOT(28)  BFME_SLOT(29)  BFME_SLOT(30)  BFME_SLOT(31)
	BFME_SLOT(32)  BFME_SLOT(33)  BFME_SLOT(34)  BFME_SLOT(35)
	BFME_SLOT(36)  BFME_SLOT(37)  BFME_SLOT(38)  BFME_SLOT(39)
	BFME_SLOT(40)  BFME_SLOT(41)  BFME_SLOT(42)  BFME_SLOT(43)
	BFME_SLOT(44)  BFME_SLOT(45)  BFME_SLOT(46)  BFME_SLOT(47)
	BFME_SLOT(48)  BFME_SLOT(49)  BFME_SLOT(50)  BFME_SLOT(51)
	BFME_SLOT(52)  BFME_SLOT(53)  BFME_SLOT(54)  BFME_SLOT(55)
	BFME_SLOT(56)  BFME_SLOT(57)  BFME_SLOT(58)  BFME_SLOT(59)
	BFME_SLOT(60)  BFME_SLOT(61)  BFME_SLOT(62)  BFME_REAL_SLOT(63)
	BFME_SLOT(64)  BFME_SLOT(65)  BFME_SLOT(66)  BFME_REAL_SLOT(67)
	BFME_SLOT(68)  BFME_SLOT(69)  BFME_SLOT(70)  BFME_SLOT(71)
	BFME_REAL_SLOT(72) BFME_SLOT(73) BFME_SLOT(74)  BFME_SLOT(75)
	BFME_SLOT(76)  BFME_SLOT(77)  BFME_SLOT(78)  BFME_SLOT(79)
	BFME_SLOT(80)  BFME_SLOT(81)  BFME_SLOT(82)  BFME_SLOT(83)
	BFME_SLOT(84)  BFME_SLOT(85)  BFME_SLOT(86)  BFME_SLOT(87)
	BFME_SLOT(88)  BFME_SLOT(89)  BFME_SLOT(90)  BFME_SLOT(91)
	BFME_SLOT(92)  BFME_SLOT(93)  BFME_SLOT(94)  BFME_SLOT(95)
	BFME_SLOT(96)  BFME_SLOT(97)  BFME_SLOT(98)  BFME_SLOT(99)
	BFME_SLOT(100) BFME_SLOT(101) BFME_SLOT(102) BFME_SLOT(103)
	BFME_SLOT(104) BFME_SLOT(105) BFME_SLOT(106) BFME_SLOT(107)
	BFME_SLOT(108) BFME_SLOT(109) BFME_SLOT(110) BFME_SLOT(111)
	virtual Rva00741830 *createNamedCamera(const AsciiString &name);

private:
	char m_padding0004[0x0c - 4];
	Coord3D m_position;
	char m_padding0018[0x44 - 0x18];
	unsigned char m_cameraChanged;
	char m_padding0045[0x6c - 0x45];
	Real m_cameraValue;
	Real m_cameraOutput;
	char m_padding0074[0x23f8 - 0x74];
	Real m_groundLevel;
};

#undef BFME_SLOT
#undef BFME_REAL_SLOT

Rva00741830 *Rva00745B10Owner::createNamedCamera(const AsciiString &name)
{
	Coord3D position;
	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;
	m_cameraChanged = 0;
	return new Rva00741830(name, position,
		m_groundLevel, slot63(), m_cameraOutput, slot72(), m_cameraValue,
		slot67());
}
