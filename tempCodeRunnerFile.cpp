for(int i = 1; i < numRows;i++){
        if(i%2 == 0) {
            for (int j = 1; j < numColumns; j+=2){
                abs_value = abs(dp[i][j-1] - dp[i][j+1]);
                dp[i][j] = max(dp[i][j-2], dp[i-1][j-1]) + abs_value;
            }
        }
    }