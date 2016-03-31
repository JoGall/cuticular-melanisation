#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>

//MAIN
int main( int argc, char** argv ){
	
	//ERROR HANDLING
	if(argc < 2){
		std::cout<<"Usage: "<<argv[0]<<" file1 file2 ..."<<std::endl;
		return 0;
				}
				
	//OUTPUT RESULTS FILE: HEADERS
	std::ofstream fout("results.txt");
	fout << "Image" << "\t"<< "meanB" <<"\t"<< "meanG" <<"\t"<< "meanR" <<"\t"<< "hue" <<"\t"<< "sat" <<"\t"<< "value" <<"\t"<< "box1" <<"\t"<< "box2" <<"\t"<< std::endl;

	//FILE LOOP
	for(int i=1;i<argc;i++){	
		
		//CREATE STORAGE
		cv::Mat input,imgGray,imgHSV,imgBlurred,imgThreshed,output;
		input=cv::imread(argv[i],1);
		
		//CONVERT COLOUR
		cvtColor(input, imgGray, CV_BGR2GRAY);
		cvtColor(input, imgHSV, CV_RGB2HSV);
		
		//PRE-PROCESS IMAGE
		cv::blur(imgGray, imgBlurred, cv::Size(9,9));
		cv::threshold(imgBlurred,imgThreshed,155,255,CV_THRESH_BINARY_INV);
//		cv::bilateralFilter(imgGray, imgBlurred, 25, 50,50);
//		cv::adaptiveThreshold(imgGray,imgThreshed, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 201,10);
	
		//FIND ALL CONTOURS
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(imgThreshed.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		//FIND LARGEST CONTOUR
		int tmpMax=0;
		int tmpMaxInd=0;
		for(int k =0;k<(int) contours.size() ; k++){
			if ((contours[k]).size() > tmpMax){
				tmpMax	= (contours[k]).size();
				tmpMaxInd = k; 
			}
		}
		//DRAW LARGEST CONTOUR
		cv::Mat result(imgThreshed.size(),CV_8U,cv::Scalar(0));
		cv::Mat imgOutput(imgThreshed.size(),CV_8U,cv::Scalar(255));
		cv::drawContours(result,contours,tmpMaxInd,cv::Scalar(255),CV_FILLED);
		cv::drawContours(imgOutput,contours,tmpMaxInd,cv::Scalar(0),CV_FILLED);
		
		//FIND MINIMUM ENCLOSING RECTANGLE
		cv::RotatedRect minRect = cv::minAreaRect(cv::Mat(contours[tmpMaxInd]));
		//DRAW RECTANGLE
		cvtColor(imgOutput, imgOutput, CV_GRAY2BGR);
		cv::Point2f vertices[4];
		minRect.points(vertices);
		for (int j = 0; j < 4; j++) {
			line(imgOutput, vertices[j], vertices[(j+1)%4], cv::Scalar(0,0,255),5); }

		//CALCULATE BRIGHTNESS SCORES
		cv::Scalar meansBGR = cv::mean(input, imgThreshed);
		cv::Scalar meansHue = cv::mean(imgHSV, imgThreshed);
		
		//OUTPUT RESULTS FILE: DATA
		fout<< argv[i] <<"\t"<< meansBGR[0] <<"\t"<< meansBGR[1] <<"\t"<< meansBGR[2] <<"\t"<< meansHue[0] <<"\t"<< meansHue[1] <<"\t"<< meansHue[2] <<"\t"<< minRect.size.height <<"\t"<< minRect.size.width <<"\t"<< std::endl;
			
		//WRITE IMAGE MASK
		std::ostringstream text;
		text<< "mask-" <<argv[i];
		cv::imwrite(text.str(),imgOutput);
		
	}
	
	return 1;
}
