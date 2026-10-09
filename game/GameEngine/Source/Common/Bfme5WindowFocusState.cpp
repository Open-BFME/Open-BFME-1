struct BfmeWindowNode
{
	char m_bfmeFields[0x70];
	int m_bfmeFocus;
};

struct BfmeWindowResult
{
	char m_bfmeFields[0x20];
	int m_bfmeValue;
};

class BfmeWindowManager
{
public:
	void bfmeClear(int *focus);
	void bfmeSet(int *focus);
};

class CollisionManager;
extern CollisionManager *TheCollisionManager;


class Gen_0028B810
{
public:
	int bfmeUpdate(void);

private:
	char m_bfmeFields[0x14];
	unsigned char m_bfmeActive;
	unsigned char m_bfmePending;
};

// The two window-focus entry points the class above calls live at
// 0x009A2590/0x009A25A0. Retail bodies there are 8-byte thiscall forwarders:
//   mov ecx, [ecx+0Ch] ; jmp <0x009A29A0 / 0x009A36F0>
// i.e. they reload `this` from the CollisionManager's +0xC member and tail-jump
// to the owner whose setter/apply is already matched:
//   ?set@Rva009A29A0WindowManager@@QAEXPAURva009A29A0Window@@@Z (0x009A29A0)
//   ?apply@Rva009A36F0Owner@@QAEXPAVRva009A36F0Param@@@Z      (0x009A36F0)
// Their types have no shared header (they are .cpp-local in
// Rva009A29A0WindowManagerSet.cpp and collisionmanager_impl.cpp), so declare
// them TU-locally with the tags their ledger names require.
struct Rva009A29A0Window;
class Rva009A29A0WindowManager
{
public:
	void set(Rva009A29A0Window *window);
};

class Rva009A36F0Param;
class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
};

// ?bfmeUpdate@Gen_0028B810@@QAEHXZ
int Gen_0028B810::bfmeUpdate(void)
{
	if (m_bfmeActive) {
		if ((*reinterpret_cast<BfmeWindowManager **>(&TheCollisionManager)) != 0) {
			BfmeWindowNode *node = *reinterpret_cast<BfmeWindowNode **>(
				reinterpret_cast<char *>(this) - 8);
			int *focus = node != 0 ? &node->m_bfmeFocus : 0;
			(*reinterpret_cast<BfmeWindowManager **>(&TheCollisionManager))->bfmeClear(focus);
		}

		m_bfmeActive = 0;
		m_bfmePending = 0;
		BfmeWindowResult *result = *reinterpret_cast<BfmeWindowResult **>(
			reinterpret_cast<char *>(this) - 12);
		return result->m_bfmeValue;
	}

	if (!m_bfmePending && (*reinterpret_cast<BfmeWindowManager **>(&TheCollisionManager)) != 0) {
		BfmeWindowNode *node = *reinterpret_cast<BfmeWindowNode **>(
			reinterpret_cast<char *>(this) - 8);
		int *focus = node != 0 ? &node->m_bfmeFocus : 0;
		(*reinterpret_cast<BfmeWindowManager **>(&TheCollisionManager))->bfmeSet(focus);
	}

	return 1;
}

// Out-of-line definitions of the two forwarders the caller above names. Each is
// the retail 8-byte delegate (reload this from +0xC, tail-jump to the matched
// owner), so the caller keeps emitting `push focus; call <forwarder>` and the
// link finds a definition for the pinned symbols.
void __declspec(noinline) BfmeWindowManager::bfmeClear(int *focus)
{
	((Rva009A36F0Owner *)*(void **)((char *)this + 0xC))->apply(
		(Rva009A36F0Param *)focus);
}

void __declspec(noinline) BfmeWindowManager::bfmeSet(int *focus)
{
	((Rva009A29A0WindowManager *)*(void **)((char *)this + 0xC))->set(
		(Rva009A29A0Window *)focus);
}
