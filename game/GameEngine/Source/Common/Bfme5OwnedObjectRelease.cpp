class Object {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class BfmeDestroyable
{
public:
	virtual void bfmeDestroy(int deleting);
};

BfmeDestroyable *bfmeFindModule(void);

class Gen_0028CF50
{
public:
	void bfmeRelease(void);

private:
	char m_bfmeFields[0x24];
	int m_bfmeObjectID;
};

// The caller passes the owner object through EAX, which this function reads directly.
__declspec(noinline) BfmeDestroyable *bfmeFindModule(void)
{
	__asm
	{
		mov esi, dword ptr [eax + 1F0h]
		mov eax, dword ptr [esi]
		test eax, eax
		je noModule
		align 16
	loopModules:
		mov edx, dword ptr [eax + 0Ch]
		lea ecx, [eax + 0Ch]
		call dword ptr [edx + 78h]
		test eax, eax
		jne foundModule
		mov eax, dword ptr [esi + 4]
		add esi, 4
		test eax, eax
		jne loopModules
	noModule:
		xor eax, eax
	foundModule:
	}
}

// ?bfmeRelease@Gen_0028CF50@@QAEXXZ
void Gen_0028CF50::bfmeRelease(void)
{
	if (m_bfmeObjectID != 0) {
		Object *object = TheGameLogic->findObjectByID(m_bfmeObjectID);
		if (object != 0) {
			BfmeDestroyable *module = bfmeFindModule();
			if (module != 0) {
				module->bfmeDestroy(0);
				TheGameLogic->destroyObject(object);
			}
		}
		m_bfmeObjectID = 0;
	}
}
