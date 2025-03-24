class Solution {
    #define ll long long
    //nilambar
    bool canAssign(ll& mid,vector<int>& candies,ll& k){
        ll count=0;
        for(ll ele: candies){
            if(ele >= mid)
                count += ele/mid;
        }
        return count>=k;
    }
public:
    int maximumCandies(vector<int>& candies, long long k) {
        ll low = 1;
        ll high = *max_element(candies.begin(),candies.end());
        ll mid;

        //Binary search on range of answer
        ll max_candies=0;
        while(low<=high){
            mid = low+(high-low)/2;
            if(canAssign(mid,candies,k)){
                max_candies = mid;
                low = mid+1;
            }else{
                high = mid-1;
            }
        }
        return max_candies;
    }
};