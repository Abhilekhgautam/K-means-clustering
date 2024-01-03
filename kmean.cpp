#include <iostream>
#include <array>
#include <random>

#include <raylib.h>

/*
 No banter about the time complexity please!!!!
 */

// 1. Data: generate random numbers how many though? 1M
// 2. apply the algorithm
// 3. display the result
// probably convert into multithreading application
template <int S>
struct Data{
  std::array<float, S> Val;
  int Cluster;

};

constexpr int NumberOfCluster = 3;
constexpr int MaxNoOfIteration = 40;
constexpr int SizeOfArray = 800;

template <int S>
void KMean(std::array<Data<S>, SizeOfArray>& data){

  std::array<std::array<float, S>, NumberOfCluster> Centroids{};
  std::random_device r;
 
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, SizeOfArray);
  
  // randomly select centroids
  for(int i = 0 ; i < NumberOfCluster ; ++i){
      for(int j = 0 ; j < S ; ++j)
         Centroids[i][j] = {data[uniform_dist(e1)].Val[0]};
  }
 int NoOfIterations = 0;

 while(NoOfIterations < MaxNoOfIteration) {
  for(int i = 0 ; i < SizeOfArray; ++i) {
    int SmallestCentroidIndex = 0;
   for(int j = 0 ; j < NumberOfCluster ; ++j) {
     // calculate the distance between data[i].Val and Centroids[j]
     // assign data[i].Cluster to the smallest distance index
     float DistSum = 0.0f;
     float CentroidDistSum = 0.0f;
     for(int k = 0 ; k < S ; ++k){
         DistSum += (data[i].Val[k] - Centroids[j][k]) * (data[i].Val[k] - Centroids[j][k]);
         CentroidDistSum += (data[i].Val[k] - Centroids[SmallestCentroidIndex][k]) * (data[i].Val[k] - Centroids[SmallestCentroidIndex][k]);
     }
     if(DistSum < CentroidDistSum){
        SmallestCentroidIndex = j;     
     }
   }
   data[i].Cluster = SmallestCentroidIndex + 1;
  }	
  for(int i = 0 ; i < NumberOfCluster ; ++i) {
    std::array<float, S> Sum{};
    Sum.fill(0.0f);
    std::array<int, S> Count{};
    Count.fill(0);
    for(int j = 0 ; j < SizeOfArray ; ++j) {
        if(data[j].Cluster == i + 1) {
            for(int k = 0 ; k < S ; ++k) {
                Sum[k] += data[j].Val[k];
                Count[k]++;
            }
        }
    }
    // update the centroid
    for(int k = 0 ; k < S ; ++k)
       Centroids[i][k] = Count[k] > 0 ?  Sum[k] / (float)Count[k] : Centroids[i][k];
  }
  NoOfIterations++;
 }
// prints all the centroids
 for(const auto& elt: Centroids) {
     for(const auto& e : elt)
       std::cout <<  e << " " ;
     std::cout << '\n';
 }
 std::cout << '\n';
}

template<int S>
void plot(const std::array<Data<S>, SizeOfArray>& data){
    if(S != 2){
        std::cerr << "Only 2d data are supported for plotting";
        return;
    }
    const int screenWidth = 900;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Plotter");

    SetTargetFPS(60);
    auto PointColor = RED;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        for(const auto& elt: data){
            if(elt.Cluster == 1) PointColor = RED;
            else if (elt.Cluster == 2) PointColor = GREEN;
            else PointColor = DARKBLUE;
            DrawCircle(elt.Val[0] , elt.Val[1], 4, PointColor);
        }

        EndDrawing();

    }

    CloseWindow();
}

int main(){
  constexpr int S = 2;
  std::array<Data<S>, SizeOfArray> data{};
  //generate random number here.
  // Seed with a real random value, if available
  std::random_device r;
 
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, SizeOfArray);
  for(int i = 0 ; i < SizeOfArray ; ++i) {
      for(int j = 0 ; j < S ; ++j)
         data[i].Val[j] = (float)uniform_dist(e1);
      data[i].Cluster = 0;
  }

  KMean(data);
  for(auto& elt: data) {
      for(auto& e : elt.Val) {
          std::cout << e << ' ' ;
      }
      std::cout << " : " << elt.Cluster << ' ';
      std::cout << '\n';
  }
    plot(data);

  return 0;
}
