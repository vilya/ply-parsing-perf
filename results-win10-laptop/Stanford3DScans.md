* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --slowdown --quiet allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans.md`
* Current Directory: `C:\Users\vilya\Models\Stanford`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       23.263    (1.00x) |      120.672    (5.19x) |       failed            |       52.468    (2.26x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |        9.887    (1.00x) |      449.624   (45.47x) |       failed            |       49.091    (4.97x) |       63.965    (6.47x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.304    (1.00x) |      100.869   (43.78x) |       failed            |       11.239    (4.88x) |       14.289    (6.20x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.665    (1.00x) |       23.340   (35.09x) |       failed            |        2.744    (4.12x) |        3.338    (5.02x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.259    (1.00x) |        6.736   (26.04x) |       failed            |        0.674    (2.60x) |        0.831    (3.21x) |
| ./dragon_recon/dragon_vrip.ply              |      103.981    (1.00x) |     4579.179   (44.04x) |       failed            |      461.839    (4.44x) |      646.422    (6.22x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       23.979    (1.00x) |     1053.055   (43.92x) |       failed            |      104.651    (4.36x) |      145.935    (6.09x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.415    (1.00x) |      244.492   (45.15x) |       failed            |       24.548    (4.53x) |       32.355    (5.98x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.322    (1.00x) |       55.082   (41.67x) |       failed            |        5.577    (4.22x) |        7.358    (5.57x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.637    (1.00x) |       21.694   (34.08x) |       failed            |        2.415    (3.79x) |        2.985    (4.69x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.291    (1.00x) |        8.278   (28.46x) |       failed            |        0.983    (3.38x) |        1.238    (4.26x) |
| ./happy_recon/happy_vrip.ply                |      129.372    (1.00x) |     5733.269   (44.32x) |       failed            |      587.238    (4.54x) |      817.690    (6.32x) |
| ./happy_recon/happy_vrip_res2.ply           |       33.938    (1.00x) |     1530.628   (45.10x) |       failed            |      153.523    (4.52x) |      215.105    (6.34x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.817    (1.00x) |      347.154   (44.41x) |       failed            |       34.402    (4.40x) |       46.839    (5.99x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.777    (1.00x) |       77.199   (43.45x) |       failed            |        7.697    (4.33x) |        9.962    (5.61x) |
| ./lucy/lucy.ply                             |     1579.505    (1.00x) |     8806.906    (5.58x) |       failed            |     4048.066    (2.56x) |     3436.973    (2.18x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      396.274    (1.00x) |     2316.535    (5.85x) |       failed            |     1056.431    (2.67x) |      899.489    (2.27x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      261.221    (1.00x) |     1621.480    (6.21x) |       failed            |      688.100    (2.63x) |      542.063    (2.08x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      579.858    (1.00x) |     3172.341    (5.47x) |       failed            |     1448.510    (2.50x) |     1225.992    (2.11x) |
| Overall Total                               |     3161.764    (1.00x) |    30268.534    (9.57x) |       failed            |     8740.195    (2.76x) |       failed            |
