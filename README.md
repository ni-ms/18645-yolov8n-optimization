# 1×1 convolution — start here

**[Open the report](report/report.pdf)** · **[Open the optimized code](code/optimized/candidate.cpp)** · **[Open the optimized compute kernel](code/optimized/fixed_tiles.h)**

| Folder | What belongs here |
|---|---|
| **[report/](report/README.md)** | Current report PDF, editable LaTeX, calculations, findings and presentation sources. |
| **[code/](code/README.md)** | Retained optimized implementation, original reference implementation, baseline configuration and current tools. |
| **[resources/](resources/README.md)** | Hand-in copies, presentation and source ZIPs. |
| **[archives/](archives/README.md)** | All earlier experiments, inputs, raw results, rejected candidates and historical documentation. |

The retained primary kernel is **block-major input, variant 1 (`nt_block_major`)**, measured at **91.190–91.373% of arithmetic peak** in its original study and **90.855–91.019%** in the latest separate remeasurement. [Its identity and scope](code/configs/research_baseline.json) are frozen. This is the primary C256/S400/O256 research baseline; the five-shape report uses explicitly named selections for the other shapes.

The current report is four pages and directly answers all 18 assignment questions. The nine-page detailed companion and twenty-five-page calculations remain separate. Presentation reconciliation, rehearsal and human hand-in are still outstanding. [status.md](status.md) is the full progress timeline.

Every pre-cleanup file is retained, including older versions of edited navigation/tools and refreshed packages. [Preservation verification](archives/working_materials/20_simple_project_structure/verification.json) and the [old-to-new path map](archives/working_materials/20_simple_project_structure/moves.json) document the cleanup.

To refresh hand-in copies after source/export updates, run `python3 code/tools/refresh_resources.py` from this folder. Target kernels, assembly generation and assembly inspection stay on ECE. The hidden `.project` workspace supports historical paths and workflows; the existing `build` and `.idea` compatibility links are retained.

For GitHub, [.gitignore](.gitignore) allows only the retained kernel and its headers/guard test, original API/implementation, baseline/variant metadata and project guides/progress. New files are ignored until explicitly added to the allowlist. Reports, hand-in exports, datasets, experiment results, archived material, build products and editor settings stay local; links to those files in these guides refer to the full local workspace. Git ignore rules do not remove files already tracked in an existing repository.

`code/optimized` is a symbolic link. The allowlist also includes its actual kernel files under `code/.workspace/diagnostics/block_major_input_v1/`, so a fresh checkout retains the code. The historical experiment runners depend on excluded evidence and are not included; see the [code guide](code/README.md) for the source-only ECE build.
