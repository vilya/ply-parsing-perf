* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --transposed --slowdown --quiet allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       22.169    (1.00x) |       82.311    (3.71x) |       72.212    (3.26x) |       44.173    (1.99x) |       91.571    (4.13x) |
| ./bunny/reconstruction/bun_zipper.ply       |        9.579    (1.00x) |      265.478   (27.71x) |      172.928   (18.05x) |       32.853    (3.43x) |       31.139    (3.25x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.121    (1.00x) |       61.295   (28.90x) |       46.461   (21.91x) |        7.429    (3.50x) |        7.081    (3.34x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.516    (1.00x) |       14.120   (27.35x) |        9.179   (17.78x) |        1.758    (3.41x) |        1.678    (3.25x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.136    (1.00x) |        3.398   (25.02x) |        2.266   (16.69x) |        0.441    (3.25x) |        0.490    (3.61x) |
| ./dragon_recon/dragon_vrip.ply              |      100.745    (1.00x) |     2807.309   (27.87x) |     1924.839   (19.11x) |      336.806    (3.34x) |      353.502    (3.51x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       22.084    (1.00x) |      627.400   (28.41x) |      441.150   (19.98x) |       78.214    (3.54x) |       77.663    (3.52x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        4.883    (1.00x) |      149.485   (30.61x) |      102.621   (21.02x) |       18.210    (3.73x) |       17.982    (3.68x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.148    (1.00x) |       33.364   (29.05x) |       23.320   (20.31x) |        4.148    (3.61x) |        4.091    (3.56x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.468    (1.00x) |       12.916   (27.58x) |        8.576   (18.31x) |        1.714    (3.66x) |        1.707    (3.65x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.182    (1.00x) |        5.005   (27.54x) |        3.453   (19.00x) |        0.679    (3.74x) |        0.653    (3.60x) |
| ./happy_recon/happy_vrip.ply                |      128.022    (1.00x) |     3474.447   (27.14x) |     2399.195   (18.74x) |      422.527    (3.30x) |      449.203    (3.51x) |
| ./happy_recon/happy_vrip_res2.ply           |       30.205    (1.00x) |      919.619   (30.45x) |      638.126   (21.13x) |      112.574    (3.73x) |      115.004    (3.81x) |
| ./happy_recon/happy_vrip_res3.ply           |        6.894    (1.00x) |      209.879   (30.44x) |      144.479   (20.96x) |       25.473    (3.69x) |       25.233    (3.66x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.522    (1.00x) |       45.633   (29.98x) |       32.997   (21.68x) |        5.697    (3.74x) |        5.728    (3.76x) |
| ./lucy/lucy.ply                             |     1786.415    (1.00x) |     6802.225    (3.81x) |     4906.618    (2.75x) |     3364.710    (1.88x) |     6354.597    (3.56x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      351.470    (1.00x) |     1664.850    (4.74x) |     1231.550    (3.50x) |      858.549    (2.44x) |     1642.051    (4.67x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      230.685    (1.00x) |     1073.998    (4.66x) |      942.164    (4.08x) |      547.541    (2.37x) |      988.172    (4.28x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      548.734    (1.00x) |     2347.725    (4.28x) |     1691.295    (3.08x) |     1173.941    (2.14x) |     2323.112    (4.23x) |
| Overall Total                               |     3247.980    (1.00x) |    20600.456    (6.34x) |    14793.431    (4.55x) |     7037.437    (2.17x) |    12490.657    (3.85x) |
