%结构光条纹中心求法
clear;
I=imread('picture3.jpg');
 figure;
imshow(I);
 [M,N]=size(I);
for i=1:M
    for j=1:N
        if I(i,j)>105
            e(i,j)=255;  %e  二值图像
        else e(i,j)=0;
        end
    end
end
figure;
imshow(e);   
a(1)=0;
a(2)=0; 
 n=0; 
 max=0;
 K=zeros(size(I));  %K  明暗条纹界限
d=zeros(size(I));   %d  条纹中心图像
[M,N]=size(I);
for i=1:M
    for j=1:N-1
        if (xor(e(i,j),e(i,j+1)))   %求左右边界
            if n==0
             K(i,j)=255;
            else K(i,j+1)=255;
            end
             n=n+1;
             if n==1;
             a(n)=j;
             else a(n)=j+1;
             end
        end
       if  n==2
             %  t=floor((a(1)+a(2))/2);
             %  d(i,t)=255;
             % n=0;
              %  这里求出的是条纹的几何中心，一开始用的是这种方法，
             %  后来还是觉得求几何中心比较好，因此把这里注释掉了。
          for x=a(1):a(2)
              max=I(i,a(1));
             if I(i,x)>max    %明条纹区间中原图像像素极大值
                 temp=max;
                 max=I(i,x);
                 I(i,x)=temp;
                 b=x;
             end
          end
          d(i,x)=255;
          n=0;
        end
    end
end
%去掉散斑
for i=2:M-1
    for j=2:N-1
        if d(i,j)==255&&d(i-1,j-1)+d(i-1,j)+d(i-1,j+1)+d(i,j-1)+d(i,j+1)+d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0
            d(i,j)=0;
        end
    end
end
figure;
imshow(d);;
%从断点向下搜寻明纹中心
for i=2:M-1
    for j=2:N-1
        if d(i,j)==255&&(d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0)
            if I(i+1,j-1)>I(i+1,j)&&I(i+1,j-1)>I(i+1,j+1)
                d(i+1,j-1)=255;
            elseif I(i+1,j)>I(i+1,j-1)&&I(i+1,j)>I(i+1,j+1)
                d(i+1,j)=255;
            else d(i+1,j+1)=255;
            end
        end
    end
end
figure;
imshow(d); %显示结构光条纹的中心线
title('向下完善明纹中心')
%图像上下翻转继续完善明纹中心
d=flipud(d);%翻转图像
I=flipud(I);
for i=50:M-1        %因为主要是为了把右上角明纹断点处补充完整，i，j不从1开始，可以减少计算量
    for j=50:N-1
        if d(i,j)==255&&(d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0)
            if I(i+1,j-1)>I(i+1,j)&&I(i+1,j-1)>I(i+1,j+1)
                d(i+1,j-1)=255;
            elseif I(i+1,j)>I(i+1,j-1)&&I(i+1,j)>I(i+1,j+1)
                d(i+1,j)=255;
            else d(i+1,j+1)=255;
            end
        end
    end
end
d=flipud(d);
for i=2:M-1          %单像素化
    for j=2:N-1
        if d(i,j)==255&&d(i,j+1)==255;
            if I(i,j)>I(i,j+1)
                d(i,j)=255;
                d(i,j+1)=0;
            else d(i,j+1)=255;
                d(i,j)=0;
            end
        end
    end
end
figure;
imshow(d);
title('所求得的明纹中心') 
 %figure;
%imshow(d); %显示结构光条纹的中心线
%title('向下和向上完善明纹中心')