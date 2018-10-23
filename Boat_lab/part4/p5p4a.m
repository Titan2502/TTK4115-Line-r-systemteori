%% State space parameters
omega_0 = 0.7823;
lambda = 0.0872;
T = 70.5465;
K = 0.1557;
K_w = 0.0038;

%% State space model 
A = [   0               1           0           0           0;
    -omega_0^2  -2*lambda*omega_0   0           0           0;
        0               0           0           1           0;
        0               0           0          -1/T       -K/T;
        0               0           0           0           0];
    
B = [   0   ;
        0   ;
        0   ;
       K/T  ;
       0    ];
   
E = [   0   0   ;
       K_w  0   ;
        0   0   ;
        0   0   ;
        0   1   ];
    
 C = [0 1 1 0 0];

%% State space model without disturbance
%B
A_u1 = [ 0   1;
        0  -1/T];
    
C_u1 = [1 0];

%C
A_u2 = [ 0    1     0;
         0  -1/T   -K/T;
         0    0     0];
    
C_u2 = [1 0 0];

%D
A_u3 = [ 0              1           0           0;
    -omega_0^2  -2*lambda*omega_0   0           0;
        0               0           0           1;
        0               0           0          -1/T];
    
C_u3 = [0 1 1 0];
%% Observability
Ob = obsv(A,C);
rank_obserM = rank(Ob);

Ob_u1 = obsv(A_u1,C_u1);
rank_obserM_u1 = rank(Ob_u1);

Ob_u2 = obsv(A_u2,C_u2);
rank_obserM_u2 = rank(Ob_u2);

Ob_u3 = obsv(A_u3,C_u3);
rank_obserM_u3 = rank(Ob_u3);
 