// cl: /DNDEBUG /MD /EHsc

// Base, vptr, a copied name, then twelve zeroed words.
//
// The order in the body is the order retail emits: the eleven words from 0xA0
// up, and only then the one at 0x9C. Member construction runs first and is fixed
// by declaration order, but these are body statements, so the source has to say
// them the way the bytes do.
//
// The zero lives in edi across all of it, which is also why the unwind state is
// stored as the four-byte register form rather than the eight-byte immediate --
// a difference that shows up in the function's total size, not in its shape.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	AsciiString(void);
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString(void);

private:
	char *m_data;
};

namespace FXParticleSystem
{

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemInfo
{
public:
	ParticleSystemInfo(void);

	virtual ~ParticleSystemInfo(void);

private:
	unsigned char m_pad[0x94];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const AsciiString &name);

private:
	AsciiString m_name;
	int m_slaveTemplate;
	void *m_a0[11];
};

// ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABVAsciiString@@@Z
ParticleSystemTemplate::ParticleSystemTemplate(const AsciiString &name) :
	m_name(name)
{
	m_a0[0] = 0;
	m_a0[1] = 0;
	m_a0[2] = 0;
	m_a0[3] = 0;
	m_a0[4] = 0;
	m_a0[5] = 0;
	m_a0[6] = 0;
	m_a0[7] = 0;
	m_a0[8] = 0;
	m_a0[9] = 0;
	m_a0[10] = 0;
	m_slaveTemplate = 0;
}

}
