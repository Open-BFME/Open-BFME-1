// Open-BFME5: clean C++ conversion of the stdcall-to-cdecl adapter.

class Rva008AF650Object;
class BfmeStrVKI;
class AptValue;

bool rva008AF650Implementation(
	Rva008AF650Object *object, BfmeStrVKI *key, AptValue *value);

void __stdcall rva008C3E70Adapter(int first, int second, int third)
{
	rva008AF650Implementation(
		reinterpret_cast<Rva008AF650Object *>(first),
		reinterpret_cast<BfmeStrVKI *>(second),
		reinterpret_cast<AptValue *>(third));
}
