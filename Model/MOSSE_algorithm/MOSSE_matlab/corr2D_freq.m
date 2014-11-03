function [S_res, PSR, dx, dy] = corr2D_freq(f, H)

eps = 1e-6;

F = fft2(f);

S_res = real(ifft2(F.*H));
size_S = size(S_res);
[mval, mind] = max(S_res(:));
[y, x] = ind2sub(size(S_res), mind);

dx = x - floor(size_S(2)/2);
dy = y - floor(size_S(1)/2);

PSR = (mval - mean(S_res(:)))/(std(reshape(S_res, 1, size_S(1)*size_S(2)),1)+eps);

end