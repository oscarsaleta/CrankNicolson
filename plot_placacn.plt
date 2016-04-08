reset
set encoding utf8
set pm3d
set view map
unset surface
set cbrange [0:25]

set terminal postscript color enhanced
set output "placacn0.eps"
splot "placacn.txt" index 0 title ''

set output "placacn5.eps"
splot "placacn.txt" index 5 title ''

set output "placacn10.eps"
splot "placacn.txt" index 10 title ''

set output "placacn15.eps"
splot "placacn.txt" index 15 title ''

!mv *.eps ../Latex/Figures/
