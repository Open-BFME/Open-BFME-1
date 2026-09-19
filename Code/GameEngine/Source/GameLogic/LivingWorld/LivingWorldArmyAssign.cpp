// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"
#include "string_base.h"

struct AsciiSlot
{
	void *m_data;

	void set( const AsciiString &other )
	{
		((StringBase<char> *)this)->set( *(const StringBase<char> *)&other );
	}

	void set( const AsciiSlot &other )
	{
		((StringBase<char> *)this)->set( *(const StringBase<char> *)&other );
	}

	AsciiSlot &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
};

struct WideSlot
{
	void *m_data;

	void set( const WideSlot &other )
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other );
	}
};

class LivingWorldArmy
{
public:
	AsciiString getName() const;
	void copyFrom( const LivingWorldArmy &other );

private:
	struct SixWords { int value[ 6 ]; };
	struct ThreeWords { int value[ 3 ]; };
	struct TenWords { int value[ 10 ]; };

	char m_header[ 4 ];
	AsciiSlot m_name;
	int m_08;
	int m_0c;
	SixWords m_10;
	ThreeWords m_28;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	AsciiSlot m_4c;
	TenWords m_50;
	WideSlot m_78;
	SixWords m_7c;
	SixWords m_94;
	AsciiSlot m_ac;
	AsciiSlot m_b0;
};

// ?copyFrom@LivingWorldArmy@@QAEXABV1@@Z
void LivingWorldArmy::copyFrom( const LivingWorldArmy &other )
{
	m_name = other.getName();
	m_10 = other.m_10;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_28 = other.m_28;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_39 = other.m_39;
	m_3c = other.m_3c;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_50 = other.m_50;
	m_78.set( other.m_78 );
	m_ac.set( other.m_ac );
	m_b0.set( other.m_b0 );
	m_7c = other.m_7c;
	m_94 = other.m_94;
	m_4c.set( other.m_4c );
}
