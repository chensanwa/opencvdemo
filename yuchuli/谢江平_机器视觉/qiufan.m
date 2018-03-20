%求反
I=imread('001.jpg');
figure(1);
imshow(I);
title('彩色图像')              %显示原图像
a=isgray(I)                    %彩色图像转为灰度图像
b=isrgb(I)
r=I(:,:,1);
g=I(:,:,2);
b=I(:,:,3); 
 [M,N]=size(r)
 for i=1:M;
    for j=1:N;
         h(i,j)=0.2989*r(i,j)+0.5870*g(i,j)+0.1140*b(i,j); 
    end
end
c=isgray(h)
d=isrgb(h)
figure(2);                   %显示灰度图像
imshow(h);
 title('灰度图像');
h=double(h);                 %求反
h=255-h;
h=uint8(h);
figure(3);
imshow(uint8(h));           %显示求反后的图像
title('求反后的图像')