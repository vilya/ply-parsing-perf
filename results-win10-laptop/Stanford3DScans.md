* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --transposed --slowdown --quiet allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans.md`
* Current Directory: `C:\Users\vilya\Models\Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       32.716    (1.00x) |      158.244    (4.84x) |      156.863    (4.79x) |       59.163    (1.81x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |       11.444    (1.00x) |      595.489   (52.04x) |      306.035   (26.74x) |       55.921    (4.89x) |       72.220    (6.31x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.996    (1.00x) |      120.001   (40.05x) |       70.324   (23.47x) |       12.413    (4.14x) |       15.812    (5.28x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.644    (1.00x) |       27.387   (42.55x) |       17.075   (26.53x) |        2.860    (4.44x) |        3.607    (5.60x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.231    (1.00x) |        6.579   (28.50x) |        3.960   (17.16x) |        0.858    (3.72x) |        0.887    (3.84x) |
| ./dragon_recon/dragon_vrip.ply              |      126.636    (1.00x) |     5649.458   (44.61x) |     3526.593   (27.85x) |      524.761    (4.14x) |      737.118    (5.82x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       27.171    (1.00x) |     1256.888   (46.26x) |      802.864   (29.55x) |      123.087    (4.53x) |      165.197    (6.08x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        6.161    (1.00x) |      284.904   (46.25x) |      177.568   (28.82x) |       28.447    (4.62x) |       37.221    (6.04x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.511    (1.00x) |       63.717   (42.18x) |       40.479   (26.79x) |        6.916    (4.58x) |        8.151    (5.40x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.629    (1.00x) |       25.478   (40.49x) |       15.004   (23.85x) |        2.632    (4.18x) |        3.363    (5.34x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.329    (1.00x) |        9.768   (29.70x) |        5.685   (17.29x) |        1.155    (3.51x) |        1.448    (4.40x) |
| ./happy_recon/happy_vrip.ply                |      149.517    (1.00x) |     7202.881   (48.17x) |     4365.140   (29.19x) |      677.590    (4.53x) |      933.609    (6.24x) |
| ./happy_recon/happy_vrip_res2.ply           |       41.342    (1.00x) |     1757.092   (42.50x) |     1134.368   (27.44x) |      182.024    (4.40x) |      242.609    (5.87x) |
| ./happy_recon/happy_vrip_res3.ply           |       14.688    (1.00x) |      388.747   (26.47x) |      263.566   (17.94x) |       39.217    (2.67x) |       54.767    (3.73x) |
| ./happy_recon/happy_vrip_res4.ply           |        3.397    (1.00x) |       86.569   (25.48x) |       57.650   (16.97x) |        8.756    (2.58x) |       12.600    (3.71x) |
| ./lucy/lucy.ply                             |     1925.968    (1.00x) |    10072.164    (5.23x) |    10364.650    (5.38x) |     4663.201    (2.42x) |     3905.899    (2.03x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      499.339    (1.00x) |     2614.767    (5.24x) |     2705.829    (5.42x) |     1185.571    (2.37x) |     1016.125    (2.03x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      303.697    (1.00x) |     1793.980    (5.91x) |     2101.659    (6.92x) |      796.154    (2.62x) |      612.376    (2.02x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      731.481    (1.00x) |     3616.877    (4.94x) |     3693.359    (5.05x) |     1657.317    (2.27x) |     1408.124    (1.93x) |
| Overall Total                               |     3879.896    (1.00x) |    35730.991    (9.21x) |    29808.671    (7.68x) |    10028.043    (2.58x) |       failed            |
