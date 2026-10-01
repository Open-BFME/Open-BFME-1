// cl: /Igame/Libraries/Source/WWVegas/WWLib
// 159-byte retail body: RET12 at +0x9C, INT3 padding starts at +0x9F.
// Same independently proven callee as Rva00769C30StringForwarder.cpp;
// the selected string fields here are +0x1F8 and related-object +0xE8.
// Identity and ABI evidence: 00769b60-string-forwarder.md.
#include "ascii_string.h"

struct Rva00766AA0Buffer;
template <> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }

// The owner identity is not established by the available evidence.  Keep its
// address in the type name until an independently supported identity is known.
class Rva00766AA0Owner
{
public:
	bool forward00769C30(Rva00766AA0Buffer *argument1, AsciiString value,
		void **argument2, void **argument3);
};

class Rva00769B60Interface
{
public:
	bool forwardString(Rva00766AA0Buffer *argument1, void **argument2, void **argument3);
};

// Retail 0x00769B60.  The receiver passed to the owner routine is the
// owner at interfaceThis - 0x0C; [this - 8] is the related object whose
// AsciiString is at +0xE8.
bool Rva00769B60Interface::forwardString(
	Rva00766AA0Buffer *argument1, void **argument2, void **argument3)
{
	void *interfaceThis = this;
	AsciiString local;
	const AsciiString *stringAt1F8 = reinterpret_cast<const AsciiString *>(
		static_cast<char *>(interfaceThis) + 0x1F8);
	if (!stringAt1F8->isEmpty())
	{
		local.set(*stringAt1F8);
	}
	else
	{
		void *relatedObject = *reinterpret_cast<void **>(
			static_cast<char *>(interfaceThis) - 8);
		local.set(*reinterpret_cast<const AsciiString *>(
			static_cast<char *>(relatedObject) + 0xE8));
	}

	return reinterpret_cast<Rva00766AA0Owner *>(
		static_cast<char *>(interfaceThis) - 0x0C)->forward00769C30(
			argument1, local, argument2, argument3);
}
