%拉普拉斯算子
clear;
H=imread('jll.bmp');
a=isgray(H)
b=isrgb(H)                     %彩色图像转灰度图像
r=H(:,:,1);
g=H(:,:,2);
b=H(:,:,3); 
 [M,N]=size(r)
 for o=1:M;
    for p=1:N;
         J(o,p)=0.2989*r(o,p)+0.5870*g(o,p)+0.1140*b(o,p); 
    end
 end
c=isgray(J)
figure;
imshow(uint8(J));
title('灰度图像')         %显示原图像
I=double(J);
[M,N]=size(I);
a=zeros(1,9);
for i=2:M-1;
    for j=2:N-1;
        a(1)=I(i-1,j-1); %定义3*3模块【0,-1,0;-1,4,-1,0,-1,0】
        a(2)=I(i-1,j);
        a(3)=I(i-1,j+1);
        a(4)=I(i,j-1);
        a(5)=I(i,j);
        a(6)=I(i,j+1);
        a(7)=I(i+1,j-1);
        a(8)=I(i+1,j);
        a(9)=I(i+1,j+1);
        J(i,j)=(0*a(1)+1*a(2)+0*a(3)+1*a(4)-4*a(5)+1*a(6)+0*a(7)+1*a(8)+0*a(9));
                 if J(i,j)<0
                    J(i,j)=0;
                 elseif J(i,j)>255
                    J(i,j)=255;
                 else  J(i,j)= J(i,j);
                 end
           K(i,j)=I(i,j)-J(i,j);%拉斯掩膜中心为负，所以原图像-拉斯算子
    end
   
end
figure();            %显示拉斯算子
imshow(uint8(J));
title('拉斯算子')
figure();             %显示处理后的图像
imshow(uint8(K));
title('拉斯变换结果')