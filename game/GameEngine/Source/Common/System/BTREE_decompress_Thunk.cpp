// cl: /DNDEBUG /Igame/Libraries/Source/Compression/EAC

#include "codex.h"

struct BTreeDecodeContext
{
	signed char cluetbl[256];
	unsigned char left[256];
	unsigned char right[256];
	unsigned char *d;
};

static void BTREE_chase(BTreeDecodeContext *dc, unsigned char node)
{
	if (dc->cluetbl[node]) {
		BTREE_chase(dc, dc->left[node]);
		BTREE_chase(dc, dc->right[node]);
		return;
	}
	*dc->d++ = node;
}

static int BTREE_decompress(unsigned char *packbuf, unsigned char *unpackbuf)
{
	int node;
	int i;
	int nodes;
	int clue;
	int ulen;
	unsigned char *s;
	signed char c;
	unsigned int type;
	BTreeDecodeContext dc;

	s = packbuf;
	dc.d = unpackbuf;
	ulen = 0;

	if (s) {
		type = ggetm(s, 2);
		s += 2;
		if (type == 0x47fb)
			s += 3;
		ulen = ggetm(s, 3);
		s += 3;

		for (i = 0; i < 256; ++i)
			dc.cluetbl[i] = 0;

		clue = *s++;
		dc.cluetbl[clue] = 1;
		nodes = *s++;
		for (i = 0; i < nodes; ++i) {
			node = *s++;
			dc.left[node] = *s++;
			dc.right[node] = *s++;
			dc.cluetbl[node] = -1;
		}

		for (;;) {
			node = *s++;
			c = dc.cluetbl[node];
			if (!c) {
				*dc.d++ = (unsigned char)node;
				continue;
			}
			if (c < 0) {
				BTREE_chase(&dc, dc.left[node]);
				BTREE_chase(&dc, dc.right[node]);
				continue;
			}
			node = *s++;
			if (node) {
				*dc.d++ = (unsigned char)node;
				continue;
			}
			break;
		}
	}
	return ulen;
}

int __cdecl BTREE_decode(void *dest, const void *compresseddata, int *)
{
	return BTREE_decompress((unsigned char *)compresseddata, (unsigned char *)dest);
}
