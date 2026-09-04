// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Open-BFME5: LivingWorldCampaign copy constructor at retail 0x003B6BA0 (116B).
// Inline StringBase forwarding keeps lea ecx / push arg in retail order.

typedef int Int;

class AsciiString
{
public:
	__forceinline AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	char *m_data;
};

class BfmeMissionPlaceholder;

class Rva003A9860
{
public:
	Rva003A9860(const Rva003A9860 &other);			// ILT 0x00039FCC
	~Rva003A9860();						// ILT 0x00037A4C

	BfmeMissionPlaceholder *m_start;
	BfmeMissionPlaceholder *m_finish;
	BfmeMissionPlaceholder *m_endOfStorage;
};

class BfmeLivingWorldCampaignBase
{
public:
	virtual void bfmeSlot0(void);
	~BfmeLivingWorldCampaignBase() {}
};

class LivingWorldCampaign : public BfmeLivingWorldCampaignBase
{
public:
	LivingWorldCampaign(const LivingWorldCampaign &other);

private:
	AsciiString m_name;
	Int m_field08;
	Rva003A9860 m_missions;
	Int m_current;
	bool m_flag1C;
};

LivingWorldCampaign::LivingWorldCampaign(const LivingWorldCampaign &other) :
	m_name(other.m_name),
	m_field08(other.m_field08),
	m_missions(other.m_missions),
	m_current(other.m_current),
	m_flag1C(other.m_flag1C)
{
}
