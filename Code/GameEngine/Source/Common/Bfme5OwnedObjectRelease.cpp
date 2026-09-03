class Object {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
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
