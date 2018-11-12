#include <iostream>
#include <fstream>

#include <cstdlib>
#include <ctime>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

bool loopFlag = false;
char msgChar;
char getChar;

bool bitVal(char msgChar, int bitPos) {
	msgChar = msgChar >> bitPos;
	if(msgChar & 1){
		return true;
	}
	else
		return false;
}

char crypt (char ch){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	srand(ltm -> tm_yday);
	msgChar = ch + ltm->tm_min + rand();
	return msgChar;
}

int main(int argc, char** argv) {

	Mat image = imread(argv[1]);

	ifstream file(argv[2]);


	file.get(getChar);
	crypt(getChar);
	int bitCount = 0;
	bool eofNull = false;
	bool isEncoded = false;

	int xDimMax = image.rows;
	int yDimMax = image.cols;
	int xDim=0; 
	int yDim=0;


	while(xDim<xDimMax && loopFlag == false) {
		while(yDim<yDimMax && loopFlag == false) {
			for(int zDim=0; zDim < 3; zDim++) {
				Vec3b operatingPixel = image.at<Vec3b>(Point(xDim,yDim));
				if(bitVal(msgChar,7-bitCount))
					operatingPixel.val[zDim] |= 1;
				else
					operatingPixel.val[zDim] &= ~1;
				image.at<Vec3b>(Point(xDim,yDim)) = operatingPixel;
				bitCount++;
				if(eofNull && bitCount == 8) {
					isEncoded  = true;
					loopFlag = true;
					break;
				}
				else if(bitCount == 8) {
					bitCount = 0;
					file.get(getChar);
					crypt(getChar);
					if(file.eof()) {
						eofNull = true;
						msgChar = '\0';
					}
				}

			}
		yDim++;
		}
	xDim++;
	}
	if(!isEncoded) {
		cout << "msg too large" << endl;
		exit(-1);
	}
	imwrite(argv[3],image);
    return 0;
}
