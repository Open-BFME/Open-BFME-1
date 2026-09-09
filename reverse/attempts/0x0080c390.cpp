// _Rva0080C390
// partial score=0.85 date=2026-09-09
// cl: /DNDEBUG /MD /GX /Od /GZ /GS
//
// PARKED at 825/811 bytes. Standalone extract of the candidate added to
// Code/Libraries/Source/DirtySock/commudp.cpp (append, after CommUdpGive at
// EOF) -- re-apply there rather than compiling this file alone, since the
// callees below are genuinely declared in that TU already (memcpy/memset via
// <string.h>) and the Y4CommDigest.c / Y4MultiPrecision.c structs are
// duplicated here only for reference.

extern "C" {
	struct Rva00810060Context
	{
		unsigned int m_count;
		unsigned int m_state[4];
		unsigned char m_block[0x40];
	};
	void Rva00810020(struct Rva00810060Context *context);
	void Rva00810060(struct Rva00810060Context *context, const unsigned char *data, int length);
	void Rva00810FF0(struct Rva00810060Context *context, char *out, int outSize);

	struct Rva0080F200Rc4
	{
		unsigned char m_x;
		unsigned char m_y;
		unsigned char m_s[256];
	};
	void Rva0080F300(struct Rva0080F200Rc4 *state, unsigned char *data, int length);

	int Rva0080C390(void *ref, const void *data, int length);
}

// Retail 0x0080C390 (811 B, /Od /GZ). Assembles one reliable packet into the
// ring buffer at ref->+0x120 (a control block distinct from the plain queue
// above): reserves 4 header bytes, plus 16 more when a key is configured
// (+0x812c > 0) for an MD5 signature (Rva00810020/60/FF0, already landed in
// Y4CommDigest.c), copies the caller's payload, pads it out to the block size
// at +0x81b0 when one is set, signs (key +0x8130 length +0x812c, payload,
// then the big-endian +0x4008 sequence counter) into the reserved slot, RC4-
// enciphers the signature+payload+padding in place with the state embedded at
// +0x87be (Rva0080F300, Y4MultiPrecision.c), then writes a variable-length
// trailer backwards from the header boundary: an optional pad-count byte,
// then the two-byte total length with its top bit doubling as a "no padding /
// final" flag. Publishes the new header start/end at +0x00/+0x04 and bumps
// the sequence counter at +0x4008. Length is validated to [1, 0x3e80].
//
// PARKING NOTES (825/811, +14 bytes over, structurally exact -- frame size
// 0x88 matches, local slot order matches (od-frame-slots-follow-names: this
// compiler assigns slots in STRICT declaration order, first declared closest
// to ebp; "ctrl" and "pad" both had to move to the very end of the list,
// AFTER digestCtx/counterBytes, to land at their retail offsets -0x84/-0x88
// -- see the order below), padding formula fixed to read `length` not `pos`
// and to be ONE combined expression (two separate statements cost a spurious
// intermediate store retail does not have). Two residual mismatches, both
// near "and reg,0xff" sites retail has and this source does not reproduce
// without ALSO adding bytes elsewhere (tried explicit `& 0xff` on the
// counterBytes shifts and on the three trailer-byte stores -- each made the
// diff WORSE, 825->848->866, so something about how those two sites want the
// mask is more specific than "add the same cast everywhere"; likely needs the
// mask on one but not the other, or a differently-typed intermediate at just
// one of them). Untried: probe.py / docs/shape_levers.md per AGENTS.md for a
// 0.9+ near-miss; splitting the counter-byte block into its own nested scope
// (mirroring how "pad" needed its own late slot) in case it wants a similarly
// late slot rather than reusing counterBytes' position.
int Rva0080C390(void *ref, const void *data, int length)
{
	int totalLen;
	int hdrLen;
	int pos;
	int dataStart;
	int padCount;
	struct Rva00810060Context digestCtx;
	unsigned char counterBytes[4];
	char *ctrl;
	int pad;

	ctrl = *(char **)((char *)ref + 0x120);

	if (length < 1 || length > 0x3e80)
		return -1;

	pos = 4;
	hdrLen = pos;
	if (*(int *)(ctrl + 0x812c) > 0)
		pos += 0x10;
	dataStart = pos;
	memcpy(ctrl + pos + 8, data, length);
	pos += length;

	if (*(int *)(ctrl + 0x81b0) > 0)
	{
		pad = (*(int *)(ctrl + 0x81b0) - length % *(int *)(ctrl + 0x81b0))
			% *(int *)(ctrl + 0x81b0);
	}
	else
	{
		pad = 0;
	}
	padCount = pad;
	memset(ctrl + pos + 8, 0, padCount);
	pos += padCount;

	if (*(int *)(ctrl + 0x812c) > 0)
	{
		counterBytes[0] = (unsigned char)(*(unsigned int *)(ctrl + 0x4008) >> 24);
		counterBytes[1] = (unsigned char)(*(unsigned int *)(ctrl + 0x4008) >> 16);
		counterBytes[2] = (unsigned char)(*(unsigned int *)(ctrl + 0x4008) >> 8);
		counterBytes[3] = (unsigned char)*(unsigned int *)(ctrl + 0x4008);

		Rva00810020(&digestCtx);
		Rva00810060(&digestCtx, (unsigned char *)(ctrl + 0x8130), *(int *)(ctrl + 0x812c));
		Rva00810060(&digestCtx, (unsigned char *)(ctrl + dataStart + 8), pos - dataStart);
		Rva00810060(&digestCtx, counterBytes, 4);
		Rva00810FF0(&digestCtx, ctrl + hdrLen + 8, 0x10);
	}

	totalLen = pos - hdrLen;

	if (*(int *)(ctrl + 0x812c) > 0)
		Rva0080F300((struct Rva0080F200Rc4 *)(ctrl + 0x87be),
			(unsigned char *)(ctrl + hdrLen + 8), totalLen);

	if (padCount > 0)
		*(unsigned char *)(ctrl + --hdrLen + 8) = (unsigned char)padCount;
	*(unsigned char *)(ctrl + --hdrLen + 8) = (unsigned char)totalLen;
	*(unsigned char *)(ctrl + --hdrLen + 8) = (unsigned char)(totalLen >> 8);
	if (padCount == 0)
		*(unsigned char *)(ctrl + hdrLen + 8) |= 0x80;

	*(int *)ctrl = hdrLen;
	*(int *)(ctrl + 4) = pos;
	++*(unsigned int *)(ctrl + 0x4008);

	return 0;
}
