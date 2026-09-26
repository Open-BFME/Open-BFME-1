// cl: /DNDEBUG /MD /EHsc
// Retail factory0x006BAE20,86B. This was falsely claimed as GameLogic's
// GhostObjectManager factory. Its12B allocation calls ILT2BA49 ->6BC530,
// whose installed primary vtable111CF68 slot+8 reaches the name getter
// 6BC550 returning "W3DBuffLogic". The called base1B0D20 similarly names
// "BuffLogic". The real GhostObjectManager ctor1B3AA0 has a single vtable
// and different member initialization; its pins are left intact.
// The factory's owning class is still unresolved, so its identity stays
// address-scoped. The existing neutral constructor name is retained.
// The11B unwind atC495A0 is this allocation's constructor-failure cleanup,
// proved by the factory EH registration and matching emitted parent handler.
class Gen_006BC530 {
public:
 Gen_006BC530();
 char m_storage[12];
};
class Rva006BAE20Factory {
public:
 Gen_006BC530 *createBuffLogic();
};
Gen_006BC530 *Rva006BAE20Factory::createBuffLogic() {
 return new Gen_006BC530;
}
