* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --slowdown --quiet allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       27.403    (1.00x) |       82.872    (3.02x) |       failed            |       43.862    (1.60x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |       10.620    (1.00x) |      261.379   (24.61x) |       failed            |       34.886    (3.28x) |       32.610    (3.07x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.026    (1.00x) |       59.688   (29.46x) |       failed            |        8.285    (4.09x) |        6.890    (3.40x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        1.214    (1.00x) |       16.542   (13.63x) |       failed            |        1.879    (1.55x) |        1.738    (1.43x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.201    (1.00x) |        4.796   (23.80x) |       failed            |        0.501    (2.49x) |        0.454    (2.25x) |
| ./dragon_recon/dragon_vrip.ply              |      100.861    (1.00x) |     2738.009   (27.15x) |       failed            |      344.418    (3.41x) |      348.231    (3.45x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       21.051    (1.00x) |      622.018   (29.55x) |       failed            |       79.354    (3.77x) |       80.094    (3.80x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        7.687    (1.00x) |      144.949   (18.86x) |       failed            |       18.207    (2.37x) |       18.884    (2.46x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.344    (1.00x) |       33.177   (24.69x) |       failed            |        4.106    (3.05x) |        4.044    (3.01x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        1.052    (1.00x) |       16.246   (15.44x) |       failed            |        1.644    (1.56x) |        1.589    (1.51x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.434    (1.00x) |        8.099   (18.65x) |       failed            |        0.850    (1.96x) |        0.769    (1.77x) |
| ./happy_recon/happy_vrip.ply                |      125.681    (1.00x) |     3427.888   (27.27x) |       failed            |      433.087    (3.45x) |      437.876    (3.48x) |
| ./happy_recon/happy_vrip_res2.ply           |       30.252    (1.00x) |      912.704   (30.17x) |       failed            |      115.050    (3.80x) |      118.057    (3.90x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.506    (1.00x) |      203.811   (27.15x) |       failed            |       26.256    (3.50x) |       25.995    (3.46x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.893    (1.00x) |       44.646   (23.58x) |       failed            |        5.699    (3.01x) |        5.670    (3.00x) |
| ./lucy/lucy.ply                             |     1669.420    (1.00x) |     6757.490    (4.05x) |       failed            |     3357.088    (2.01x) |     4133.415    (2.48x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      317.307    (1.00x) |     1642.436    (5.18x) |       failed            |      821.223    (2.59x) |      973.979    (3.07x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      224.003    (1.00x) |     1110.452    (4.96x) |       failed            |      566.109    (2.53x) |      593.580    (2.65x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      534.815    (1.00x) |     2260.328    (4.23x) |       failed            |     1181.895    (2.21x) |     1410.924    (2.64x) |
| Overall Total                               |     3084.772    (1.00x) |    20347.531    (6.60x) |       failed            |     7044.401    (2.28x) |       failed            |
