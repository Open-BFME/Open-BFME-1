// cl: /EHsc
//
// This translation unit owns one anonymous MSVC 7.1 constructor-cleanup body.
// Retail 0x00C4C3E8 is an Unwind@ boundary with no recoverable standalone
// parent identity.  The body is the compiler's vector-destructor cleanup for
// W3DPropBuffer's 4000 entries (0x30 bytes each) after its Snapshot base.
// These absent-from-retail stand-ins preserve that clean compiler machinery;
// only the compiler-local `$L` body is claimed below.

extern void w3d_prop_buffer_unwind_ext();

class GenW3DPropBufferBase
{
public:
	GenW3DPropBufferBase();
	virtual ~GenW3DPropBufferBase();
};

struct GenW3DPropBufferEntry
{
	GenW3DPropBufferEntry();
	~GenW3DPropBufferEntry();
	char payload[0x30];
};

class GenW3DPropBufferHost : public GenW3DPropBufferBase
{
public:
	GenW3DPropBufferHost();
	GenW3DPropBufferEntry props[4000];
};

// ??0GenW3DPropBufferHost@@QAE@XZ absent-from-retail
GenW3DPropBufferHost::GenW3DPropBufferHost()
{
	w3d_prop_buffer_unwind_ext();
}
