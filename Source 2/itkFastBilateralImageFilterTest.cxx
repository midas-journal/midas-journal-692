#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>
#include "itkFastBilateralImageFilter.h"
#include "itkNullImageToImageFilterDriver.txx"

/**
 * This test was originally taken from the tests for the itkBilateralImageFilter
 * and modified for the itkFastBilateralImageFilter.
 */
int main(int, char* [] )
{
  try
    {
      typedef itk::Image<float, 2> ImageType;

      // Set up filter
      itk::FastBilateralImageFilter<ImageType, ImageType>::Pointer
        filter = itk::FastBilateralImageFilter<ImageType,
        ImageType>::New();
      filter->SetDomainSigma(2.0);
      filter->SetRangeSigma(35.0f);

      // Run Test
      itk::Size<2> sz;
      sz[0] = 250;
      sz[1] = 250;
      itk::NullImageToImageFilterDriver< ImageType, ImageType > test1;
      test1.SetImageSize(sz);
      test1.SetFilter(filter.GetPointer());
      test1.Execute();
    }
  catch(itk::ExceptionObject &err)
    {
      (&err)->Print(std::cerr);
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
