%�ֶ����Ա任���Ҷ��и
 
I=imread('jll.bmp');
a=isgray(I)
b=isrgb(I)
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
imshow(uint8(J));
J=double(J);
[M,N]=size(J);
for i=1:M
    for j=1:N
    if J(i,j)<100                   %�Ҷ�С��100�����أ��ҶȲ���
        J(i,j)=0;
    elseif J(i,j)>100&&J(i,j)<200   %�ҶȽ���50��200֮��ģ���Ҷȵ���150
        J(i,j)=150;
    else J(i,j)=J(i,j);            %�Ҷȴ���200�����أ��Ҷ�ֵ����
    end
  end
end
figure(2);
imshow(uint8(J));
title('�Ҷ��и�')
 