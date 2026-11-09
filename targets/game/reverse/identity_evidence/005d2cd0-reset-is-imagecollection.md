# 0x005D2CD0 is ImageCollection::reset, not LocomotorStore::reset

Facts from retail (tools/vtable_lookup.py, tools/ilt_oracle.py, tools/dis_retail.py):

- Vtable 0x01110104 slot 4 is ILT 0x00033799, which jumps to the one-byte body
  at 0x005D2CD0. Slots 1 and 5 reach the one-byte bodies 0x005D2CC0 (init) and
  0x005D2CE0 (update). Constructor 0x005D30E0 installs the table.
- The ledger already records that constructor as `icf-alias=??0ImageCollection`
  with `object-symbol=??0ImageCollection@@QAE@XZ`, and 0x005D2CF0 (next body in
  the range) is ImageCollection::findImageByName. tu_map.csv places
  0x005D2BD0..0x005D2CF0 in GameClient/System/Image.cpp.
- `ilt_oracle.py check` for ?init@ImageCollection (0x005D2CC0),
  ?reset@ImageCollection (0x005D2CD0) and ?update@ImageCollection (0x005D2CE0):
  all CONFIRMED, exact. The same check for the LocomotorStore spellings of
  init/reset/update at these addresses: CONTRADICTED (outside the slot windows
  of LocomotorStore's ILT entries). `?reset@LocomotorStore@@UAEXXZ` at
  0x001B7160 (123 bytes, ILT 0x0004867B): CONFIRMED, exact.

Conclusion: the empty body is ImageCollection::reset. LocomotorStore::reset is
the 123-byte body at 0x001B7160, which stays as it is. The init and update
rows at 0x005D2CC0 and 0x005D2CE0, and the ctor/dtor 0x005D30E0 and 0x005D2C10,
carry the same wrong LocomotorStore attribution; they are not changed here.

The body is the header-inline `virtual void reset(void) {}` of ZH's ImageCollection
(Image.h), emitted as a COMDAT by Image.cpp, so the row is homed in Image.cpp.
