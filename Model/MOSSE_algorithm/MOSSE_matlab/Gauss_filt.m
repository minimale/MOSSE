function G = Gauss_filt(h, w, hsize, sigma)

g = zeros(h, w);
g(h/2 , w/2) = 1;
gauss_kern = fspecial('gaussian', hsize, sigma);
g = imfilter(g, gauss_kern);
g = g/max(g(:));
G = fft2(g);

end

