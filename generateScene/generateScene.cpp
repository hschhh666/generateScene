#include <iostream>
#include "define.h"


struct Position
{
	int x, y;
};

double sceneSize = 100;//meter
double pixelSize = 0.2;//meter
int imgSize = sceneSize / pixelSize;


CvRect box;
cv::Mat scene(imgSize, imgSize, CV_8UC3, cv::Scalar(255, 255, 255));
cv::Mat tmp = scene.clone();
cv::Mat SatalliteImage;

bool buttonState = 0;

int key = -1;

std::vector<Position> targetPositions;


void MouseCallback1(int event, int x, int y, int flag, void * param)
{
	int thinkness = -1;
	scene = SatalliteImage.clone();

	if (key == int('o')) 
	{
		switch (event)
		{
		case CV_EVENT_LBUTTONDOWN:
			buttonState = 1;
			box = cvRect(x, y, 0, 0);
			std::cout << "CV_EVENT_LBUTTONDOWN\n";
			break;
		case CV_EVENT_MOUSEMOVE:
			if (buttonState) 
			{
				CvRect tmpbox;
				tmpbox.x = MIN(x, box.x);
				tmpbox.y = MIN(y, box.y);
				tmpbox.width = fabs(x - box.x);
				tmpbox.height = fabs(y - box.y);
				std::cout << "CV_EVENT_MOUSEMOVE\n";
				cv::rectangle(scene, tmpbox, cv::Scalar(0, 0, 0), thinkness);
				//cv::line(scene, cv::Point(box.x, box.y), cv::Point(x, y), cv::Scalar(0, 0, 0), 2);
			}
			break;
		case CV_EVENT_LBUTTONUP:
			buttonState = 0;
			CvRect tmpbox;
			tmpbox.x = MIN(x, box.x);
			tmpbox.y = MIN(y, box.y);
			tmpbox.width = fabs(x - box.x);
			tmpbox.height = fabs(y - box.y);
			std::cout << "CV_EVENT_LBUTTONUP\n";
			cv::rectangle(tmp, tmpbox, cv::Scalar(0, 0, 0), thinkness);
			cv::rectangle(SatalliteImage, tmpbox, cv::Scalar(0, 0, 0), thinkness);
			//cv::line(SatalliteImage, cv::Point(box.x, box.y), cv::Point(x, y), cv::Scalar(0, 0, 0), 2);
			//cv::line(tmp, cv::Point(box.x, box.y), cv::Point(x, y), cv::Scalar(0, 0, 0), 2);
			break;
		}
	}
	else if (key == int('p') )
	{
		switch (event)
		{
		case CV_EVENT_LBUTTONDOWN:
				Position p;
				p.x = x;
				p.y = y;
				targetPositions.push_back(p);
				std::cout << "CV_EVENT_LBUTTONDOWN\n";
				cv::circle(tmp, cv::Point(x, y), 4, cv::Scalar(0, 0, 255), -1);
				//cv::circle(SatalliteImage, cv::Point(x, y), 4, cv::Scalar(0, 0, 255), -1);
				break;
		}
	}
}


int main()
{
	std::string storagedPath = "D:/Research/IV2020MapPrediction/Code/MapPrediction/GenerateFakeMap/C++/tmp";
	std::string SatalliteImageFile = "D:/Research/IV2020MapPrediction/Code/MapPrediction/GenerateFakeMap/C++/SatelliteEastSouthGate.png";

	SatalliteImage = cv::imread(SatalliteImageFile);
	scene = SatalliteImage.clone();




    std::cout << "Hello World!\n"; 
	cv::namedWindow("Scene");
	cv::setMouseCallback("Scene", MouseCallback1, 0);

	while (1) {

		for (int i = 0; i < targetPositions.size(); i++) {
			cv::circle(scene, cv::Point(targetPositions[i].x, targetPositions[i].y), 4, cv::Scalar(0, 0, 255), -1);
			cv::putText(scene, std::to_string(i), cv::Point(targetPositions[i].x + 5, targetPositions[i].y + 5), 1, 1, cv::Scalar(0, 0, 0));
		}
			
		cv::putText(scene, "press 'o' to draw obstacle, 'p' to draw points, 'q' to quit.", cv::Point( 5, 15), 0, 0.5, cv::Scalar(0, 0, 255));
		cv::imshow("Scene", scene);
		int tmpkey = cv::waitKey(100);
		key = (tmpkey != -1 ? tmpkey : key);

		std::cout << key << std::endl;

		if (key == int('q')) {

			cv::FileStorage storage(storagedPath + ".yml", cv::FileStorage::WRITE);
			if (!storage.isOpened()) {
				std::cout << "Cannot write to " + storagedPath + ".yml \n Press any key to exit.\n";
				getchar();
				return(-1);
			}

			storage << "sceneSize" << sceneSize;
			storage << "pixelSize" << pixelSize;

			int size = targetPositions.size();
			storage << "targetPositionsNum" << size;
			for (int i = 0; i < targetPositions.size(); i++) {
				storage << "targetPosition" + std::to_string(i) + "x" << targetPositions.at(i).x;
				storage << "targetPosition" + std::to_string(i) + "y" << targetPositions.at(i).y;
			}

			storage << "structure" << tmp;
			storage.release();

			cv::destroyAllWindows();
			
			for (int i = 0; i < targetPositions.size(); i++)
			{
				cv::circle(tmp, cv::Point(targetPositions[i].x, targetPositions[i].y), 4, cv::Scalar(0, 0, 255), -1);
				cv::putText(tmp, std::to_string(i), cv::Point(targetPositions[i].x + 5, targetPositions[i].y + 5), 1, 1, cv::Scalar(0, 0, 0));
			}

				
			cv::imwrite(storagedPath + ".jpg", tmp);
			std::cout << "Succeed write file to " + storagedPath + ".yml and jpg \nPress any key to exit.\n";
			getchar();

			break;
		}

	}

}

