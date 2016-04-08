reset
set encoding utf8
set pm3d
set view map
unset surface
set cbrange [0:25]

set terminal postscript color enhanced
set output "placaexp5.eps"
splot "placaexp.txt" index 5 title ''

set output "placaexp25.eps"
splot "placaexp.txt" index 25 title ''

set output "placaexp45.eps"
splot "placaexp.txt" index 45 title ''

set output "placaexp65.eps"
splot "placaexp.txt" index 65 title ''

!mv *.eps ../Latex/Figures/
