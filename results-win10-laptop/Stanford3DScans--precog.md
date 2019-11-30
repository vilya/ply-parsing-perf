* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --slowdown --quiet --precognition -o results-precog.md allplyfiles.txt`
* Current Directory: `C:\Users\vilya\Models\Stanford`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       17.467    (1.00x) |      122.539    (7.02x) |       67.699    (3.88x) |       55.259    (3.16x) |       13.205    (0.76x) |
| ./bunny/reconstruction/bun_zipper.ply       |        9.085    (1.00x) |      457.154   (50.32x) |      184.905   (20.35x) |       54.961    (6.05x) |       63.905    (7.03x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.324    (1.00x) |      102.920   (44.29x) |       42.109   (18.12x) |       11.570    (4.98x) |       13.552    (5.83x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.617    (1.00x) |       23.669   (38.35x) |        9.669   (15.67x) |        2.736    (4.43x) |        3.202    (5.19x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.241    (1.00x) |        5.823   (24.20x) |        2.349    (9.76x) |        0.683    (2.84x) |        0.786    (3.27x) |
| ./dragon_recon/dragon_vrip.ply              |       97.564    (1.00x) |     4841.354   (49.62x) |     2291.706   (23.49x) |      510.429    (5.23x) |      652.791    (6.69x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       23.518    (1.00x) |     1139.346   (48.45x) |      517.673   (22.01x) |      116.776    (4.97x) |      147.243    (6.26x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.336    (1.00x) |      265.010   (49.67x) |      118.248   (22.16x) |       26.665    (5.00x) |       32.475    (6.09x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.172    (1.00x) |       60.134   (51.30x) |       27.297   (23.29x) |        6.070    (5.18x) |        7.329    (6.25x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.574    (1.00x) |       23.805   (41.46x) |        9.853   (17.16x) |        2.629    (4.58x) |        2.975    (5.18x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.275    (1.00x) |        8.747   (31.85x) |        3.818   (13.90x) |        1.037    (3.78x) |        1.271    (4.63x) |
| ./happy_recon/happy_vrip.ply                |      129.284    (1.00x) |     6044.515   (46.75x) |     2734.688   (21.15x) |      631.986    (4.89x) |      799.290    (6.18x) |
| ./happy_recon/happy_vrip_res2.ply           |       33.303    (1.00x) |     1618.641   (48.60x) |      761.063   (22.85x) |      169.426    (5.09x) |      214.255    (6.43x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.271    (1.00x) |      356.336   (49.01x) |      160.749   (22.11x) |       35.562    (4.89x) |       46.651    (6.42x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.899    (1.00x) |       89.986   (47.39x) |       37.208   (19.60x) |        8.348    (4.40x) |        9.435    (4.97x) |
| ./lucy/lucy.ply                             |     1096.396    (1.00x) |     9425.751    (8.60x) |     4655.430    (4.25x) |     4481.186    (4.09x) |     1125.139    (1.03x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      285.173    (1.00x) |     2398.738    (8.41x) |     1204.953    (4.23x) |     1169.095    (4.10x) |      297.288    (1.04x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      189.876    (1.00x) |     1615.749    (8.51x) |      967.884    (5.10x) |      763.126    (4.02x) |      183.247    (0.97x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      401.384    (1.00x) |     3290.856    (8.20x) |     1720.825    (4.29x) |     1591.107    (3.96x) |      399.219    (0.99x) |
| Overall Total                               |     2302.757    (1.00x) |    31891.073   (13.85x) |    15518.126    (6.74x) |     9638.654    (4.19x) |     4013.256    (1.74x) |
