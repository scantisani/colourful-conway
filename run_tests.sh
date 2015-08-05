#!/bin/sh

options="--log_level=test_suite"

make tests
./cell_test $options
./game_test $options