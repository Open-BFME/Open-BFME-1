// ?updateAudioFlags@Rva005A00B0Owner@@QAEXXZ
// stlport
#include <list>
struct Rva005A00B0Transition { char m_pad[0x30]; int m_pending; };
struct Rva005A00B0AudioClient {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void setFlagVolume(float volume, int mask);
};
extern Rva005A00B0Transition* TheTransitionHandler;
extern Rva005A00B0AudioClient* TheAudioClientUpdate;
class GameWindowTransitionsHandler
{
public:
	void rva0048B690(void *destination);
};

struct Rva0059FF70Group
{
	char m_pad[0x18];
	unsigned int m_flags;
	char m_pad1[4];
	float m_volume;
};

class Rva0059FF70Track
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Rva0059FF70Group *rva0059FF70Group();
};

struct Rva0059FF70Window
{
	char m_pad[0x10];
	Rva0059FF70Track *m_track;
};

float __cdecl Rva005A00B0FlagVolume(int index)
{
	unsigned int mask = 1 << index;
	float volume = 1.0f;
	if (TheTransitionHandler) {
		_STL::list<Rva0059FF70Window *> windows;
		reinterpret_cast<GameWindowTransitionsHandler *>(TheTransitionHandler)->rva0048B690(&windows);
		for (_STL::list<Rva0059FF70Window *>::iterator it = windows.begin();
			it != windows.end(); ++it) {
			Rva0059FF70Window *window = *it;
			if (window && window->m_track) {
				Rva0059FF70Group *group = window->m_track->rva0059FF70Group();
				if (group && (group->m_flags & mask))
					volume *= group->m_volume;
			}
		}
	}
	return volume;
}

struct Rva005A00B0Owner { char m_pad[0x18]; int m_flags; void updateAudioFlags(); };
void Rva005A00B0Owner::updateAudioFlags()
{
	if (TheTransitionHandler && TheTransitionHandler->m_pending <= 0) {
		for (int i = 0; i < 3; ++i) {
			int mask = 1 << i;
			if (m_flags & mask) {
				float volume = Rva005A00B0FlagVolume(i);
				TheAudioClientUpdate->setFlagVolume(volume, mask);
			}
		}
	}
}

// ?Rva005A0130SetAllFlagVolumes@@YAXXZ
void Rva005A0130SetAllFlagVolumes()
{
	for (int i = 0; i < 3; ++i) {
		float volume = Rva005A00B0FlagVolume(i);
		TheAudioClientUpdate->setFlagVolume(volume, 1 << i);
	}
}
