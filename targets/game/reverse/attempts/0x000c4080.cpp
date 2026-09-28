// ?rva000C4080@BFMEActionManager@@QAEEPBVObject@@0W4CommandSourceType@@@Z
// partial score=0.83 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
typedef int Int;
typedef unsigned char Bool;

class Object;
enum CommandSourceType { CMD_SRC_0 = 0 };

class RvaC4390First;
class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int allowLookup);
};

class ObjectIface
{
public:
	void *unidentified_001BFE20() const;
};

class RvaC4390VTable
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Bool slot27(void *arg);
};

class BFMEActionManager
{
public:
	Bool rva000C4080(const Object *a, const Object *b, CommandSourceType src);
};

Bool BFMEActionManager::rva000C4080(const Object *a, const Object *b, CommandSourceType src)
{
	if (a == 0 || b == 0)
		return false;
	RvaC4390First *ra = ((RvaC4390Second *)a)->resolve(0);
	RvaC4390First *rb = ((RvaC4390Second *)b)->resolve(0);
	if (ra == rb)
		return false;
	void *z;
	void *arg;
	if (ra != 0 && rb == 0) {
		z = ((ObjectIface *)ra)->unidentified_001BFE20();
		arg = (void *)b;
		if (z == 0)
			return false;
	} else {
		z = ((ObjectIface *)rb)->unidentified_001BFE20();
		arg = (void *)a;
		if (z == 0)
			return false;
	}
	return ((RvaC4390VTable *)z)->slot27(arg);
}
