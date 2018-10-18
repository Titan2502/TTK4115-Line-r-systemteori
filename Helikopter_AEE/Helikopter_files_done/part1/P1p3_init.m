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
Joystick_gain_x = 2;
Joystick_gain_y = -8;


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

L1 = l_p*K_f;
L2 = l_c*m_c*g - 2*l_h*m_p*g;
L3 = l_h*K_f;
L4 = l_h*K_f;

K1 = L1/J_p;
K2 = L3/J_e;
K3 = -(L4*L2)/(J_lambda*L3);

% %% Print Vs
% a = load('P1p4.mat');
% b = load('P1p4_Vs.mat');
% figure(1)
% plot(a.simout(1,:), a.simout(6, :), 'r')
% hold on
% plot(b.simout_Vs(1,:), b.simout_Vs(2,:),'b')
% grid on
% title('Elevation plotted against Vs Offset')
% xlabel('$t [s]$', 'interpreter', 'latex')
% ylabel('Elevation [deg] / Vs offset [rad]')
% legend('Elevation','Vs Offset')
% hold off