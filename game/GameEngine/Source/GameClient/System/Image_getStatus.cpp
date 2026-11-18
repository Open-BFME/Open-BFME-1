// cl: /O2

#include "../../../Include/Common/ScalarTypes.h"

class Image
{
private:
	char m_unmodeled_00[0x30];
	UnsignedInt m_status;

public:
	UnsignedInt getStatus(void) const;
};

// ?getStatus@Image@@QBEIXZ
UnsignedInt Image::getStatus(void) const
{
	return m_status;
}
