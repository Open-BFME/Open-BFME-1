// cl: /DNDEBUG /MD /O2 /EHsc
// Re-homed from ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ so the 318B
// retail body at 0x00451460 can carry that name. This file keeps the 5-byte
// ILT trampoline as a tail call.

void b_00451460();

void j_000139e9()
{
	b_00451460();
}
