// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ze
// Two BFME command-mask arrays are checked before a command is exposed.
// The helper is the retail bit-mask intersection thunk at ILT 0x003F18E.

extern void j_0003f18e();

struct BfmeCommandMaskOwner
{
	unsigned char m_pad000[0x188];
	unsigned int m_second[10];
	unsigned int m_first[10];
};

static bool testCommandMask(const void *maskObject, const unsigned int *mask)
{
	// VC7.1 rejects __thiscall in a free-function-pointer typedef.  A
	// single-inheritance pointer-to-member has the same one-word call target
	// here, while preserving ECX for the receiver and leaving the mask on the
	// stack.
	struct MaskCall
	{
		unsigned char call(const unsigned int *);
	};
	typedef unsigned char (MaskCall::*MaskCallFn)(const unsigned int *);
	union
	{
		void *asVoid;
		MaskCallFn asMember;
	} fnCast;
	fnCast.asVoid = reinterpret_cast<void *>(j_0003f18e);
	return (reinterpret_cast<MaskCall *>(const_cast<void *>(maskObject))->*
		fnCast.asMember)(mask);
}

// ?Rva004A3D50@@YAHPAUCommandMaskOwner@@0@Z
int __stdcall Rva004A3D50CommandMaskCheck(const BfmeCommandMaskOwner *object,
	const void *maskObject)
{
	unsigned int i = 0;
	const unsigned int *first;
	first = object->m_first;
	for (; i < 10; ++i, ++first)
	{
		if (*first != 0)
		{
			if (testCommandMask((const unsigned char *)maskObject + 0x110,
				object->m_first))
				return 3;
			break;
		}
	}

	for (i = 0; i < 10; ++i)
	{
		if (object->m_second[i] != 0)
		{
			if (testCommandMask((const unsigned char *)maskObject + 0x110,
				object->m_second))
				goto second_match;
			return 3;
		}
	}

	second_match:
	return 2;
}
