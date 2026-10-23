#!/usr/bin/python3


#
#
#
#  This is a script to convert exr files to
#  jpg files, then a movie, then clean up the
#  jpg files.  Assuming you are created a 
#  collection of exr files with names
#
#      some_base_name.XXXX.exr
#
#  where XXXX is a zero-padded four digit frame
#  number, you can use this tool like this:
#
#       python ./makemovie.py some_base_name.*.exr
#
#  when done, a file "test.mov" will be generated.
#
#  The ImageMagick routine "convert" is used in this script.
#  Annotations are applied to each frame
#
#





import os
import sys

def formattedTime():
    import time
    T = time.localtime(time.time())
    year  = str(T[0])
    month = str(T[1])
    if T[1] < 10 :
        month = "0" + month
    day   = str(T[2])
    if T[2] < 10 :
        day = "0" + day
    hour = str(T[3])
    if T[3] < 10:
        hour = "0" + hour
    minute = str(T[4])
    if T[4] < 10 :
        d = "0" + minute
    sec = str(T[5])
    if T[5] < 10 :
        sec = "0" + sec
    formatted = year + "-" + month + "-" + day + "_" + hour + ":" + minute + ":" + sec
    return formatted


if len(sys.argv) > 1:
    if "-h" in sys.argv:
        print( "makemovie.py usage:" )
        print( "\tmakemovie.py <list of files to convert to a movie>" )
        print( "Wild cards may be used in the list." )
        print( "The output movie will be named \"test.mp4\"." )
        print( "Example:" )
        print( "\t./makemovie.py *.exr" )
        print( " " )
        print( "Before generating the movie, a collection of jpeg conversion" )
        print( "files are created using the ImageMagick tool \"convert\"." )
        print( "After the movie is generated, these files are removed." )
        print( " " )
        sys.exit()

course = "cpsc8190" 
user = os.getenv("USER")
now = formattedTime()
label_font = " -font Courier "
fontcolor = "white"
fontsize = 15


frame = 1
for img in sys.argv[1:]:
    print( str(frame) + " " + img )
    padframe = str(frame)
    if frame < 1000:
        padframe = "0" + padframe
    if frame < 100:
        padframe = "0" + padframe
    if frame < 10:
        padframe = "0" + padframe
    outimage = "conversion." + padframe + ".jpg"
    #cmd = "convert " + img + " " + outimage
    cmd = "magick " + img + label_font
    cmd = cmd + " -gravity southwest -fill " + fontcolor + " -pointsize " + str(fontsize) + " -weight 100 -annotate +15+0 '" + user + "' -gravity south -annotate 0 '" + img + "    " + padframe + "' -gravity southeast -annotate +15+0 '" + now + "' -gravity northwest -annotate +15+0 '" + course + "' "
    cmd = cmd + outimage
    os.system(cmd)
    frame = frame + 1

if len(sys.argv[1:]) > 1:
    cmd = "ffmpeg -r 24 -i conversion.%04d.jpg -r 24 test.mp4"
    os.system(cmd)
    cmd = "rm -rf conversion.????.jpg"
    os.system(cmd)
    #cmd = "ffplay -loop 0 test.mov"
    #os.system(cmd)
else:
    print( "Not enough frames found. No movie generated." )

