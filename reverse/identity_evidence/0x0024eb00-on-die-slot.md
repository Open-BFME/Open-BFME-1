# 0x0024EB00: secondary die-interface slot, not a destructor

The matched row formerly called 0x0024EB00/329
`SlaughterHordeContain::~SlaughterHordeContain`. Its source
`SlaughterHordeContainDestructorThunk.cpp` is a historical naked byte lift:
exact bytes prove the extent, not the C++ name. The body processes contained
objects and ends in `ret 4`. The old `no-match` verdict in
`reverse/re_attempts.log` already observed the destructor ABI conflict. A later
automated `converted` verdict only recognized that the row had a `.cpp` source;
it did not establish identity.

## Retail witnesses

* Constructor 0x0024E7A0 stores vtable 0x010B0F1C at complete-object `+0x28`.
  Its slot 0 is ILT 0x00041B82, a five-byte jump to 0x0024EB00. Destructor
  0x0024E8E0 installs the same table during teardown, so the table alone does
  not distinguish whether the override is declared by the base or derived
  class.
* The aligned GarrisonContain constructor 0x0021D820 stores vtable
  0x010AB574 at `+0x28`, and OpenContain constructor 0x002277A0 stores
  0x010AC014 there. Slot 0 of both tables uses ILT 0x0003F044 to 0x00222640.
  That body takes one stack pointer argument and performs contained-object
  death handling. The Zero Hour `DieModuleInterface` has just one virtual
  method, `onDie(const DamageInfo*)`; `OpenContain` declares and implements it,
  while `GarrisonContain` inherits it. These aligned tables support the method
  name and argument type. The Zero Hour declarations are comparative evidence,
  not proof of the BFME declaring class.
* Actual complete destructor 0x0024E8E0 tears down members and ends in plain
  `ret`. Scalar-deleting wrapper 0x0024EA90 reads a deletion flag, calls the
  destructor/free, returns the object pointer, and ends in `ret 4`.
  0x0024EB00 does none of those destructor operations. `ret 4` alone is not
  decisive because a scalar-deleting destructor also uses it; the vtable slot
  role and body behavior rule out that alternative.

`tools/callers_of.py` finds no named direct caller of either 0x0024EB00 or
ILT 0x00041B82; this is a virtual call site, so no caller proves the exact
class. The local `Object::onDie` source calls `getDie()->onDie`, but its own
method is marked present-unmatched and is not a retail caller witness.
Therefore the corrected name is `Rva0024EB00::onDie(const DamageInfo*)`:
the method is descriptive and the owner remains address-derived.

## Ownership and regression checks

The physical extent is `[0x0024EB00,0x0024EC49)`, disjoint from the preceding
`onRemoving` row `[0x0024EAC0,0x0024EAF0)` and the next dump starting at
0x0024ECA0. `tools/check_csv.py` passes. The only `reverse/symbols.csv` pin
at the body address is address-qualified `?b_0024eb00@@YAXXZ`; there is no
semantic destructor pin to repoint. Leave the ILT row and all vtable pins
unchanged. `tools/pin_consistency.py --symbol
'??1SlaughterHordeContain@@UAE@XZ'` reports no pin. Baseline
`name_regression.py HEAD HEAD` and `name_history.py HEAD HEAD` both report
zero findings.

The source still emits COFF symbol `??1SlaughterHordeContain@@UAE@XZ` for the
pre-existing byte lift. This is a **historical, semantically wrong emission
label** retained only via explicit `object-symbol=` ledger metadata, not a
second identity claim. Correcting the lifted signature line would add a new
`__declspec(naked)` line under `conversion_gate.py` Rule A; this repair leaves
all byte-emission lines untouched. It claims zero new native C++ bytes and
adds no semantic pin.
