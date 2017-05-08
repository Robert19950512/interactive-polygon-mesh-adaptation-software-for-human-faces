#pragma once
#include "opencv/highgui.h"
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "glm.h"

void MA(float *landmarks, GLMmodel* pModel,int* icols, int* irows);