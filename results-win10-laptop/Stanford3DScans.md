* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --transposed --slowdown --quiet allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans.md`
* Current Directory: `C:\Users\vilya\Models\Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       23.722    (1.00x) |      188.084    (7.93x) |      147.580    (6.22x) |       57.373    (2.42x) |      112.649    (4.75x) |
| ./bunny/reconstruction/bun_zipper.ply       |       21.095    (1.00x) |      485.537   (23.02x) |      281.707   (13.35x) |       52.943    (2.51x) |       67.724    (3.21x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        6.573    (1.00x) |      111.449   (16.96x) |       65.410    (9.95x) |       11.890    (1.81x) |       15.190    (2.31x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        1.178    (1.00x) |       25.974   (22.05x) |       14.840   (12.60x) |        2.794    (2.37x) |        3.467    (2.94x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.365    (1.00x) |        6.227   (17.05x) |        3.841   (10.51x) |        0.715    (1.96x) |        0.871    (2.38x) |
| ./dragon_recon/dragon_vrip.ply              |      113.475    (1.00x) |     5063.259   (44.62x) |     3232.378   (28.49x) |      490.246    (4.32x) |      687.532    (6.06x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       25.606    (1.00x) |     1149.368   (44.89x) |      735.425   (28.72x) |      131.147    (5.12x) |      156.517    (6.11x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.927    (1.00x) |      266.950   (45.04x) |      168.799   (28.48x) |       27.379    (4.62x) |       37.659    (6.35x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.343    (1.00x) |       62.049   (46.21x) |       39.017   (29.05x) |        6.069    (4.52x) |        8.488    (6.32x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.582    (1.00x) |       23.785   (40.87x) |       14.403   (24.75x) |        2.479    (4.26x) |        3.695    (6.35x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.331    (1.00x) |        9.739   (29.43x) |        5.438   (16.43x) |        1.044    (3.15x) |        1.466    (4.43x) |
| ./happy_recon/happy_vrip.ply                |      142.436    (1.00x) |     6331.214   (44.45x) |     4086.379   (28.69x) |      636.788    (4.47x) |      881.185    (6.19x) |
| ./happy_recon/happy_vrip_res2.ply           |       37.340    (1.00x) |     1704.020   (45.63x) |     1091.347   (29.23x) |      164.808    (4.41x) |      227.560    (6.09x) |
| ./happy_recon/happy_vrip_res3.ply           |        8.312    (1.00x) |      467.352   (56.23x) |      238.057   (28.64x) |       36.525    (4.39x) |       49.254    (5.93x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.845    (1.00x) |       83.164   (45.09x) |       52.732   (28.59x) |        7.871    (4.27x) |       10.855    (5.88x) |
| ./lucy/lucy.ply                             |     1731.060    (1.00x) |     9826.099    (5.68x) |    10228.256    (5.91x) |     4393.173    (2.54x) |     7997.809    (4.62x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      432.921    (1.00x) |     2439.082    (5.63x) |     2604.006    (6.01x) |     1175.128    (2.71x) |     2015.917    (4.66x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      280.446    (1.00x) |     1799.085    (6.42x) |     2011.080    (7.17x) |      735.548    (2.62x) |     1209.978    (4.31x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      633.614    (1.00x) |     3464.050    (5.47x) |     3639.774    (5.74x) |     1571.805    (2.48x) |     2773.721    (4.38x) |
| Overall Total                               |     3468.169    (1.00x) |    33506.487    (9.66x) |    28660.468    (8.26x) |     9505.724    (2.74x) |    16261.535    (4.69x) |
