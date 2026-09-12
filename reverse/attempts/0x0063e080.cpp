// ??0GameSpyBuddyMessageQueue@@QAE@XZ
// partial score=0.91 date=2026-09-12
// Real identity confirmed: vtable 0x01118E70, matched via startThread 0x0063C650
// and getLocalProfileID 0x004EBE30. The present-unmatched ctor already in
// Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp compiles to
// 173B against retail's 190B: it is missing 17 bytes of a BFME-added THIRD
// sub-object the Zero Hour reference class (BuddyThread.cpp there, same class)
// does not have.
//
// Real retail layout recovered from tools/dis_retail.py 0x0063E080 190:
//   +0x00 vtable = 0x01118E70
//   +0x04 MutexClass m_requestMutex      (call ??0MutexClass@@QAE@PBD@Z, EH state 0)
//   +0x0c MutexClass m_responseMutex     (call ??0MutexClass@@QAE@PBD@Z, EH state 1)
//   +0x14 RequestQueue m_requests, 0x28B (zero-fill then a REAL call to
//         _M_initialize_map(0) via jump thunk j_000295a0 -> Ghidra FUN_00a3b850
//         = retail VA 0x0063B850, EH state 2 -- NOT yet pinned/named)
//   +0x3c ResponseQueue m_responses, 0x28B (same shape, thunk j_00006a19 ->
//         Ghidra FUN_00a3b9e0 = retail VA 0x0063B9E0, EH state 3 -- NOT pinned)
//   +0x64 an unidentified 4-byte POD field, zeroed directly (no ctor call)
//   +0x68 MutexClass m_<unknown>Mutex    (call ??0MutexClass@@QAE@PBD@Z, EH state 4)
//   +0x70 BuddyThreadClass *m_thread = NULL
//
// The class in BuddyThread.cpp only declares m_requestMutex, m_responseMutex,
// m_requests, m_responses, m_thread -- missing the +0x64 field and the third
// MutexClass at +0x68. Probe evidence (tools/probe.py) also shows our compiled
// RequestQueue/ResponseQueue construction resolves the state-2/state-3 calls
// to an unrelated/unresolved target (`call 0x97`) instead of retail's
// _M_initialize_map calls, so std::queue<BuddyRequest>/std::queue<BuddyResponse>
// as used in this TU do not reproduce retail's non-trivial deque default-ctor
// shape here even before the missing member is added.
//
// Ruled out: this is not a register/scheduling wall. It is (a) a genuinely
// BFME-added field pair (int-or-pointer + MutexClass) absent from the Zero
// Hour reference GameSpyBuddyMessageQueue, and (b) the two queue members' own
// default constructors not emitting the real _M_initialize_map(0) calls that
// retail has -- both need resolving before this can byte-match. Next step:
// pin/name retail VA 0x0063B850 and 0x0063B9E0 (both currently unmatched,
// Ghidra-named ?_M_initialize_map@?$_Deque_base@... over synthetic Gen_t_*
// element types) and figure out why our queue member shape short-circuits
// that call; then add the two missing members in declaration order above.
