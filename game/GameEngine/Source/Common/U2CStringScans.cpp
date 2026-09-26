// Two relocation-free scans over a NUL-terminated buffer.
//
// 0x0084E030 walks the buffer in place: a digit is replaced by its VALUE
// (`sub al,'0'`) and the cursor advances, a ';' is DELETED by shifting the rest
// of the string down one byte with the cursor left where it is, and anything
// else is skipped.  The shift is written out rather than called, and its two
// loads of q[1] per iteration -- one to store, one to test -- are what a
// `while (*q) { *q = q[1]; ++q; }` compiles to: the store invalidates the
// compiler's copy of the value the loop condition then re-reads.  `this`
// arrives in ecx and is used directly as the char pointer, so the buffer is the
// object.
//
// 0x00850790 is a string hash with a rolling five-bit rotation:
//
//     rot = ((unsigned char)*s + rot) & 31;  h ^= 1 << rot;
//
// The character is zero-extended (`xor edx,edx / mov dl,[esi]`), so it is read
// as unsigned; the shift count lives in cl and the accumulator in eax, and both
// start at zero.  It is a free function taking one argument, not a member.
//
// Identity is not recovered; both names are derived from an address.

class Rva0084E030Buffer
{
public:
	void squash();

	char m_chars[1];
};

void Rva0084E030Buffer::squash()
{
	char *p = m_chars;
	while (*p)
	{
		if (*p >= '0' && *p <= '9')
		{
			*p = (char)(*p - '0');
			++p;
		}
		else if (*p == ';')
		{
			char *q = p;
			while (*q)
			{
				*q = q[1];
				++q;
			}
		}
		else
		{
			++p;
		}
	}
}

unsigned int Rva00850790Hash(const char *s)
{
	unsigned int h = 0;
	unsigned int rot = 0;
	while (*s)
	{
		rot = ((unsigned char)*s + rot) & 31;
		h ^= (1 << rot);
		++s;
	}
	return h;
}
