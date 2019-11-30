* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --slowdown --quiet -o results.md allplyfiles.txt`
* Current Directory: `C:\Users\vilya\Models\Stanford`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       24.611    (1.00x) |      130.340    (5.30x) |      128.234    (5.21x) |       53.184    (2.16x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |       10.075    (1.00x) |      466.166   (46.27x) |      266.430   (26.44x) |       51.912    (5.15x) |       68.065    (6.76x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.482    (1.00x) |      109.511   (44.12x) |       62.935   (25.36x) |       11.832    (4.77x) |       14.965    (6.03x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.674    (1.00x) |       25.222   (37.44x) |       14.750   (21.89x) |        2.786    (4.14x) |        3.531    (5.24x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.231    (1.00x) |        6.038   (26.14x) |        3.671   (15.89x) |        0.715    (3.09x) |        0.856    (3.71x) |
| ./dragon_recon/dragon_vrip.ply              |      114.981    (1.00x) |     4770.389   (41.49x) |     3214.772   (27.96x) |      500.496    (4.35x) |      690.697    (6.01x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       25.114    (1.00x) |     1087.741   (43.31x) |      700.929   (27.91x) |      111.308    (4.43x) |      144.209    (5.74x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.151    (1.00x) |      255.442   (49.59x) |      161.580   (31.37x) |       25.166    (4.89x) |       32.961    (6.40x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.311    (1.00x) |       56.626   (43.20x) |       37.800   (28.84x) |        6.186    (4.72x) |        7.684    (5.86x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.650    (1.00x) |       22.712   (34.95x) |       14.144   (21.76x) |        2.632    (4.05x) |        3.035    (4.67x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.285    (1.00x) |        8.486   (29.81x) |        5.328   (18.71x) |        1.039    (3.65x) |        1.229    (4.32x) |
| ./happy_recon/happy_vrip.ply                |      140.168    (1.00x) |     5975.904   (42.63x) |     4058.979   (28.96x) |      600.972    (4.29x) |      819.099    (5.84x) |
| ./happy_recon/happy_vrip_res2.ply           |       36.697    (1.00x) |     1618.123   (44.09x) |     1048.679   (28.58x) |      168.408    (4.59x) |      224.911    (6.13x) |
| ./happy_recon/happy_vrip_res3.ply           |        8.022    (1.00x) |      365.439   (45.55x) |      228.748   (28.52x) |       37.421    (4.66x) |       46.508    (5.80x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.775    (1.00x) |       78.304   (44.12x) |       51.382   (28.95x) |        7.776    (4.38x) |       10.084    (5.68x) |
| ./lucy/lucy.ply                             |     1639.847    (1.00x) |     9216.427    (5.62x) |     8858.152    (5.40x) |     4247.183    (2.59x) |     3649.007    (2.23x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      419.564    (1.00x) |     2436.474    (5.81x) |     2238.493    (5.34x) |     1083.934    (2.58x) |      952.874    (2.27x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      271.877    (1.00x) |     1645.900    (6.05x) |     1819.143    (6.69x) |      693.106    (2.55x) |      560.438    (2.06x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      596.517    (1.00x) |     3334.031    (5.59x) |     3099.264    (5.20x) |     1483.916    (2.49x) |     1262.102    (2.12x) |
| Overall Total                               |     3300.032    (1.00x) |    31609.277    (9.58x) |    26013.413    (7.88x) |     9089.971    (2.75x) |     8492.409    (2.57x) |
