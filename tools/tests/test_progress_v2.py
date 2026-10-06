"""progress_v2: the old Rebuilt-from-source bar is exactly the sum of its v2 parts; the
authored lane splits by name evidence; the link-cycle series comes from the committed
receipt or reads "pending"; counters come from the hatch register; history rows carry
rules=v2."""
import json
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import progress  # noqa: E402
import progress_v2 as v2  # noqa: E402

ROWS = {  # (name, rva): (size, source, lane)
    ("?update@Locomotor@@QAEXXZ", "0x00001000"): (100, "Code/a.cpp", "authored"),
    ("?get@Rva00002000DwordField@@QBEHXZ", "0x00002000"): (50, "Code/b.cpp", "authored"),
    ("?d_00003000@@YAXXZ", "0x00003000"): (20, "Code/c.cpp", "authored"),
    ("_inflate", "0x00004000"): (40, "Code/zlib.c", "vendored"),
    ("?uw_00005000@@YAXXZ", "0x00005000"): (30, "Code/gen_small/x.cpp", "generated"),
    ("_lib", "0x00006000"): (25, "Code/x.lib", "library"),
    ("?dump@@YAXXZ", "0x00007000"): (10, "Code/x.asm", "dump"),
}
RECEIPT = {"tool": "link_cycle", "rules": "link-cycle-1", "commit": "00edcc355a0000", "date_utc": "2026-10-06",
           "series": {"real": {"placed": {"rows": 3, "bytes": 150, "unique_bytes": 150, "pct_text": 39.89},
                               "placed_self_strict": {"rows": 2, "bytes": 120, "unique_bytes": 120, "pct_text": 20.83},
                               "placed_closed_strict": {"rows": 1, "bytes": 100, "unique_bytes": 100,
                                                        "pct_text": 10.37}}},
           "links": [{"link": "iter1"}]}


@pytest.fixture
def fake(monkeypatch):
    files = {}
    monkeypatch.setattr(v2, "text_at", lambda ref, path: files.get(path))
    monkeypatch.setattr(progress, "matched_at", lambda ref: {k: (v[0], v[1]) for k, v in ROWS.items()})
    monkeypatch.setattr(progress, "notes_at", lambda ref: {k: "" for k in ROWS})
    monkeypatch.setattr(progress, "retail_text", lambda: (0x1000, 0x10000))
    monkeypatch.setattr(progress, "naked_cpp_rows_at", lambda matched, ref: ())
    monkeypatch.setattr(progress, "real_code_denominator", lambda start, size: (0, 1000))

    def real_split(matched, notes, start, size, naked=(), keep=None):
        out = {lane: 0 for lane in progress.SOURCE_LANES}
        for key, (n, source) in matched.items():
            if keep is None or keep(key, source):
                out[ROWS[key][2]] += n
        return out
    monkeypatch.setattr(progress, "real_split", real_split)
    return files


def test_parts_sum_to_the_old_bar(fake):
    point = v2.measure()
    assert point["byte_matched"] == progress.rebuildable(point) == 100 + 50 + 20 + 40 + 30 + 25
    assert point["recovered"] + point["generated"] + point["library"] == point["byte_matched"]
    assert point["dump"] == 10 and "dumps (not in the bar)" in v2.report(point)


def test_authored_split_by_name(fake, monkeypatch):
    point = v2.measure()
    assert (point["cpp_readable"], point["cpp_address"]) == (100, 70)
    if point["cpp_evidence"] is None:
        assert "n/a" in v2.report(point)
    fake[v2.EVIDENCE] = "rva,kind,value,route,basis\n0x00001000,name,Locomotor::update,wb1,strong\n"
    point = v2.measure()
    assert (point["cpp_evidence"], point["cpp_readable"], point["cpp_address"]) == (100, 0, 70)
    assert point["cpp_evidence"] + point["cpp_readable"] + point["cpp_address"] == point["authored"]


@pytest.mark.parametrize("name, tier", [
    ("??0Locomotor@@QAE@XZ", "readable"), ("?get@Rva00002000DwordField@@QBEHXZ", "address"),
    ("?d_00c6bc20@@YAXXZ", "address"), ("?Add_Ref@Thing@@QAEXXZ", "readable"),
    ("??3Gen007F0190@@YAXPAX@Z", "address"), ("?g_Va00A1B2C3@@3HA", "address"),
])
def test_name_tiers(name, tier):
    assert v2.name_tier(name, 0x1000, None) == tier


def test_demangled_ctor_dtor_method():
    assert v2.demangled("??0Locomotor@@QAE@XZ") == "Locomotor::Locomotor"
    assert v2.demangled("??1Locomotor@@UAE@XZ") == "Locomotor::~Locomotor"
    assert v2.demangled("?update@Locomotor@@QAEXXZ") == "Locomotor::update"
    assert v2.demangled("_inflate") is None


def test_link_cycle_pending_then_from_the_committed_receipt(fake):
    point = v2.measure()
    assert point["link"] is None and "LINK CYCLE  pending" in v2.report(point) and "pending" in v2.svg(point)
    fake[v2.RECEIPT] = json.dumps(RECEIPT)
    point = v2.measure()
    assert point["link"]["closed_strict"] == (1, 100, 10.37)
    assert "closed-strict credit" in v2.report(point) and "10.37%" in v2.svg(point)


def test_store_receipt_keeps_series_drops_detail(tmp_path, monkeypatch):
    monkeypatch.setattr(v2, "ROOT", tmp_path)
    src = tmp_path / "receipt.json"
    src.write_text(json.dumps(RECEIPT))
    v2.store_receipt(src)
    stored = json.loads((tmp_path / v2.RECEIPT).read_text())
    assert stored["series"] == RECEIPT["series"] and "links" not in stored
    src.write_text(json.dumps({"tool": "other"}))
    with pytest.raises(SystemExit):
        v2.store_receipt(src)


def test_counters_and_gate_debt(fake):
    fake[v2.HATCHES] = ("# mode: shadow\npin\tr/s.csv\t0x00001000\t2\npin\tr/s.csv\t0x00002000\t1\n"
                        "emit\tCode/a.cpp\t*\t4\nobject_symbol\tr/f.csv\t0x00003000\t1\n")
    for path, kind in v2.GATE_DEBT:
        fake[path] = "check,target_rva,name,detail\ntail,0x1,a,x\n" if kind == "csv" else "# c\ntail 0x1 a\nltable 0x2 b\n"
    point = v2.measure()
    assert point["hatches"]["pin"] == 3 and point["hatches"]["emit"] == 4
    assert point["gate_debt"] == sum(1 if kind == "csv" else 2 for _, kind in v2.GATE_DEBT)
    text = v2.report(point)
    assert "pins 3 (0.43 per matched row)" in text and "alias rows 1" in text


def test_history_rows_carry_rules_v2_and_deltas_compare_within_rules(fake, tmp_path, monkeypatch):
    monkeypatch.setattr(v2, "ROOT", tmp_path)
    (tmp_path / v2.HISTORY).parent.mkdir(parents=True)
    point = v2.measure()
    rows = [dict(v2.history_row(point, "2026-10-05", "abc"), gate_debt=5)]
    v2.write_history(rows + [v2.history_row(point, "2026-10-06", "def")])
    text = (tmp_path / v2.HISTORY).read_text()
    assert text.splitlines()[0].split(",") == v2.FIELDS
    assert all(line.split(",")[2] == "v2" for line in text.splitlines()[1:])
    prev = v2.previous_v2(rows + [{"date": "2026-10-05x", "rules": "v3"}], "2026-10-06")
    assert prev["date"] == "2026-10-05"
    assert "(-5 since 2026-10-05)" in v2.report(point, prev)
