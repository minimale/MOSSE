function I_p = preproces(I, window)

eps = 1e-5;

if nargin == 1
    im = log(double(I) + 1);
    I_p  = (im - mean2(im))/(std2(im) + eps);
elseif nargin == 2
%      im = log(double(I) + 1);
    im = double(I);
%       im = (im - mean2(im))/(std2(im) + eps);
    I_p = window.*im;
%     im = fix(255*double(I)/max(double(I(:))));
%     im = double(histeq(I,256));
%     im = double(I);
%     I_p = fix(((fix(256*window).*im))/256);
else error('No image')
    
end

end