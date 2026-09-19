// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: the 133-byte constructor at 0x00605270.  The parser immediately
// before this body builds one animation name, one audio-event reference, a
// frame value, and two ten-word model-condition masks before calling it.  The
// adjacent copy/destructor/comparison bodies establish the same 0x60-byte
// record: StringBase<char> at +0x00, an intrusive audio pointer at +0x04, the
// frame at +0x08, masks at +0x0c/+0x34, and a derived bool at +0x5c.

#include "Common/AsciiString.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

// BFME's AudioEventInfoRef is a one-word intrusive reference holder.  The
// referent carries its counter immediately after its vptr, at +4.
struct AudioEventInfoRef
{
	void *m_referent;
};

class ModelConditionFlags
{
public:
	bool any(void) const
	{
		for (unsigned int i = 0; i < 10; ++i)
			if (m_words[i] != 0)
				return true;
		return false;
	}

	unsigned int m_words[10];
};

class AnimationSoundInfo
{
public:
	AnimationSoundInfo(const AudioEventInfoRef &sound,
		const AsciiString &animation, float frame,
		const ModelConditionFlags &required,
		const ModelConditionFlags &excluded);

private:
	AsciiString m_animation;
	void *m_sound;
	float m_frame;
	ModelConditionFlags m_required;
	ModelConditionFlags m_excluded;
	unsigned char m_hasModelConditions;
};

// ??0AnimationSoundInfo@@QAE@ABUAudioEventInfoRef@@ABVAsciiString@@MABVModelConditionFlags@@2@Z
AnimationSoundInfo::AnimationSoundInfo(const AudioEventInfoRef &sound,
	const AsciiString &animation, float frame,
	const ModelConditionFlags &required,
	const ModelConditionFlags &excluded)
	: m_animation(animation)
{
	m_sound = sound.m_referent;
	if (m_sound != 0)
		InterlockedIncrement((long *)((char *)m_sound + 4));
	m_frame = frame;

	m_required = required;
	m_excluded = excluded;

	m_hasModelConditions = required.any() || excluded.any();
}
