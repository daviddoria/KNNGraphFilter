#include <vtkPolyData.h>
#include <vtkGraph.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkGraphReader.h>

#include <vtkstd/limits>

#include "vtkKNNGraphFilter.h"

template<class A>
bool fuzzyCompare(A a, A b) 
{
  return fabs(a - b) < vtkstd::numeric_limits<A>::epsilon();
}

int main (int argc, char *argv[])
{
  //verify command line arguments
  if(argc != 3)
    {
    cout << "Required arguments: InputFilename GroundTruthFilename" << endl;
    return EXIT_FAILURE;
    }
  
  //parse command line arguments
  vtkstd::string inputFilename = argv[1];
  vtkstd::string groundTruthFilename = argv[2];
  
  //read the input file
  vtkSmartPointer<vtkXMLPolyDataReader> inputReader = 
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  inputReader->SetFileName(inputFilename.c_str());
  inputReader->Update();
  
  vtkPolyData* inputPolyData = inputReader->GetOutput();
  
  //estimate normals
  vtkSmartPointer<vtkKNNGraphFilter> knnGraphFilter = 
      vtkSmartPointer<vtkKNNGraphFilter>::New();
  knnGraphFilter->SetInputData(inputReader->GetOutput());
  knnGraphFilter->Update();
  
  vtkGraph* knnGraph = knnGraphFilter->GetOutput();

  //read the ground truth file
  vtkSmartPointer<vtkGraphReader> groundTruthReader = 
      vtkSmartPointer<vtkGraphReader>::New();
  groundTruthReader->SetFileName(groundTruthFilename.c_str());
  groundTruthReader->Update();

  vtkGraph* groundTruth = groundTruthReader->GetOutput();
  
  if(groundTruth->GetNumberOfVertices() != knnGraph->GetNumberOfVertices())
    {
    std::cout << "GroundTruth->GetNumberOfVertices() != RiemannianGraph->GetNumberOfVertices()" << std::endl;
    std::cout << "ground truth: " << groundTruth->GetNumberOfVertices() << std::endl;
    std::cout << "nearest neighbor graph: " << knnGraph->GetNumberOfVertices() << std::endl;
    return EXIT_FAILURE;
    }

    if(groundTruth->GetNumberOfEdges() != knnGraph->GetNumberOfEdges())
    {
    std::cout << "GroundTruth->GetNumberOfEdges() != RiemannianGraph->GetNumberOfEdges()" << std::endl;
    std::cout << "ground truth: " << groundTruth->GetNumberOfEdges() << std::endl;
    std::cout << "nearest neighbor graph: " << knnGraph->GetNumberOfEdges() << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
