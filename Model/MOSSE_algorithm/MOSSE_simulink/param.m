
K_shift = 4; % - коэффицент альфа-смешивания
hsize = [5 5]; % - размер Гауссового распределения
h = 64;
w = 64;
sigma = 2; % - сигма
Gau = Gauss_filt(h, w, hsize, sigma); % Генерация коэффициентов распределения Гаусса
Gau = reshape(conj(Gau'), 1, 4096);
save('Gauss_coeff.mat','Gau')
load('Gauss_coeff.mat')
PSR = 6;
