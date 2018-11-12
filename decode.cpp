#include <iostream>

#include <cstdlib>
#include <ctime>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

bool loopFlag = false;
char msgChar;
char dCryptChar;
string storeChars;

bool bitVal(char msgChar, int bitPos) {
	msgChar = msgChar >> bitPos;
	if(msgChar & 1){
		return true;
	}
	else
		return false;
}

char dCrypt (char ch){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	srand(ltm -> tm_yday);
	dCryptChar = ch - ltm->tm_min - rand();
	return dCryptChar;
}

int main(int argc, char** argv) {

	Mat image = imread(argv[1]);
	char msgChar = 0;
	int bitCount = 0;
	int xDimMax = image.rows;
	int yDimMax = image.cols;
	int xDim=0; 
	int yDim=0;

	while(xDim<xDimMax && loopFlag == false) {
		while(yDim<yDimMax && loopFlag == false) {
			for(int zDim=0; zDim < 3; zDim++) {
				Vec3b operatingPixel = image.at<Vec3b>(Point(xDim,yDim));

				if(bitVal(operatingPixel.val[zDim],0))
					msgChar |= 1;
				bitCount++;

				switch(bitCount){
				case(8):
					if(msgChar == '\0'){
						loopFlag = true;
						break;
					}

					bitCount = 0;
					dCrypt(msgChar);
					cout << dCryptChar;
					msgChar = 0;
				
				default:
					msgChar = msgChar << 1;
				}
			}
		yDim++;
		}
	xDim++;
	}
	return 0;
}
