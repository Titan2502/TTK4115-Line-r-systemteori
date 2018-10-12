% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 1;
Joystick_gain_y = -0.5;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

%% Egen Kode %% 
% Moment of intertia
J_p = 2*m_p*l_p^2;
J_e = m_c*l_c^2 + 2*m_p*l_h^2;
J_lambda = m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2);

% Kf til elevation
V_s = 6.802;
K_f = (2*l_h*m_p*g - l_c*m_c*g)/(l_h * V_s);

L1 = l_p*K_f;
L2 = l_c*m_c*g - 2*l_h*m_p*g;
L3 = l_h*K_f;
L4 = -l_h*K_f;

K1 = L1/J_p;
K2 = L3/J_e;
K3 = -(L4*L2)/(J_lambda*L3);

% Zeta and omega
zeta = 0.9;
T_s = 2;
omega_n = -(log(0.02*sqrt(1-zeta^2)))/(zeta*T_s);

% Pitch Controller
K_pp = omega_n^2/K1; 
K_pd = (2*zeta*omega_n)/K1;

% Travel Rate Controller
K_rp = -2;

%% Part 3 %%
% State Space equation:: dot(x) = Ax + Bu
A = [0 1 0 0 0 0;
     0 0 0 0 0 0;
     0 0 0 1 0 0;
     0 0 0 0 0 0;
     0 0 0 0 0 1;
     K3 0 0 0 0 0];
B = [0  0;
     0  K1;
     K2 0;
     0  0;
     0  0;
     0  0];
% Br= [0  0;
%      0  0;
%      0  0;
%      1  0;
%      0  1];
C = [1 0 0 0 0 0;
     0 0 1 0 0 0;
     0 0 0 0 1 0];

% Weighting matrices
q1 = 100;
q2 = 10;
q3 = 150;
q4 = 200;
q5 = 200;
Q = diag([q1 q2 q3 q4 q5]);

r1 = 0.3;
r2 = 1;
R = diag([r1 r2]);

% LQR: u = -K*x and P matrix --> u = Pr - K*x
K = lqr(A,B,Q,R);
P = -inv(A-B*K)*inv(C)*(C*inv(A-B*K)*Br + eye(2));
