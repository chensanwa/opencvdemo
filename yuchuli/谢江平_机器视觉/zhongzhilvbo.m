%��ֵ�˲�
H=imread('jll.bmp');  %��ȡ����˽���������ͼ�񣬿��Խ�ͼƬ���ĳ��Լ���Ҫ�����ͼƬ
a=isgray(H)
b=isrgb(H)                     %��ɫͼ��ת�Ҷ�ͼ��
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
title('����˽���������ͼ��')
I=double(J);             %��ֵ�˲�
[M,N]=size(I);
a=zeros(1,9);
for i=2:M-1;
    for j=2:N-1;
        a(1)=I(i-1,j-1); %����3*3ģ�� 
        a(2)=I(i-1,j);
        a(3)=I(i-1,j+1);
        a(4)=I(i,j-1);
        a(5)=I(i,j);
        a(6)=I(i,j+1);
        a(7)=I(i+1,j-1);
        a(8)=I(i+1,j);
        a(9)=I(i+1,j+1);
   %3*3ģ��Ԫ������    
       for x=1:8
        for y=(x+1):9
           if a(y)<a(x);
               t=a(x);
               a(x)=a(y);
               a(y)=t;
             end
         end
   end
    %ȡ��ֵa(5��
    k(i,j)= a(5);
    end
end
figure();
imshow(uint8(k));
title('��ֵ�˲����')
 