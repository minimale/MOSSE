
% ima1 = imread('cameraman.jpg');
vidObj= VideoReader('klt_algorithm_robustness_640x360.avi');
%ima1 = imread('cameraman.jpg');
ima1 = rgb2gray(read(vidObj, 1));
h = 128;
w = 128;
[~, rect] = imcrop(ima1);
ima3 = uint8(zeros(h, w));
h1 = 48;
w1 = 48;
x = rect(1) + (h - h1)/2;
y = rect(2) + (w - w1)/2;
ima2 = imcrop(ima1, [x y w1-1 h1-1]);
ima3((h - h1)/2 + 1:h/2 + h1/2, (w - w1)/2 + 1:w/2 + w1/2) = ima2;
imwrite(ima3, 'test1.jpg');

ima1 = rgb2gray(read(vidObj, 1));
x = rect(1) + 0;
y = rect(2) + 0;
ima = imcrop(ima1, [x y w-1 h-1]);
imwrite(ima,'test.jpg');


close all
%full_model