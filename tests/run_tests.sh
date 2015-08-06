#!/bin/sh

options="--log_level=test_suite"

make
./cell_test $options
./game_test $options
./gui_test $options