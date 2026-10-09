// Callees (tools/callees.py 0x1FCE70 55): ILT 0x44161 -> 0x0026F630
// Gen_0026F630::bfmeMatches, ILT 0xB627 -> 0x001FCD40
// AICommandInterface::bfmeCommand52 (source CMD_FROM_AI).
#include "../GameLogic/command_source_type.h"

class Object;
class BfmeThingEP;

class Gen_0026F630
{
public:
	bool bfmeMatches(const BfmeThingEP *thing) const;
};

class AICommandInterface
{
public:
	void bfmeCommand52(Object *obj, CommandSourceType cmdSource);
};

class BfmeItemGB;

class BfmeListGB
{
public:
	unsigned char m_bfmeHeadGB[0x20];
	unsigned char m_bfmeSubGB[4];
};

class BfmeCtxGB
{
public:
	unsigned char m_bfmeHeadGB[0x204];
	BfmeListGB *m_bfmeListGB;
};

class BfmeOwnerGB
{
public:
	void bfmeAddGB(BfmeCtxGB *ctx, int unused);

	unsigned char m_bfmeHeadGB[0xc];
	BfmeItemGB *m_bfmeItemGB;
};

void BfmeOwnerGB::bfmeAddGB(BfmeCtxGB *ctx, int unused)
{
	BfmeItemGB *item = m_bfmeItemGB;
	if (item == 0)
		return;

	if (ctx == 0)
		return;

	BfmeListGB *list = ctx->m_bfmeListGB;
	if (list == 0)
		return;

	if (reinterpret_cast<Gen_0026F630 *>(list)->bfmeMatches((const BfmeThingEP *)item))
		return;

	reinterpret_cast<AICommandInterface *>(list->m_bfmeSubGB)->bfmeCommand52((Object *)item, CMD_FROM_AI);
}
