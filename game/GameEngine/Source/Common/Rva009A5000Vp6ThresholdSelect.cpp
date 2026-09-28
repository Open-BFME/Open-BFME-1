// _bfmeVp6ThresholdSelect
// Retail boundary 0x009A5000 through 0x009A5193 inclusive.
// Names retained from the preferred stash; descriptive labels are not original symbols.
// Retail 0x009A5000, 404 bytes. A VP6 codec-context threshold selector,
// called only by the adjacent VP6 decode-frame routine at 0x009A51A0 (still
// unmatched). Pure integer/state-machine body: no virtual calls, no STL, no
// x87 -- every branch is an integer compare or a constant-divisor magic
// multiply (imul by a literal, mul by 0x51eb851f, shr 5; the standard MSVC
// idiom for `(unsigned)(v*K) / 100u`). __cdecl, one context pointer
// argument (mov ecx,[esp+4] at entry, before any push, rules out thiscall).

struct BfmeVp6Context
{
	char pad_to_1a0[ 0x1a0 ];
	int m1a0;
	char pad_1a4_1a8[ 0x1a8 - 0x1a4 ];
	int m1a8;
	char pad_1ac_910[ 0x910 - 0x1ac ];
	int m910;
	int m914;
	// Modes 4/5/6/8 address the threshold slots through the same array.
	union {
		int m918[11];
		struct {
			char pad_918_928[0x10];
			int m928;
			int m92c;
			int m930;
			char pad_934_938[0x4];
			int m938;
			char pad_93c_940[0x4];
			int m940;
		};
	};
};

extern "C" int __cdecl bfmeVp6ThresholdSelect( BfmeVp6Context *ctx )
{
	unsigned int idx = (unsigned int)ctx->m1a0;
	int arrayVal = ctx->m918[ idx ];
	int edxv = ctx->m940;
	int thresholdD = ctx->m938;
	int b = ctx->m914;
	int a = ctx->m910;
	a += thresholdD;
	a += edxv;
	b += edxv;
	arrayVal += a;

	if( ctx->m930 == 0 )
		ctx->m930 = b >> 1;
	if( ctx->m92c == 0 )
		ctx->m92c = b >> 1;
	if( ctx->m928 == 0 )
		ctx->m928 = b >> 2;
	if( thresholdD == 0 )
		ctx->m938 = b >> 3;

	int scale = ctx->m1a8;
    if (scale == 0) return idx;

 unsigned limit = (unsigned)(scale * 0x7918) / 100u;
 if (arrayVal > (int)limit) goto high;

	{
		unsigned int scaled1 = (unsigned int)( scale * 0x7530 );
		unsigned int lim1 = scaled1 / 100u;
		if( arrayVal < (int)lim1 )
		{
			unsigned int scaled2 = (unsigned int)( scale * 0x6d60 );
			unsigned int lim2 = scaled2 / 100u;
			if( arrayVal > (int)lim2 )
				return idx;
		}
	}

	{
		unsigned int scaled3 = (unsigned int)( scale * 0x6d60 );
		unsigned int lim = scaled3 / 100u;
		if( (unsigned)( ctx->m930 + b ) < lim )
			return 6;
		if( (unsigned)( ctx->m92c + b ) < lim )
			return 5;
		if( (unsigned)( ctx->m928 + b ) < lim )
			return 4;
		return ( (unsigned)( ctx->m938 + b ) < lim ) ? 8 : 0;
	}
high:
			ctx->m914 = ctx->m910;
			if( (unsigned)( ctx->m930 + a ) < limit )
				return 6;
			if( (unsigned)( ctx->m92c + a ) < limit )
				return 5;
			if( (unsigned)( ctx->m928 + a ) < limit )
				return 4;
			return ( (unsigned)( ctx->m938 + a ) < limit ) ? 8 : 0;
}
