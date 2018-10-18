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
Joystick_gain_x = 0.8;
Joystick_gain_y = 1;


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


%% Part 3: LQR %%
% State Space equation:: dot(x) = Ax + Bu
A_lqr = [0 1 0;0 0 0;0 0 0];
B_lqr = [0 0;0 K1;K2 0];
C_lqr = [1 0 0;0 0 1];

% % Weighting matrices
% q1 = 60;
% q2 = 30;
% q3 = 100;
% Q = diag([q1 q2 q3]);
% 
% r1 = 0.5;
% r2 = 0.3;
% R = diag([r1 r2]);

q1 = 100;
q2 = 1;
q3 = 150;
Q = diag([q1, q2, q3]);

r1 = 0.5;
r2 = 1;
R = diag([r1, r2]);

% LQR: u = -K*x and P matrix --> u = Pr - K*x
K = lqr(A_lqr,B_lqr,Q,R);
P = -inv(C_lqr*inv(A_lqr-B_lqr*K)*B_lqr);

poles_LQR = eig(A_lqr-B_lqr*K);

%% PART 4: State Estimation
% State Space equation:: dot(x) = Ax + Bu
A = [0 1 0 0 0 0;
     0 0 0 0 0 0;
     0 0 0 1 0 0;
     0 0 0 0 0 0;
     0 0 0 0 0 1;
     K3 0 0 0 0 0];
B = [0  0;
     0  K1;
     0  0;
     K2 0;
     0  0;
     0  0];

C = [1 0 0 0 0 0;
     0 0 1 0 0 0;
     0 0 0 0 1 0];
 
ratio = 20;
r_LQR = max(abs(poles_LQR));
grader = 40;
phi = (pi/180)*grader;
r_est = r_LQR*ratio;
spread = -phi:(phi/1.5):phi;
poles_est = -r_est*exp(1i*spread);
poles_est = [-55, -20, poles_est];

% figure(1)
% plot(poles_est, 'xr', 'Markersize', 12)
% ylabel('Imaginary axis', 'interpreter', 'latex')
% xlabel('Real axis', 'interpreter', 'latex')
% title('Poles for the estimator', 'interpreter', 'latex')
% xlim([-55 1])
% ylim([-r_est r_est])
% hold on
% line([0,0], ylim)
% line(xlim, [0 0])
% hold off

% You can also use place for estimator gain selection by transposing the A 
% matrix and substituting C' for B.
L = place(A', C', poles_est).';

% %% Plotting
% a = load('p4p2_states_uV1.mat');
% b = load('p4p2_reference_uV1.mat');
% c = load('p4p2_estimate_uV1.mat');
% 
% figure(3)
% subplot(2, 3, 1);
% plot(a.states(1,:), a.states(2,:),'b'), grid on
% hold on
% plot(c.estimate(1,:), c.estimate(2,:),'k')
% plot(c.estimate(1,:), c.estimate(2,:)-a.states(2,:),'r')
% hold off
% ylabel('Travel $\lambda$ [deg]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\tilde{\lambda}$','$\hat{\lambda}$', 'Error'}, 'interpreter', 'latex')
% 
% subplot(2, 3, 4);
% plot(a.states(1,:), a.states(3,:),'b'), grid on
% hold on
% plot(c.estimate(1,:), c.estimate(3,:),'k')
% plot(c.estimate(1,:), c.estimate(3,:)-a.states(3,:),'r')
% hold off
% ylabel('TravelRate $\dot{\lambda}$ [deg/s]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\dot{\tilde{\lambda}}$','$\dot{\hat{\lambda}}$', 'Error'}, 'interpreter', 'latex')
% 
% 
% 
% 
% 
% subplot(2, 3, 2);
% plot(a.states(1,:), a.states(4,:),'b'), grid on
% hold on
% plot(c.estimate(1,:), c.estimate(4,:),'k')
% plot(c.estimate(1,:), c.estimate(4,:)-a.states(4,:),'r')
% plot(b.reference(1,:), b.reference(2,:), 'g')
% hold off
% ylabel('Pitch $p$ [deg]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\tilde{p}$','$\hat{p}$', 'Error', 'p ref'}, 'interpreter', 'latex')
% 
% subplot(2, 3, 5);
% plot(a.states(1,:), a.states(5,:),'b'), grid on
% hold on
% plot(c.estimate(1,:), c.estimate(5,:),'k')
% plot(c.estimate(1,:), c.estimate(5,:)-a.states(5,:),'r')
% hold off
% ylabel('PitchRate $\dot{p}$ [deg/s]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\dot{\tilde{p}}$','$\dot{\hat{p}}$', 'Error'}, 'interpreter', 'latex')
% 
% 
% 
% 
% 
% subplot(2, 3, 3);
% plot(a.states(1,:), a.states(6,:),'b'), grid on
% hold on
% plot(c.estimate(1,:), c.estimate(6,:),'k')
% plot(c.estimate(1,:), c.estimate(6,:)-a.states(6,:),'r')
% hold off
% ylabel('Elevation $e$ [deg]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\tilde{e}$','$\hat{e}$', 'Error'}, 'interpreter', 'latex')
% 
% subplot(2, 3, 6);
% plot(a.states(1,50:end), a.states(7,50:end),'b'), grid on
% hold on
% plot(c.estimate(1,50:end), c.estimate(7,50:end),'k')
% plot(c.estimate(1,50:end), c.estimate(7,50:end)-a.states(7,50:end),'r')
% plot(b.reference(1,50:end), b.reference(3,50:end), 'g')
% hold off
% ylabel('ElevationRate $\dot{e}$ [deg/s]', 'interpreter', 'latex')
% xlabel('$t [s]$', 'interpreter', 'latex')
% legend({'$\dot{\tilde{e}}$','$\dot{\hat{e}}$', 'Error', 'e reference'}, 'interpreter', 'latex')