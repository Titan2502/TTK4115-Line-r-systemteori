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
Joystick_gain_y = -1;


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
V_s = 7.187;
K_f = (2*l_h*m_p*g - l_c*m_c*g)/(l_h * V_s);

% Pitch Controller
K_pp = 10; 
K_pd = 10;

% Travel Controller
K_rp = -1;

L1 = l_p*K_f;
L2 = l_c*m_c*g - 2*l_h*m_p*g;
L3 = l_h*K_f;
L4 = l_h*K_f;

K1 = L1/J_p;
K2 = L3/J_e;
K3 = -(L4*L2)/(J_lambda*L3);



%% Part 3 %%
% State Space equation:: dot(x) = Ax + Bu
A = [0 1 0 0 0;
     0 0 0 0 0;
     0 0 0 0 0;
     1 0 0 0 0;
     0 0 1 0 0];
B = [0  0;
     0  K1;
     K2 0;
     0  0;
     0  0];
Br= [0  0;
     0  0;
     0  0;
     1  0;
     0  1];
C = [1 0 0 0 0;
     0 0 1 0 0];

% Weighting matrices
q1 = 1;
q2 = 1;
q3 = 1;
q4 = 1;
q5 = 1;
Q = [q1 0 0 0 0;
     0 q2 0 0 0;
     0 0 q3 0 0;
     0 0 0 q4 0;
     0 0 0 0 q5];

r1 = 1;
r2 = 1;
R = [r1 0;0 r2];

% LQR: u = -K*x and P matrix --> u = Pr - K*x
K = lqr(A,B,Q,R);