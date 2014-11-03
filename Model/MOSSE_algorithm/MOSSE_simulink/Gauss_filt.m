function G = Gauss_filt(h, w, hsize, sigma)

g = zeros(h, w);
g(h/2 , w/2) = 1;
gauss_kern = fspecial('gaussian', hsize, sigma);
g = conv2(g, gauss_kern, 'same');
g = g/max(g(:));
G = fft2(255*g);
G = fix(G);
end

