# 0x0010BAF0 is Watchdog's override of ThreadClass::Execute (vftable slot 1)

## Vftable proof

Watchdog's vftable `??_7Watchdog@@6B@` is at VA 0x01088E34 (`dir32_addresses.csv`). Its four
slots are ILT stubs (image base 0x400000, `lotrbfme.exe`):

| slot | stub VA  | stub target |
|------|----------|-------------|
| 0    | 0x413629 | 0x0010BD60 `??_GWatchdog@@UAEPAXI@Z` |
| 1    | 0x409FD9 | 0x0010BAF0 |
| 2    | 0x415924 | 0x0010B740 `?Thread_Function@Watchdog@@UAEXXZ` |
| 3    | 0x42E2A8 | 0x0010B8A0 `?reportWatchdog@Watchdog@@UAEXXZ` |

ThreadClass's vftable `??_7ThreadClass@@6B@` (VA 0x01144844) has slot 0 the destructor stub,
slot 1 the stub to 0x009DB650 (`?Execute@ThreadClass@@UAEXXZ`) and slot 2 Thread_Function.
Watchdog's slot 1 therefore overrides ThreadClass::Execute.

## Body proof

The 144-byte body at 0x0010BAF0 takes the object's mutex lock (`MutexClass::LockClass(m_mutex, -1)`),
replaces the owned lock, then calls ThreadClass::Execute. No caller names `start`; the row was
named by guess as a non-virtual member (`QAE`), which also made Watchdog.cpp declare ThreadClass::Execute
non-virtual and emit a two-slot vftable that is not retail's.
