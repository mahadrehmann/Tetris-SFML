//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum)     //This function is responsible for downward movement. Takes timer,delay and colorNum as inputs
{
    if (timer>delay)
    {
        for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                 //How much units downward    
        } 
        
        if (!anamoly())
        {
            for (int i=0;i<4;i++)                      //gives 7 random blocks in diff colors (added from video)
            {
                gameGrid[point_2[i][1]] [point_2[i][0]] = colorNum;
            }   
            
            colorNum= rand()%7+1; 
            int n=rand()%7;
        
            for (int i=0;i<4;i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer=0;
    }
}

void move(int& delta_x) 
{   
    if (delta_x != 0) 
    {
        for (int i = 0; i < 4; i++) 
        {
            point_2[i][0] = point_1[i][0];
            point_1[i][0] += delta_x;
        }
        if (!anamoly()) 
        {
            for (int i = 0; i < 4; i++) 
            {
                point_1[i][0] = point_2[i][0];
            }
        }
        delta_x = 0;
    }
}

void rotation(bool& rotate) {
    if (rotate) {
        int cx = point_1[1][0]; // center x
        int cy = point_1[1][1]; // center y
        for (int i = 0; i < 4; i++) {
            int x = point_1[i][1] - cy; // y - center y
            int y = point_1[i][0] - cx; // x - center x
            point_1[i][0] = cx - x;
            point_1[i][1] = cy + y;
        }
        if (!anamoly()) {
            for (int i = 0; i < 4; i++) {
                point_1[i][0] = point_2[i][0];
                point_1[i][1] = point_2[i][1];
            }
        }
        rotate = false;
    }
}

void checklines(int &score) 
{
    int lines = 0;
    for (int i = M - 1; i >= 0; i--) 
    {
        int count = 0;
        for (int j = 0; j < N; j++) 
        {
            if (gameGrid[i][j] != 0) 
            {
                count++;
            }
        }
        if (count == N) 
        {
            lines++;
            for (int k = i; k > 0; k--) 
            {
                for (int j = 0; j < N; j++) 
                {
                    gameGrid[k][j] = gameGrid[k-1][j];
                }
            }
            for (int j = 0; j < N; j++) 
            {
                gameGrid[0][j] = 0;
            }
            i++; // recheck this row after collapsing
        }
    }
    if (lines == 1) 
        score += 10;
    else if (lines == 2)
        score += 30;
    else if (lines == 3) 
        score += 60;
    else if (lines >= 4) 
        score += 100;
}



/*
void bomb()
{
    int x= rand()%6;  //spawans random number b/w 1 and 6. This means the bomb has 1 in 6 chance of falling              
          
    if(x==2)
    {
    
    }      
     
}
*/