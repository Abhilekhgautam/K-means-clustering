#include <iostream>
#include <array>
#include <random>
// todos:
// 1. Data: generate random numbers how many though? 1M
// 2. apply the algorihm
// 3. display the result
// probably convert into multi-threaded

struct Data{
  int Val;
  int Cluster;
};

constexpr int NumberOfCluster = 3;
constexpr int MaxNoOfIteration = 40;
constexpr int SizeOfArray = 100;
void kmean(std::array<Data, SizeOfArray>& data){

  std::array<float, NumberOfCluster> Centroids;
  std::random_device r;
 
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, SizeOfArray);
  
  // randomly select centroids
  for(int i = 0 ; i < NumberOfCluster ; ++i){
   Centroids[i] = data[uniform_dist(e1)].Val; 	  
  }
 int NoOfIterations = 0; 
 while(NoOfIterations < MaxNoOfIteration){
  for(int i = 0 ; i < SizeOfArray; ++i){
    int SmallestCentroidIndex = 0;
   for(int j = 0 ; j < NumberOfCluster ; ++j){
     // calculate the distance between data[i].Val and Centroids[j]
     // assign data[i].Cluster to the smallest distance index 
     
     if(std::abs(data[i].Val - Centroids[j]) < std::abs(data[i].Val - Centroids[SmallestCentroidIndex])){
        SmallestCentroidIndex = j;     
     }
   }
   data[i].Cluster = SmallestCentroidIndex + 1;
  }	
  for(int i = 0 ; i < NumberOfCluster ; ++i){
    float Sum = 0.0f , Count = 0;
    for(int j = 0 ; j < SizeOfArray ; ++j){
      if(data[j].Cluster == i + 1){
	 Sum += data[j].Val;
	 Count++;
      }	    
    }	  
    Centroids[i] = Count > 0 ?  Sum / (float)Count : Centroids[i];
  }
  NoOfIterations++;
 }
 for(auto& elt: Centroids) {
   std::cout <<  elt << " " ;
 }
 std::cout << '\n';
}

int main(int argc, char** argv){
  
  std::array<Data, SizeOfArray> data;
  //generate random number here.
  // Seed with a real random value, if available
  std::random_device r;
 
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, 500);
  for(int i = 0 ; i < SizeOfArray ; ++i){
    data[i].Val = uniform_dist(e1);
    data[i].Cluster = 0;
  }

  kmean(data);
  for(auto& elt: data){
   std::cout << elt.Val << " : " << elt.Cluster << '\n';  
  }

  return 0;
}
