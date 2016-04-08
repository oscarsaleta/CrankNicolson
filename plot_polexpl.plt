reset
set encoding utf8
set pm3d
set view map
unset surface
f(t,x,y)=t+2*x*y+x**2+y**2

set terminal postscript color enhanced
set output "polexpl0.eps"
splot "polexpl.txt" index 1 u 1:2:(abs($3-f(0.01,$1,$2))) title ''

set output "polexpl20.eps"
splot "polexpl.txt" index 20 u 1:2:(abs($3-f(0.2,$1,$2))) title ''

!mv *.eps ../Latex/Figures/
