// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The packet CRC, 0x00065250, 42 bytes.
//
// Same accumulation the engine's CRC class uses -- rotate the running value left
// by one and add the byte -- but as a free function taking and returning the
// running value rather than as a method on a CRC object, which is why it has no
// counterpart in the reference. The name is this tree's; retail carries no
// symbol for it.
//
// It is one of the two things 0x00683830 does to a packet, the other being the
// rolling-XOR pass at 0x006832C0.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

// The carry bit has to be written as a branch, exactly as the engine's own CRC
// class writes it, even though MSVC compiles it to a shift either way. Written
// as `crc >> 31` the compiler folds the byte and the carry together and adds
// crc*2 last; written as the branch it keeps retail's order, adding the byte to
// crc*2 first and the carry after.
UnsignedInt BFMEComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc)
{
	if (data != 0) {
		while (length > 0) {
			Int carryBit;
			if (crc & 0x80000000) {
				carryBit = 1;
			} else {
				carryBit = 0;
			}
			crc <<= 1;
			crc += *data;
			++data;
			crc += carryBit;
			--length;
		}
	}

	return crc;
}
