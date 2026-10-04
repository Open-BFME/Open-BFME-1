// Native default handle constructor at 006910E0 (9 bytes).
// Identity: targets/game/reverse/identity_evidence/20261003-audio-handle-default-ctor.md
// Keep this definition separate: visible clobbers reshape callers.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
class Gen006BA220;
class Rva006910F0Handle {
public: Rva006910F0Handle(); ~Rva006910F0Handle(); Gen006BA220 *m_receiver;
};
Rva006910F0Handle::Rva006910F0Handle() : m_receiver(0) {}
