// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

#define OBJECT_TU_MEMBERS \
	void Rva001BE7A0( Bool enable );
#include "object.h"

void Object::Rva001BE7A0( Bool enable )
{
	if ( enable )
		m_privateStatus |= 0x04;
	else
		m_privateStatus &= 0xfb;
}
