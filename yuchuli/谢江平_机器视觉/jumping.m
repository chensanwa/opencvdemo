function varargout = jumping(varargin)
% JUMPING M-file for jumping.fig
%      JUMPING, by itself, creates a new JUMPING or raises the existing
%      singleton*.
%
%      H = JUMPING returns the handle to a new JUMPING or the handle to
%      the existing singleton*.
%
%      JUMPING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in JUMPING.M with the given input arguments.
%
%      JUMPING('Property','Value',...) creates a new JUMPING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before jumping_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to jumping_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help jumping

% Last Modified by GUIDE v2.5 17-Oct-2009 22:03:01

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @jumping_OpeningFcn, ...
                   'gui_OutputFcn',  @jumping_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before jumping is made visible.
function jumping_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to jumping (see VARARGIN)

% Choose default command line output for jumping
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes jumping wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = jumping_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%ì¨¨
 %求反
 clear;
I=imread('001.jpg'); 
%彩色图像转为灰度图像
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

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%
%对数变换
I=imread('001.jpg');
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



% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%¨¨¨
%分段线性变换（灰度切割）
 
I=imread('001.jpg');
a=isgray(I);
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
    if J(i,j)<100                   %灰度小于100的像素，灰度不变
        J(i,j)=0;
    elseif J(i,j)>100&&J(i,j)<200   %灰度介于50和200之间的，令灰度等于150
        J(i,j)=150;
    else J(i,j)=J(i,j);            %灰度大于200的像素，灰度值不变
    end
  end
end
figure(2);
imshow(uint8(J));
title('灰度切割')

% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 %均值滤波
H=imread('001.jpg'); 
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
title('灰度图像')
J=double(J);
[M,N]=size(J);  %均值滤波
for i=2:M-1;
    for j=2:N-1; 
        K(i,j)=1/8*(J(i-1,j-1)+J(i-1,j)+J(i-1,j+1)+J(i,j-1)+J(i,j)+J(i,j+1)+J(i+1,j-1)+J(i+1,j)+J(i+1,j+1));
    end
end
figure(2);
imshow(uint8(K));
title('均值滤波结果')
% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%中值滤波
H=imread('salt&pepper.tif');  %读取添加了椒盐噪声的图像
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
title('添加了椒盐噪声的图像')
I=double(J);             %中值滤波
[M,N]=size(I);
a=zeros(1,9);
for i=2:M-1;
    for j=2:N-1;
        a(1)=I(i-1,j-1); %定义3*3模块 
        a(2)=I(i-1,j);
        a(3)=I(i-1,j+1);
        a(4)=I(i,j-1);
        a(5)=I(i,j);
        a(6)=I(i,j+1);
        a(7)=I(i+1,j-1);
        a(8)=I(i+1,j);
        a(9)=I(i+1,j+1);
   %3*3模板元素冒泡排序    
       for x=1:8
        for y=(x+1):9
           if a(y)<a(x);
               t=a(x);
               a(x)=a(y);
               a(y)=t;
             end
         end
   end
    %取中值a(5）
    k(i,j)= a(5);
    end
end
figure();
imshow(uint8(k));
title('中值滤波结果')
 


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%拉普拉斯算子
H=imread('001.jpg');
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
% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%直方图均衡化 
 H=imread('002.jpg'); 
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
s=double(J);
sum=M*N; 
k=zeros(1,256); 
e=zeros(1,256); 
t=zeros(size(s)); 
for i=1:M 
    for j=1:N 
          k(s(i,j)+1)=k(s(i,j)+1)+1; %原图像概率密度 
    end 
end 
k=k./sum; 
for i=1:256 
    for j=1:i 
        e(i)=e(i)+k(j); %累积分布 
    end 
end 
for i=1:256 
       e(i)=floor(e(i)*255+0.5); %映射关系 
end 
for i=1:M 
    for j=1:N 
        t(i,j)=e(s(i,j)+1); 
    end 
end 
s=uint8(s); 
t=uint8(t); 
figure;
subplot(2,2,1); 
imshow(s); 
title('原图')
 
subplot(2,2,2); 
imhist(s);
title('原图直方图')
 
subplot(2,2,3); 
imshow(t); 
title('直方图均衡化后的图像')
  
subplot(2,2,4); 
imhist(t); 
title('直方图均衡化后图像的直方图')
 

% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%结构光条纹中心求法
clear;
I=imread('picture3.jpg');
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
title('二值图像')
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
imshow(d);
title('初步求得的明纹中心')
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


% --- Executes on button press in pushbutton9.
function pushbutton9_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%彩色图转灰度图 
clear;
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