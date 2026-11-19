# Current linking and reference review

{
  "checked_at": "2026-11-19T19:14:17.122Z",
  "bfme1": {
    "source_base": "b05415e8f58b7ae699c04af961f6e66268f3027f",
    "reference": "147fd3e52b36ee0306aaeef5b316beb09f7c7671",
    "reference_receipt": "build/bfme2-last-check.txt",
    "reference_checked_at": "2026-11-18T13:45:16.710083+00:00",
    "freshness_hours": 72,
    "pulled_source_native_gate": {
      "sources": 2,
      "passed": true,
      "task_credit": 0
    },
    "native_link_queue": {
      "census_commit": "4da772231e",
      "census_when": "2026-11-18 15:28",
      "blockers": [
        {
          "name": "?compare@AsciiString@@QBEHABV1@@Z",
          "bytes": 4433,
          "files": 9,
          "kind": "losers"
        },
        {
          "name": "?_M_reallocate_map@?$deque@UGen_t_00593270_p12cd@@V?$allocator@UGen_t_00593270_p12cd@@@_STL@@@_STL@@IAEXI_N@Z",
          "bytes": 3291,
          "files": 1,
          "kind": "losers"
        },
        {
          "name": "?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z",
          "bytes": 2067,
          "files": 6,
          "kind": "wrong_selected"
        }
      ],
      "scope": "Native picker output; not a current whole-image link or new LINKED-byte proof."
    },
    "prior_ai_review": "Pinned donor and established EH/provider-selection mismatch unchanged; prior review is reused rather than repeating the same codegen sweep. No donor address, provider pin or alias is imported."
  },
  "bfme2": {
    "source_base": "aa5bcbaa07687123f9a3a0e207f4c832bfdd7357",
    "reference": "f956f041626b7cdedec401bbe55282ccee1a3fe8",
    "reference_verified_at": "2026-11-18T17:20:04.734095+00:00",
    "freshness_hours": 168,
    "pulled_source_native_gate": {
      "sources": 39,
      "passed": true,
      "task_credit": 0
    },
    "source_base_hosted_retail": {
      "run_id": 44582066234,
      "job_id": 135765056671,
      "matched": 102308,
      "functions": 102308,
      "source_files": 17482,
      "conclusion": "success",
      "url": "https://github.com/Open-BFME/Open-BFME-2/actions/runs/44582066234"
    },
    "latest_real_measurement": {
      "run_id": 44581907592,
      "commit": "818011e2ae2b2e7695098de50277664426876a7c",
      "when": "2026-11-19 18:37 UTC",
      "authoritative": true,
      "unresolved": 1,
      "duplicates": 0,
      "image_written": false,
      "initializers_bridged": 468,
      "vtables_bridged": 3060,
      "vtable_slots_bridged": 45400,
      "artifact_id": 14563485919,
      "artifact_sha256_verified": true
    },
    "remaining_linker_symbol": "?fFC@IfaceFC@@UAEXXZ",
    "referencing_sources": [
      "Code/GameEngine/Source/GameLogic/Object/Contain/AODHordeContain.cpp",
      "Code/GameEngine/Source/GameLogic/Object/Contain/AODHordeContainDtor.cpp"
    ],
    "source_review": "Both contain an IfaceFC virtual fFC declaration; HordeContain inherits that padded view. A real provider identity or safe hierarchy repair needs independent target ABI/vtable evidence. No guessed body, stub or pure-virtual change is introduced.",
    "prior_destructor_boundary": "The older Rva009203A destructor error is absent from this measurement. Counts alone hid this changed blocker; absence is not game-start proof.",
    "runtime_receipt": "No new primary image exists in the measured run. No fresh game-start proof is claimed."
  },
  "shutdown": false
}

These declaration operations preserve target-native runtime and type contracts. They establish no new linked coverage, complete image or game start. The already pinned reference inputs remain unchanged. Existing names and matching primitives are source-consistency evidence, not newly recovered semantic identities. Hosted byte checks and whole-image/runtime checks retain their separate scopes.
