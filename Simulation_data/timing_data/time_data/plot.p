set terminal png size 1400,1000
set output 'timing.png'
set title 'Module Timing'
set xlabel "Aluminum Thickness (um)"
set ylabel "Simulation time (1000 events)"
set xrange [0:6100]
set key right bottom

f1(x) = a1 + b1*x
f2(x) = a2 + b2*x
f3(x) = a3 + b3*x
f4(x) = a4 + b4*x
f5(x) = a5 + b5*x
f6(x) = a6 + b6*x
f7(x) = a7 + b7*x
fit f1(x) "timing_data_for_gnuplot.txt" u 2:3 via a1,b1
fit f2(x) "timing_data_for_gnuplot.txt" u 2:4 via a2,b2
fit f3(x) "timing_data_for_gnuplot.txt" u 2:5 via a3,b3
fit f4(x) "timing_data_for_gnuplot.txt" u 2:6 via a4,b4
fit f5(x) "timing_data_for_gnuplot.txt" u 2:7 via a5,b5
fit f6(x) "timing_data_for_gnuplot.txt" u 2:8 via a6,b6
fit f7(x) "timing_data_for_gnuplot.txt" u 2:9 via a7,b7
plot "timing_data_for_gnuplot.txt" u 2:3 t "EM Opt0" lc "red" pt 2, f1(x) lc "red" t "EM Opt0 fit", "timing_data_for_gnuplot.txt" u 2:4 t "EM Opt1" lc "goldenrod" pt 2, f2(x) lc "goldenrod" t "EM Opt1 fit", "timing_data_for_gnuplot.txt" u 2:5 t "EM Opt2" lc "orange" pt 2, f3(x) lc "orange" t "EM Opt2 fit", "timing_data_for_gnuplot.txt" u 2:6 t "EM Opt3" lc "brown" pt 2, f4(x) lc "brown" t "EM Opt3 fit", "timing_data_for_gnuplot.txt" u 2:7 t "EM Opt4" lc "web-blue" pt 2, f5(x) lc "web-blue" t "EM Opt4 fit", "timing_data_for_gnuplot.txt" u 2:8 t "EM LIV" lc "dark-spring-green" pt 2, f6(x) lc "dark-spring-green" t "EM LIV fit", "timing_data_for_gnuplot.txt" u 2:9 t "EM PEN" lc "dark-plum" pt 2, f7(x) lc "dark-plum" t "EM PEN fit"