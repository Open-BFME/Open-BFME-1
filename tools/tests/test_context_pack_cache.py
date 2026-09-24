"""Cold evidence-pack readers use the real, atomically published call index."""
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
import context_pack  # noqa: E402


def test_call_index_rebuilds_corrupt_or_wrong_image_cache(tmp_path):
    path = tmp_path / "calls.json"
    body = b"\xe8\xfb\xff\xff\xff\x90"
    assert context_pack.call_index(body, 0x1000, path) == {0x1000: [0x1000]}
    assert context_pack.call_index(body, 0x2000, path) == {0x2000: [0x2000]}
    assert context_pack.call_index(b"\x90" * len(body), 0x2000, path) == {}
    path.write_text("{incomplete", encoding="utf-8")
    assert context_pack.call_index(body, 0x1000, path) == {0x1000: [0x1000]}
    malformed = json.loads(path.read_text())
    malformed["calls"] = {"4096": "not a site list"}
    path.write_text(json.dumps(malformed), encoding="utf-8")
    assert context_pack.call_index(body, 0x1000, path) == {0x1000: [0x1000]}
    assert json.loads(path.read_text())["text_rva"] == 0x1000


def test_concurrent_cold_processes_get_complete_index(tmp_path):
    path = tmp_path / "calls.json"
    script = (
        "import json,sys; "
        "sys.path[:0]=sys.argv[2:4]; "
        "import context_pack; "
        "print(json.dumps(context_pack.call_index(bytes.fromhex(sys.argv[4]), "
        "4096, sys.argv[1])))"
    )
    command = [sys.executable, "-c", script, str(path), str(ROOT / "tools/fleet"),
               str(ROOT / "tools"), "e8fbffffff90"]

    def reader(_):
        return subprocess.run(command, check=True, capture_output=True, text=True).stdout

    with ThreadPoolExecutor(max_workers=6) as pool:
        outputs = list(pool.map(reader, range(6)))
    assert all(json.loads(output) == {"4096": [4096]} for output in outputs)
    assert json.loads(path.read_text())["calls"] == {"4096": [4096]}
    assert not list(tmp_path.glob("*.tmp"))
