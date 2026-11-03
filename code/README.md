# Code — open the retained implementation

**[candidate.cpp](optimized/candidate.cpp)** is the optimized operator: allocation, packing, dispatch, cleanup and the public call. **[fixed_tiles.h](optimized/fixed_tiles.h)** contains its FMA compute template; the report's first FMA step is lines 200–219. [pack_tiles.h](optimized/pack_tiles.h) contains additional packed-weight tile code.

| Folder | Purpose |
|---|---|
| **[optimized/](optimized/README.md)** | Exact retained block-major input candidate and its original ECE workflow, tests, proof and manifest. |
| **[reference/](reference/README.md)** | Original public API and full 35-shape implementation; its production dispatch is unchanged. |
| **[configs/](configs/research_baseline.json)** | Exact research-baseline identity plus frozen study/variant configurations. |
| **tools/** | Current report, resource and profiling-analysis tools. Earlier build/analysis tools are [archived](../archives/project_support/tools/). |

The retained primary is variant **1, `nt_block_major`**, source SHA256 `993a3f9209fa7476f4b08459bd569e6567f20f0dee2ccc4a08950f5161f307f6`, measured ECE library SHA256 `533ab30d7c4b445e807a8ff0a6a9ed283512cc332b19fc326b574accc8c621c1`. It retains the NCHW input/output API and charges recurring input packing. It has not replaced the original production dispatch or established detector integration.

- [Original retained run and verification](../archives/experiments/38_block_major_input_packing/).
- [User-authorized baseline promotion](../archives/experiments/39_working_baseline_promotion/).
- [Latest separate remeasurement](../archives/experiments/54_scratch_halfline_phase/).
- [Full findings and rejected alternatives](../report/findings.md).
- [Design and optimization inventory](../archives/project_support/docs/design.md).

Run `python3 code/tools/refresh_resources.py` from the project root to refresh resources. Run `python3 code/tools/verify_project_layout.py` to check preservation and current source/export identities.

Frozen ECE workflows retain their original internal paths. For those commands, first enter the hidden workspace with `cd .project` from the project root, then use the recorded `diagnostics/block_major_input_v1/...` paths. That directory resolves to this same optimized source, without a second editable copy. Build/run workflows are ECE-only; the cleanup performed no native execution or instruction inspection. Historical JSON paths are also relative to this workspace.

The Git allowlist includes the retained C++ inputs and `guard.cpp`, but excludes the historical runners and their archived dependencies. To build the retained library from a source-only checkout, run the following **on ECE only**, from the project root, using the recorded GCC8.5 compiler and a new output directory:

```sh
kernel_build=$(mktemp -d /tmp/p2-kernel-build.XXXXXX)
/usr/bin/g++ -std=c++17 -O3 -fno-fast-math -ffp-contract=off -mavx2 -mfma -mtune=broadwell -fPIC -shared code/optimized/candidate.cpp -o "$kernel_build/libpanel5_candidate.so"
```

This is a source-only build command, not a rerun of the frozen validation or timing protocol. Select variant1 (`nt_block_major`) through the `p5_*` API in [candidate.h](optimized/candidate.h). No target build was performed for the Git ignore change.
