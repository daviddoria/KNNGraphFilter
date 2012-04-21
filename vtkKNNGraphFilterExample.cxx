#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTree.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkGraphToPolyData.h>
#include <vtkGraphWriter.h>
#include <vtkGraphReader.h>

#include "vtkKNNGraphFilter.h"

int main (int argc, char *argv[])
{
  if(argc != 3)
    {
    cout << "Required arguments: InputFile(vtp) OutputFile(vtp)" << endl;
    return EXIT_FAILURE;
    }
    
  vtkstd::string inputFilename = argv[1];
//  vtkstd::string outputGraphFilename = argv[2];
  vtkstd::string outputPolyDataFilename = argv[2];
    
  vtkSmartPointer<vtkXMLPolyDataReader> inputReader = 
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  inputReader->SetFileName(inputFilename.c_str());
  inputReader->Update();
  
  /*
  vtkSmartPointer<vtkGraphReader> inputReader = vtkSmartPointer<vtkGraphReader>::New();
  inputReader->SetFileName(inputFilename.c_str());
  inputReader->Update();
  vtkTree* inputTree = vtkTree::SafeDownCast(inputReader->GetOutput());
  */
  
  vtkPolyData* inputPolyData = inputReader->GetOutput();
  
  vtkSmartPointer<vtkKNNGraphFilter> knnGraphFilter = 
      vtkSmartPointer<vtkKNNGraphFilter>::New();
  knnGraphFilter->SetInputData(inputPolyData);
  knnGraphFilter->Update();
  
  vtkGraph* knnGraph = knnGraphFilter->GetOutput();
  
  /*
  //write the graph to a file
  vtkSmartPointer<vtkGraphWriter> graphWriter = 
      vtkSmartPointer<vtkGraphWriter>::New();
  graphWriter->SetInput(knnGraph);
  graphWriter->SetFileName(outputGraphFilename.c_str());
  graphWriter->Write();
  */
  
  //convert the graph to a polydata
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter = 
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputData(knnGraph);
  graphToPolyDataFilter->Update();
  
  //write the result to a file
  vtkSmartPointer<vtkXMLPolyDataWriter> polyDataWriter = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  polyDataWriter->SetInputData(graphToPolyDataFilter->GetOutput());
  polyDataWriter->SetFileName(outputPolyDataFilename.c_str());
  polyDataWriter->Write();
  
  return EXIT_SUCCESS;
}
