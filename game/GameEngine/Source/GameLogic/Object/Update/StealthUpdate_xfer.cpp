// cl: /DNDEBUG /MD /EHsc
//
// StealthUpdate::xfer, retail RVA 0x002AC200.
// The base UpdateModule transfer, light-CRC guard, disguise-template lookup,
// and the seven trailing bool transfers identify this serializer.

#include "../../../Common/System/xfer.h"

typedef unsigned int UnsignedInt;
typedef int Int;

struct XferVersionView : Xfer::Version
{
	XferVersionView(unsigned char first, unsigned char current)
	{
		data[0] = first;
		data[1] = current;
	}
};

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned char m_base[0x1C];
};

template <typename T>
class StringBase
{
private:
	friend class AsciiString;
	StringBase(const StringBase<T> &source);
};

class AsciiString
{
public:
	static AsciiString TheEmptyString;

	AsciiString(const AsciiString &that)
	{
		// AsciiString is the one-pointer StringBase<char> view used by the
		// retail copy constructor at 0x00887B60.
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString();

	bool isEmpty() const
	{
		const StringHeader *header = *(const StringHeader * const *)this;
		return header == 0 || header->length == 0;
	}

private:
	struct StringHeader
	{
		int referenceCount;
		unsigned short length;
		unsigned short capacity;
	};

	void *m_data;
};

class ThingTemplate
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class StealthUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	bool m_enabled;
	bool m_unknown2D;
	bool m_unknown2E;
	bool m_unknown2F;
	bool m_unknown30;
	unsigned char m_pad31[3];
	Int m_disguiseAsPlayerIndex;
	const ThingTemplate *m_disguiseAsTemplate;
	UnsignedInt m_disguiseTransitionFrames;
	bool m_disguiseHalfpointReached;
	bool m_transitioningToDisguise;
	bool m_disguised;
};

// ?xfer@StealthUpdate@@MAEXPAVXfer@@@Z
void StealthUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;

	XferVersionView version(1, 2);
	*xfer == version;
	*xfer == m_stealthAllowedFrame;
	*xfer == m_detectionExpiresFrame;
	if (version.data[1] >= 2)
		*xfer == m_nextBlackMarketCheckFrame;
	*xfer == m_enabled;
	*xfer == m_disguiseAsPlayerIndex;

	AsciiString name = m_disguiseAsTemplate != 0
		? m_disguiseAsTemplate->getName()
		: AsciiString::TheEmptyString;
	*xfer == name;
	if (xfer->IsLoading())
	{
		m_disguiseAsTemplate = 0;
		if (!name.isEmpty())
		{
			m_disguiseAsTemplate = TheThingFactory->findTemplate(name);
			if (m_disguiseAsTemplate == 0)
			{
				BfmeFormattedText error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
		}
	}

	*xfer == m_disguiseTransitionFrames;
	*xfer == m_disguiseHalfpointReached;
	*xfer == m_transitioningToDisguise;
	*xfer == m_disguised;
	*xfer == m_unknown30;
	*xfer == m_unknown2E;
	*xfer == m_unknown2F;
	*xfer == m_unknown2D;
}
