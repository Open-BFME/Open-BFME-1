// cl: /O2 /Ob0
//
// RVA-derived predicate object (ctor at 0x001DCE00 installs vft 0x0109FB64,
// stores an Object* at +8 and a skip-iterate flag at +0xC). Neighbour
// Gen_001DD040 shares the +8/+0xC layout.
//
// Object+0x1FC is m_contain (Object.cpp). Slot +8 is a bool query; slot +0xFC
// is iterateContained(func, user, reverse). Callback 0x001DCF20 is a sibling
// helper not converted here.

class Object;
class ContainModuleInterface;

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

struct ContainV0
{
	virtual void s00();
	virtual void s01();
	virtual bool query08();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s0a();
	virtual void s0b();
	virtual void s0c();
	virtual void s0d();
	virtual void s0e();
	virtual void s0f();
};

struct ContainV1 : ContainV0
{
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s1a();
	virtual void s1b();
	virtual void s1c();
	virtual void s1d();
	virtual void s1e();
	virtual void s1f();
};

struct ContainV2 : ContainV1
{
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s2a();
	virtual void s2b();
	virtual void s2c();
	virtual void s2d();
	virtual void s2e();
	virtual void s2f();
};

class ContainModuleInterface : public ContainV2
{
public:
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s3a();
	virtual void s3b();
	virtual void s3c();
	virtual void s3d();
	virtual void s3e();
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
};

class Object
{
public:
	bool bfmeCheckC80F0();
	bool isNonFactionStructure() const;

	char m_pad[0x1FC];
	ContainModuleInterface *m_contain;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_SCRIPT = 2
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource, CanEnterType mode, bool *out);
};

extern BFMEActionManager *TheActionManager;

void iterRel001DCF20(Object *obj, void *userData);

struct IterUser001DCF50
{
	Object *obj;
	unsigned char flag;
};

class Gen_001DCF50
{
public:
	unsigned char canEnter(Object *target);

private:
	void *m_vptr;
	int m_04;
	Object *m_obj;
	unsigned char m_flag;
};

unsigned char Gen_001DCF50::canEnter(Object *target)
{
	Object *obj = target;
	if (obj->bfmeCheckC80F0())
	{
		if (obj->isNonFactionStructure())
		{
			ContainModuleInterface *contain = obj->m_contain;
			if (contain)
			{
				if (contain->query08())
				{
					if (TheActionManager->canEnterObject(m_obj, obj, CMD_FROM_SCRIPT, CHECK_CAPACITY, 0))
					{
						if (m_flag)
							return true;

						IterUser001DCF50 user;
						user.flag = 0;
						user.obj = m_obj;
						contain->iterateContained(iterRel001DCF20, &user, true);
						return user.flag == 0;
					}
				}
			}
		}
	}
	return false;
}
