run('p5p4a')
% Discretization of system
Ts = 1/10;
[Ad Bd] = c2d(A,B,Ts);
[Ad Ed] = c2d(A,E,Ts);
Cd = C;

