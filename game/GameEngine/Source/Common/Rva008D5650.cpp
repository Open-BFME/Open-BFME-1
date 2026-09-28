// cl: /O2
// Opaque identity: int3 at 0x008D5648..0x008D564F proves the start;
// mov eax,ecx; ret at 0x008D5650..0x008D5652, then int3 to 0x008D565F.
class Rva008D5650 {
public:
    Rva008D5650 *method();
};
Rva008D5650 *Rva008D5650::method() { return this; }
