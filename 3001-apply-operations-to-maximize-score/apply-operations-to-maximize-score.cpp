class Solution {
public:
    //nilambar
    int mod = 1e9+7;
    
    long fpow(long a, long b) {
        long res = 1;
        while (b) {
            if (b & 1) res = res*a%mod;
            a = a*a%mod;
            b>>=1;
        }
        return res;
    }
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> score;
        score.reserve(n);
        
        for (int x: nums) {
            int o = x;
            int num = 0;
            for (long p = 2; p*p <= o; ++p) {
                if (x % p == 0) {
                    num++;
                    while (x % p == 0) x /= p;
                }
            }
            if (x != 1) num++;
            score.push_back(num);
        }
        
        vector<int> nextG1(n, n), prevG1(n, -1);
        { // compute the score
            stack<int> st;
            for (int i = 0; i < n; ++i) {
                while (st.size() && score[st.top()] < score[i]) {
                    nextG1[st.top()] = i;
                    st.pop();
                }
                if (st.size()) prevG1[i] = st.top();
                st.push(i);
            }
        }

        // step3
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums[i] > nums[j]; 
        });
        
        long ans = 1;
        for (int o: idx) {
            long left = prevG1[o];
            long right = nextG1[o];
            long val = nums[o];
            long cnt = (long)(o-left)*(right-o); // number of subarray contains nums[o]
            long mn = min(cnt, (long)k);
            ans = ans * fpow(val, mn) % mod;
            k -= mn;
        }
        
        return ans;
    }
};