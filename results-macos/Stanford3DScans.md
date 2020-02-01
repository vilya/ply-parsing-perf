* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --transposed --slowdown --quiet allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       22.443    (1.00x) |       86.792    (3.87x) |       74.885    (3.34x) |       45.129    (2.01x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |        9.324    (1.00x) |      282.097   (30.25x) |      172.414   (18.49x) |       33.277    (3.57x) |       32.014    (3.43x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.053    (1.00x) |       64.856   (31.59x) |       46.207   (22.51x) |        7.438    (3.62x) |        7.216    (3.51x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.512    (1.00x) |       14.912   (29.14x) |        9.071   (17.73x) |        1.817    (3.55x) |        1.708    (3.34x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.136    (1.00x) |        3.930   (28.91x) |        2.208   (16.25x) |        0.444    (3.27x) |        0.429    (3.15x) |
| ./dragon_recon/dragon_vrip.ply              |      100.897    (1.00x) |     2957.055   (29.31x) |     1918.594   (19.02x) |      340.220    (3.37x) |      359.868    (3.57x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       21.867    (1.00x) |      661.239   (30.24x) |      437.820   (20.02x) |       81.035    (3.71x) |       79.153    (3.62x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        4.937    (1.00x) |      155.544   (31.51x) |      102.285   (20.72x) |       18.709    (3.79x) |       18.218    (3.69x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.266    (1.00x) |       35.956   (28.40x) |       23.499   (18.56x) |        4.169    (3.29x) |        4.168    (3.29x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.501    (1.00x) |       13.473   (26.87x) |        8.526   (17.00x) |        1.665    (3.32x) |        1.693    (3.38x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.199    (1.00x) |        5.122   (25.78x) |        3.346   (16.84x) |        0.638    (3.21x) |        0.673    (3.39x) |
| ./happy_recon/happy_vrip.ply                |      129.320    (1.00x) |     3681.798   (28.47x) |     2399.179   (18.55x) |      429.913    (3.32x) |      453.742    (3.51x) |
| ./happy_recon/happy_vrip_res2.ply           |       32.524    (1.00x) |      969.795   (29.82x) |      640.523   (19.69x) |      114.738    (3.53x) |      117.667    (3.62x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.369    (1.00x) |      221.657   (30.08x) |      144.368   (19.59x) |       26.247    (3.56x) |       25.765    (3.50x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.623    (1.00x) |       48.682   (30.00x) |       32.470   (20.01x) |        5.754    (3.55x) |        5.942    (3.66x) |
| ./lucy/lucy.ply                             |     1790.181    (1.00x) |     6914.794    (3.86x) |     5169.858    (2.89x) |     3455.053    (1.93x) |     4258.506    (2.38x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      348.231    (1.00x) |     1684.636    (4.84x) |     1263.111    (3.63x) |      873.085    (2.51x) |     1035.302    (2.97x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      239.047    (1.00x) |     1097.696    (4.59x) |      972.006    (4.07x) |      549.207    (2.30x) |      637.350    (2.67x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      564.525    (1.00x) |     2386.529    (4.23x) |     1722.882    (3.05x) |     1195.601    (2.12x) |     1497.230    (2.65x) |
| Overall Total                               |     3276.957    (1.00x) |    21286.562    (6.50x) |    15143.252    (4.62x) |     7184.140    (2.19x) |       failed            |
