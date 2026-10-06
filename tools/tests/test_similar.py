#!/usr/bin/env python3
"""tools/similar.py: masked n-gram neighbours and the next_work `similar` tier."""
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import similar  # noqa: E402

# x86 bodies: B is A with every general register renamed (register allocation),
# C is unrelated control flow.
A = bytes.fromhex("8b442404" "8b4808" "03c8" "894808" "85c9" "7405" "e800000000" "c3")
B = bytes.fromhex("8b542404" "8b4a08" "03ca" "894a08" "85c9" "7405" "e800000000" "c3")
C = bytes.fromhex("d9442404" "d8c8" "d9542408" "dec1" "d95c240c" "33c0" "40" "c20800")


def feat(code):
    toks = similar.tokens_of(code)
    return (len(code), len(toks), similar.shingles(toks))


@pytest.fixture
def index(monkeypatch, tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "?f@@YAXXZ,,0x00001000,24,game/Lib/f.cpp,matched,\n"
        "?dump@@YAXXZ,,0x00003000,24,game/gen_asm/dump.cpp,matched,\n", encoding="utf-8")
    feats = {"home": {0x1000: feat(A), 0x2000: feat(B), 0x3000: feat(A), 0x4000: feat(C)},
             "peer": {0x9000: feat(B)}}
    peer_ledger = tmp_path / "peer.csv"
    peer_ledger.write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                           "?g@@YAXXZ,,0x00009000,24,Code/Lib/g.cpp,matched,\n", encoding="utf-8")
    monkeypatch.setattr(similar, "HOME", "home")
    monkeypatch.setattr(similar, "game_features", lambda g, jobs=None: feats[g.name])
    monkeypatch.setattr(similar, "read_functions", lambda path: [])
    monkeypatch.setattr(similar, "stop_words", lambda f: set())
    return similar.Index([similar.Game("home", "x.exe", "f.csv", ledger),
                          similar.Game("peer", "y.exe", "g.csv", peer_ledger)])


def test_register_renaming_is_invisible():
    assert similar.tokens_of(A) == similar.tokens_of(B)
    assert similar.tokens_of(A) != similar.tokens_of(C)


def test_big_constants_and_targets_are_masked():
    assert similar.normalise("mov", "eax, dword ptr [0x8e4af0]") == "mov R, dword ptr [I]"
    assert similar.normalise("add", "esp, 0xc") == "add esp, 0xc"
    assert similar.normalise("call", "0x690690") == "call"


def test_neighbour_found_across_games_with_source_lead(index):
    queue = similar.candidates(index, min_score=0.5)
    by_rva = {c["target_rva"]: c for c in queue}
    hit = by_rva["0x00002000"]
    assert hit["similarity"] == 1.0
    sources = {lead["source"] for lead in hit["neighbours"]}
    assert sources == {"game/Lib/f.cpp", "Code/Lib/g.cpp"}


def test_generated_dump_is_never_a_lead_and_stays_open_work(index):
    queue = {c["target_rva"]: c for c in similar.candidates(index, min_score=0.5)}
    assert "0x00003000" in queue  # a gen_asm row is open work, not done
    for c in queue.values():
        assert all("gen_asm" not in lead["source"] for lead in c["neighbours"])


def test_unrelated_body_is_not_served(index):
    queue = {c["target_rva"] for c in similar.candidates(index, min_score=0.5)}
    assert "0x00004000" not in queue
    assert "0x00001000" not in queue  # matched itself


def test_claimed_filter(index):
    queue = similar.candidates(index, claimed={0x1000, 0x2000}, claimed_ranges=[(0x2FF0, 0x3010)])
    assert {c["target_rva"] for c in queue} == set()


def test_pe_section_mapping():
    blob = bytearray(0x400)
    struct.pack_into("<I", blob, 0x3C, 0x80)
    struct.pack_into("<HH", blob, 0x84, 0x14C, 1)          # machine, one section
    struct.pack_into("<H", blob, 0x94, 0xE0)               # optional header size
    struct.pack_into("<IIII", blob, 0x80 + 24 + 0xE0 + 8, 0x100, 0x1000, 0x100, 0x200)
    blob[0x210:0x214] = b"\xde\xad\xbe\xef"
    sections = similar.pe_sections(bytes(blob))
    assert sections == [(0x1000, 0x100, 0x200)]
    assert similar.read_rva(bytes(blob), sections, 0x1010, 4) == b"\xde\xad\xbe\xef"
    assert similar.read_rva(bytes(blob), sections, 0x5000, 4) == b""


def test_next_work_similar_tier_is_explicit_only():
    import next_work
    cand = [{"function": "FUN_1", "target_rva": "0x00001000", "size": 64, "similarity": 1.0}]
    assert next_work.selected_queue("similar", [], [], [], [], [], (), (), (), cand)[1] == cand
    label, _ = next_work.selected_queue(None, [], [], [], [], [], (), (), (), cand)
    assert label == "validated queue"  # never the default pick
    full = next_work.candidate_weight(cand[0])
    half = next_work.candidate_weight(dict(cand[0], similarity=0.5))
    assert full > half >= 1
