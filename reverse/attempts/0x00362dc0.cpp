// ?d_00362dc0@@YAXXZ
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Retail layout: reuses the exact BfmeOwnVUM field layout established by the
// landed destructor Code/GameEngine/Source/Common/BfmeConv1645.cpp
// (??1BfmeOwnVUM@@QAE@XZ, 0x00360F90, vftable ??_7BfmeOwnVUM@@6B@,
// 0x010E8F34), and the same class as the banked 0x00362F30 partial. This
// no-argument constructor copy-constructs the +4 AsciiString member from
// AsciiString::TheEmptyString (retail pushes 0x01336E50, already pinned as
// ?TheEmptyString@AsciiString@@2V1@B) through the real AsciiString copy ctor
// 0x00887B60, then zero-initializes every other field.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	static const AsciiString TheEmptyString;

private:
	char *m_data;
};

class BfmeOwnVUM
{
public:
	BfmeOwnVUM();
	~BfmeOwnVUM();
	virtual void bfmeSlot0VUM();
	virtual void bfmeSlot1VUM();
	virtual void bfmeSlot2VUM();
	virtual void bfmeSlot3VUM();
	virtual void bfmeSlot4VUM();

private:
	AsciiString m_bfme04;
	int m_08, m_0c;
	int m_10, m_14, m_18, m_1c, m_20, m_24;
	int m_28, m_2c, m_30;
	int m_34;
	unsigned char m_38, m_39;
	int m_3c, m_40, m_44, m_48, m_4c;
	int m_50, m_54, m_58, m_5c, m_60, m_64, m_68, m_6c, m_70, m_74;
	int m_78;
	int m_7c, m_80, m_84, m_88, m_8c, m_90;
	int m_94, m_98, m_9c, m_a0, m_a4, m_a8;
	int m_ac, m_b0;
};

// ?d_00362dc0@@YAXXZ
BfmeOwnVUM::BfmeOwnVUM()
	: m_bfme04(AsciiString::TheEmptyString)
{
	m_08 = 0;
	m_0c = 0;

	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;

	m_28 = 0;
	m_2c = 0;
	m_30 = 0;

	m_34 = 0;
	m_38 = 0;
	m_39 = 0;
	m_3c = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4c = 0;

	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_70 = 0;
	m_74 = 0;

	m_78 = 0;

	m_7c = 0;
	m_80 = 0;
	m_84 = 0;
	m_88 = 0;
	m_8c = 0;
	m_90 = 0;

	m_94 = 0;
	m_98 = 0;
	m_9c = 0;
	m_a0 = 0;
	m_a4 = 0;
	m_a8 = 0;

	m_ac = 0;
	m_b0 = 0;
}
