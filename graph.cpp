#include "graph.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <map>

struct Node{
    int parent=-1;
    size_t rang=1;
};
class dsu{
private:
    std::vector<Node> mass;
    int _get(int index){
        if (mass[index].parent == -1)
            return index;
        return mass[index].parent=_get(mass[index].parent);
    }
    void _unite(int x, int y)
    {
        int first_root = _get(x);
        int second_root = _get(y);

        if (first_root != second_root) {
            if (mass[first_root].rang < mass[second_root].rang) {
                mass[first_root].parent = second_root;
            }
            else if (mass[first_root].rang > mass[second_root].rang) {
                mass[second_root].parent = first_root;
            }
            else {
                mass[second_root].parent = first_root;
                mass[first_root].rang += 1;
            }
        }
    }
public:
    dsu(size_t size){
        mass.resize(size);
    }
    int get(int x){
        return _get(x);
    }
    void unite(int x,int y){
        _unite(x,y);
    }
};


bool comp(const edge& first,const edge& second){
    if(first.limit<second.limit)
        return true;
    if(first.limit>second.limit)
        return false;
    if(first.vertices<second.vertices)
        return true;
    if(first.vertices>second.vertices)
        return false;
    if(first.to<second.to)
        return true;
    return false;
}



const double PI = 3.14159265358979323846;
const double RADIUS = 6371;
double toRadians(double degrees) {
    return degrees * PI / 180;
}
double distance(double lat1, double lon1, double lat2, double lon2) {
    double phi1 = toRadians(lat1);
    double phi2 = toRadians(lat2);
    double deltaPhi = toRadians(lat2 - lat1);
    double deltaLambda = toRadians(lon2 - lon1);
    double a = sin(deltaPhi/2) * sin(deltaPhi/2) + cos(phi1) * cos(phi2) * sin(deltaLambda/2) * sin(deltaLambda/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return RADIUS * c;
}



std::vector<std::vector<int>> graph::_floyd_uorsh() {
    std::vector<std::vector<int>> dist=adjacency_matrix;
    for(int i=0;i<count_of_vertices;i++){
        dist[i][i]=0;
    }
    for (int i = 0; i < count_of_vertices; i++) {
        for (int j = 0; j < count_of_vertices; j++) {
            for (int z = 0; z < count_of_vertices; z++) {
                if (dist[i][z] != INT_MAX && dist[j][i] != INT_MAX&& dist[j][z] > (dist[j][i] + dist[i][z]))
                    dist[j][z] = dist[j][i] + dist[i][z];
            }
        }
    }
    return dist;
}

void graph::_color(){
    int result[count_of_vertices];
    result[0]  = 0;
    for (int u = 1; u < count_of_vertices; u++)
        result[u] = -1;
    int count=-1;
    bool available[count_of_vertices];
    for (int cr = 0; cr < count_of_vertices; cr++)
        available[cr] = false;
    for (int u = 1; u < count_of_vertices; u++){
        for (auto i:adjacency_list[u])
            if (result[i] != -1)
                available[result[i]] = true;
        int cr;
        for (cr = 0; cr < count_of_vertices; cr++)
            if (available[cr] == false)
                break;
        result[u] = cr;
        count=std::max(count,cr);
        for (auto i:adjacency_list[u])
            if (result[i] != -1)
                available[result[i]] = false;
    }
    /*for (int u = 0; u < count_of_vertices; u++)
       std::cout << "Vertex " << u << " --->  Color "<< result[u] << "\n";
       */
    std::cout<<"The chromatic number: "<<count-1;
}
void graph::_radix_deam_mid(){
    std::vector<std::vector<int>> tmp=_floyd_uorsh();
    int count_mid=INT_MAX,count_deam=INT_MIN,count_radix=INT_MAX;
    for(int i=0;i<count_of_vertices;i++){
        if(i==10 || i==21 || i==47 || i==20 || i==27)
            continue;
        int level=0,level_max=-1;
        for(int j=0;j<count_of_vertices;j++){
            if(tmp[i][j]!=INT_MAX) {
                level += tmp[i][j];
                level_max=std::max(tmp[i][j],level_max);
            }
        }
        if(count_mid>level){
            count_mid=level;
        }
        if(count_deam<level_max){
            count_deam=level_max;
        }
        if(count_radix>level_max){
            count_radix=level_max;
        }
    }
    std::cout<<"Diameter: "<<count_deam<<"\n";
    std::cout<<"Radius: "<<count_radix<<"\n";
    std::cout<<"Centre:\n";
    for(int i=0;i<count_of_vertices;i++){
        int level=0,level_max=-1;
        if(i==10 || i==21 || i==47 || i==20 || i==28)
            continue;
        for(int j=0;j<count_of_vertices;j++){
            if(tmp[i][j]!=INT_MAX) {
                level += tmp[i][j];
                level_max = std::max(level_max, tmp[i][j]);
            }
        }
        if(count_radix==level_max){
            std::cout<<"        "<<name[i]<<" "<<i+1<<"\n";
        }
    }
}
void graph::_max_min_deg(){
    size_t max_deg=0,min_deg=SIZE_MAX;
    for(int i=0;i<count_of_vertices;i++){
        if(adjacency_list[i].size()>=max_deg) {
            max_deg = adjacency_list[i].size();
        }
        if(adjacency_list[i].size()<=min_deg && adjacency_list[i].size()!=0){
            min_deg=adjacency_list[i].size();
        }
    }
    std::cout<<"Max degree: "<<max_deg<<"\n";
    std::cout<<"Min degree: "<<min_deg<<"\n";
}
void graph::_add_edge(int& vertices,int& to){
    adjacency_matrix[vertices-1][to-1] = 1;
    adjacency_matrix[to-1][vertices-1] = 1;
    adjacency_list[vertices-1].push_back(to-1);
    adjacency_list[to-1].push_back(vertices-1);
    list_of_edge.push_back({distance(coordinate[vertices-1].first,coordinate[vertices-1].second,coordinate[to-1].first,coordinate[to-1].second),vertices-1,to-1});
    adg_bool[vertices-1][to-1] = true;
    adg_bool[to-1][vertices-1] = true;
}
void graph::_two_component(){
    std::set<std::pair<int,int>> most=_most();
    std::vector<color> visited(count_of_vertices);
    std::vector<int> color_of_el(count_of_vertices);
    int count_color=0;
    for(int i=0;i<count_of_vertices;i++){
        if(!visited[i]){
            count_color++;
            _dfs_for_two_comp(i,visited,most,count_color,count_color,color_of_el);
        }
    }
    std::vector<std::vector<int>> comp(count_color);
    for(int i=0;i<count_of_vertices;i++){
        comp[color_of_el[i]-1].push_back(i);
    }
    std::cout<<"Component of edge ambiguity"<<"\n";
    for(int i=0;i<count_color;i++){
        if(i<9)
            std::cout<<i+1<<"  ";
        else
            std::cout<<i+1<<" ";
        for(auto j:comp[i]){
            std::cout<<j+1<<" ";
        }
        std::cout<<"\n";
    }
}
std::set<std::pair<int,int>> graph::_most() {
    std::vector<color> visited(count_of_vertices);
    std::vector<int> first(count_of_vertices,INT_MIN);
    std::vector<int> second(count_of_vertices,INT_MIN);
    int parent=INT_MIN;
    std::set<std::pair<int,int>> ans;
    for(int i=0;i<count_of_vertices;i++){
        if(visited[i]==white){
            int round=0;
            _dfs_for_most(i,visited,second,first,INT_MIN,round,ans);
        }
    }
    return ans;
}
void graph::_find_max_click(){
    std::set<int> R, P, X;
    for(int i = 0; i < 49; i++) {
        P.insert(i);
    }
    BronKerbosch(R, P, X);
    std::cout<<"Max size of qlick: "<<max_size<<"\n";
    printSet(qlick);
}


void graph::printSet(std::set<int> set_a) {
    std::cout << "{ ";
    for(auto& e: set_a) {
        std::cout << e << " ";
    }
    std::cout << "}" << std::endl;
}
std::set<int> graph::neighbor(int v) {
    std::set<int> result;
    for(int i = 0; i < count_of_vertices; i++) {
        if (adg_bool[v][i]) {
            result.insert(i);
        }
    }
    return result;
}
std::set<int> graph::intersection(std::set<int> set_a, std::set<int> set_b) {
    std::set<int> result;
    set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), inserter(result, result.begin()));
    return result;
}
void graph::BronKerbosch(std::set<int> R, std::set<int> P, std::set<int> X) {
    if (P.size() == 0 && X.size() == 0) {
        if(max_size<R.size()){
            max_size=R.size();
            qlick=R;
        }
        return;
    }

    int pivot = 0;


    for(int i = 0; i < count_of_vertices; i++) {
        if(P.count(i) && !adg_bool[pivot][i]) {
            R.insert(i);
            BronKerbosch(R, intersection(P, neighbor(i)), intersection(X, neighbor(i)));
            R.erase(i);
            P.erase(i);
            X.insert(i);
        }
    }
}


std::set<int> graph::_point_of_articulation(){
    std::set<int> ans;
    std::vector<color> visited(count_of_vertices);
    std::vector<int> first(count_of_vertices,INT_MIN);
    std::vector<int> second(count_of_vertices,INT_MIN);
    int round=0;
    for(int i=0;i<count_of_vertices;i++){
        if(!visited[i]){
            _dfs_for_point(i,visited,second,first,-1,round,ans);
        }
    }
    return ans;
}
void graph::_write_to_file_weight(){
    std::ofstream file("road.csv");
    file<<";";
    for(int i=0;i<count_of_vertices;i++){
        file<<name[i]<<";";
    }
    file<<"\n";
    for(int i=0;i<count_of_vertices;i++){
        file<<name[i]<<";";
        for(int j=0;j<count_of_vertices;j++){
            if(adjacency_matrix[i][j]!=INT_MAX)
                file<<distance(coordinate[i].first,coordinate[i].second,coordinate[j].first,coordinate[j].second)<<";";
            else
                file<<"INF;";
        }
        file<<"\n";
    }
    file.close();
}
void graph::_kruskals_mst(){
    sort(list_of_edge.begin(), list_of_edge.end(),comp);
    dsu s(count_of_vertices);
    int ans=0;
    for (auto edge : list_of_edge) {
        int w = edge.limit;
        int x = edge.vertices;
        int y = edge.to;
        if (s.get(x) != s.get(y)) {
            s.unite(x, y);
            ostov.push_back(edge);
        }
    }
    adjacency_list_ostov.resize(count_of_vertices,std::vector<int>(count_of_vertices));
    std::cout<<"MST of graph:\n";
    for(auto i:ostov){
        std::cout<<i.vertices+1<<" "<<i.to+1<<" "<<i.limit<<"\n";
        adjacency_list_ostov[i.vertices][i.to]=1;
        adjacency_list_ostov[i.to][i.vertices]=1;
    }
}
int graph::_size_from(int index,std::vector<std::vector<int>>& tmp){
    int size=0;
    for(int i=0;i<count_of_vertices;i++){
        size+=tmp[index][i];
    }
    return size;
}
void graph::_delete_from(int index,std::vector<std::vector<int>>& tmp){
    for(int i=0;i<count_of_vertices;i++){
        tmp[i][index]=0;
    }

}
void graph::_prufer_code(){
    std::queue<int> ans;
    std::vector<bool> visited(count_of_vertices);

    std::vector<std::vector<int>> tmp=adjacency_list_ostov;
    while(ans.size()!=count_of_vertices-6){
        int num=-1,size=50;
        for(int i=0;i<count_of_vertices;i++){
            if(!visited[i] && _size_from(i,tmp) < size && _size_from(i,tmp)!=0){
                size=_size_from(i,tmp);
                num=i;
            }
        }
        visited[num]=true;
        _delete_from(num,tmp);
        for(int i=0;i<count_of_vertices;i++){
            if(tmp[num][i]){
                ans.push(i);
                break;
            }
        }
    }
    std::cout<<"Prufer code:\n";
    while(!ans.empty()){
        std::cout<<ans.front()+1<<" ";
        ans.pop();
    }
}
void graph::_binary_code(){
    std::vector<bool> visited(count_of_vertices);
    std::queue<int> answer;
    _dfs_for_bin_code(3,visited,answer);
    std::cout<<"\n";
    std::cout<<"Binary code:\n";
    while(!answer.empty()){
        std::cout<<answer.front()<<" ";
        answer.pop();
    }
}



void graph::_dfs_for_bin_code(int vertices,std::vector<bool>& visited,std::queue<int>& ans){
    visited[vertices]= true;
    for(int i=0;i<count_of_vertices;i++){
        if(adjacency_list_ostov[vertices][i] && !visited[i]){
            ans.push(1);
            _dfs_for_bin_code(i,visited,ans);
        }
    }
    ans.push(0);
}
void graph::_dfs(int vertices, std::vector<color>& visited, std::set<int>& clique) {
    visited[vertices]=black;
    clique.insert(vertices);
    for (auto i:adjacency_list[vertices]) {
        if (!visited[i]) {
            _dfs(i,visited, clique);
        }
    }
}
void graph::_dfs_for_most(int vertices,std::vector<color>& visited,std::vector<int>& second,std::vector<int>& first,int parent,int& round,std::set<std::pair<int,int>>& ans){
    round++;
    visited[vertices] = grey;
    second[vertices] = first[vertices] = round;
    for (auto i:adjacency_list[vertices]){
        if(i==parent)
            continue;
        if(visited[i]){
            first[vertices]  = std::min(first[vertices], second[i]);
        }
        else{
            _dfs_for_most(i, visited, second, first, vertices,round,ans);
            first[vertices]  = std::min(first[vertices], first[i]);
            if (first[i] > second[vertices])
                ans.insert({std::min(i,vertices),std::max(i,vertices)});
        }
    }
}
void graph::_dfs_for_two_comp(int vertices,std::vector<color>& visited,std::set<std::pair<int,int>>& most,int& count_color,int color,std::vector<int>& color_of_el){
    visited[vertices]=black;
    color_of_el[vertices]=color;
    for(auto i:adjacency_list[vertices]){
        if(!visited[i]){
            if(most.find({vertices,i})==most.end() && most.find({i,vertices})==most.end() ){
                _dfs_for_two_comp(i,visited,most,count_color,color,color_of_el);
            }
            else{
                count_color++;
                _dfs_for_two_comp(i,visited,most,count_color,count_color,color_of_el);
            }
        }
    }
}
void graph::_dfs_for_point(int vertices,std::vector<color>& visited,std::vector<int>& second,std::vector<int>& first,int parent,int& round,std::set<int>& ans){
    round++;
    visited[vertices] = grey;
    second[vertices] = first[vertices] = round;
    int count=0;
    for (auto i:adjacency_list[vertices]){
        if(i==parent)
            continue;
        if(visited[i]){
            first[vertices]  = std::min(first[vertices], second[i]);
        }
        else{
            _dfs_for_point(i, visited, second, first, vertices,round,ans);
            count++;
            first[vertices]  = std::min(first[vertices], first[i]);
            if (parent!=-1 && first[i] > second[vertices])
                ans.insert(vertices);
        }
    }

}



void graph::add_edge(int first,int second){
    _add_edge(first,second);
    edge_list_for_count.insert({std::min(first,second),std::max(first,second)});
}
void graph::print(){
    for(int i=0;i<count_of_vertices;i++){
        if(i<9)
            std::cout<<i+1<<"  ";
        else
            std::cout<<i+1<<" ";
        for(auto j:adjacency_list[i]){
            std::cout<<j<<" ";
        }
        std::cout<<"\n";
    }
}
void graph::max_min_deg(){
    _max_min_deg();
}
void graph::radix_deam_mid(){
    _radix_deam_mid();
}
void graph::color_of_graph(){
    _color();
}
void graph::max_click_of_graph(){
    _find_max_click();
}
void graph::component(){
    _two_component();
}
void graph::component_ver(){
    _two_component_ver();
}
void graph::road_for_csv(){
    _write_to_file_weight();
}
void graph::ostv(){
    _kruskals_mst();
    std::cout<<"\n\n";
    _prufer_code();
    std::cout<<"\n\n";
    _binary_code();
}
void graph::pint_edge(){
    for(int i=0;i<count_of_vertices;i++){
        std::cout<<i+1<<": ";
        for(auto j:adjacency_list[i]){
            std::cout<<j+1<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<edge_list_for_count.size();
}





std::vector<std::vector<int>> graph;
std::vector<int> used, enter, ret, colors, painted;
std::map<std::pair<int, int>, std::vector<int>> numbersOfEdges;
int coll, n, m, maxColor;

std::pair<int, int> getEdge(int a, int b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    return std::make_pair(a, b);
};
void setColor(int v, int to, int color) {
    std::vector<int> numbers = numbersOfEdges[getEdge(v, to)];
    for (int i = 0; i < numbers.size(); ++i) {
        colors[numbers[i]] = color;
    }
};
void dfs(int v, int p = -1) {
    used[v] = 1;
    enter[v] = ret[v] = coll++;
    int c = 0;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to == p) continue;
        if (used[to]) {
            ret[v] = std::min(ret[v], enter[to]);
        } else {
            dfs(to, v);
            c++;
            ret[v] = std::min(ret[v], ret[to]);
        }
    }
}
void paint(int v, int color, int p) {
    painted[v] = 1;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to == p) continue;
        if (!painted[to]) {
            if (ret[to] >= enter[v]) {
                int newColor = ++maxColor;
                setColor(v, to, newColor);
                paint(to, newColor, v);
            } else {
                setColor(v, to, color);
                paint(to, color, v);
            }
        } else if (enter[to] < enter[v]) {
            setColor(v, to, color);
        }
    }
}
std::string name[49]{
        "Albania",
        "Andorra",
        "Armenia",
        "Austria",
        "Azerbaijan",
        "Belarus",
        "Belgium",
        "Bosnia and Herzegovina",
        "Bulgaria",
        "Croatia",
        "Cyprus",
        "Czechia",
        "Denmark",
        "Estonia",
        "Finland",
        "France",
        "Germany",
        "Georgia",
        "Greece",
        "Hungary",
        "Iceland",
        "Ireland",
        "Italy",
        "Latvia",
        "Liechtenstein",
        "Lithuania",
        "Luxembourg",
        "Malta",
        "Moldova",
        "Monaco",
        "Montenegro",
        "Netherlands",
        "North Macedonia",
        "Norway",
        "Poland",
        "Portugal",
        "Romania",
        "Russia",
        "San Marino",
        "Serbia",
        "Slovakia",
        "Slovenia",
        "Spain",
        "Sweden",
        "Switzerland",
        "Turkey",
        "Ukraine",
        "United Kingdom",
        "Vatican City",
};
void solve(int arg,int s,std::set<std::pair<int,int>>& edge_list) {
    n=49,m=93;
    graph.resize(n + 1);
    used.resize(n + 1);
    painted.resize(n + 1);
    enter.resize(n + 1);
    ret.resize(n + 1);
    colors.resize(m + 1);
    int host=1;
    for (auto i:edge_list) {
        int beg=i.first, end=i.second;
        graph[beg].push_back(end);
        graph[end].push_back(beg);

        numbersOfEdges[getEdge(beg, end)].push_back(host++);
    }

    coll = 1;
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) dfs(i);
    }

    maxColor = 0;
    for (int i = 1; i <= n; ++i) {
        if (!painted[i]) {
            paint(i, maxColor, -1);
        }
    }

    std::map<int,std::set<std::string>> ans;
    coll=1;
    for (auto i:edge_list) {
        std::string tmp="("+std::to_string(i.first)+";"+std::to_string(i.second)+")";
        ans[colors[coll]].insert(tmp);
        coll++;
    }
    std::cout<<"Component of vertices ambiguity"<<"\n";
    for(auto i:ans){
        std::cout<<i.first<<": ";
        for(auto j:i.second){
            std::cout<<j<<" ";
        }
        std::cout<<"\n";
    }

}

void graph::_two_component_ver() {
    solve(49,93,edge_list_for_count);
}
