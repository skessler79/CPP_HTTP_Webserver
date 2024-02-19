#!/bin/bash

# This script cleans the build directory specified as the first argument.

BUILD_DIR=$1

if [ -z "$BUILD_DIR" ]; then
    echo "Usage: $0 <build-dir>"
    exit 1
fi

if [ ! -d "$BUILD_DIR" ]; then
    echo "Directory $BUILD_DIR does not exist."
    exit 1
fi

# Confirm with the user
read -p "This will delete everything in $BUILD_DIR. Are you sure? (y/n) " -n 1 -r
echo    # Move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    # rm -rf "$BUILD_DIR"/*
    rm "$BUILD_DIR/stuff"
    echo "Cleaned $BUILD_DIR."
fi