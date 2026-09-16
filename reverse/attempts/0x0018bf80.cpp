// ?xfer@Rva0018BF80Owner@@QAEXPAVXfer@@@Z
// partial score=0.99 date=2026-09-16
// Scratch-only reconstruction of retail RVA 0x0018BF80 (274 bytes).
// The semantic owner is not recovered; the address-labelled owner records
// the proven layout and xfer operation without inventing a game-class name.
// The serialized element is the canonical ObjectID enum consumed by the
// existing friend_xferObjectID helper; it is not the generic ScienceType ICF
// alias.  The helper's four-byte pointer ABI does not establish a typedef.
//
// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC
#include <vector>

#include "Common/GameType.h"
typedef char ObjectIDSizeCheck[(sizeof(ObjectID) == 4) ? 1 : -1];

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// BFME-specific Xfer ABI view for this matched transfer family.  It is not a
// claim about the canonical ZH Xfer class layout.  The target uses the skip
// predicate at +0x10, version at +0x28, and short transfer at +0x7c; unused
// entries remain address-only placeholders so those slots are retained.
class Xfer
{
public:
	virtual ~Xfer(void);
	virtual void slot01(void);
	virtual Bool isSaving(void);
	virtual void slot03(void);
	virtual Bool skip(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Xfer &xferVersion(XferVersion *version);
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
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual Xfer &xferShort(UnsignedShort *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

// Existing typed helper pin reaches the ObjectID transfer at RVA0010C3C0
// through ILT0000C9B4, forwarding the four-byte value via Xfer slot0x90.
extern void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva0018BF80Owner
{
public:
	virtual ~Rva0018BF80Owner(void);
	_STL::vector<ObjectID> m_first;
	_STL::vector<ObjectID> m_second;

	void xfer(Xfer *xfer);
};

void Rva0018BF80Owner::xfer(Xfer *xfer)
{
	if (xfer->skip())
		return;

	{
		XferVersion version = { 1, 1 };
		xfer->xferVersion(&version);
	}

	UnsignedShort count = static_cast<UnsignedShort>(m_first.size());
	xfer->xferShort(&count);

	if (xfer->isSaving())
	{
		ObjectID *current = m_first.begin();
		while (current != m_first.end())
		{
			ObjectID value = *current;
			friend_xferObjectID(xfer, &value);
			++current;
		}
	}
	else
	{
		if (m_second.size() != 0)
		{
			XferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		UnsignedShort index = 0;
		while (index < count)
		{
			ObjectID value;
			friend_xferObjectID(xfer, &value);
			m_first.push_back(value);
			++index;
		}
	}
}
