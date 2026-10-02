# RadarUpgrade::onCapture at RVA 0x002D7CD0

All addresses below were decoded directly from the retail-1.03-unpacked
lotrbfme.exe. RVAs exclude image base 0x00400000; table addresses are VAs.

The independently matched RadarUpgrade constructor at RVA 0x002D7AA0 installs
primary vtable VA 0x010CDB64 and UpgradeMux table VA 0x010CDA50 at this+0x10.
Primary slot 2 routes through ILT 0x00032006 to RVA 0x002D7AF0, whose literal
is RadarUpgrade. Primary slot 9 at VA 0x010CDB88 contains VA 0x0040ED36,
the ILT jumping to RVA 0x002D7CD0. This is the only absolute occurrence of
that ILT pointer in the retail image.

The full method name is witnessed by the Zero Hour twin, not guessed from
behavior: GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/
RadarUpgrade.cpp defines RadarUpgrade::onCapture(Player *oldOwner,
Player *newOwner), and Include/GameLogic/Module/RadarUpgrade.h declares it
public virtual. Its sequence matches this BFME body: save module data,
return unless already upgraded, return when Object is disabled, conditionally
remove radar from oldOwner and clear upgrade execution, then conditionally
add radar to newOwner and set execution. The exact owner, callback slot,
parameter order, and both Player operations agree.

Retail uses module data at this+4, Object at this+8, and UpgradeMux at this+16.
The canonical object.h supplies m_disabledMask at +0x1A4. The module-data byte
at +0x70 is the same m_isDisableProof input used by the already recovered
RadarUpgrade upgradeImplementation (the Zero Hour twin names it explicitly).
The UpgradeMux slot-0 predicate returns AL; slot 8 takes a bool and returns
void. Their table entries route to RVA 0x002D9AB0 (byte getter) and 0x001EE7D0
(byte setter). No new direct pins or identities for those shared bodies are
introduced. Direct call routes 0x0000321A -> 0x000CC0B0 and
0x000179FE -> 0x000CBFA0 are Player::removeRadar(bool) and addRadar(bool),
respectively, as tools/callees.py reports.

The body begins with PUSH EBX/ESI/EDI, ends with their reverse pops and RET 8
at +0x5E, and occupies exactly 97 bytes. INT3 padding follows at +0x61.
