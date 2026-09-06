// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Grok promote from masm_dumps — retail 0x0027FCE0 size 56
// was: Code/masm_dumps/_cache__isFreeToAssist_AssistedTargetingUpdate__QBE_NXZ_27FCE0.asm

class AssistedTargetingObjectShim {
public:
	bool check();
	void *find(int flags);
};

class AssistedTargetingResultShim {
public:
	int check();
};

class AssistedTargetingUpdate { public: bool isFreeToAssist(void) const; };

// ?isFreeToAssist@AssistedTargetingUpdate@@QBE_NXZ
bool AssistedTargetingUpdate::isFreeToAssist(void) const
{
	AssistedTargetingObjectShim *object =
		(AssistedTargetingObjectShim *)*(const void **)((const unsigned char *)this + 8);
	if (object->check()) {
		if (object->find(0)) {
			AssistedTargetingResultShim *result =
				(AssistedTargetingResultShim *)object->find(0);
			if (!result->check())
				return true;
		}
	}
	return false;
}

