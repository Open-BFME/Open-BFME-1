// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen( const char *text );

#include "../../../Include/Common/ScalarTypes.h"

#include "../../../Include/Common/Enums/ScienceAvailabilityType.h"








class AsciiString
{
public:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	Header *m_data;

public:
	// Retail-proven prefix-compare shape (same spelling as the StringBase
	// two-arg body): outlined as this TU's COMDAT, so this TU both provides
	// and consumes AsciiString::compareNoCase(PBDH) with no outside reference.
	int compareNoCase( const char *text, int length ) const
	{
		const int thisLength = m_data ? m_data->m_length : 0;
		const char *data = m_data ? (const char *)(m_data + 1) : "";
		int difference = _memicmp( data, text,
			thisLength < length ? thisLength : length );
		if( difference != 0 )
		{
			return difference;
		}
		return thisLength - length;
	}
};

static const char *ScienceAvailabilityNames[] =
{
	"Available",
	"Disabled",
	"Hidden",
	0
};

class Player
{
public:
	ScienceAvailabilityType getScienceAvailabilityTypeFromString( const AsciiString& name );
};

ScienceAvailabilityType Player::getScienceAvailabilityTypeFromString( const AsciiString& name )
{
	for( Int i = 0; i < SCIENCE_AVAILABILITY_COUNT; i++ )
	{
		if( !name.compareNoCase( ScienceAvailabilityNames[ i ], ScienceAvailabilityNames[ i ] ? strlen( ScienceAvailabilityNames[ i ] ) : 0 ) )
		{
			return (ScienceAvailabilityType)i;
		}
	}
	return SCIENCE_AVAILABILITY_INVALID;
}
