// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ObjectTypes::getNthInList (0x000EE670, 77 bytes).  Identity: the ILT thunk
// 0x000177A6 jumps here and is pinned under this name; the matched caller at
// 0x00326660 (Rva00326490Condition.cpp) calls it by name.  The body is the
// Zero Hour inline accessor from GameLogic/ObjectTypes.h verbatim: the
// conditional expression is what makes MSVC keep the vector base in esi and
// reload the hidden return pointer in each arm.  Layout follows the landed
// ObjectTypesXfer.cpp (one vtable, m_listName at +4, m_objectTypes at +8).

#include <vector>
#include "ascii_string.h"

// AsciiString::TheEmptyString; ascii_string.h does not declare it.
extern const AsciiString Rva01336E50EmptyString;

class Xfer;

class ObjectTypes
{
private:
	AsciiString m_listName;
	std::vector<AsciiString> m_objectTypes;

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

public:
	unsigned int getListSize(void) const { return m_objectTypes.size(); }
	AsciiString getNthInList(int index) const;
};

AsciiString ObjectTypes::getNthInList(int index) const
{
	return (index < getListSize()) ? m_objectTypes[index] : Rva01336E50EmptyString;
}
