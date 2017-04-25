myOrg = imread('pinkheart.png');
imshow(myOrg);
title('Original Image');

%resize image
myImg = imresize(myOrg, [20 20]);
imshow(myImg); 
title('Resized');

myImg = rgb2gray(myImg);
figure; 
imshow(myImg); 
title('B&W');

%myImg = floydHalftone(myImg);
%imshow(myImg)

outImg = imbinarize(myImg,.5);
figure; 
imshow(outImg);
title('Binary');


% M = outImg;
% fid = fopen('Selu30Matrix.txt', 'w+');
% for i=1:size(M, 1)
%     fprintf(fid, '{');
%     fprintf(fid, '%d, ', M(i,1:29));
%     fprintf(fid, '%d ', M(i,30:30));
%     fprintf(fid, '}\n');
% end
% fclose(fid);


%rle
% [h,w] = size(outImg);
% rle = [];
% for row=1: h
%     for col=1: w
%         %do stuff
%     end
% end
% display(rle)

%find edges
%BW = edge(outImg);
%imshow(BW)
%figure

%complement image
%0 black
%1 white
% (0,0) top left hand corner
%imageComp = imcomplement(BW);
%imshow(imageComp)

imtool(outImg)





