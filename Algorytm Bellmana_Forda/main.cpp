#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <exception>
#include <algorithm>

using namespace std;

typedef pair<int,int> Pair;



enum kolory {WHITE,YELLOW,BLACK};


class negative_cycle_in_graph_exception : exception
{   
public:

    string text = "Program nie jest w stanie wykonać działania z powodu ujemnego cyklu znajdującego się w podanym grafie! ";

};



class edge
{   

public:

    int starting_node,finishing_node,value;
    edge(int start,int finish,int val):starting_node(start),finishing_node(finish),value(val){}
    void print_content()const
    {
        cout << "(" << starting_node << "," << finishing_node << "," << value << ")" << endl;
    }
};


class Graph
{ 
public:

    vector<vector<Pair>> adjacent_list;
    vector<Pair> list_of_edges;
    vector<int> list_ofcolours;
    vector<edge> bellman_ford_edges;
    vector<int> topologic_order;
    
    vector<int> table_of_predecessors_bellman_ford;

    Graph(vector<edge> const& edges,int size)
    {
        adjacent_list.resize(size);
        list_ofcolours.resize(size);

        table_of_predecessors_bellman_ford.resize(size);
        

        for(int i=0;i<table_of_predecessors_bellman_ford.size();++i)
        {
           table_of_predecessors_bellman_ford[i] = -1;  /// inicjalizacja na brak poprzednikow
        }

        for(auto &edge:edges)
        {
            int beginning = edge.starting_node;
            int ending = edge.finishing_node;
            int weight = edge.value;

            adjacent_list[beginning].push_back(make_pair(ending,weight)); // wierzcholek i jego krawedzie
            list_of_edges.push_back(make_pair(beginning,ending));
            bellman_ford_edges.push_back(edge); // do Bellmana Forda przyda się
        }


    }

};


int* Bellman_Forda_algorithm(Graph& graph,int number_of_nodes)  // wlasciwy algorytm
{
    int counter_of_changes = 0;
     // 0,1,2,3 .. n -> indexy są wierzcholkami
   // int table_of_values_of_nodes[number_of_nodes]; // global table for Bellman Ford values paths
    int * table_of_values_of_nodes = new int[number_of_nodes];
    table_of_values_of_nodes[0] = 0;

    for(int i=1;i<number_of_nodes;i++)
    {   
        table_of_values_of_nodes[i] =  std::numeric_limits<int>::max();   // poczatkowe ustawienia
    }


    for(int i=0;i<number_of_nodes;i++)  // normalnie ma byc n-1 relaksacji, ale dzięki n- tej sprawdzimy czy zachodzi ujemny cykl (jesli zmieni sie jakas wartosc)
    {   
        counter_of_changes = 0;

        for(auto& current_edge : graph.bellman_ford_edges)
        {
            if(table_of_values_of_nodes[current_edge.starting_node] + current_edge.value < table_of_values_of_nodes[current_edge.finishing_node])
            {
                table_of_values_of_nodes[current_edge.finishing_node] = table_of_values_of_nodes[current_edge.starting_node] + current_edge.value;
                graph.table_of_predecessors_bellman_ford[current_edge.finishing_node] = current_edge.starting_node; // ustawienie na poprzednika
                counter_of_changes++;
            }
        }

        if(i == number_of_nodes - 1 && counter_of_changes > 0) // wylapanie ujemnego cyklu
        {
            delete [] table_of_values_of_nodes;  // zwolnienie pamieci przed zwijaniem stosu
            throw negative_cycle_in_graph_exception();
        }

    }

    cout << "Bellman - Ford Algorithm result: " << endl;

    for(int i=0;i<number_of_nodes;i++)
    {
        cout << "Shortest path to node " << i << " is equal " << table_of_values_of_nodes[i] << ", Predecessor (node): " << graph.table_of_predecessors_bellman_ford[i] << endl;
    }


    cout <<"\nShortest path from beginning node of the graph (0) to the end node of the graph" << endl;
    for(int i =number_of_nodes -1 ; i != 0;) // szukamy najkrotszej sciezki od konca od poczatku
    {   
        cout << i << " <- ";
        i = graph.table_of_predecessors_bellman_ford[i];
    }
    cout << "0" << endl;      // znalezlismy droge do poczatku wiec go jeszcze wypisujemy na koncu, bo juz nie spelnia warunku petli

    return table_of_values_of_nodes;

}



//////////////////////////////////////////////////////////////




void DFS_visit(Graph& graph,int size,int nr_node) //dodatek
{

    

    graph.list_ofcolours[nr_node] = YELLOW;

    for(auto& m : graph.adjacent_list[nr_node])
    {
       if(graph.list_ofcolours[m.first] == WHITE)
        {
            DFS_visit(graph,size,m.first);
        }
    }

    
    graph.list_ofcolours[nr_node] = BLACK;
    cout << "NR of node : " << nr_node << endl;
    graph.topologic_order.push_back(nr_node);

}




void DFS_graph(Graph& graph,int size) // dodatek
{

    cout << "-------- DFS SEARCH ---------" << endl;

    for(int i=0;i<size;i++)
    {
       graph.list_ofcolours[i] = WHITE;
    }

    for(int i=0;i<graph.list_ofcolours.size();i++)
    {
        if(graph.list_ofcolours[i] == WHITE)
        {
            DFS_visit(graph,size,i);
        }

    }


    cout << "------------ Topological order ----------" << endl;
    reverse(graph.topologic_order.begin(),graph.topologic_order.end());
    for(int i=0;i<graph.topologic_order.size();i++)
    {
        cout << "Node: " << graph.topologic_order[i] << endl;
    }
    
    cout << "\n";

}





void printGraph(Graph const& graph,int size)
{

    for(int i=0;i<size;i++)
    {
        for(Pair m : graph.adjacent_list[i])
        {
            cout << "("<< i << ", " << m.first << ", " << m.second << ") ";
        }
        cout << endl;
    }


}

void calculate_degree_rate(Graph const& graph,int size)   // dodatek
{

    for(int i=0; i<size ;i++)
    {   
        int counter_of_Degree = 0;
        for(Pair m : graph.list_of_edges)
        {
            if( i == m.first || i == m.second)
            {
                ++counter_of_Degree;
            }

        }
        cout << "Stopien " << i << " wierzcholka = " << counter_of_Degree << endl;
    }


}



/////////////////////////////////////////////////




int main()
{   


    int number_of_edges = 0;
    
    

    string name_of_file_to_read = "test2.txt";  /// <------------ tutaj wpisujemy nazwe pliku txt , wazne aby node'y byly numerowane od 0...n

    ifstream ins;
    ins.open(name_of_file_to_read); // nalezy upewnic sie czy odczytal dobrze
    
    if(!ins.good())
    {
        cout << "Cannot open your file.. Termination -> Make sure that everything is all right." << endl;
        exit(1);  // zakoncz program, bo jesli wczytanie nie udalo się to nic nie jestesmy w stanie zrobic
    }
    
    string data_from_file;

    vector<int> container_for_file_value;

    int size_of_graph;
    bool condition_on_size = true;

    while(!ins.eof())
     {  
        
        int value;
        ins >> value;
        if(condition_on_size){size_of_graph = value;condition_on_size = false;}
        else {container_for_file_value.push_back(value);}
     }
    container_for_file_value.pop_back(); // pierwsza liczba to ilosc node'ow
    //for(int i=0;i<container_for_file_value.size();i++){cout << container_for_file_value[i] << " ";}

    

    ins.close();


    

    vector<edge> edges;

    

    int number_of_iterations = container_for_file_value.size()/3;

    for(int i=0;i<number_of_iterations;i++)
    {
        //cout << container_for_file_value[0+3*i] << "," << container_for_file_value[1+3*i] << "," << container_for_file_value[2+3*i] << endl;
        int start_node = container_for_file_value[0+3*i];
        int end_node = container_for_file_value[1+3*i];
        int weight = container_for_file_value[2+3*i];
        edges.emplace_back(start_node,end_node,weight);
        ++number_of_edges;
    }

    //cout << "\n";

    cout << "Edges of Graph from input (start,end,value) " << endl;
    for(auto& element : edges)
    {
        element.print_content(); // aby sprawdzic czy mamy poprawnie zapisane krawedzie
    }


    Graph first_graph(edges,size_of_graph);
    //printGraph(first_graph,size_of_graph);
    //calculate_degree_rate(first_graph,size_of_graph);


    cout << "\n";

    DFS_graph(first_graph,size_of_graph);

    cout << "\n";

    int * result_of_function;
    
    try{
    result_of_function = Bellman_Forda_algorithm(first_graph,size_of_graph);
    delete [] result_of_function;
    }
    catch(negative_cycle_in_graph_exception excpt)
    {   
        cout << "\n";
        cout << excpt.text << endl;
        cout << "Algorytm Bellmana-Forda nie może posiadać ujemnego cyklu!" << endl;
    }


    


    return 0;
}

