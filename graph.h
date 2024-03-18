#ifndef DM_GRAPH_H
#define DM_GRAPH_H
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <map>

enum color{white,grey,black};
struct edge{
    double limit;
    int vertices;
    int to;

};





class graph {
private:
    std::vector<std::vector<int>> adjacency_matrix;
    std::vector<std::vector<bool>> adg_bool;
    std::vector<std::vector<int>> adjacency_list;
    std::vector<edge> list_of_edge;
    std::vector<edge> ostov;
    std::vector<std::vector<int>> adjacency_list_ostov;
    size_t count_edge=0;
    std::set<std::pair<int,int>> edge_list_for_count;
    size_t max_size=0;
    std::set<int> qlick;



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
    std::pair<double,double> coordinate[49]{
            {41.328294, 19.817981},
            {42.506260, 1.521692},
            {40.177628, 44.512546},
            {48.206481, 16.363451},
            {40.372973, 49.853145},
            {53.902735, 27.555691},
            {50.846699, 4.352542},
            {43.855818, 18.405753},
            {42.697838, 23.314498},
            {45.808594, 15.978577},
            {35.172871, 33.354173},
            {50.080345, 14.428973},
            {55.680671, 12.586098},
            {59.437529, 24.744767},
            {60.208567, 24.944985},
            {48.856663, 2.351556},
            {52.516363, 13.378906},
            {41.693081, 44.801559},
            {37.975527, 23.734855},
            {47.492647, 19.051399},
            {64.147115, -21.939213},
            {53.423001, -7.893721},
            {41.902689, 12.496176},
            {56.946840, 24.106075},
            {47.141050, 9.520889},
            {54.689383, 25.270894},
            {49.611423, 6.119478},
            {35.899106, 14.513613},
            {47.024512, 28.832159},
            {43.731022, 7.421121},
            {42.441228, 19.263139},
            {52.373059, 4.892559},
            {41.995902, 21.431449},
            {59.912754, 10.734371},
            {52.232090, 21.007139},
            {38.707890, -9.136594},
            {44.436377, 26.099038},
            {55.755863, 37.617700},
            {43.920703, 12.451231},
            {44.816236, 20.460467},
            {48.143488, 17.108361},
            {46.050888, 14.500313},
            {40.418407, -3.712746},
            {59.325003, 18.070900},
            {46.947979, 7.440390},
            {39.920756, 32.854049},
            {50.449247, 30.547764},
            {51.507351, -0.127695},
            {41.902185, 12.455707}
    };
    size_t count_of_vertices;

    void _two_component_ver();




    std::vector<std::vector<int>> _floyd_uorsh();
    void _color();
    void _radix_deam_mid();
    void _max_min_deg();
    void _add_edge(int& vertices,int& to);
    void _two_component();
    std::set<std::pair<int,int>> _most();
    void _find_max_click();

    void printSet(std::set<int> set_a);
    std::set<int> neighbor(int v);
    std::set<int> intersection(std::set<int> set_a, std::set<int> set_b);
    void BronKerbosch(std::set<int> R, std::set<int> P, std::set<int> X);

    std::set<int> _point_of_articulation();
    void _write_to_file_weight();
    void _kruskals_mst();
    int _size_from(int index,std::vector<std::vector<int>>& tmp);
    void _delete_from(int index,std::vector<std::vector<int>>& tmp);
    void _prufer_code();
    void _binary_code();












    void _dfs_for_bin_code(int vertices,std::vector<bool>& visited,std::queue<int>& ans);
    void _dfs(int vertices, std::vector<color>& visited, std::set<int>& clique);
    void _dfs_for_most(int vertices,std::vector<color>& visited,std::vector<int>& second,std::vector<int>& first,int parent,int& round,std::set<std::pair<int,int>>& ans);
    void _dfs_for_two_comp(int vertices,std::vector<color>& visited,std::set<std::pair<int,int>>& most,int& count_color,int color,std::vector<int>& color_of_el);
    void _dfs_for_point(int vertices,std::vector<color>& visited,std::vector<int>& second,std::vector<int>& first,int parent,int& round,std::set<int>& ans);
public:
    explicit graph(size_t size):count_of_vertices(size){
        adjacency_matrix.resize(size,std::vector<int>(size,INT_MAX));
        adg_bool.resize(size,std::vector<bool>(size, false));
        adjacency_list.resize(size);
        add_edge(1,31);add_edge(1,40);add_edge(1,33);add_edge(1,19);
        add_edge(2,16);add_edge(2,43);
        add_edge(3,46);add_edge(3,18);add_edge(3,5);
        add_edge(4,25);add_edge(4,23);add_edge(4,42);add_edge(4,20);add_edge(4,41);add_edge(4,12);add_edge(4,17);add_edge(4,45);
        add_edge(5,18);add_edge(5,38); add_edge(5,46);
        add_edge(6,35);add_edge(6,26);add_edge(6,24);add_edge(6,38);add_edge(6,47);
        add_edge(7,16);add_edge(7,27);add_edge(7,17);add_edge(7,32);
        add_edge(8,10);add_edge(8,40);add_edge(8,31);
        add_edge(9,37);add_edge(9,33);add_edge(9,19);add_edge(9,46);add_edge(9,40);
        add_edge(10,20);add_edge(10,40);add_edge(10,42);add_edge(10,31);
        add_edge(12,17);add_edge(12,35);add_edge(12,41);
        add_edge(13,17);
        add_edge(14,24);add_edge(14,38);
        add_edge(15,34);add_edge(15,38);add_edge(15,44);
        add_edge(16,43);add_edge(16,30);add_edge(16,23);add_edge(16,45);add_edge(16,17);add_edge(16,27);
        add_edge(17,27);add_edge(17,32);add_edge(17,35);add_edge(17,45);
        add_edge(18,46);add_edge(18,38);
        add_edge(20,42);add_edge(20,41);add_edge(20,40);add_edge(20,47);add_edge(20,37);
        add_edge(23,45);add_edge(23,42);add_edge(23,39);add_edge(23,49);
        add_edge(24,26);add_edge(24,38);
        add_edge(26,38);
        add_edge(35,26);add_edge(35,41);add_edge(35,47);add_edge(35,38);
        add_edge(40,31);add_edge(40,33);add_edge(40,37);
        add_edge(19,33);add_edge(19,46);
        add_edge(29,37);add_edge(29,47);
        add_edge(47,41);add_edge(47,38);add_edge(47,37);
        add_edge(34,38);add_edge(34,44);
        add_edge(22,48);
        add_edge(25,45);
        add_edge(36,43);

    };
    void add_edge(int first,int second);
    void print();
    void max_min_deg();
    void radix_deam_mid();
    void color_of_graph();
    void max_click_of_graph();
    void component();
    void component_ver();
    void road_for_csv();
    void ostv();
    void pint_edge();

};


#endif //DM_GRAPH_H
