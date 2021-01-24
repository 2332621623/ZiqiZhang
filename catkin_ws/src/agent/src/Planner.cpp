    #define Agent 2
    #include <math.h>
    #include <iostream>
    #include <vector>
    #include <string>
    #include <map>
    #include <algorithm>
    using namespace std;
    struct Point
    {
        Point(){}
     
        Point(int x, int y, int t){
            this->x = x;
            this->y = y;
            this->t = t;
        }
        int x = 0;
        int y = 0;
        int t = 0;
     
        double distance(const Point &pos){
            double dis = pos.x + x+ pos.y + y;
            return dis;
        }
     
        bool operator==(const Point &pos){
            return this->x == pos.x&&this->y == pos.t&&this->t;
        }
    };
     
    struct Data
    {
        Data(){}
        Data(Point pos, double h, double g, Data *parent){
            this->pos = pos;
            this->h = h;
            this->g = g;
            this->parent = parent;
        }
     
        Point pos=Point(0,0,0);
        double h = 0;
        double g = 0;
        Data *parent = nullptr;
     
        double f(){
            return this->g + this->h;
        }
    };
     
    struct MinHeap 
    {
        vector<Data*> m_vec;
        map<string, Data*> m_map;
        int index = 0;
     
        Data *getMinAndRemove(){
            if (isEmpty()){
                return nullptr;
            }
            sort();
            auto first = m_vec.at(0);
            auto last = m_vec.at(index - 1);
            m_vec[0] = last;
    		
            --index;
            return first;    
        }
     
        bool isEmpty(){
            return index <= 0;
        }
     
        string getKey(Point pos){
            char buff[32] = { 0 };
            sprintf(buff, "%d-%d -%d", pos.x, pos.y, pos.t);
            return buff;
        }
     
        Data *find(Point pos){
            auto it = m_map.find(getKey(pos));
            if (it!=m_map.end())
            {
                return it->second;
            }
            return nullptr;
        }
     
        void add(Data *data){
            if (index<m_vec.size())
            {
                m_vec[index] = data;
            }
            else
            {
                m_vec.push_back(data);
            }
            index = m_vec.size();
            m_map[getKey(data->pos)] = data;
        }
     
        void sort(){
           std::sort(m_vec.begin(), m_vec.end(), [](Data *a, Data *b){return a->f() < b->f(); });
        }
     
        void release(){
           for (auto it = m_map.begin();it!=m_map.end();)
           {
                Data *tmp = it->second;
                it = m_map.erase(it);
                delete tmp;
           }
        }
    };
     
    int main()
    {
        const char START = 's';
        const char END = 'e';
        const char VISITED = '.';
        const char SPACE = '*';
        const char OBSTACLE = '1';
        Point startPos;
        Point endPos;
        int loop = 1;
        int step = 2; 
        int last_step = 6;
        int agent_num  = 2;
        int last_path[][3]={{2,0,0},{2,1,1},{2,2,2},{2,3,3},{2,4,4},{2,5,5}};

        //for(int loop = 1; loop < Agent+1; ++loop)
        //{

            int map3d[11][11][121] = {0};
          /* if (loop = 1)
            {
                for (int i = 0; i<121; ++i)
                {  
                     map3d[2][5][i]=3;
                }
                map3d[2][0][0]=2;
            }*/
            //else
           //{   
                for(int i = 0; i<last_step; ++i)
                {
                    map3d[last_path[i][0]][last_path[i][1]][last_path[i][2]]=agent_num+10;
                }
                for(int i = 0; i>=last_step&&i<121; ++i)
                {
                    map3d[last_path[-1][0]][last_path[-1][1]][i]=agent_num+10;
                }
            
          
              for (int i = 0; i<121; ++i)
                {  
                     map3d[6][3][i]=3;
                }
                map3d[0][3][0]=2;
           //}

        char arr[11][11][121] = { 0 };
        int index = 0;
        for(int k =0; k<121; ++k)
        {
            for (int i = 0; i <11;++i)
          {
                for (int j = 0; j <11;++j)
              {
                 int map_node = map3d[i][j][k];
                 if (map_node==0)
                 {
                     arr[i][j][k] = SPACE;
                 }
                
                 else if (map_node==2)
                 {
                     arr[i][j][k] = START;
                     startPos = Point(i, j,k);
                 }
                 else if (map_node==3)
                 {
                     arr[i][j][k] =  END;
                     endPos = Point(i,j,k);
                 }
                 else
                 {
                    arr[i][j][k] = OBSTACLE ;
                 }
                 
                }
            }
        }
        
        int directs[][3] = { { 0, 1, 1 }, { 1, 0, 1 }, { 0, -1, 1 }, { -1, 0, 1 } };
     
        MinHeap heap;
        heap.add(new Data(startPos, 0, 0, nullptr));
        bool finish = false;
        Data *lastData = nullptr;
        
        while (!finish&&!heap.isEmpty())
        {
        	Data *data = heap.getMinAndRemove();
        	if (arr[data->pos.x][data->pos.y][data->pos.t]==SPACE)
        	{
                arr[data->pos.x][data->pos.y][data->pos.t] = VISITED;
        	}   
     
        	for (auto dir : directs)
        	{
                Point pos = Point(data->pos.x+dir[0], data->pos.y + dir[1], data->pos.t + dir[2]);
                Point current_pos = Point(data->pos.x, data->pos.y , data->pos.t + dir[2]);
                Point pos_other_agent_last = Point(data->pos.x+dir[0], data->pos.y + dir[1], data->pos.t );
                

                if (pos.x>0&&pos.x<11
                    && pos.y>0 && pos.y<11
                    && pos.t>0 && pos.t<121)
                {
                    char c = arr[pos.x][pos.y][pos.t];
                    char c1 = arr[current_pos.x][current_pos.y][current_pos.t];
                    char c2 = arr[pos_other_agent_last.x][pos_other_agent_last.y][pos_other_agent_last.t];
                    if (c==END)
                    {
                        finish = true;
                        lastData = data;
                        break;
                    }
                    if (c!=SPACE)
                    {
                        continue;
                    } 
                    if (c1 == OBSTACLE&&c2 == OBSTACLE)
                    {
                        continue;
                    }
                   
                    auto nn = heap.find(pos);
                    if (nn)
                    {
                        if (nn->g>data->g+1)
                        {
                            nn->g = data->g + 1;
                            nn->parent = data;
                        }
                    } else{
                        heap.add(new Data(pos, pos.distance(endPos), data->g + 1,data));
                    }
                }
            }
        }
     
        if (lastData)
        {
            
            while (lastData->parent)
            {
                arr[lastData->pos.x][lastData->pos.y][lastData->pos.t] = '@';
                cout <<"x="<<lastData->pos.x<<",y="<<lastData->pos.y<<",t="<<lastData->pos.t<<endl;
                lastData = lastData->parent;
                ++step;
            }
             cout <<"x="<<startPos.x<<",y="<<startPos.y<<",t="<<startPos.t<<endl;
            
        } else{
            cout << "no path" << endl;
        }


        for  (int k = 0; k < step+1; ++k)
        {
            arr[endPos.x][endPos.y][k] = SPACE;
        }

        for  (int k = 0; k < step+2; ++k)
        {
            for (int i = 0; i < 11; ++i)
            {
                for (int j = 0; j < 11; ++j)
                {
                 cout << arr[i][j][k];
                }
                cout << endl;
            }
            cout << "--------------------------------------------------"<<endl;
            cout << endl;
        }

        heap.release();
        //}
             
        return 0;
    }