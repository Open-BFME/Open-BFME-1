// cl: /DNDEBUG /MD /EHsc

// BFME text-entry character policy, called by the private IME insertion
// helper through ILT 0x000275C0 (body 0x000861E0).

typedef unsigned short WideChar;

extern "C" __declspec(dllimport) int __cdecl iswalnum(WideChar character);
extern "C" __declspec(dllimport) int __cdecl iswascii(WideChar character);
extern "C" __declspec(dllimport) int __cdecl iswdigit(WideChar character);

// ?GadgetTextEntryValidateCharacter@@YA_NGC@Z
bool __cdecl GadgetTextEntryValidateCharacter(
	WideChar character, signed char flags)
{
	if (character >= 0xe01 && character <= 0xe3a)
		return false;
	if (character >= 0xe3f && character <= 0xe5b)
		return false;

	if ((flags & 0x80) == 0)
		goto noNegativeSpace;
	if (character == 0x20)
		return true;

noNegativeSpace:
	if ((flags & 1) && character == 0x20)
		return false;
	if ((flags & 2) && character == 0x25)
		return false;
	if (flags & 4)
	{
		if (character < 0x22 || character > 0x7e || character == 0x5c)
			return false;
	}
	if (flags & 8)
	{
		if (character == 0x2a || character == 0x3f || character == 0x3a ||
			character == 0x5c || character == 0x2f || character == 0x22 ||
			character == 0x3c || character == 0x3e || character == 0x7c)
			return false;
	}
	if ((flags & 0x10) && !iswascii(character))
		return false;
	if ((flags & 0x20) && !iswdigit(character))
		return false;
	if ((flags & 0x40) && !iswalnum(character))
		return false;

	return true;
}
