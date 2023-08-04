#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;
char s[1000000000];
struct node{
    node* next_node;
    node* pre_node;
    int name;
    node(int n){
        name = n;
        next_node = NULL;
        pre_node = NULL;
    }
};
struct Q_node{
    Q_node* next_Q_node;
    Q_node* pre_Q_node;
    int node_name;
    int fpga_name;
    Q_node(int n_n, int f_n){
        node_name = n_n;
        fpga_name = f_n;
        next_Q_node = NULL;
        pre_Q_node = NULL;
    }
};
struct Fix_Node_s{
    Fix_Node_s* next_Fix_Node_s;
    node* first_node;
    int* distance_with_Vj;
    int Fix_Node_name;
    int fpga_name;
    int distance;
    Fix_Node_s(int F_N_n, int f_n){
        Fix_Node_name = F_N_n;
        fpga_name = f_n;
        distance = -1;
        first_node = NULL;
        next_Fix_Node_s = NULL;
        distance_with_Vj = NULL;
    }
};
struct PQ_Q_element{
    int num_of_cddt;
    int movable_node_name;
    PQ_Q_element(int n, int m){
        num_of_cddt = n;
        movable_node_name = m;
    }
};

struct Qcmp{
    bool operator()(PQ_Q_element a, PQ_Q_element b){
        return a.num_of_cddt > b.num_of_cddt;
    }
};

void relax(int min_node_name, int adjacency_node_name, int* &distance_arr){
    if(distance_arr[adjacency_node_name] > distance_arr[min_node_name]+1){
        distance_arr[adjacency_node_name] = distance_arr[min_node_name]+1;
    }
}
void dijkstra(node** &adjacency_list, int total_num, int node_name, int limit, int* &distance_arr){
    if(limit == -1){  
        node *unvisit = new node(-1);
        for(int i = 0; i < total_num; i++){
            if(i != node_name){
                node* new_node = new node(i);
                if(unvisit->next_node == NULL){
                    unvisit->next_node = new_node;
                    new_node->pre_node = unvisit;
                }
                else{
                    new_node->next_node = unvisit->next_node;
                    new_node->pre_node = unvisit;
                    unvisit->next_node->pre_node = new_node;
                    unvisit->next_node = new_node;
                }
            }
        }
        for(int i = 0; i < total_num; i++){
            distance_arr[i] = 1000000;
        }
        //initial distance array : self = 0, adjancy = 1
        distance_arr[node_name] = 0;
        node* next = adjacency_list[node_name]->next_node;
        while(next){
            distance_arr[next->name] = 1;
            next = next->next_node;
        }
        while(unvisit->next_node != NULL){
            node* unvisit_next = unvisit->next_node;
            int temp_min = 1000000;
            node* min_node = NULL;
            while(unvisit_next != NULL){
                if(distance_arr[unvisit_next->name] < temp_min){
                    temp_min = distance_arr[unvisit_next->name];
                    min_node = unvisit_next;
                }
                unvisit_next = unvisit_next->next_node;
            }
            if(min_node != NULL){
                min_node->pre_node->next_node = min_node->next_node;
                if(min_node->next_node != NULL){
                    min_node->next_node->pre_node = min_node->pre_node;
                }
                int min_node_name = min_node->name;
                //delete min_node;
                //relax all adjacency node of min_node
                node* next = adjacency_list[min_node_name]->next_node;
                while(next){
                    relax(min_node_name, next->name, distance_arr);
                    next = next->next_node;
                }
            }
            else{
                unvisit_next = unvisit->next_node;
                while(unvisit_next != NULL){
                    node* del = unvisit_next;
                    del->pre_node->next_node = del->next_node;
                    if(del->next_node != NULL){
                        del->next_node->pre_node = del->pre_node;
                    }
                    unvisit_next = unvisit_next->next_node;
                    //delete del;
                }
            }
        }
    }
    else{
        node *unvisit = new node(-1);
        for(int i = 0; i < total_num; i++){
            if(i != node_name){
                node* new_node = new node(i);
                if(unvisit->next_node == NULL){
                    unvisit->next_node = new_node;
                    new_node->pre_node = unvisit;
                }
                else{
                    new_node->next_node = unvisit->next_node;
                    new_node->pre_node = unvisit;
                    unvisit->next_node->pre_node = new_node;
                    unvisit->next_node = new_node;
                }
            }
        }
        for(int i = 0; i < total_num; i++){
            distance_arr[i] = 1000000;
        }
        //initial distance array : self = 0, adjancy = 1
        distance_arr[node_name] = 0;
        node* next = adjacency_list[node_name]->next_node;
        while(next){
            distance_arr[next->name] = 1;
            next = next->next_node;
        }
        while(unvisit->next_node != NULL){
            node* unvisit_next = unvisit->next_node;
            int temp_min = 1000000;
            node* min_node = NULL;
            while(unvisit_next != NULL){
                if(distance_arr[unvisit_next->name] < temp_min){
                    temp_min = distance_arr[unvisit_next->name];
                    min_node = unvisit_next;
                }
                unvisit_next = unvisit_next->next_node;
            }
            if(min_node != NULL){
                min_node->pre_node->next_node = min_node->next_node;
                if(min_node->next_node != NULL){
                    min_node->next_node->pre_node = min_node->pre_node;
                }
                int min_node_name = min_node->name;
                //delete min_node;
                //relax all adjacency node of min_node
                if(distance_arr[min_node_name] < limit){
                    node* next = adjacency_list[min_node_name]->next_node;
                    while(next){
                        relax(min_node_name, next->name, distance_arr);
                        next = next->next_node;
                    }
                }
            }
            else{
                unvisit_next = unvisit->next_node;
                while(unvisit_next != NULL){
                    node* del = unvisit_next;
                    del->pre_node->next_node = del->next_node;
                    if(del->next_node != NULL){
                        del->next_node->pre_node = del->pre_node;
                    }
                    unvisit_next = unvisit_next->next_node;
                    //delete del;
                }
            }
        }
    }
}
int part[1000000];
int vi_cddt_with_k[1000000];
int update_cdd[1000000];
int capacity [1000000];
int outdegree_count[1000000];
int main(int argc, char** argv){
    FILE* input = fopen(argv[1], "r");
    int Total_num_FPGAs;
    int Total_num_FPGA_channels;
    int Capacity_per_FPGA;
    int Total_num_nodes;
    int Total_num_nets;
    int Total_num_fixed_nodes;
    fscanf(input, "%d %d %d %d %d %d\n", &Total_num_FPGAs, &Total_num_FPGA_channels, &Capacity_per_FPGA, &Total_num_nodes, &Total_num_nets, &Total_num_fixed_nodes);
    node** adjacency_FPGA = new node*[Total_num_FPGAs];
    node** adjacency_node = new node*[Total_num_nodes];
    for(int i = 0; i < Total_num_FPGAs; i++) adjacency_FPGA[i] = new node(-1);
    for(int i = 0; i < Total_num_nodes; i++) adjacency_node[i] = new node(-1);
    for(int i = 0; i < Total_num_FPGA_channels; i++){
        int x, y;
        fscanf(input, "%d %d\n", &x, &y);
        node* new_node_y = new node(y);
        new_node_y->next_node = adjacency_FPGA[x]->next_node;
        adjacency_FPGA[x]->next_node = new_node_y;
        node* new_node_x = new node(x);
        new_node_x->next_node = adjacency_FPGA[y]->next_node;
        adjacency_FPGA[y]->next_node = new_node_x;
    }
    for(int i = 0; i < Total_num_nets; i++){
        fscanf(input, "%[^\n]\n", s);
        stringstream ss(s);
        string source_s;
        string sink_s;
        ss >> source_s;
        int source = stoi(source_s);
        while(ss >> sink_s){
            int sink = stoi(sink_s);
            node* new_sink_node = new node(sink);
            new_sink_node->next_node = adjacency_node[source]->next_node;
            adjacency_node[source]->next_node = new_sink_node;
            node* new_source_node = new node(source);
            new_source_node->next_node = adjacency_node[sink]->next_node;
            adjacency_node[sink]->next_node = new_source_node;
        }
    }
    int* movable = new int[Total_num_nodes];
    for(int i = 0; i < Total_num_nodes; i++) movable[i] = 1;
    Q_node* Q = new Q_node(-1, -1);
    Q_node* last_Q = Q;
    for(int i = 0; i < Total_num_fixed_nodes; i++){
        int n_id, F_id;
        fscanf(input, "%d %d\n", &n_id, &F_id);
        Q_node* new_Q_node = new Q_node(n_id, F_id);
        movable[n_id] = 0;
        new_Q_node->pre_Q_node = last_Q;
        last_Q->next_Q_node = new_Q_node;
        last_Q = new_Q_node;
    }

    int **FPGA_distance_array = new int*[Total_num_FPGAs];
    for(int i = 0; i < Total_num_FPGAs; i++){
        FPGA_distance_array[i] = new int[Total_num_FPGAs];
        dijkstra(adjacency_FPGA, Total_num_FPGAs, i, -1, FPGA_distance_array[i]);
    }
    //algorithm 1 : 1 
    int* maxDist_FPGAs = new int[Total_num_FPGAs];
    for(int i = 0; i < Total_num_FPGAs; i++) maxDist_FPGAs[i] = 0;
    for(int i = 0; i < Total_num_FPGAs; i++){
        for(int j = 0; j < Total_num_FPGAs; j++){
            maxDist_FPGAs[i] = max(maxDist_FPGAs[i], FPGA_distance_array[i][j]);
        }
    }
    //algorithm 1 : 2~4
    node*** FPGA_S = new node**[Total_num_FPGAs];
    for(int i = 0; i < Total_num_FPGAs; i++){
        FPGA_S[i] = new node*[maxDist_FPGAs[i] + 1];
        for(int j = 0; j <= maxDist_FPGAs[i]; j++){
            FPGA_S[i][j] = new node(-1);
        }
    }
    for(int i = 0; i < Total_num_FPGAs; i++){
        for(int j = 0; j < Total_num_FPGAs; j++){
            int x = FPGA_distance_array[i][j];
            for(int k = x; k <= maxDist_FPGAs[i]; k++){
                node* new_node = new node(j);
                new_node->next_node = FPGA_S[i][k]->next_node;
                FPGA_S[i][k]->next_node = new_node;
            }
        }
    }
    
    for(int i = 0; i < Total_num_FPGAs; i++){
        //delete [] FPGA_distance_array[i];
    }
    //delete FPGA_distance_array;

    //algorithm 1 : 5~7
    Fix_Node_s* Fix_Node_S = new Fix_Node_s(-1,-1);
    int **Fix_node_distance_array = new int*[Total_num_fixed_nodes];
    Q_node* next_Q = Q->next_Q_node;
    for(int i = 0; i < Total_num_fixed_nodes; i++){
        int fix_node_name = next_Q->node_name;
        int fix_node_FPGA_name = next_Q->fpga_name;
        int d = maxDist_FPGAs[fix_node_FPGA_name];
        Fix_Node_s* new_Fix_Node_s_node = new Fix_Node_s(fix_node_name, fix_node_FPGA_name);
        new_Fix_Node_s_node->distance = d;
        new_Fix_Node_s_node->first_node = new node(-1);
        new_Fix_Node_s_node->distance_with_Vj = new int[Total_num_nodes];
        dijkstra(adjacency_node, Total_num_nodes, fix_node_name, d, new_Fix_Node_s_node->distance_with_Vj);
        for(int j = 0; j < Total_num_nodes; j++){
            if(new_Fix_Node_s_node->distance_with_Vj[j] < d && j != fix_node_name){
                node* new_node = new node(j);
                new_node->next_node = new_Fix_Node_s_node->first_node->next_node;
                new_Fix_Node_s_node->first_node->next_node = new_node;
            }
        }
        new_Fix_Node_s_node->next_Fix_Node_s = Fix_Node_S->next_Fix_Node_s;
        Fix_Node_S->next_Fix_Node_s = new_Fix_Node_s_node;
        next_Q = next_Q->next_Q_node;
    }
    //algorithm 1 : 8~9
    int** Cddt = new int*[Total_num_nodes];
    for(int i = 0; i < Total_num_nodes; i++){
        int* new_Cddt = new int[Total_num_FPGAs];
        for(int j = 0; j < Total_num_FPGAs; j++) new_Cddt[j] = 1;
        Cddt[i] = new_Cddt;
    }
    next_Q = Q->next_Q_node;
    while(next_Q != NULL){
        int fix_node_name = next_Q->node_name;
        int fix_node_FPGA_name = next_Q->fpga_name;
        for(int j = 0; j < Total_num_FPGAs; j++) Cddt[fix_node_name][j] = 0;
        Cddt[fix_node_name][fix_node_FPGA_name] = 1;
        next_Q = next_Q->next_Q_node;
    }
    
    //algorithm 1 : 10 ~ 20
    
    Q_node* Q_Top = Q->next_Q_node;
    while(Q_Top != NULL){
        // 11~12
        int Q_pair_node = Q_Top->node_name;
        int Q_pair_fpga = Q_Top->fpga_name;
        // 13
        Fix_Node_s* next = Fix_Node_S->next_Fix_Node_s;
        node* Vj = NULL;
        int *distance_array_of_Q_pair_node = NULL;
        while(next != NULL){
            if(next->Fix_Node_name == Q_pair_node){
                Vj = next->first_node->next_node;
                distance_array_of_Q_pair_node = next->distance_with_Vj;
            }
            next = next->next_Fix_Node_s;
        }
        while(Vj != NULL){
            int Vj_name = Vj->name;
            if(movable[Vj_name] == 1){
                // 14
                int k = distance_array_of_Q_pair_node[Vj_name]; 
                for(int i = 0; i < Total_num_FPGAs; i++) vi_cddt_with_k[i] = 0;
                node* next_FPGA_S_node = FPGA_S[Q_pair_fpga][k]->next_node;
                while(next_FPGA_S_node != NULL){
                    int cdd = next_FPGA_S_node->name;
                    vi_cddt_with_k[cdd] = 1;
                    next_FPGA_S_node = next_FPGA_S_node->next_node;
                }
                // 15
                int Cddt_size = 0;
                for(int i = 0; i < Total_num_FPGAs; i++){
                    Cddt[Vj_name][i] = Cddt[Vj_name][i] & vi_cddt_with_k[i];
                    if(Cddt[Vj_name][i] == 1) Cddt_size++;
                }
                // 16
                if(Cddt_size == 1){
                    for(int i = 0; i < Total_num_FPGAs; i++){
                        if(Cddt[Vj_name][i] == 1){ 
                            int FPGA_Vj = i;
                            Q_node* new_Q_node = new Q_node(Vj_name, FPGA_Vj);
                            new_Q_node->pre_Q_node = last_Q;
                            last_Q->next_Q_node = new_Q_node;
                            last_Q = new_Q_node;
                            movable[Vj_name] = 0;
                            Fix_Node_s* new_Fix_Node_s_node = new Fix_Node_s(Vj_name, FPGA_Vj);
                            new_Fix_Node_s_node->first_node = new node(-1);
                            new_Fix_Node_s_node->distance = maxDist_FPGAs[FPGA_Vj];
                            new_Fix_Node_s_node->distance_with_Vj = new int[Total_num_nodes];
                            dijkstra(adjacency_node, Total_num_nodes, Vj_name, maxDist_FPGAs[FPGA_Vj], new_Fix_Node_s_node->distance_with_Vj);
                            for(int j = 0; j < Total_num_nodes; j++){
                                if(new_Fix_Node_s_node->distance_with_Vj[j] < new_Fix_Node_s_node->distance && j != Vj_name){
                                    node* new_node = new node(j);
                                    new_node->next_node = new_Fix_Node_s_node->first_node->next_node;
                                    new_Fix_Node_s_node->first_node->next_node = new_node;
                                }
                            }
                            new_Fix_Node_s_node->next_Fix_Node_s = Fix_Node_S->next_Fix_Node_s;
                            Fix_Node_S->next_Fix_Node_s = new_Fix_Node_s_node;
                        }
                    }
                }
                else if(Cddt_size == 0){
                    return -1;
                }
                Vj = Vj->next_node;
            }
            else{
                Vj = Vj->next_node;
            }
        }
        Q_Top = Q_Top->next_Q_node;
    }
    for(int i = 0; i < Total_num_nodes; i++) outdegree_count[i] = 0;
    //algorithm 2 : 1~8
    for(int i = 0; i < Total_num_nodes; i++) part[i] = -1;
    for(int i = 0; i < Total_num_FPGAs; i++) capacity[i] = Capacity_per_FPGA;
    for(int i = 0; i < Total_num_nodes; i++){
        if(movable[i] == 0){
            int Cddt_name;
            for(int j = 0; j < Total_num_FPGAs; j++){
                if(Cddt[i][j] == 1) Cddt_name = j; 
            }
            capacity[Cddt_name]--;
            part[i] = Cddt_name;
        }
    }
    

    int movable_count = 0;
    int* cdd_count = new int[Total_num_nodes];
    for(int i = 0; i < Total_num_nodes; i++){
        int i_cdd_count = 0;
        for(int j = 0; j < Total_num_FPGAs; j++){
            if(Cddt[i][j] == 1) i_cdd_count++; 
        }
        cdd_count[i] = i_cdd_count;
    }
    for(int i = 0; i < Total_num_nodes; i++){
        if(movable[i] == 1){
            movable_count++;
        }
    }
    //algorithm 2 : 9
    node* nocddt = new node(-1);
    while(movable_count > 0){
        int node_Vj;
        int min_cdd = Total_num_FPGAs + 1;
        for(int i = 0; i < Total_num_nodes; i++){
            if(part[i] == -1){
                if(cdd_count[i] < min_cdd){
                    node_Vj = i;
                    min_cdd = cdd_count[i];
                }
            }
        }

        
        movable_count--;
        //algorithm 2 : 10~13
        int FPGA;
        int have_cdd = 0;
        int min_out_degree = 1000000;
        for(int i = 0; i < Total_num_FPGAs; i++){
            int outdegree = 0;
            if(Cddt[node_Vj][i] > 0){
                have_cdd = 1;
                node* next = adjacency_node[node_Vj]->next_node;
                while(next != NULL){
                    int next_in_FPGA = part[next->name];
                    if(next_in_FPGA != -1 && next_in_FPGA != -2){
                        if(next_in_FPGA != i) outdegree++;
                    }
                    next = next->next_node;
                }
                if(outdegree <= min_out_degree){
                    min_out_degree = outdegree;
                    FPGA = i;
                }
            }
        }

        int capacity_FPGA_Vj;
        if(have_cdd == 0){
            capacity_FPGA_Vj = 0;
        }
        else{
            capacity_FPGA_Vj = capacity[FPGA];
        }
        if(capacity_FPGA_Vj > 0){
            part[node_Vj] = FPGA;
            capacity[FPGA] =capacity[FPGA] - 1;
            int Traceback = 0;
            //algorithm 2 : 14
            for(int i = 0; i < Total_num_FPGAs; i++) update_cdd[i] = 1;
            node* next_FPGA_Vk = adjacency_FPGA[FPGA]->next_node;
            update_cdd[FPGA] = 0;                      
            while(next_FPGA_Vk != NULL){
                update_cdd[next_FPGA_Vk->name] = 0;
                next_FPGA_Vk = next_FPGA_Vk->next_node;
            }
            node* next_node_Vk = adjacency_node[node_Vj]->next_node;
            while(next_node_Vk != NULL){
                if(part[next_node_Vk->name] == -1){
                    int Cddt_vk = 0;
                    for(int i = 0; i < Total_num_FPGAs; i++){
                        Cddt[next_node_Vk->name][i] = Cddt[next_node_Vk->name][i] - update_cdd[i];
                        if(Cddt[next_node_Vk->name][i] > 0) Cddt_vk++;
                    }
                    if(Cddt_vk == 0){
                        Traceback = 1;
                    }
                    cdd_count[next_node_Vk->name] = Cddt_vk;
                }
                next_node_Vk = next_node_Vk->next_node;
            }
            if(Traceback == 1){
                Cddt[node_Vj][FPGA] = 0;
                capacity[FPGA] = capacity[FPGA] + 1;
                part[node_Vj] = -1;
                movable_count++;
                
                cdd_count[node_Vj] = cdd_count[node_Vj] - 1;
                node* next = adjacency_node[node_Vj]->next_node;
                while(next != NULL){
                    if(part[next->name] == -1){
                        int count = 0;
                        for(int i = 0; i < Total_num_FPGAs; i++){
                            Cddt[next->name][i] = Cddt[next->name][i] + update_cdd[i];
                            if(Cddt[next->name][i] > 0) count++;
                        }
                        cdd_count[next->name] = count;
                    }
                    next = next->next_node;
                }
            }
        }
        else{
            if(have_cdd == 1){
                Cddt[node_Vj][FPGA] = 0;
                part[node_Vj] = -1;
                cdd_count[node_Vj] = cdd_count[node_Vj] - 1;
                movable_count++;
            }
            else{
                node* newn = new node(node_Vj);
                newn->next_node = nocddt->next_node;
                nocddt->next_node = newn;
                part[node_Vj] = -2;
            }
        }
    }
    int ooooo = 0;
    node* next = nocddt->next_node;
    while(next != NULL){
        ooooo++;
        for(int i = 0; i < Total_num_FPGAs; i++){
            if(capacity[i] > 0){
                part[next->name] = i;
                capacity[i] = capacity[i] - 1;
                break;
            }
        }
        next = next->next_node;
    }
    FILE* output = fopen(argv[2], "w");
    for(int i = 0; i < Total_num_nodes; i++){
        fprintf(output, "%d %d\n", i, part[i]);
    }
    
}