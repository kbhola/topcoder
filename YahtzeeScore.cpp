#include <vector>
using namespace std;    
int count[6];
class YahtzeeScore {
    public:
    int maxPoints(vector<int> toss) {
        for(size_t i = 0; i < toss.size(); ++i) {
            count[toss[i] -1] += toss[i];
        }
        
        int mx = 0;
        for(int i = 0; i < 6; ++i) {
            if (count[i] > mx)
                mx = count[i];
        }
        
        return mx;
    }
};
