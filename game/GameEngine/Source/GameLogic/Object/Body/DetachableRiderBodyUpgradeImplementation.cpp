// cl: /DNDEBUG /MD /EHsc
// DetachableRiderBody::upgradeImplementation at retail 0x00212D10: slot 9 of the UpgradeMux table
// 0x010A7FC0, reached only through ILT 0x0002E9DD (its VA appears once in the image).
// DetachableRiderBody's registered constructor 0x00212EC0 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// The UpgradeMux subobject sits at +0xE0. DetachableRiderBody has no Zero
// Hour twin; the method name comes from the UpgradeMux slot it overrides.
// Retail is a single `ret`.

class DetachableRiderBody
{
protected:
	virtual void upgradeImplementation();
};

void DetachableRiderBody::upgradeImplementation()
{
}
