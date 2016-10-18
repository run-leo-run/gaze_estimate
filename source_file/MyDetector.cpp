#include "MyDetector.h"

MyDetector::MyDetector()
{
	face_cascade_name = "haarcascade_frontalface_alt.xml";
	if( !face_cascade.load( face_cascade_name ) )
	{ 
		printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n"); 
	}
}

std::vector<cv::Point> MyDetector::returnFeature()
{
	std::vector<cv::Point>  feature;
	feature.push_back(irisL);
	feature.push_back(irisR);
	feature.push_back(LcornerL);
	feature.push_back(LcornerR);
	feature.push_back(RcornerL);
	feature.push_back(RcornerR);
	return feature;

}
void MyDetector::detectAndDisplay( cv::Mat frame )
{
  std::vector<cv::Rect> faces;
  //cv::Mat frame_gray;

  std::vector<cv::Mat> rgbChannels(3);
  cv::split(frame, rgbChannels);
  cv::Mat frame_gray = rgbChannels[2];

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );
  //cv::pow(frame_gray, CV_64F, frame_gray);
  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
//  findSkin(debugImage);

  for( int i = 0; i < faces.size(); i++ )
  {
    rectangle(debugImage, faces[i], 1234);
  }
  //-- Show what you got
  if (faces.size() > 0) {
    findEyes(frame_gray, faces[0]);
  }
}

void MyDetector::findEyes(cv::Mat frame_gray, cv::Rect face) {
  cv::Mat faceROI = frame_gray(face);
  cv::Mat debugFace = faceROI;
  cv::Point tmp_left_center , tmp_right_center;//用来保存在EyeRegion中虹膜中心的位置
  if (kSmoothFaceImage) {
    double sigma = kSmoothFaceFactor * face.width;
    GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
  }
  //-- Find eye regions and draw them
  int eye_region_width = face.width * (kEyePercentWidth/100.0);
  int eye_region_height = face.width * (kEyePercentHeight/100.0);
  int eye_region_top = face.height * (kEyePercentTop/100.0);
  cv::Rect leftEyeRegion(face.width*(kEyePercentSide/100.0),
                         eye_region_top,eye_region_width,eye_region_height);
  cv::Rect rightEyeRegion(face.width - eye_region_width - face.width*(kEyePercentSide/100.0),
                          eye_region_top,eye_region_width,eye_region_height);

  //-- Find Eye Centers
  cv::Point leftPupil = findEyeCenter(faceROI,leftEyeRegion,"Left Eye");
  cv::Point rightPupil = findEyeCenter(faceROI,rightEyeRegion,"Right Eye");

  tmp_left_center = leftPupil;
  tmp_right_center = rightPupil;//记录在人眼区域的相对坐标
  // get corner regions
  cv::Rect leftRightCornerRegion(leftEyeRegion);
  leftRightCornerRegion.width -= leftPupil.x;
  leftRightCornerRegion.x += leftPupil.x;
  leftRightCornerRegion.height /= 2;
  leftRightCornerRegion.y += leftRightCornerRegion.height / 2;
  cv::Rect leftLeftCornerRegion(leftEyeRegion);
  leftLeftCornerRegion.width = leftPupil.x;
  leftLeftCornerRegion.height /= 2;
  leftLeftCornerRegion.y += leftLeftCornerRegion.height / 2;
  cv::Rect rightLeftCornerRegion(rightEyeRegion);
  rightLeftCornerRegion.width = rightPupil.x;
  rightLeftCornerRegion.height /= 2;
  rightLeftCornerRegion.y += rightLeftCornerRegion.height / 2;
  cv::Rect rightRightCornerRegion(rightEyeRegion);
  rightRightCornerRegion.width -= rightPupil.x;
  rightRightCornerRegion.x += rightPupil.x;
  rightRightCornerRegion.height /= 2;
  rightRightCornerRegion.y += rightRightCornerRegion.height / 2;
  //rectangle(debugFace,leftRightCornerRegion,200);
  //rectangle(debugFace,leftLeftCornerRegion,200);
  //rectangle(debugFace,rightLeftCornerRegion,200);
  //rectangle(debugFace,rightRightCornerRegion,200);
  
  // change eye centers to face coordinates
  rightPupil.x += rightEyeRegion.x;
  rightPupil.y += rightEyeRegion.y;
  leftPupil.x += leftEyeRegion.x;
  leftPupil.y += leftEyeRegion.y;
  // draw eye centers
  //circle(debugFace, rightPupil, 3, 1234);
  //circle(debugFace, leftPupil, 3, 1234);

  //-- Find Eye Corners  -- leo
  cv::Rect Left_eye_corner_region(leftEyeRegion);
  Left_eye_corner_region.height /= 2;
  Left_eye_corner_region.y += Left_eye_corner_region.height / 2;
  rectangle(debugFace,Left_eye_corner_region,200);

  cv::Rect Right_eye_corner_region(rightEyeRegion);
  Right_eye_corner_region.height /= 2;
  Right_eye_corner_region.y += Right_eye_corner_region.height / 2;
  rectangle(debugFace,Right_eye_corner_region,200);
  
  cv::Mat Right_eye_small_region = debugFace( Right_eye_corner_region ).clone();
  cv::Mat Left_eye_small_region = debugFace( Left_eye_corner_region).clone();
  //eyeCenter 坐标转换
  //转换到 small_region 里的坐标系
  cv::Point right_pupil_small_region , left_pupil_small_region;
  right_pupil_small_region.x = tmp_right_center.x;
  right_pupil_small_region.y = tmp_right_center.y - rightEyeRegion.height / 4;
  left_pupil_small_region.x = tmp_left_center.x;
  left_pupil_small_region.y = tmp_left_center.y - leftEyeRegion.height / 4;
  
  //circle(Right_eye_small_region, right_pupil_small_region, 3, 1234);
  //circle(Left_eye_small_region, left_pupil_small_region, 3, 1234);
  cv::Point LdetaL , LdetaR ,Lcornerl ,Lcornerr;
  cv::Point RdetaL , RdetaR , Rcornerl ,Rcornerr;

  test_file += "right";
  detecteye_row(Right_eye_small_region ,right_pupil_small_region,Right_eye_small_region.cols ,RdetaL ,RdetaR);
  test_file += "left";
  detecteye_row(Left_eye_small_region ,left_pupil_small_region,Left_eye_small_region.cols , LdetaL ,LdetaR);

  Lcornerl = leftPupil - LdetaL;   
  Lcornerr = leftPupil - LdetaR;   
  Rcornerl = rightPupil - RdetaL;  
  Rcornerr = rightPupil - RdetaR; 

  /*LcornerL.x = leftPupil.x + LdetaL.x;   LcornerL.y = leftPupil.y + LdetaL.y;
  LcornerR.x = leftPupil.x + LdetaR.x;   LcornerR.y = leftPupil.y + LdetaR.y;
  RcornerL.x = rightPupil.x + RdetaL.x;  RcornerL.y = rightPupil.y + RdetaL.y;
  RcornerR.x = rightPupil.x + RdetaR.x;  RcornerR.y = rightPupil.y + RdetaR.y;
  */
  circle(debugFace, rightPupil, 3, 1234);
  circle(debugFace, leftPupil, 3, 1234);

  circle(debugFace , Lcornerl , 2 ,1234);
  circle(debugFace , Lcornerr , 2 ,1234);
  circle(debugFace , Rcornerl , 2 ,1234);
  circle(debugFace , Rcornerr , 2 ,1234);

  this->debugImage = debugFace;
  this->irisL = leftPupil;
  this->irisR = rightPupil;
  this->LcornerL = Lcornerl;
  this->LcornerR = Lcornerr;
  this->RcornerL = Rcornerl;
  this->RcornerR = Rcornerr;
  //detecteye_row( 
  //imshow(main_window_name,debugImage);

  //-- Find Eye Corners  -- the author
  if (kEnableEyeCorner) {
    cv::Point2f leftRightCorner = findEyeCorner(faceROI(leftRightCornerRegion), true, false);
    leftRightCorner.x += leftRightCornerRegion.x;
    leftRightCorner.y += leftRightCornerRegion.y;
    cv::Point2f leftLeftCorner = findEyeCorner(faceROI(leftLeftCornerRegion), true, true);
    leftLeftCorner.x += leftLeftCornerRegion.x;
    leftLeftCorner.y += leftLeftCornerRegion.y;
    cv::Point2f rightLeftCorner = findEyeCorner(faceROI(rightLeftCornerRegion), false, true);
    rightLeftCorner.x += rightLeftCornerRegion.x;
    rightLeftCorner.y += rightLeftCornerRegion.y;
    cv::Point2f rightRightCorner = findEyeCorner(faceROI(rightRightCornerRegion), false, false);
    rightRightCorner.x += rightRightCornerRegion.x;
    rightRightCorner.y += rightRightCornerRegion.y;
    circle(faceROI, leftRightCorner, 3, 200);
    circle(faceROI, leftLeftCorner, 3, 200);
    circle(faceROI, rightLeftCorner, 3, 200);
    circle(faceROI, rightRightCorner, 3, 200);
	//String x;
	//x = test_file + "coner.jpg";
	////const cv::String ss(x);
	//imwrite(x,faceROI);

  }

  //imshow(face_window_name, faceROI);
//  cv::Rect roi( cv::Point( 0, 0 ), faceROI.size());
//  cv::Mat destinationROI = debugImage( roi );
//  faceROI.copyTo( destinationROI );
}

int MyDetector::detecteye_row( cv::Mat& eyeROI , cv::Point eyeCenter , int eye_region_width , cv::Point &detaL , cv::Point &detaR)
{
	//这里的eyeROI就是眼睛区域
	//int n = (eyeROI.cols/100)*2 + 1;
	int n = 5;
	cv::Mat kernel( 1, n, CV_32F, cv::Scalar(0));
	cv::Mat face_gradient;
	face_gradient.create(eyeROI.size(),eyeROI.type());

	for(int i = 0;i < kernel.cols;i++)
	{     
		if(i <= ((kernel.cols /2)-1)) kernel.at<float>(0, i) = 1.0;
		else if ( i >= (kernel.cols /2)+1) kernel.at<float>(0, i) = -1.0;
	}


	filter2D( eyeROI, face_gradient, eyeROI.depth(), kernel);

	//--4.2 complete the sun of each row in face_gradient
	cv::Mat sumOfrow(1,face_gradient.rows,CV_32F,cv::Scalar(2));		
	cv::Scalar sum_tmp;
	double mintmp = 0;
	double maxtmp = 0;
	int minidx = 0;
	int maxidx = 0;
	int loc ;
	
	
	for(int i =0;i<face_gradient.rows;i++)
	{			
		sum_tmp = sum(face_gradient.row(i));
		sumOfrow.at<float>(0,i) = sum_tmp[0];
	}
	
	loc = maxofrow(sumOfrow);

	//line(eyeROI ,cv::Point2f(0,loc),cv::Point2f(eyeROI.cols,loc),cv::Scalar(0,0,0));

	//minMaxIdx(sumOfrow,&mintmp,&maxtmp,&minidx,&maxidx);
	//
	//loc = maxidx;
	cv::Mat corner_value , corner_row;	
	if( (loc + 0.3*eyeROI.rows) < ( eyeROI.rows -1 ))
		corner_row = eyeROI.rowRange(loc , loc + 0.3*eyeROI.rows);
	else
		corner_row = eyeROI.rowRange(loc ,eyeROI.rows -1);
	
	//人眼中心需要转换坐标系
	cv::Point eye_pupil;
	cv::Mat left_corner_row , right_corner_row;
	//cv::Point left_corner , right_corner;
	cv::Point tmp;
	double tmpa,tmpb;
	left_corner_row = corner_row.colRange(cv::Range(0,eyeCenter.x));
	right_corner_row = corner_row.colRange(cv::Range(eyeCenter.x,corner_row.cols - 1));

	//--just test
	cv::Point left_corner_center(0.5*left_corner_row.cols , 0.5*left_corner_row.rows + loc);
	cv::Point right_corner_center(0.5*right_corner_row.cols + eyeCenter.x , 0.5*left_corner_row.rows + loc);
	
	
	//use the goodFeatureToTrack + subpixCorner
	std::vector<cv::Point2f> left_corner_track , right_corner_track;
	corner_track(left_corner_row , left_corner_track);
	for(int i = 0;i < left_corner_track.size();i++)
	{
		left_corner_track[i].y += loc;
		//left_corner_center
		//circle(eyeROI , left_corner_track[i],2 ,Scalar(255,255,255));
		
	}

	corner_track(right_corner_row , right_corner_track);
	for(int i = 0;i < right_corner_track.size();i++)
	{
		right_corner_track[i].y += loc;
		right_corner_track[i].x += eyeCenter.x;
		//circle(eyeROI , right_corner_track[i],2 ,Scalar(255,255,255));

	}
	//circle(eyeROI ,left_corner_center , 3, cv::Scalar(0,0,0));
	//circle(eyeROI ,right_corner_center , 3, cv::Scalar(0,0,0));
	circle(eyeROI , eyeCenter ,4 ,cv::Scalar(0,0,0));

	//--找两边眼角区域的眼角
	cv::Point leftCorner , rightCorner;
	leftCorner = eye_corner_detect(left_corner_track ,left_corner_center ,loc);
	if( leftCorner.x ==0 && leftCorner.y == 0)
		leftCorner = eye_corner_detect(right_corner_track , left_corner_center, loc);

	rightCorner = eye_corner_detect(right_corner_track , right_corner_center ,loc);
	if( rightCorner.x == 0 && rightCorner.y == 0)
		rightCorner = eye_corner_detect(left_corner_track,right_corner_center ,loc);

	detaL = eyeCenter - leftCorner;
	detaR = eyeCenter - rightCorner;

	//circle(eyeROI ,eyeCenter - detaL , 2, cv::Scalar(255,255,255));
	//circle(eyeROI ,eyeCenter - detaR , 2, cv::Scalar(255,255,255));

	//eye_corner_detect(std::vector<Point2f>) left_corner_track , cv::Point &eye_center)

	//minMaxLoc(left_harris_row , &tmpa, &tmpb ,&tmp ,&left_corner);
	//left_corner.y += loc;
	//minMaxLoc(right_harris_row , &tmpa, &tmpb ,&tmp ,&right_corner);
	//right_corner.y += loc;
	//right_corner.x += eye_corner_pairs.y;

	//circle(eyeROI,left_corner ,3 ,Scalar(255,255,255));
	//circle(eyeROI,right_corner,3 , Scalar(255,255,255));

	//String x;
	//x = test_file + "coner.jpg";
	////const cv::String ss(x);
	//imwrite(x,eyeROI);
	

	//Point p1 = Point(0,loc);
	//Point p2 = Point(eyeROI.cols,loc);
	//line(eyeROI ,p1, p2, Scalar(0,100,255)); 

	return loc;
}

int MyDetector::maxofrow(cv::Mat &row)
{
	float a,b;
	int loc = row.cols / 2;
	float max;
	for(int i = 0; i<row.cols  ;i++)
	{
		if(!i)
		{
			a = row.at<float>(0,i);
			b = row.at<float>(0,i+1);
			max = ( a > b ? a :b);	
		}
		if(max < row.at<float>(0,i)) 
		{
			max = row.at<float>(0,i);
			loc = i;
		}

	}
	return loc;
}

void MyDetector::corner_track(cv::Mat &src_gray , std::vector<cv::Point2f> &corners) 
{
  /// Parameters for Shi-Tomasi algorithm
  int maxCorners = 10;
  //vector<Point2f> corners;
  double qualityLevel = 0.01;
  double minDistance = 10;
  int blockSize = 3;
  bool useHarrisDetector = false;
  double k = 0.04;

  /// Copy the source image
  //Mat copy;
  //copy = src.clone();

  /// Apply corner detection
  goodFeaturesToTrack( src_gray,
                       corners,
                       maxCorners,
                       qualityLevel,
                       minDistance,
                       cv::Mat(),
                       blockSize,
                       useHarrisDetector,
                       k );

  /// Set the neeed parameters to find the refined corners
  
  cv::Size winSize = cv::Size( 2, 2 );//注意，要防止越界

  cv::Size zeroZone = cv::Size( -1, -1 );
  cv::TermCriteria criteria = cv::TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );
 
  /// Calculate the refined corner locations
  if(corners.size()>0)
	cv::cornerSubPix( src_gray, corners, winSize, zeroZone, criteria );


}

cv::Point MyDetector::eye_corner_detect(std::vector<cv::Point2f> &corner_track , cv::Point &eye_centerO , int loc)
{
	float min ;
	cv::Point min_corner_can(0,0); 
	cv::Point2f eye_center;
	//eye_center.x = eye_centerO.x;
	//eye_center.y = eye_centerO.y;
	eye_center = eye_centerO;
	for(int i =0; i<corner_track.size(); i++)
	{
		cv::Point Ptmp = corner_track[i] - eye_center;
		float tmp = 0.5*((corner_track[i].y - loc) * (corner_track[i].y - loc))+ 
			        0.5*(Ptmp.x * Ptmp.x)+ 0.5*(Ptmp.y * Ptmp.y);
				    
		if(i == 0) 
		{
			min = tmp;
			min_corner_can = corner_track[i];
		}
		else
		{
			if(tmp < min)
				{
					min_corner_can = corner_track[i];
					min = tmp;
				}
		}
	}
	return min_corner_can;

}