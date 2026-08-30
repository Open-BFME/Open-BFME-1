// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class RadiusDecalTemplate
{
public:
	bool operator==( const RadiusDecalTemplate &that ) const;

private:
	AsciiString m_name;
	AsciiString m_secondName;
	int m_shadowType;
	float m_minOpacity;
	float m_maxOpacity;
	float m_opacityThrobTime;
	unsigned int m_color;
	bool m_onlyVisibleToOwningPlayer;
	float m_unmodelled_20;
	float m_unmodelled_24;
	unsigned int m_unmodelled_28;
	float m_unmodelled_2C;
};

bool RadiusDecalTemplate::operator==( const RadiusDecalTemplate &that ) const
{
	if( m_shadowType != that.m_shadowType
		|| m_minOpacity != that.m_minOpacity
		|| m_maxOpacity != that.m_maxOpacity
		|| m_opacityThrobTime != that.m_opacityThrobTime
		|| m_color != that.m_color
		|| m_name != that.m_name
		|| m_secondName != that.m_secondName
		|| m_unmodelled_24 != that.m_unmodelled_24
		|| m_unmodelled_20 != that.m_unmodelled_20
		|| m_unmodelled_28 != that.m_unmodelled_28
		|| m_unmodelled_2C != that.m_unmodelled_2C )
		return false;

	return true;
}
