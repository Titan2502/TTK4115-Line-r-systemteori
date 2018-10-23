s = load('wave.mat');
wave = s.psi_w(2,:);
fs = 10;
[pxx,f] = pwelch(wave,window, [], [],fs);
pxx_corrected = 2*pi*pxx;
omega = f/(2*pi);
plot(omega,pxx_corrected)
xlabel('$\omega$ $[rad/s]$','Interpreter','latex')
ylabel('Power spectral density [s/rad]','Interpreter','latex')
