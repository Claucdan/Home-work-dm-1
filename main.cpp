#include <iostream>
#include "graph.h"

int main() {
    int N=49;
    graph host(N);

    host.max_min_deg();
    std::cout<<"\n\n";
    host.radix_deam_mid();
    std::cout<<"\n\n";
    host.color_of_graph();
    std::cout<<"\n\n";
    host.max_click_of_graph();
    std::cout<<"\n\n";
    host.component();
    std::cout<<"\n\n";
    host.component_ver();
    std::cout<<"\n\n";
    host.ostv();
    return 0;
}

