#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>


using namespace std;

float computeDistance( pair<float,float> point1, pair<float,float>point2 );
float calculateTotalDistance( vector<pair<float,float>> points );
int computeGPSXAtTime( pair<float,float> previousPoint, pair<float,float> currentPoint, int previousTime, int currentTime, int timeNow );
int computeGPSYAtTime( pair<float,float> previousPoint, pair<float,float> currentPoint, int previousTime, int currentTime, int timeNow );
float convertDiffToPercentage( float diff, float actualDistance );

int main() {
  pair<float,float> currentPoint;
  pair<float,float> previousPoint;
  int numPositionsAlongPath = 0;
  float GPSTimeInterval = 0.0;
  int newXCoord = 0, newYCoord = 0;
  int totalRunningTime = 0;
  vector< pair<float,float> > points;
  vector< pair<float,float> > GPSpoints;
  vector<int> times;
  float GPSXCoord = 0;
  float GPSYCoord = 0;
  int recordedTime = 0;
 // cout << computeDistance(p1,p2) << endl;
 
 
  
  cin >> numPositionsAlongPath >> GPSTimeInterval;
  
   for( int i = 0; i < numPositionsAlongPath; i++ )
   {
        cin >> newXCoord >> newYCoord >> recordedTime;
        currentPoint.first = newXCoord;
        currentPoint.second = newYCoord;
        points.push_back( currentPoint );
        times.push_back(recordedTime);
   }
   
  // cout << "GPS Points" << endl;
   
   GPSpoints.push_back(pair<float,float>(0,0));
   totalRunningTime = GPSTimeInterval;
   for( int i = 1; i < points.size(); i++ )
   {
   //    cout << points[i].first << ", " << points[i].second << endl;
       GPSXCoord = computeGPSXAtTime(points[i - 1], points[i], times[i - 1], times[i], totalRunningTime);
       GPSYCoord = computeGPSYAtTime(points[i - 1], points[i], times[i - 1], times[i], totalRunningTime);
       totalRunningTime += GPSTimeInterval;
       GPSpoints.push_back( pair<float,float>(GPSXCoord, GPSYCoord) );
   }
    
    GPSpoints.push_back( points[points.size()-1] );
    
   // cout << endl;
 
    // for( int i = 0; i < points.size(); i++ )
    // {
    //     cout << "(" << points[i].first << ", "
    //     << points[i].second << ")" << endl;
    // }
  
   // cout << "total distance = " << calculateTotalDistance(points) << endl;
    
    // for( int i = 0; i < GPSpoints.size(); i++ )
    // {
    //     cout << "(" << GPSpoints[i].first << ", "
    //     << GPSpoints[i].second << ")" << endl;
    // }
    
    float POINTDIST = calculateTotalDistance(points);
    float GPSDIST = calculateTotalDistance(GPSpoints);
    float diff = POINTDIST - GPSDIST;
   // cout << "total distance = " << calculateTotalDistance(GPSpoints) << endl;
  
  
    cout << convertDiffToPercentage( diff, POINTDIST ) << endl;
  
    return 0;
}

float computeDistance( pair<float,float> point1, pair<float,float>point2 )
{
    float yDiff = point2.second - point1.second;
    float xDiff =  point2.first - point1.first;
    
    return sqrt( pow( xDiff, 2 ) + pow(yDiff, 2));
}

float calculateTotalDistance( vector<pair<float,float>> points )
{
    float totalDistance = 0.0;
    
    
    for( int i = 0; i < points.size()-1; i++ )
    {
        totalDistance += computeDistance(points[i], points[i + 1]);
    }
    
    return totalDistance;
}

int computeGPSXAtTime( pair<float,float> previousPoint, pair<float,float> currentPoint, int previousTime, int currentTime, int timeNow )
{
    float GPS_X;
    float deltaX = currentPoint.first - previousPoint.first;
    int deltaT = currentTime - previousTime;
    int multiplier = timeNow - previousTime;
    
    GPS_X = ( (deltaX) / (deltaT ) )*multiplier;
    GPS_X += previousPoint.first;
    
    return GPS_X;
}

int computeGPSYAtTime( pair<float,float> previousPoint, pair<float,float> currentPoint, int previousTime, int currentTime, int timeNow )
{
    float GPS_Y = 0;
    float deltaY = currentPoint.second - previousPoint.second;
    int deltaT = currentTime - previousTime;
    int multiplier = timeNow - previousTime;
    
    GPS_Y = ( (deltaY) / ( deltaT) )*multiplier;
    GPS_Y += previousPoint.second;
    
    return GPS_Y;
}

float convertDiffToPercentage( float diff, float actualDistance )
{
    float percent = 0.0;
    
    float temp = actualDistance / 100;
    percent = diff / temp;
    return percent;
}
