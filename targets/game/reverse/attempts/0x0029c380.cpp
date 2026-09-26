// ?d_0029c380@@YAXXZ
// partial score=0.5675675676 date=2026-09-25
// cl: /ICode/GameEngine/Source/GameLogic/Object
class Rva000FA8B0Key;
class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "object.h"
// Retail 0x0029C380 returns the current record from an embedded iterator.
struct Rva0029C380Record
{
	unsigned char m_pad00[4];
	unsigned int m_type;
	Rva000FA8B0Key *m_word08;
	unsigned char m_pad0c[4];
	int m_word10;
};

class Rva0029C380Embedded
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual Rva0029C380Record *slot48();
	virtual Rva0029C380Record *slot4C(Rva0029C380Record *record);
};

class Rva000FA8B0Owner {
public:
 int find(Rva000FA8B0Key *, int);
 float evaluate(int);
};
extern float g_bfmeDefaultBU;

class Rva0029C380
{
public:
	unsigned char m_pad00[8];
	Object *m_related08;
	unsigned char m_pad0c[0x14];
	Rva0029C380Embedded m_embedded;
	unsigned char m_pad24[4];
	void *m_pad28;

	Rva0029C380Record *getRecord();
};

Rva0029C380Record *Rva0029C380::getRecord()
{
	Rva0029C380Record *record = m_embedded.slot48();
	while (record != 0)
	{
		if (record->m_type == 3)
		{
			Player *player = m_related08->getControllingPlayer();
			Rva000FA8B0Owner *helper = reinterpret_cast<Rva000FA8B0Owner *>(
				reinterpret_cast<char *>(player) + 0x684);
			int index = helper->find(record->m_word08, record->m_word10);
			float value = helper->evaluate(index);
			if (value >= g_bfmeDefaultBU)
				return record;
		}
		record = m_embedded.slot4C(record);
	}
	return reinterpret_cast<Rva0029C380Record *>(m_pad28);
}
