s = load('wave.mat');
wave = s.psi_w(2,:)*pi/180;
window = 4096;
fs = 10;
[pxx,f] = pwelch(wave,window, [], [],fs);
pxx_corrected = pxx/(2*pi);
omega = f*(2*pi);
plot(omega,pxx_corrected)
xlabel('$\omega$ $[rad/s]$','Interpreter','latex')
ylabel('Power spectral density [s/rad]','Interpreter','latex')

%%
% Finding omega_0 can be done my finding omega wich corresponds to the
% maximum power spectal density function value

[sig2 ind] = max(pxx_corrected);
sig = sqrt(sig2);
omega_0 = omega(ind)