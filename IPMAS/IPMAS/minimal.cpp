#include "minimal.h"
using namespace cv;
using namespace std;
void minimal(float* landmark,int* icols, int* irows) {

	Scalar delaunay_color(255, 255, 255), points_color(0, 0, 255);
	
	char path[128] = "";
	char TitleName[128] = "";
	PopFileOpenDlg(NULL, path, TitleName);
	cv::Mat_<unsigned char> img = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
	/*Size dsize;
	dsize.width = 500;
	dsize.height = 500;
	cv::Mat_<unsigned char> img= Mat(dsize, CV_32F);
	cv::resize(img1, img, dsize,CV_INTER_AREA);*/
	//	img2 = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
	{
		printf("Cannot load %s\n", path);
		exit(1);
	}

	int foundface;
//	float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)

	if (!stasm_search_single(&foundface, landmark,
		(const char*)img.data, img.cols, img.rows, path, "../data"))
	{
		printf("Error in stasm_search_single: %s\n", stasm_lasterr());
		exit(1);
	}

	if (!foundface)
		printf("No face found in %s\n", path);
	else
	{
		// draw the landmarks on the image as white dots (image is monochrome)
		stasm_force_points_into_image(landmark, img.cols, img.rows);
		for (int i = 0; i < stasm_NLANDMARKS; i++)
		
			img(cvRound(landmark[i * 2 + 1]), cvRound(landmark[i * 2])) = 255;
			
			
		
	}
	//
	cv::imshow("if the point is not ideal, please make adjustment", img);
	*icols = img.cols;
	*irows = img.rows;

	//trangulations
//	vector<Point> impoints;
//	vector<Point2f> impoints1;
////	impoints.resize(77);
//	for (int i = 0; i < 77; i++)
//	{
//		impoints.push_back(Point(cvRound(landmark[2 * i]), cvRound(landmark[2 * i + 1])));
//
//	}
//	
//	for (int i = 0; i < stasm_NLANDMARKS - 1; i++)
//	{
//
//		line(img, impoints[i], impoints[i+1], delaunay_color, 1, CV_AA, 0);
//
//
//	}
//		
////	imshow("order", img);
//	
//		
//	Rect rect(0, 0, img.cols, img.rows);
//
//	// Create an instance of Subdiv2D
//	Subdiv2D subdiv(rect);
//	// Insert points into subdiv
//	for (vector<Point>::iterator it = impoints.begin(); it != impoints.end(); it++)
//	{
//		subdiv.insert(*it);
//
//
//	}
//	//trangulation
//	vector<Vec6f> imtriangleList;
//	vector<int> trilist;
//	subdiv.getTriangleList(imtriangleList);
//	vector<Point> pt(3);
//	for (size_t i = 0; i < imtriangleList.size(); i++)
//	{
//		Vec6f t = imtriangleList[i];
//		pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
//		pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
//		pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
//		
//		if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
//		{
//			impoints1.push_back(pt[0]);
//			impoints1.push_back(pt[1]);
//			impoints1.push_back(pt[2]);
//			line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
//			line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
//			line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
//			for (int a = 0; a < 77; a++) {
//				if (pt[0] == impoints[a])
//					trilist.push_back(a);
//				if (pt[1] == impoints[a])
//					trilist.push_back(a);
//				if (pt[2] == impoints[a])
//					trilist.push_back(a);
//
//			}
//		}
//	}
	
//	imshow("win_delaunay", img);
	////
	//ofstream f1("trilist.txt");//#include <fstream>  
	//char savePoints[100];//×Ö·ûÊý×é  
	//strcpy_s(savePoints, "quad_pts");
	//f1 << savePoints << endl;
	//for (int i = 0; i < trilist.size(); i++)
	//{
	//	sprintf_s(savePoints, "%d", trilist[i]);
	//	f1 << savePoints << endl;
	//}
	//
	//cv::imwrite("tri.txt", impoints1);
//	for(int i=0;i<=76*2;i++)
//	std::cout << landmark[i] << std::endl;
//	cv::waitKey();
//	landmark = landmarks;
	
}