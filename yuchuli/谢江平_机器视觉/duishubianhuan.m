%对数变换
I=imread('jll.bmp');
a=isgray(I);
b=isrgb(I);
r=I(:,:,1);
g=I(:,:,2);
b=I(:,:,3); 
 [M,N]=size(r)
 for i=1:M;
    for j=1:N;
         J(i,j)=0.2989*r(i,j)+0.5870*g(i,j)+0.1140*b(i,j); 
    end
 end
figure;
imshow(uint8(J));        %显示灰度图像
J=double(J);
[M,N]=size(J);
for i=1:M
  for j=1:N
     J(i,j)=38*log(1+J(i,j));%在公式s=c*log（1+r）中，随C值的增大图像变亮
    end

end
figure();
imshow(uint8(J));           %显示对数变换后的图像
title('对数变换');

