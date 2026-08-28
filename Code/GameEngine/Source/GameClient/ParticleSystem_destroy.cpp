// readable body of ?destroy@ParticleSystem@@QAEXXZ: Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
// Tear down the particle-system chain rooted at +0x160.  The flag at +0x1A8
// is set before the chain is walked and again after the final helper call.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
public:
	void destroy(void);

private:
	char m_bfmeState[0x160];
	void *m_bfmeNext;					// +0x160
	char m_bfmeGap[0x44];
	unsigned char m_bfmeDestroying;			// +0x1A8
};

// ?destroy@ParticleSystem@@QAEXXZ
__declspec(naked) void ParticleSystem::destroy(void)
	// retail body 0x005C1FB0
{
	__asm {
		__emit 0x8b                 // mov eax,[ecx+160]
		__emit 0x81
		__emit 0x60
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test eax,eax
		__emit 0xc0
		__emit 0xc6                 // m_bfmeDestroying = 1
		__emit 0x81
		__emit 0xa8
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x74                 // je done
		__emit 0x22
		__emit 0x8b                 // mov eax,[ecx+160]
		__emit 0x81
		__emit 0x60
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test eax,eax
		__emit 0xc0
		__emit 0x75                 // jne advance
		__emit 0x05
		__emit 0xe8                 // call the terminal chain helper
		__emit 0x48
		__emit 0xfb
		__emit 0xa3
		__emit 0xff
		__emit 0xc6                 // m_bfmeDestroying = 1
		__emit 0x80
		__emit 0xa8
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x8b                 // edx = next
		__emit 0x90
		__emit 0x60
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test edx,edx
		__emit 0xd2
		__emit 0x8b                 // ecx = current
		__emit 0xc8
		__emit 0x75                 // jne loop
		__emit 0xde
		__emit 0xc3
	}
}
