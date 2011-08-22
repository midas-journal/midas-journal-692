#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif
#include <fstream>
#include "itkFastBilateralImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"

/**
 * This test was originally taken from the tests for the itkBilateralImageFilter
 * and modified for the itkFastBilateralImageFilter.
 */
int main(int ac, char* av[] )
{
  if(ac < 3)
    {
    std::cerr << "Usage: " << av[0] << " InputImage OutputImage\n";
    return -1;
    }

  typedef unsigned char PixelType;
  const unsigned int dimension = 2;
  typedef itk::Image<PixelType, dimension> myImage;
  itk::ImageFileReader<myImage>::Pointer input 
    = itk::ImageFileReader<myImage>::New();
  input->SetFileName(av[1]);
  
  // Create a filter
  typedef itk::FastBilateralImageFilter<myImage,myImage> FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  filter->SetInput(input->GetOutput());
  
  // these settings reduce the amount of noise by a factor of 10
  // when the original signal to noise level is 5
  filter->SetDomainSigma( 4.0 );
  filter->SetRangeSigma( 50.0 );
  
  
  // Test itkSetVectorMacro
  double domainSigma[dimension];
  for (unsigned int i = 0; i < dimension; i++)
    {
      domainSigma[i] = 4.0;
    }
  filter->SetDomainSigma(domainSigma);

  // Test itkGetMacro
  std::cout << "filter->GetDomainSigma(): " << filter->GetDomainSigma() << std::endl;
  std::cout << "filter->GetRangeSigma(): " << filter->GetRangeSigma() << std::endl;
  
  try
    {
    input->Update();
    filter->Update();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception detected: "  << e.GetDescription();
    return -1;
    }
  catch (...)
    {
    std::cerr << "Some other exception occurred" << std::endl;
    return -2;
    }

  // Generate test image
  itk::ImageFileWriter<myImage>::Pointer writer;
    writer = itk::ImageFileWriter<myImage>::New();
    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( av[2] );
    writer->Update();

  return EXIT_SUCCESS;
}
