* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --transposed --slowdown --quiet --precognition allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans--precog.md`
* Current Directory: `C:\Users\vilya\Models\Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       18.660    (1.00x) |      143.634    (7.70x) |       77.598    (4.16x) |       62.185    (3.33x) |       14.851    (0.80x) |
| ./bunny/reconstruction/bun_zipper.ply       |       15.711    (1.00x) |      552.106   (35.14x) |      208.886   (13.30x) |       57.703    (3.67x) |       69.241    (4.41x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.837    (1.00x) |      120.409   (42.45x) |       47.751   (16.83x) |       13.188    (4.65x) |       15.616    (5.51x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.730    (1.00x) |       29.007   (39.72x) |       10.941   (14.98x) |        3.286    (4.50x) |        3.610    (4.94x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.264    (1.00x) |        6.883   (26.07x) |        2.655   (10.06x) |        0.815    (3.09x) |        0.920    (3.48x) |
| ./dragon_recon/dragon_vrip.ply              |      118.950    (1.00x) |     5958.295   (50.09x) |     2462.452   (20.70x) |      548.748    (4.61x) |      707.398    (5.95x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       26.693    (1.00x) |     1271.305   (47.63x) |      558.256   (20.91x) |      124.565    (4.67x) |      156.146    (5.85x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        6.192    (1.00x) |      288.596   (46.61x) |      129.202   (20.87x) |       29.642    (4.79x) |       36.171    (5.84x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.841    (1.00x) |       73.459   (39.91x) |       28.503   (15.49x) |        6.880    (3.74x) |        8.496    (4.62x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.989    (1.00x) |       25.321   (25.60x) |       10.891   (11.01x) |        2.970    (3.00x) |        3.206    (3.24x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.456    (1.00x) |        9.489   (20.82x) |        4.085    (8.96x) |        1.254    (2.75x) |        1.364    (2.99x) |
| ./happy_recon/happy_vrip.ply                |      158.392    (1.00x) |     6840.615   (43.19x) |     3080.047   (19.45x) |      685.180    (4.33x) |      893.189    (5.64x) |
| ./happy_recon/happy_vrip_res2.ply           |       40.702    (1.00x) |     1809.034   (44.45x) |      815.580   (20.04x) |      181.779    (4.47x) |      232.218    (5.71x) |
| ./happy_recon/happy_vrip_res3.ply           |        8.635    (1.00x) |      401.646   (46.51x) |      185.471   (21.48x) |       41.015    (4.75x) |       49.792    (5.77x) |
| ./happy_recon/happy_vrip_res4.ply           |        4.219    (1.00x) |       90.365   (21.42x) |       40.082    (9.50x) |        8.780    (2.08x) |       10.662    (2.53x) |
| ./lucy/lucy.ply                             |     1296.604    (1.00x) |    10025.902    (7.73x) |     5257.389    (4.05x) |     4967.456    (3.83x) |     1209.978    (0.93x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      358.563    (1.00x) |     2598.111    (7.25x) |     1347.590    (3.76x) |     1258.649    (3.51x) |      303.315    (0.85x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      233.338    (1.00x) |     1786.584    (7.66x) |     1048.487    (4.49x) |      802.466    (3.44x) |      183.495    (0.79x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      444.496    (1.00x) |     3583.556    (8.06x) |     1865.393    (4.20x) |     1738.633    (3.91x) |      419.952    (0.94x) |
| Overall Total                               |     2738.271    (1.00x) |    35614.315   (13.01x) |    17181.260    (6.27x) |    10535.194    (3.85x) |     4319.622    (1.58x) |
