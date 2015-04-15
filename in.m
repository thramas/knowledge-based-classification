inputImage = imread('subset_3_of_imagery_VH_band_1.jpg');
inputImage = rgb2gray(inputImage);
[varianceImg, timeTaken,meanImg]=funcVarianceMap(inputImage, 5, 16);