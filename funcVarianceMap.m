% *************************************************************************
% Title: Function-Compute Variance map of the image
% Author: Samarth Khare
% Created: October 2014
% Copyright Samarth Khare, 2014
% Inputs: Input Image (var: inputImage), Window Size (var: windowSize),
% Threshold (var: thresh) Typical value is 140
% Outputs: Variance Map (var: varianceImg) , Time taken (var: timeTaken)
% Example Usage of Function: [varianceImg, timeTaken]=funcVarianceMap('MonopolyLeftColor.png', 5, 9);
% *************************************************************************
function [varianceImg, timeTaken,meanImg]=funcVarianceMap(inputImage, windowSize, thresh)
try 
    % Grab the image information (metadata) of input image using the function imfinfo
    inputImageInfo=imfinfo(inputImage);
    if(getfield(inputImageInfo,'ColorType')=='truecolor')
    % Read an image using imread function, convert from RGB color space to
    % grayscale using rgb2gray function and assign it to variable inputImage
        inputImage=rgb2gray(imread(inputImage));
        % Convert the image from uint8 to double
        inputImage=double(inputImage);
    else if(getfield(inputImageInfo,'ColorType')=='grayscale')
    % If the image is already in grayscale, then just read it.        
            inputImage=imread(inputImage);
            % Convert the image from uint8 to double
            inputImage=double(inputImage);
        else
            error('The Color Type of Left Image is not acceptable. Acceptable color types are truecolor or grayscale.');
        end
    end
catch
    % if it is not an image but a variable
    inputImage=inputImage;
end
% Find the size (columns and rows) of the input image and assign the rows to
% variable nr, and columns to variable nc
[nr,nc] = size(inputImage);
% Check the size of window to see if it is an odd number.
if (mod(windowSize,2)==0)
    error('The window size must be an odd number.');
end
% Create an image of size nr and nc, fill it with zeros and assign
% it to variable meanImg
for a=1:129
            for b=1:129
                meanImg(a,b) = inputImage(a,b);
                varianceImg(a,b) = inputImage(a,b);
            end
end
%meanImg=zeros(nr, nc);
% Create an image of size nr and nc, fill it with zeros and assign
% it to variable varianceImg
%varianceImg=zeros(nr, nc);
% Find out how many rows and columns are to the left/right/up/down of the
% central pixel based on the window size
win=(windowSize-1)/2;
tic; % Initialize the timer to calculate the time consumed.
% Compute a map of mean values
for i=1+win:nr-win
    for j=1+win:nc-win
        sum=0.0;
        for a=-win:win
            for b=-win:win
                sum=sum+inputImage((i+a),(j+b));
            end
        end
        meanImg(i,j)=double(sum/(windowSize*windowSize));
    end
end
% Compute a map of variance values
for i=1+win:nr-win
    for j=1+win:nc-win
        sum=0;
        for a=-win:win
            for b=-win:win
                sum=sum+((inputImage((i+a),(j+b))-meanImg(i,j))^2);
            end
        end         
        var=sum/((windowSize*windowSize)-1);
        % Apply threshold to produce a binarized variance map
        if (var > thresh)
            varianceImg(i,j) = var;
        else
            varianceImg(i,j) = var;
        end
    end
end
% Stop the timer to calculate the time consumed.
timeTaken=toc;
