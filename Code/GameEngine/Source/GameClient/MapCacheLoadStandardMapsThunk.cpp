// cl: /DNDEBUG /MD /O2 /EHsc
// Re-homed from ?loadStandardMaps@MapCache@@AAEXXZ so the 234B retail body
// at 0x004507A0 can carry that name. This file keeps the 5-byte ILT
// trampoline as a tail call.

void b_004507a0();

void j_000359db()
{
	b_004507a0();
}
