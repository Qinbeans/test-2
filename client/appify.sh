#!/bin/bash

# Creates .app file for executable

OS=$(uname)
if [ "$OS" = "Darwin" ]
then
   if [ ! -d "bin/Mac/Test.app" ]
   then
      mkdir bin/Mac/Test.app
   fi
   if [ ! -d "bin/Mac/Test.app/Contents" ]
   then
      mkdir bin/Mac/Test.app/Contents
   fi
   if [ ! -d "bin/Mac/Test.app/Contents/MacOS" ]
   then
      mkdir bin/Mac/Test.app/Contents/MacOS
      if [ ! -f "bin/Mac/Test.app/Contents/Info.plist" ]
      then
         echo '<?xml version="1.0" encoding="UTF-8"?>' >> bin/Mac/Test.app/Contents/Info.plist
         echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> bin/Mac/Test.app/Contents/Info.plist
         echo '<plist version="1.0">' >> bin/Mac/Test.app/Contents/Info.plist
         echo '<dict>' >> bin/Mac/Test.app/Contents/Info.plist
         echo '<key>CFBundleExecutable</key>' >> bin/Mac/Test.app/Contents/Info.plist
         echo '<string>Test</string>' >> bin/Mac/Test.app/Contents/Info.plist
         echo '</dict>' >> bin/Mac/Test.app/Contents/Info.plist
         echo '</plist>' >> bin/Mac/Test.app/Contents/Info.plist
      fi
   fi
   if [ ! -d "bin/Mac/Test.app/Contents/Resources" ]
   then
      mkdir bin/Mac/Test.app/Contents/Resources
   fi
   cp $1 bin/Mac/Test.app/Contents/MacOS/Test
   if [ "$2" = "-r" ]
   then
      cp -r $3 bin/Mac/Test.app/Contents/Resources/res
   fi
fi