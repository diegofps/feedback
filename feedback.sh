#!/bin/sh

killall feedback 2> /dev/null

../build-feedback-Desktop_Qt_5_14_1_GCC_64bit-Release/feedback $@

