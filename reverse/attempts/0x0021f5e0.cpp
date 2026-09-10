// ?addValidObjectsToGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.45 date=2026-09-09
// Complete BFME reconstruction bank for retail RVA 0x0021F5E0, size 489.
// The surrounding TU supplies Object, Weapon, AIUpdateInterface, GarrisonContain,
// BfmeGarrisonFirePointInterface, BfmeGarrisonFindClosestCall, and
// BfmeGarrisonPlacementCall.  These views are TU-local in the production probe.
// Identity: full Ghidra boundary FUN_0061F5E0 (489 bytes), with the named direct
// caller GarrisonContain::update at 0x0021F920 and the real source definition.

struct BfmeGarrisonContainedNode
{
	BfmeGarrisonContainedNode *next;
	BfmeGarrisonContainedNode *previous;
	Object *object;
};

class BfmeGarrisonHordeContainInterface;

class BfmeGarrisonContainModuleInterface
{
public:
#define BFME_GARRISON_CONTAIN_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_CONTAIN_SLOT(00); BFME_GARRISON_CONTAIN_SLOT(01);
	BFME_GARRISON_CONTAIN_SLOT(02); BFME_GARRISON_CONTAIN_SLOT(03);
	BFME_GARRISON_CONTAIN_SLOT(04); BFME_GARRISON_CONTAIN_SLOT(05);
	BFME_GARRISON_CONTAIN_SLOT(06); BFME_GARRISON_CONTAIN_SLOT(07);
	BFME_GARRISON_CONTAIN_SLOT(08); BFME_GARRISON_CONTAIN_SLOT(09);
	BFME_GARRISON_CONTAIN_SLOT(10); BFME_GARRISON_CONTAIN_SLOT(11);
	BFME_GARRISON_CONTAIN_SLOT(12); BFME_GARRISON_CONTAIN_SLOT(13);
	BFME_GARRISON_CONTAIN_SLOT(14); BFME_GARRISON_CONTAIN_SLOT(15);
	BFME_GARRISON_CONTAIN_SLOT(16); BFME_GARRISON_CONTAIN_SLOT(17);
	BFME_GARRISON_CONTAIN_SLOT(18); BFME_GARRISON_CONTAIN_SLOT(19);
	BFME_GARRISON_CONTAIN_SLOT(20); BFME_GARRISON_CONTAIN_SLOT(21);
	BFME_GARRISON_CONTAIN_SLOT(22); BFME_GARRISON_CONTAIN_SLOT(23);
	BFME_GARRISON_CONTAIN_SLOT(24); BFME_GARRISON_CONTAIN_SLOT(25);
	virtual BfmeGarrisonHordeContainInterface *getHordeContainInterface() = 0;
#undef BFME_GARRISON_CONTAIN_SLOT
};

class BfmeGarrisonHordeContainInterface
{
public:
#define BFME_GARRISON_HORDE_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_HORDE_SLOT(00); BFME_GARRISON_HORDE_SLOT(01);
	BFME_GARRISON_HORDE_SLOT(02); BFME_GARRISON_HORDE_SLOT(03);
	BFME_GARRISON_HORDE_SLOT(04); BFME_GARRISON_HORDE_SLOT(05);
	BFME_GARRISON_HORDE_SLOT(06); BFME_GARRISON_HORDE_SLOT(07);
	BFME_GARRISON_HORDE_SLOT(08); BFME_GARRISON_HORDE_SLOT(09);
	BFME_GARRISON_HORDE_SLOT(10); BFME_GARRISON_HORDE_SLOT(11);
	BFME_GARRISON_HORDE_SLOT(12); BFME_GARRISON_HORDE_SLOT(13);
	BFME_GARRISON_HORDE_SLOT(14); BFME_GARRISON_HORDE_SLOT(15);
	BFME_GARRISON_HORDE_SLOT(16); BFME_GARRISON_HORDE_SLOT(17);
	BFME_GARRISON_HORDE_SLOT(18); BFME_GARRISON_HORDE_SLOT(19);
	BFME_GARRISON_HORDE_SLOT(20); BFME_GARRISON_HORDE_SLOT(21);
	BFME_GARRISON_HORDE_SLOT(22); BFME_GARRISON_HORDE_SLOT(23);
	BFME_GARRISON_HORDE_SLOT(24); BFME_GARRISON_HORDE_SLOT(25);
	BFME_GARRISON_HORDE_SLOT(26); BFME_GARRISON_HORDE_SLOT(27);
	BFME_GARRISON_HORDE_SLOT(28); BFME_GARRISON_HORDE_SLOT(29);
	BFME_GARRISON_HORDE_SLOT(30); BFME_GARRISON_HORDE_SLOT(31);
	BFME_GARRISON_HORDE_SLOT(32); BFME_GARRISON_HORDE_SLOT(33);
	BFME_GARRISON_HORDE_SLOT(34); BFME_GARRISON_HORDE_SLOT(35);
	BFME_GARRISON_HORDE_SLOT(36); BFME_GARRISON_HORDE_SLOT(37);
	BFME_GARRISON_HORDE_SLOT(38); BFME_GARRISON_HORDE_SLOT(39);
	BFME_GARRISON_HORDE_SLOT(40); BFME_GARRISON_HORDE_SLOT(41);
	BFME_GARRISON_HORDE_SLOT(42); BFME_GARRISON_HORDE_SLOT(43);
	BFME_GARRISON_HORDE_SLOT(44); BFME_GARRISON_HORDE_SLOT(45);
	BFME_GARRISON_HORDE_SLOT(46); BFME_GARRISON_HORDE_SLOT(47);
	BFME_GARRISON_HORDE_SLOT(48); BFME_GARRISON_HORDE_SLOT(49);
	BFME_GARRISON_HORDE_SLOT(50); BFME_GARRISON_HORDE_SLOT(51);
	BFME_GARRISON_HORDE_SLOT(52); BFME_GARRISON_HORDE_SLOT(53);
	BFME_GARRISON_HORDE_SLOT(54); BFME_GARRISON_HORDE_SLOT(55);
	BFME_GARRISON_HORDE_SLOT(56); BFME_GARRISON_HORDE_SLOT(57);
	BFME_GARRISON_HORDE_SLOT(58);
	virtual _STL::list<Object *> &getMemberList() = 0;
#undef BFME_GARRISON_HORDE_SLOT
};

class BfmeGarrisonObjectLayout
{
public:
	unsigned char m_unmodelled_000[0x74];
	UnsignedInt m_id;
	unsigned char m_unmodelled_078[0x1c];
	unsigned char m_status94;
	unsigned char m_unmodelled_095[0x1fc - 0x95];
	BfmeGarrisonContainModuleInterface *m_contain;
	unsigned char m_unmodelled_200[4];
	AIUpdateInterface *m_ai;
};

struct BfmeGarrisonStatusTriple
{
	UnsignedInt first;
	UnsignedInt second;
	UnsignedInt third;
};

class BfmeGarrisonStatusInterface
{
public:
#define BFME_GARRISON_STATUS_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_STATUS_SLOT(00); BFME_GARRISON_STATUS_SLOT(01);
	BFME_GARRISON_STATUS_SLOT(02); BFME_GARRISON_STATUS_SLOT(03);
	BFME_GARRISON_STATUS_SLOT(04); BFME_GARRISON_STATUS_SLOT(05);
	BFME_GARRISON_STATUS_SLOT(06); BFME_GARRISON_STATUS_SLOT(07);
	BFME_GARRISON_STATUS_SLOT(08); BFME_GARRISON_STATUS_SLOT(09);
	BFME_GARRISON_STATUS_SLOT(10); BFME_GARRISON_STATUS_SLOT(11);
	BFME_GARRISON_STATUS_SLOT(12); BFME_GARRISON_STATUS_SLOT(13);
	BFME_GARRISON_STATUS_SLOT(14); BFME_GARRISON_STATUS_SLOT(15);
	BFME_GARRISON_STATUS_SLOT(16); BFME_GARRISON_STATUS_SLOT(17);
	BFME_GARRISON_STATUS_SLOT(18); BFME_GARRISON_STATUS_SLOT(19);
	BFME_GARRISON_STATUS_SLOT(20); BFME_GARRISON_STATUS_SLOT(21);
	BFME_GARRISON_STATUS_SLOT(22); BFME_GARRISON_STATUS_SLOT(23);
	BFME_GARRISON_STATUS_SLOT(24); BFME_GARRISON_STATUS_SLOT(25);
	BFME_GARRISON_STATUS_SLOT(26); BFME_GARRISON_STATUS_SLOT(27);
	BFME_GARRISON_STATUS_SLOT(28); BFME_GARRISON_STATUS_SLOT(29);
	BFME_GARRISON_STATUS_SLOT(30); BFME_GARRISON_STATUS_SLOT(31);
	BFME_GARRISON_STATUS_SLOT(32); BFME_GARRISON_STATUS_SLOT(33);
	BFME_GARRISON_STATUS_SLOT(34); BFME_GARRISON_STATUS_SLOT(35);
	BFME_GARRISON_STATUS_SLOT(36); BFME_GARRISON_STATUS_SLOT(37);
	BFME_GARRISON_STATUS_SLOT(38);
	virtual BfmeGarrisonStatusTriple getStatus(Object *object) const = 0;
#undef BFME_GARRISON_STATUS_SLOT
};

class BfmeOutOfWeaponRangeTemplate
{
public:
	Bool isLeechRangeWeapon() const;
};

class BfmeGarrisonWeaponLayout
{
public:
	unsigned char m_unmodelled_000[4];
	BfmeOutOfWeaponRangeTemplate *m_template;
};

#pragma comment(linker, "/alternatename:?isLeechRangeWeapon@BfmeOutOfWeaponRangeTemplate@@QBE_NXZ=?j_00028f74@@YAXXZ")

void GarrisonContain::addValidObjectsToGarrisonPoints( void )
{
	BfmeGarrisonContainedNode *sentinel =
		*reinterpret_cast<BfmeGarrisonContainedNode **>(
			reinterpret_cast<char *>( this ) + 0x38);
	BfmeGarrisonContainedNode *it = sentinel->next;
	if (it == sentinel)
		return;

	BfmeGarrisonStatusInterface *statusInterface =
		reinterpret_cast<BfmeGarrisonStatusInterface *>(
			reinterpret_cast<char *>( this ) + 0x20);

	for ( ; it != sentinel; it = it->next )
	{
		Object *object = it->object;
		BfmeGarrisonObjectLayout *objectLayout =
			reinterpret_cast<BfmeGarrisonObjectLayout *>( object );
		if ((objectLayout->m_status94 & 0x10) != 0)
			continue;

		BfmeGarrisonContainModuleInterface *contain = objectLayout->m_contain;
		if (contain != 0)
		{
			BfmeGarrisonHordeContainInterface *horde =
				contain->getHordeContainInterface();
			if (horde != 0)
			{
				_STL::list<Object *> members(horde->getMemberList());
				for (_STL::list<Object *>::iterator memberIt = members.begin();
					memberIt != members.end(); ++memberIt)
				{
					Object *member = *memberIt;
					Weapon *weapon = member->getCurrentWeapon(0);
					if (weapon != 0 &&
						(reinterpret_cast<BfmeGarrisonWeaponLayout *>( weapon )
							->m_template->isLeechRangeWeapon() != FALSE))
						continue;

					BfmeGarrisonObjectLayout *memberLayout =
						reinterpret_cast<BfmeGarrisonObjectLayout *>( member );
					AIUpdateInterface *ai = memberLayout->m_ai;
					if (ai != 0)
					{
						Object *victim = ai->getCurrentVictim();
						const Coord3D *victimPos = ai->getCurrentVictimPos();
						if (victim != 0 || victimPos != 0)
						{
							BfmeGarrisonStatusTriple status =
								statusInterface->getStatus(0);
							if ((status.second & 0x10000000) == 0)
								putObjectAtBestGarrisonPoint(member, victim, victimPos);
						}
					}
				}
				continue;
			}
		}

		AIUpdateInterface *ai = objectLayout->m_ai;
		if (ai == 0)
			continue;

		Object *victim = ai->getCurrentVictim();
		const Coord3D *victimPos = ai->getCurrentVictimPos();
		if (victim != 0)
		{
			putObjectAtBestGarrisonPoint(object, victim, 0);
		}
		else if (victimPos != 0)
		{
			BfmeGarrisonFirePointInterface *firePoint =
				reinterpret_cast<BfmeGarrisonFirePointInterface *>( this );
			const ObjectID objectID = *reinterpret_cast<const ObjectID *>(
				reinterpret_cast<const char *>( object ) + 0x74);
			if (firePoint->getObjectGarrisonPointIndex(objectID) ==
				GARRISON_INDEX_INVALID)
			{
				Int conditionIndex = findConditionIndex();
				BfmeGarrisonFindClosestCall *pointFinder =
					reinterpret_cast<BfmeGarrisonFindClosestCall *>( this );
				Int pointIndex = pointFinder->findClosestFreeGarrisonPointIndex(
					conditionIndex, victimPos);
				if (pointIndex != GARRISON_INDEX_INVALID)
				{
					BfmeGarrisonPlacementCall *placement =
						reinterpret_cast<BfmeGarrisonPlacementCall *>( this );
					placement->putObjectAtGarrisonPoint(object, INVALID_ID,
						conditionIndex, pointIndex);
				}
			}
		}
	}
}
