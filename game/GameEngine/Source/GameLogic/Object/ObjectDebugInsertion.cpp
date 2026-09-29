// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: Debug stream insertion for an Object pointer, retail
// 0x001C45E0, 112 bytes.  Retail materializes DescribeObject's AsciiString
// return value, streams its C string through Debug's const-char virtual slot,
// destroys the temporary, and returns the original stream reference.

class Object;

extern const char Rva006A16B0Empty[];

#include "ascii_string.h"

AsciiString DescribeObject(const Object *object);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
	virtual ~Debug();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual Debug &operator<<(const char *text);
};

// ??6@YAAAVDebug@@AAV0@PBVObject@@@Z
Debug &operator<<(Debug &debug, const Object *object)
{
	debug << DescribeObject(object).str();
	return debug;
}
