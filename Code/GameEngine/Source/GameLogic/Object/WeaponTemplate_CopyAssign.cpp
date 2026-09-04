// cl: /DNDEBUG /MD
// Open-BFME5: WeaponTemplate::operator=, retail 0x001E80A0 size 1185.
// newOverride at 0x001E9AF0 calls this after the default ctor (ILT 0x0001AF3C).
// Layout is the BFME 0x53C record: AsciiString name at +8, nameKey at +0x0C,
// scatter vector at +0x34 (parseScatterTarget), 12-byte-element vector at
// +0x40, projectile name at +0x80, nine AudioEventRTS assigns from +0xB4,
// copied-override flag at +0x528. Focused TU; member types recover the
// 14 typed calls. Do not fold this into Weapon.cpp (ZH offsets differ).

template <typename T>
class StringBase
{
public:
	void set(const StringBase &src);

private:
	void *m_data;
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}

private:
	void *m_data;
};

class WtVecCoord2D
{
public:
	WtVecCoord2D &operator=(const WtVecCoord2D &that);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class WtVecPod12
{
public:
	WtVecPod12 &operator=(const WtVecPod12 &that);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class AudioEventRTS
{
public:
	AudioEventRTS &assign(const AudioEventRTS &that);

private:
	unsigned char m_bytes[0x70];
};

class WtTail
{
public:
	WtTail &operator=(const WtTail &that);

private:
	void *m_data;
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject() {}
};

class WeaponTemplate : public MemoryPoolObject
{
public:
	WeaponTemplate &operator=(const WeaponTemplate &that);

private:
	WeaponTemplate *m_nextTemplate;
	AsciiString m_name;
	int m_nameKey;
	int m_d010;
	int m_d014;
	int m_d018;
	int m_d01c;
	int m_d020;
	int m_d024;
	int m_d028;
	int m_d02c;
	unsigned char m_b030;
	unsigned char m_b031;
	unsigned char m_pad032[2];
	WtVecCoord2D m_scatterTargets;
	WtVecPod12 m_linearTargets;
	int m_d04c;
	int m_d050;
	int m_d054;
	int m_d058;
	int m_d05c;
	int m_d060;
	unsigned char m_b064;
	unsigned char m_b065;
	unsigned char m_pad066[2];
	int m_d068;
	int m_d06c;
	unsigned char m_b070;
	unsigned char m_b071;
	unsigned char m_b072;
	unsigned char m_pad073;
	int m_d074;
	int m_d078;
	int m_d07c;
	AsciiString m_projectileName;
	int m_d084;
	int m_d088;
	int m_d08c;
	int m_d090;
	int m_d094;
	int m_d098;
	int m_d09c;
	int m_d0a0;
	int m_d0a4;
	int m_d0a8;
	int m_d0ac;
	int m_d0b0;
	AudioEventRTS m_audio0b4;
	int m_d124;
	AudioEventRTS m_audio128[8];
	int m_d4a8;
	int m_d4ac;
	int m_d4b0;
	int m_d4b4;
	int m_d4b8;
	int m_d4bc;
	int m_d4c0;
	int m_d4c4;
	int m_d4c8;
	int m_d4cc;
	int m_d4d0;
	int m_d4d4;
	int m_d4d8;
	unsigned char m_b4dc;
	unsigned char m_pad4dd[3];
	int m_d4e0;
	unsigned char m_b4e4;
	unsigned char m_pad4e5[3];
	int m_d4e8;
	unsigned char m_b4ec;
	unsigned char m_b4ed;
	unsigned char m_b4ee;
	unsigned char m_pad4ef;
	int m_d4f0;
	int m_d4f4;
	unsigned char m_b4f8;
	unsigned char m_b4f9;
	unsigned char m_b4fa;
	unsigned char m_b4fb;
	unsigned char m_b4fc;
	unsigned char m_b4fd;
	unsigned char m_pad4fe[2];
	int m_d500;
	int m_d504;
	unsigned char m_b508;
	unsigned char m_b509;
	unsigned char m_pad50a[2];
	int m_d50c;
	int m_d510;
	int m_d514;
	int m_d518;
	unsigned char m_b51c;
	unsigned char m_b51d;
	unsigned char m_b51e;
	unsigned char m_b51f;
	int m_d520;
	int m_d524;
	unsigned char m_copiedOverride;
	unsigned char m_b529;
	unsigned char m_pad52a[2];
	int m_d52c;
	unsigned char m_b530;
	unsigned char m_b531;
	unsigned char m_b532;
	unsigned char m_b533;
	unsigned char m_b534;
	unsigned char m_b535;
	unsigned char m_pad536[2];
	WtTail m_tail;
};

// ??4WeaponTemplate@@QAEAAV0@ABV0@@Z
WeaponTemplate &WeaponTemplate::operator=(const WeaponTemplate &that)
{
	m_nextTemplate = that.m_nextTemplate;
	m_name = that.m_name;
	m_nameKey = that.m_nameKey;
	m_d010 = that.m_d010;
	m_d014 = that.m_d014;
	m_d018 = that.m_d018;
	m_d01c = that.m_d01c;
	m_d020 = that.m_d020;
	m_d024 = that.m_d024;
	m_d028 = that.m_d028;
	m_d02c = that.m_d02c;
	m_b030 = that.m_b030;
	m_b031 = that.m_b031;
	m_scatterTargets = that.m_scatterTargets;
	m_linearTargets = that.m_linearTargets;
	m_d04c = that.m_d04c;
	m_d050 = that.m_d050;
	m_d054 = that.m_d054;
	m_d058 = that.m_d058;
	m_d05c = that.m_d05c;
	m_d060 = that.m_d060;
	m_b064 = that.m_b064;
	m_b065 = that.m_b065;
	m_d068 = that.m_d068;
	m_d06c = that.m_d06c;
	m_b070 = that.m_b070;
	m_b071 = that.m_b071;
	m_b072 = that.m_b072;
	m_d074 = that.m_d074;
	m_d078 = that.m_d078;
	m_d07c = that.m_d07c;
	m_projectileName = that.m_projectileName;
	m_d084 = that.m_d084;
	m_d088 = that.m_d088;
	m_d08c = that.m_d08c;
	m_d090 = that.m_d090;
	m_d094 = that.m_d094;
	m_d098 = that.m_d098;
	m_d09c = that.m_d09c;
	m_d0a0 = that.m_d0a0;
	m_d0a4 = that.m_d0a4;
	m_d0a8 = that.m_d0a8;
	m_d0ac = that.m_d0ac;
	m_d0b0 = that.m_d0b0;
	m_audio0b4.assign(that.m_audio0b4);
	m_d124 = that.m_d124;
	m_audio128[0].assign(that.m_audio128[0]);
	m_audio128[1].assign(that.m_audio128[1]);
	m_audio128[2].assign(that.m_audio128[2]);
	m_audio128[3].assign(that.m_audio128[3]);
	m_audio128[4].assign(that.m_audio128[4]);
	m_audio128[5].assign(that.m_audio128[5]);
	m_audio128[6].assign(that.m_audio128[6]);
	m_audio128[7].assign(that.m_audio128[7]);
	m_d4a8 = that.m_d4a8;
	m_d4ac = that.m_d4ac;
	m_d4b0 = that.m_d4b0;
	m_d4b4 = that.m_d4b4;
	m_d4b8 = that.m_d4b8;
	m_d4bc = that.m_d4bc;
	m_d4c0 = that.m_d4c0;
	m_d4c4 = that.m_d4c4;
	m_d4c8 = that.m_d4c8;
	m_d4cc = that.m_d4cc;
	m_d4d0 = that.m_d4d0;
	m_d4d4 = that.m_d4d4;
	m_d4d8 = that.m_d4d8;
	m_b4dc = that.m_b4dc;
	m_d4e0 = that.m_d4e0;
	m_b4e4 = that.m_b4e4;
	m_d4e8 = that.m_d4e8;
	m_b4ec = that.m_b4ec;
	m_b4ed = that.m_b4ed;
	m_b4ee = that.m_b4ee;
	m_d4f0 = that.m_d4f0;
	m_d4f4 = that.m_d4f4;
	m_b4f8 = that.m_b4f8;
	m_b4f9 = that.m_b4f9;
	m_b4fa = that.m_b4fa;
	m_b4fb = that.m_b4fb;
	m_b4fc = that.m_b4fc;
	m_b4fd = that.m_b4fd;
	m_d500 = that.m_d500;
	m_d504 = that.m_d504;
	m_b508 = that.m_b508;
	m_b509 = that.m_b509;
	m_d50c = that.m_d50c;
	m_d510 = that.m_d510;
	m_d514 = that.m_d514;
	m_d518 = that.m_d518;
	m_b51c = that.m_b51c;
	m_b51d = that.m_b51d;
	m_b51e = that.m_b51e;
	m_b51f = that.m_b51f;
	m_d520 = that.m_d520;
	m_d524 = that.m_d524;
	m_copiedOverride = that.m_copiedOverride;
	m_b529 = that.m_b529;
	m_d52c = that.m_d52c;
	m_b530 = that.m_b530;
	m_b531 = that.m_b531;
	m_b532 = that.m_b532;
	m_b533 = that.m_b533;
	m_b534 = that.m_b534;
	m_b535 = that.m_b535;
	m_tail = that.m_tail;
	return *this;
}
