// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// BFME ObjectTypes::xfer.  This TU carries the witnessed BFME one-vtable and
// retail StringBase ABI; the Zero Hour header's ObjectTypes layout is wider.

#include <vector>
#include "StringInline.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct Rva001DC690Version
{
	UnsignedByte version;
	UnsignedByte currentVersion;
};

class Xfer
{
};

class Rva001DC690XferView
{
public:
	virtual ~Rva001DC690XferView(void);
	virtual Bool isLoading(void);
	virtual Bool isSaving(void);
	virtual void slot03(void);
	virtual Bool isLightCRC(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Rva001DC690XferView &xferVersion(Rva001DC690Version &version);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual Rva001DC690XferView &xferAsciiString(AsciiString *value);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual Rva001DC690XferView &xferUnsignedShort(UnsignedShort *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class ObjectTypes
{
private:
	AsciiString m_listName;
	std::vector<AsciiString> m_objectTypes;

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
};

// The retail insert call is the Open2Elem063700 vector COMDAT reached through
// the 0x0003827B thunk; its element has the same single StringBase pointer.
class Open2Elem063700 : public AsciiString
{
public:
	Open2Elem063700(const Open2Elem063700 &other) : AsciiString(other) {}
};

struct Rva001DC690ObjectTypes
{
	char pad[4];
	AsciiString listName;
	std::vector<Open2Elem063700> objectTypes;
};

// ?xfer@ObjectTypes@@MAEXPAVXfer@@@Z
void ObjectTypes::xfer(Xfer *xfer)
{
	UnsignedShort i;
	Rva001DC690XferView *receiver =
		reinterpret_cast<Rva001DC690XferView *>(xfer);
	Rva001DC690ObjectTypes *self =
		reinterpret_cast<Rva001DC690ObjectTypes *>(this);

	if (receiver->isLightCRC())
		return;
	{
		union VersionStorage
		{
			Rva001DC690Version version;
			unsigned char padding[4];
		} versionStorage;
		versionStorage.version.version = 1;
		versionStorage.version.currentVersion = 1;
		receiver->xferVersion(versionStorage.version);
	}
	receiver->xferAsciiString(&m_listName);

	UnsignedShort objectTypesCount = self->objectTypes.size();
	receiver->xferUnsignedShort(&objectTypesCount);

	if (receiver->isSaving())
	{
		Open2Elem063700 *current = self->objectTypes.begin();
		while (current != self->objectTypes.end())
		{
			receiver->xferAsciiString(current);
			++current;
		}
	}
	else
	{
		if (!self->objectTypes.empty())
		{
			XferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (void *)0x011DFE5C);
		}

		AsciiString typeName;
		i = 0;
		while (i < objectTypesCount)
		{
			receiver->xferAsciiString(&typeName);
			self->objectTypes.push_back(
				*(const Open2Elem063700 *)&typeName);
			++i;
		}
	}
}
