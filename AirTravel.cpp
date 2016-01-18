
 #include <vector>
#include <algorithm>
#include <cmath>
#include <string>

/**
   1000-point (very difficult) problem solution
   
 **/
using namespace std;

constexpr double radius = 4000.0; // radius of earth, miles
constexpr double pi = 3.1415926535897932384626433832795 ; // to convert the degrees to radians for use in the C trigonometric functions

struct Coord {
  Coord(): num(-1), lat(-1.0), lon(-1.0) {}
  Coord(int n, double at, double on) : num(n),
				       lat(at*pi/180.0),
				       lon(on*pi/180.0) {}

  int num; // airport number
  double lat;//titude
  double lon;//gitude
};



double great_circle(const Coord & c1, const Coord & c2) {
  /**
     The shortest distance between two points on a sphere is known
     as a great circle;  this is the formula for such a distance
     given two coordinates;
   **/
    
  return ( radius * acos( sin(c1.lat)
			  * sin(c2.lat) + cos(c1.lat) * cos(c2.lat)
			  * cos(c1.lon - c2.lon) ) );
}

constexpr double MXD = 9999999999999999999999999999999999999999999999999999999999.0;

class AirTravel {
    
public:
  std::vector<Coord> coords;
  int num_airports;
  double short_dist[2121];
  bool found_short_dist[2121];
  bool can_travel[2121];
	AirTravel() {
        for(int i = 0; i < 2121; ++i)
            {
            	short_dist[i] = MXD;
            	found_short_dist[i] = false;
            	can_travel[i] = false;
            }
        }
  /**
  void set_dist(Coord c1, Coord c2) {
    int idx = c2.num*100 + c1.num;
    double dist = great_circle(c1, c2);
    if(short_dist[idx] == 0 || dist < short_dist[idx]) {
      short_dist[idx] = dist;
    }    
  }
  **/

  double min_dist2(Coord from,
		   Coord to,
		   bool visited[21])
  {
    if (from.num == to.num)
      return 0.0;

    const int idx = to.num*100 + from.num;
    
    if (found_short_dist[idx])
      return short_dist[idx];
	
    bool new_visited[21];
    for(size_t i = 0; i < 21; ++i)
        {
        new_visited[i] = visited[i];
        }
    double cur_min = MXD;
    if (can_travel[idx])
      {
	found_short_dist[idx] = true;
	
	return (short_dist[idx] = great_circle(from, to));
      }
    else
      {
	for(int i = 0; i < num_airports; ++i)
	  {
	    const int cur_idx = to.num*100 + i;
	    if(!new_visited[i] && can_travel[cur_idx])
	      {
			new_visited[i] = true;
			cur_min = min(min_dist2(from, coords[i], new_visited) +
			     		 great_circle(coords[i], to),
			      		cur_min);
		
			      
	      }
	  }
      }

    found_short_dist[idx] = true;
    return (short_dist[idx] = cur_min);
  }
  

  double
  shortestTrip(vector <int> latitude,
	       vector <int> longitude,
	       vector <string> canTravel,
	       int origin,
	       int destination) {
    if(origin == destination)
      return 0.0;
    
    double dist = -1.0; //default value -1.0 indicates no such distance

    // create Coordinate objects
    // and create can-travel hashmap in the inner-for loop
    num_airports = latitude.size();
    coords.resize(num_airports);
    for(int i = 0; i < num_airports; ++i) {
      coords[i] = Coord(i, latitude[i], longitude[i]);

      // in ASCII, 0(char) = 48 (int)
      for(size_t j = 0; j < canTravel[i].size(); ++j) {
          int idx = (static_cast<int>(canTravel[i][j]) - static_cast<int>('0'))*100 + i;
		  can_travel[idx] = true;
			++j; // there is an extra space
  	    }
    }
      
    for(size_t i = 0; i < num_airports; ++i) {
        for(size_t j = 0; j < num_airports; ++j) {
            int idx = j*100 + i;
            if (can_travel[idx]) {
                found_short_dist[idx] = true;
                short_dist[idx] = great_circle(coords[i], coords[j]);
                }
            else if (i == j) {
                can_travel[idx] = true;
                found_short_dist[idx] = true;
                short_dist[idx] = 0.0;
                }

            }
       
        }

    // Now we have all the information, so we'll calculate the distance
    bool visited[21];
    for(size_t j = 0; j < 21; ++j)
        {
        	visited[j] = false;
        }
    visited[destination] = true;
    double md = min_dist2(coords[origin], coords[destination],
			  visited);
    if (md != MXD)
      dist = md;

    return dist;
    
  }
};



int main() {
  vector<int> test_lat {1, 3, 4};
  vector<int> test_long{1, 3, 4};
  vector<string> test_can{ "1", "0 2", "1"};
  return 0;
  }
