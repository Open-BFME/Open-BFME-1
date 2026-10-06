// cl: /O2 /Ob0

void bfmeGo995B(void);

struct Rva005A4BF0StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// Retail's clear() call lands on the wide releaseBuffer body (0x008881D0).
template <typename T>
class StringBase
{
	friend class Rva005A4BF0Mouse;
	void releaseBuffer();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:

	Rva005A4BF0StringHeader *m_data;
};

class Rva005A4BF0Mouse
{
public:
	void clearTooltipIfHidden(unsigned char flag, unsigned char *out);

private:
	char m_pad0[0x10FC];
	UnicodeString m_tooltip;
	char m_pad1[0x1108 - 0x1100];
	int m_tooltipExtra;
	char m_pad2[0x4DA1 - 0x110C];
	unsigned char m_engineVisible;
	unsigned char m_scriptVisible;
};

void Rva005A4BF0Mouse::clearTooltipIfHidden(unsigned char flag, unsigned char *out)
{
	UnicodeString *tooltip = &m_tooltip;
	*out = flag;
	if (tooltip->m_data && tooltip->m_data->length)
	{
		if (!m_engineVisible || !m_scriptVisible)
		{
			bfmeGo995B();
			tooltip->StringBase<unsigned short>::releaseBuffer();
			m_tooltipExtra = 0;
		}
	}
}
