cmake_minimum_required(VERSION 2.6)
INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

#Change PROJECT_NAME to the name of your project
PROJECT(itkFastBilateralImageFilter)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
#
# The packages can be specified with a version number, for example:
#
# ITK 2.8.1
# ITK 3.2.0
#
# If no version is specified, the most recent release of the package
# will be used.
SET(Required_Packages
ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
ITKCommon
ITKIO
)

SET(CurrentExe "ImageCompare")
ADD_EXECUTABLE(${CurrentExe} ImageCompare.cxx) 
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

# The following tests are almost identical to itkBilateralImageFilter tests

# Test using itkNullImageToImageFilterDriver
SET(itkFastBilateralImageFilterTest)
ADD_EXECUTABLE(itkFastBilateralImageFilterTest itkFastBilateralImageFilterTest.cxx) 
TARGET_LINK_LIBRARIES(itkFastBilateralImageFilterTest ${Libraries})

ADD_TEST(itkFastBilateralImageFilterTest itkFastBilateralImageFilterTest)

# Test with a single pass with a larger range sigma
SET(itkFastBilateralImageFilterTest2)
ADD_EXECUTABLE(itkFastBilateralImageFilterTest2 itkFastBilateralImageFilterTest2.cxx) 
TARGET_LINK_LIBRARIES(itkFastBilateralImageFilterTest2 ${Libraries})

ADD_TEST(itkFastBilateralImageFilterTest2 itkFastBilateralImageFilterTest2
  ${CMAKE_SOURCE_DIR}/cake_easy.png
  ${CMAKE_BINARY_DIR}/Testing/Temporary/FastBilateralImageFilterTest2.png)

ADD_TEST(CompareImageForTest2 ImageCompare
  ${CMAKE_SOURCE_DIR}/FastBilateralImageFilterTest2.png
  ${CMAKE_BINARY_DIR}/Testing/Temporary/FastBilateralImageFilterTest2.png)

# Test with multiple passes with a lower range sigma
SET(itkFastBilateralImageFilterTest3)
ADD_EXECUTABLE(itkFastBilateralImageFilterTest3 itkFastBilateralImageFilterTest3.cxx) 
TARGET_LINK_LIBRARIES(itkFastBilateralImageFilterTest3 ${Libraries})

ADD_TEST(itkFastBilateralImageFilterTest3 itkFastBilateralImageFilterTest3
  ${CMAKE_SOURCE_DIR}/cake_easy.png
  ${CMAKE_BINARY_DIR}/Testing/Temporary/FastBilateralImageFilterTest3.png)

ADD_TEST(CompareImageForTest3 ImageCompare
  ${CMAKE_SOURCE_DIR}/FastBilateralImageFilterTest3.png
  ${CMAKE_BINARY_DIR}/Testing/Temporary/FastBilateralImageFilterTest3.png)
