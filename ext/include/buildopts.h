// Copyright Contributors to the OpenImageIO project.
// SPDX-License-Identifier: Apache-2.0
// https://github.com/AcademySoftwareFoundation/OpenImageIO


// A very small number of definitions we must derive at build time.
//


#ifndef OPENIMAGEIO_BUILDOPTS_H
#define OPENIMAGEIO_BUILDOPTS_H

//Define a default plugin search path
#define OIIO_DEFAULT_PLUGIN_SEARCHPATH ""

// List of build-time dependencies (semicolon separated)
#define OIIO_ALL_BUILD_DEPS_FOUND "DCMTK NONE;expat 2.7.4;FFmpeg NONE;fmt 12.1.0;Freetype NONE;GIF NONE;Imath 3.1.12;JPEG 80;JXL NONE;libdeflate 1.23;Libheif NONE;libjpeg-turbo NONE;LibRaw NONE;libuhdr NONE;minizip-ng 4.0.10;OpenColorIO 2.5.1;OpenCV NONE;OpenEXR 3.3.5;OpenGL;OpenJPEG NONE;openjph NONE;PNG 1.6.57;Ptex NONE;Ptex NONE;pybind11 3.0.1;pystring;Python3 3.14.4;Qt5 NONE;Qt6 NONE;Robinmap 1.4.1;TBB NONE;TIFF 4.7.0;WebP 1.5.0;yaml-cpp 0.8.0;ZLIB 1.3.1;ZLIB 1.3.1"

#endif // OPENIMAGEIO_BUILDOPTS_H
