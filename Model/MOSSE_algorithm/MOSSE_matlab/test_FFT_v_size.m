clear all
close all
pref
h = 128;
w = 128;
hsize = [64 64];
sigma = 2;
G = Gauss_filt(h, w, hsize, sigma);
window = hanning(h, w);

im1 = imread('test.jpg');
im2 = imread('test1.jpg');
temp = preproces(im2, window);
[H1, H2] = FILT_func(temp, G);
H = FILT_div(H1, H2);
[S_res, PSR, dx, dy] = corr2D_freq(preproces(im1, window), H);
imshow(S_res, []);
figure
imshow(ifftshift(real(ifft2(H))), []);
