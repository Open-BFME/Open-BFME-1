# Field-parse builder at 0x00248F00

The 44-byte body at 0x00248F00 carried two names at once. Neither is right.

- `?buildFieldParse@ChinookAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z`
  (ChinookAIUpdate.cpp) resolved its base call through a pin that put
  `AIUpdateModuleData::buildFieldParse` at 0x00019772.
- `?buildFieldParse@HiveStructureBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z`
  (ModuleFactory.cpp) resolved the same call through the ledger row, and a pin,
  that named 0x00019772 `ActiveBodyModuleData::buildFieldParse`.

What the bytes and the registration table show:

- The body calls ILT 0x00019772, which is OpenContain's builder
  (0002a08b-00019772-ilt-thunks.md). It then adds two tables at offset 0.
  - 0x0108E660 holds MobileGarrison, HealObjects, TimeForFullHeal, InitialRoster
    and ImmuneToClearBuildingAttacks. These are ZH's GarrisonContainModuleData fields.
  - 0x010AFA50 holds MaxHordeCapacity, ExitDelay, EntryOffset, EntryPosition and
    ExitOffset.
  - No Chinook field (RappelSpeed, RopeName...) and no structure-body field is
    present.
- Its ILT 0x00015654 is pushed by the module-data factory 0x00116140. ModuleFactory::init
  (0x0012D0CE..0x0012D121) pushes the string "HordeGarrisonContain", then stores
  createProc ILT 0x00035882 (-> `friend_newModuleInstance@HordeGarrisonContain`
  0x001160C0) and createDataProc ILT 0x00024708 (-> 0x00116140).
- The body sits in HordeGarrisonContain's code, just before its constructor at
  0x00248F90.
- The strings "ChinookAIUpdate" and "HiveStructureBody" do not occur in the image, so
  BFME registers neither module.

The module-data class name is not in the image, so the body keeps an address-derived
owner: `?buildFieldParse@Rva00248F00@@SAXAAVWideMulti@@@Z`, in WideBuildFieldParse.cpp's
vocabulary. The HiveStructureBody claim is tombstoned. The AIUpdateModuleData and
ActiveBodyModuleData pins at 0x00019772 existed only for these two rows and are
deleted.

The ledger names the factory 0x00116140 `friend_newModuleData@ContestableContain`.
The registration table assigns "ContestableContain" to 0x00116640, so that name is
also wrong. This change does not touch it.
