// ?releasePair@@YAXXZ
struct Rva008A4AC0Object { virtual void slot0(); virtual void release(); };
extern Rva008A4AC0Object* Rva008A4AC0First;
extern Rva008A4AC0Object* Rva008A4AC0Second;
void releasePair()
{
	if (Rva008A4AC0First) { Rva008A4AC0First->release(); Rva008A4AC0First = 0; }
	if (Rva008A4AC0Second) { Rva008A4AC0Second->release(); Rva008A4AC0Second = 0; }
}
