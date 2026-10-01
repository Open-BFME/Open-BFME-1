// cl: /O2 /Ob0

// TU-local VIEW of the real GlobalData, kept only for its offsets.
class Rva0040B2E0Global
{
public:
	char m_lead[0xDC8];
	float m_value;
};

class Rva0040B2E0
{
	char m_lead[0x14];
	float m_scale;

public:
	float scale() const;
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`.  Only
// Common/GlobalData.cpp may DEFINE it; this TU is a second reader of it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

float Rva0040B2E0::scale() const
{
	return ((Rva0040B2E0Global *)TheWritableGlobalData)->m_value * m_scale;
}
