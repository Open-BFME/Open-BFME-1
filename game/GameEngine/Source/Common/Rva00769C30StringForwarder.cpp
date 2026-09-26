// cl: /Igame/Libraries/Source/WWVegas/WWLib
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

class Rva00769C30Interface
{
public:
	bool forwardString(Rva00766AA0Buffer *argument1, void **argument2, void **argument3);
};

// Retail 0x00769C30.  The receiver passed to the owner routine is the
// owner at interfaceThis - 0x0C; [this - 8] is the related object whose
// AsciiString is at +0xEC.
bool Rva00769C30Interface::forwardString(
	Rva00766AA0Buffer *argument1, void **argument2, void **argument3)
{
	void *interfaceThis = this;
	AsciiString local;
	const AsciiString *stringAt1FC = reinterpret_cast<const AsciiString *>(
		static_cast<char *>(interfaceThis) + 0x1FC);
	if (!stringAt1FC->isEmpty())
	{
		local.set(*stringAt1FC);
	}
	else
	{
		void *relatedObject = *reinterpret_cast<void **>(
			static_cast<char *>(interfaceThis) - 8);
		local.set(*reinterpret_cast<const AsciiString *>(
			static_cast<char *>(relatedObject) + 0xEC));
	}

	return reinterpret_cast<Rva00766AA0Owner *>(
		static_cast<char *>(interfaceThis) - 0x0C)->forward00769C30(
			argument1, local, argument2, argument3);
}
