
#include "MA.h"
using namespace cv;
using namespace std;



void MA(float *landmarks, GLMmodel* pModel, int* icols, int* irows) {
	std::cout << "enter into MA";
	//put img landmarks into vector
	vector<Point> impoints;
	//index of trangulation corner points
	vector<Point> impoints1;
	//all the vertex needs to change
	vector<Point2f> impoints2;
	//output coordinates
	vector<Point2f> impointsO;
	//cordinates of model's landmarks.
	vector<Point> impointsC;
	//coordinates of model's landmarks trangulation.
	vector<Point> impointsD;
	vector<int> trilist;
	vector<int> landmarkindex;
	double s,d;
	//input matrix map, for displaying
	cv::Mat_<unsigned char> img1 = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgout = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgshow1 = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgshow2 = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgshow3 = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgD = Mat::zeros(500, 500, CV_32F);
	cv::Mat_<unsigned char> imgo = Mat::zeros(500, 500, CV_32F);
	
	Scalar delaunay_color(255, 255, 255), points_color(0, 0, 255);
	std::cout << "creat map succeed";

	for (int i = 0; i < 77; i++)
	{
		impoints.push_back(Point(landmarks[2 * i+1], landmarks[2 * i]));
		
	}
	//calcuate scalling function
	s=powf((impoints[0].x - impoints[12].x), 2) + powf((impoints[0].y - impoints[12].y), 2);
	s=sqrtf(s);
	//output img map
	cv::Mat_<unsigned char> imgRect;
	landmarkindex.push_back(458);
	landmarkindex.push_back(254);
	landmarkindex.push_back(457);
	landmarkindex.push_back(577);
	landmarkindex.push_back(579);
	landmarkindex.push_back(111);
	landmarkindex.push_back(311);
	landmarkindex.push_back(77);
	landmarkindex.push_back(432);
	landmarkindex.push_back(430);
	landmarkindex.push_back(275);
	landmarkindex.push_back(173);
	landmarkindex.push_back(449);
	landmarkindex.push_back(92);
	landmarkindex.push_back(453);
	landmarkindex.push_back(121);
	landmarkindex.push_back(524);
	landmarkindex.push_back(261);
	landmarkindex.push_back(263);
	landmarkindex.push_back(264);
	landmarkindex.push_back(529);
	landmarkindex.push_back(224);
	landmarkindex.push_back(385);
	landmarkindex.push_back(178);
	landmarkindex.push_back(361);
	landmarkindex.push_back(371);
	landmarkindex.push_back(370);
	landmarkindex.push_back(362);
	landmarkindex.push_back(375);
	landmarkindex.push_back(541);
	landmarkindex.push_back(253);
	landmarkindex.push_back(539);
	landmarkindex.push_back(540);
	landmarkindex.push_back(570);
	landmarkindex.push_back(164);
	landmarkindex.push_back(554);
	landmarkindex.push_back(50);
	landmarkindex.push_back(238);
	landmarkindex.push_back(49);
	landmarkindex.push_back(11);
	landmarkindex.push_back(203);
	landmarkindex.push_back(372);
	landmarkindex.push_back(35);
	landmarkindex.push_back(422);
	landmarkindex.push_back(105);
	landmarkindex.push_back(386);
	landmarkindex.push_back(202);
	landmarkindex.push_back(36);
	landmarkindex.push_back(307);
	landmarkindex.push_back(306);
	landmarkindex.push_back(483);
	landmarkindex.push_back(500);
	landmarkindex.push_back(414);
	landmarkindex.push_back(331);
	landmarkindex.push_back(344);
	landmarkindex.push_back(321);
	landmarkindex.push_back(327);
	landmarkindex.push_back(495);
	landmarkindex.push_back(515);
	landmarkindex.push_back(241);
	landmarkindex.push_back(243);
	landmarkindex.push_back(516);
	landmarkindex.push_back(347);
	landmarkindex.push_back(348);
	landmarkindex.push_back(194);
	landmarkindex.push_back(191);
	landmarkindex.push_back(396);
	landmarkindex.push_back(421);
	landmarkindex.push_back(559);
	landmarkindex.push_back(566);
	landmarkindex.push_back(406);
	landmarkindex.push_back(407);
	landmarkindex.push_back(209);
	landmarkindex.push_back(352);
	landmarkindex.push_back(354);
	landmarkindex.push_back(518);
	landmarkindex.push_back(259);
	
	std::cout << "landmark input succeed" << endl;

	std::cout << "input coordinates into map succeed" << endl;
	for (int i = 0; i <77; i++) {
		int y = 250+ 1.5*pModel->vertices[3*landmarkindex[i]+0];
		int x = 250- 1.5*pModel->vertices[3*landmarkindex[i]+1];
		if (x > 500 || y > 500)
			std::cout << "out of range" << i << endl;
		impointsC.push_back(Point(x, y));
		imgout(cvRound(x), cvRound(y)) = 255;
		
	}
	imshow("impointsC", imgout);
	d = powf((impointsC[0].x - impointsC[12].x), 2) + powf((impointsC[0].y - impointsC[12].y), 2);
	d = sqrtf(d);
	//scale the landmarks from image to the same size of model landmarks.
	for (int i = 0; i < 77; i++) {
		impoints[i] = impoints[i]*(d/s);
		img1(cvRound(impoints[i].x), cvRound(impoints[i].y)) = 255;
	}
//	imshow("impoints", img1);
	Point M = impointsC[0] - impoints[0];
	//move the landmarks to fit the model landmarks 
	for (int i = 0; i < 77; i++) {
		impoints[i] = impoints[i]+M;
	}
	std::cout << "scalling factor" << d/s << endl;
	for (int i = 1; i <= 595; i++) {
		double y = 250 + 1.5*(pModel->vertices[3 * i + 0]);
		double x = 250 - 1.5*(pModel->vertices[3 * i + 1]);
		std::cout << "x" << x << endl;
		std::cout << "y" << y << endl;
	//	img1(x, y) = i;
		impoints2.push_back(Point(x, y));


	}

	/*impointsC.push_back(Point(0, 0));
	impointsC.push_back(Point(0, 499));
	impointsC.push_back(Point(499, 0));
	impointsC.push_back(Point(498, 498));
	impointsC.push_back(Point(0, 250));
	impointsC.push_back(Point(499, 250));
	impointsC.push_back(Point(250, 0));
	impointsC.push_back(Point(250, 499));*/

	
	
	std::cout << "model landmarks input succeed" << endl;
		// Rectangle to be used with Subdiv2D

	//Rect rect(0, 0, 500, 500);

	//// Create an instance of Subdiv2D
	//Subdiv2D subdiv(rect);
	//// Insert points into subdiv
	//for (vector<Point>::iterator it = impointsC.begin(); it != impointsC.end(); it++)
	//{
	//	subdiv.insert(*it);
	//	
	//}
	////trangulation
	//vector<Vec6f> imtriangleList;
	//subdiv.getTriangleList(imtriangleList);
	//
	vector<Point> pt(3);
	//for (size_t i = 0; i < imtriangleList.size(); i++)
	//{
	//	Vec6f t = imtriangleList[i];
	//	pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
	//	pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
	//	pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

	//	if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
	//	{
	//		impointsD.push_back(pt[0]);
	//		impointsD.push_back(pt[1]);
	//		impointsD.push_back(pt[2]);
	//		
	//		for (int a = 0; a < 77; a++) {
	//			
	//			if (pt[0] == impointsC[a]) {
	//				trilist.push_back(a);	
	//			}		
	//		}
	//		for (int a = 0; a < 77; a++) {
	//			if (pt[1] == impointsC[a]) {
	//				trilist.push_back(a);
	//			}
	//		}
	//		for (int a = 0; a < 77; a++) {
	//			if (pt[2] == impointsC[a]){
	//				trilist.push_back(a);
	//			}
	//		}
	//	}
	//}
	
	ifstream ifs("newtrilist.txt");
	double X, Y;
		while (ifs >> X >> Y)
		{
			
			cout <<"X"<< X <<"Y"<<Y<< endl;
			impointsD.push_back(Point(X, Y));
					for (int a = 0; a < 77; a++) {
						
						if (Point(X,Y) == impointsC[a]) {
							trilist.push_back(a);	
						}		
					}
		}
	
	for (int i = 0; i < impointsD.size(); i++) {
		imgD(cvRound(impointsD[i].x), cvRound(impointsD[i].y)) = 255;
	}
	imshow("impointsD", imgD);
//	imshow("another shit",imgshow3);
	std::cout << "trianglelist for input image get" << trilist.size()<< endl;

	for (int i = 0; i < trilist.size(); i++) {
		impoints1.push_back(impoints[trilist[i]]);
		
	}
	for (int i = 0; i < impoints1.size(); i++) {
		imgo(cvRound(impoints1[i].x), cvRound(impoints1[i].y)) = 255;
	}
//	imshow("impoints1", imgo);
	//use impoints1 to morph impointsD
	std::cout << "trianglelist for model get" << endl;
	for (int i = 0; i < trilist.size()/3; i++)
	{
		pt[0] = impoints1[3*i];
		pt[1] = impoints1[3*i+1];
		pt[2] = impoints1[3*i+2];
		line(imgshow2, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
		line(imgshow2, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
		line(imgshow2, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
	}
//	imshow("what is this", imgshow2);
	//calculating new locations of each vertex
	for (int i = 0; i < 595; i++) {
		int flag = 0;
		for (int z = 0; z < trilist.size() / 3; z++) {
			
		Point A=impointsD[3*z];
		Point B=impointsD[3*z+1];
		Point C=impointsD[3*z+2];
		Point P = impoints2[i];
		Point v0 = C - A;
		Point v1 = B - A;
		Point v2 = P - A;
		
		float dot00 = v0.x*v0.x + v0.y*v0.y;
		float dot01 = v0.x*v1.x + v0.y*v1.y;
		float dot02 = v0.x*v2.x + v0.y*v2.y;
		float dot11 = v1.x*v1.x + v1.y*v1.y;
		float dot12 = v1.x*v2.x + v1.y*v2.y;
		
		float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);
		float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
		float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
		
		if (u >= 0 && u < 1 && v>=0 && v < 1 && u + v <= 1) {
			std::cout << i << endl;
			flag = 1;
			impointsO.push_back(impoints1[3 * z] + u*(impoints1[3 * z + 2] - impoints1[3 * z]) + v*(impoints1[3 * z + 1] - impoints1[3 * z]));
			break;

		}
		
		}
		if (flag == 0) {
			impointsO.push_back(impoints2[i]);
		}
	}
	// derictly replace landmarks from model with landmarks from image
	/*int count = 0;
	for (int i = 0; i < 595; i++) {
		int flg = 0;
		
		for (int z = 0; z < 77; z++) {
			if (landmarkindex[z] == i) {
				impointsO.push_back(Point(impoints[z].y, impoints[z].x));
				flg = 1;
				std::cout << "Z" << z << endl;
				std::cout << "I" << i << endl;
				count++;
				std::cout << "count" << count << endl;
			}
		}
		if (flg == 0) {
			impointsO.push_back(impoints2[i]);
		}
	}*/
		

	//for (int i = 0; i < impoints1.size()/ 3; i++) {
	//	vector<Point2f> t1, t;
	//	// Triangle corners for image 1.
	//	t.push_back(impoints1[i]);
	//	t.push_back(impoints1[i+1]);
	//	t.push_back(impoints1[i+2]);
	//	std::cout << "t" << impoints1[i] << impoints1[i + 1] << impoints1[i + 2] << endl;

	//	t1.push_back(impointsD[i]);
	//	t1.push_back(impointsD[i + 1]);
	//	t1.push_back(impointsD[i + 2]);
	//	std::cout << "t1" << impointsD[i] << impointsD[i + 1] << impointsD[i + 2] << endl;
	//	Rect r = boundingRect(t);// input one
	//	Rect r1 = boundingRect(t1);//generate from model
	//	// Offset points by left top corner of the respective rectangles
	//	std::cout << "1" << endl;
	//	vector<Point2f> t1Rect, tRect;
	//	vector<Point> tRectInt;

	//	for (int i = 0; i < 3; i++)
	//	{
	//		tRect.push_back(Point2f(t[i].x - r.x, t[i].y - r.y));

	//		tRectInt.push_back(Point(t[i].x - r.x, t[i].y - r.y)); // for fillConvexPoly

	//		t1Rect.push_back(Point2f(t1[i].x - r1.x, t1[i].y - r1.y));

	//	}
	//	std::cout << "2" << endl;
	//	Mat mask = Mat::zeros(r.height, r.width, CV_32F);
	//	std::cout << "2.1" << endl;
	//	fillConvexPoly(mask, tRectInt, 1.0, 16, 0);
	//	std::cout << "2.2" << endl;
	//	Mat img1Rect;
	//	img1(r1).copyTo(img1Rect);
	//	std::cout << "2.3" << endl;
	//	Mat warpImage1 = Mat::zeros(r.height, r.width, img1Rect.type());
	//	std::cout << "3" << endl;
	//	// Given a pair of triangles, find the affine transform.
	//	Mat warpMat = getAffineTransform(t1Rect, tRect);
	//	std::cout << "size of warp Mat rows" << warpMat.rows<<"cols"<<warpMat.cols<< endl;
	//	// Apply the Affine Transform just found to the src image
	//	warpAffine(img1Rect, warpImage1, warpMat, warpImage1.size(), INTER_LINEAR, BORDER_REFLECT_101);
	//	std::cout << "image warping complete" << endl;
	//	// Copy triangular region of the rectangular patch to the output image
	//	
	//	multiply(warpImage1, mask, imgRect);
	//	std::cout << "5.1" << endl;
	//	multiply(imgout(r), 1.0-mask, imgout(r));
	//	std::cout << "5.2" << endl;
	//	imgout(r) = imgout(r) + imgRect;
	//}
	/*for (int k = 0; k < 500; k++) {
		for (int l = 0; l < 500; l++) {
			if (imgout(k, l) != 0)
				imgshow(k, l) = 255;
		}
	}
	imshow("final shit", imgshow);*/
	
	std::cout << "calculation complete" << endl;
	std::cout << "size of impointsO" <<impointsO.size()<< endl;
	cv::Mat_<unsigned char> imgshow = Mat::ones(500, 500, CV_32F);
	for (int i = 0; i < impointsO.size(); i++) {
		imgshow(cvRound(impointsO[i].x), cvRound(impointsO[i].y)) = 255;
		imgshow2(cvRound(impointsO[i].x), cvRound(impointsO[i].y)) = 255;
		imgshow3(cvRound(impointsO[i].x), cvRound(impointsO[i].y)) = 255;
	}
//	imshow("final shit", imgshow);
//	imshow("what is this ", imgshow2);
//	imshow("another shit ", imgshow3);
	//put coordinats back into model
	std::cout << "img cols" <<img1.cols<< endl;
	std::cout << "img rows" << img1.rows << endl;
	GLfloat a, b;
	int hl = 0;
	int num;
	for (int i = 0; i < impointsO.size(); i++) {
		pModel->vertices[3 * i + 3] = (impointsO[i].y - 250)/1.5;
		pModel->vertices[3 * i + 4] = (250 -impointsO[i].x )/1.5;
	}
	std::cout << "hl" << hl<<endl;
	std::cout << "insert complete" <<  endl;

	glmWriteOBJ(pModel, "newface2.obj", GLM_NONE);
	
	
	}
	//std::cout<<"fuck off";
	
