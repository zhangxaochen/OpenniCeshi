/** 参考： http://blog.csdn.net/chenxin_130/article/details/6696187
 ** by zhangxaochen
 ** 
 **/

#include <iostream>
#include <string>
#include <XnCppWrapper.h>
#include <XnLog.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void checkOpenNIError(XnStatus rc, string status){
	if(rc != XN_STATUS_OK){
		cerr<<status<<" Error: "<<xnGetStatusString(rc)<<endl;
		
	}
}//checkOpenNIError

void main(){
	cout<<"hello"<<endl;
	//1.
	XnStatus rc = XN_STATUS_OK;
	xn::DepthMetaData depthMD;
	xn::ImageMetaData imageMD;
	
	//2.
	xn::Context ctx;
	rc = ctx.Init();
	checkOpenNIError(rc, "init context");

	string dataFile = "../../data/t-fast.oni";
	rc = ctx.OpenFileRecording(dataFile.c_str());
	
	checkOpenNIError(rc, "OpenFileRecording");

	xn::DepthGenerator dg;
	rc = dg.Create(ctx);
	//rc = ctx.FindExistingNode(XN_NODE_TYPE_DEPTH, dg);
	checkOpenNIError(rc, "create dg");

	xn::ImageGenerator ig;
	rc = ig.Create(ctx);
	//rc = ctx.FindExistingNode(XN_NODE_TYPE_IMAGE, ig);
	checkOpenNIError(rc, "create ig");

// 	bool mirror = false;
// 	dg.GetMirrorCap().SetMirror(mirror);
// 	ig.GetMirrorCap().SetMirror(mirror);


	//3. 
	XnMapOutputMode mapMode;
	mapMode.nXRes = 640;
	mapMode.nYRes = 480;
	mapMode.nFPS = 30;
	
	rc = dg.SetMapOutputMode(mapMode);
	checkOpenNIError(rc, "dg.SetMapOutputMode");
	rc = ig.SetMapOutputMode(mapMode);
	checkOpenNIError(rc, "ig.SetMapOutputMode");
	
	//4. 两镜头切换视角，重要
	//dg.GetAlternativeViewPointCap().SetViewPoint(ig);
	//ig.GetAlternativeViewPointCap().SetViewPoint(dg);

	//5. read data
	rc = ctx.StartGeneratingAll();

	//6. 
	//rc = ctx.WaitNoneUpdateAll();

	char key = 0;
	while((key != 27 ) && !(rc = ctx.WaitAnyUpdateAll()) ){
// 	while(key != 27 ){
// 		ctx.WaitAndUpdateAll();
		dg.GetMetaData(depthMD);
		ig.GetMetaData(imageMD);

		//7.
		// 		Mat dm(depthMD.YRes(), depthMD.XRes(), CV_16UC1, (void*)depthMD.Data());
		Mat dm(depthMD.FullYRes(), depthMD.FullXRes(), CV_16UC1, (void*)depthMD.Data());
		double dmin, dmax;
		minMaxLoc(dm, &dmin, &dmax);
		cout<<"dmin, dmax: "<<dmin<<",\t"<<dmax<<",,"<<dm.type()<<endl;
		Mat dm_draw;
		dm.convertTo(dm_draw, CV_8U, 255./(dmax-dmin), -dmin*255./(dmax-dmin));

		imshow("depth map", dm_draw);
		cout<<depthMD.XRes()<<","<<depthMD.YRes()<<"--"<<depthMD.FullXRes()<<","<<depthMD.FullYRes()<<endl;

		Mat im(imageMD.FullYRes(), imageMD.FullXRes(), CV_8UC3, (void*)imageMD.Data());
		Mat im_draw;
		cvtColor(im, im_draw, CV_BGR2RGB);
		cout<<im.type()<<endl;

		imshow("color image", im_draw);

		key = waitKey(1);
	}//while

	cv::Mat mat(3, 2, CV_32F, 1);
	cout<<mat<<endl;
	
	
}//main

