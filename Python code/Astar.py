#..................................A* Algorithm...........................
#This algorithm helps to find the shortest path between source and destination in a graph
#Here the graph is going to work for adjacency list given by the user 
#The user has to provide an heuristic value an estimatesd value for each node 
'''Heuristic value is nothing but estimated amount of distance 
#to be covered from the current node to the destination'''
#The user Has to provide the number of nodes
#Edges along with their edge weights
#It can be applied to both directed and undirected grpahs.This code going to help for an undirected graph
#The user has to provide source and destination nodes also
class Node:
    def __init__(self,parent=None,h=0 ):
        self.parent=parent 
        self.h=h   
        self.f = float('inf')
#Based on the given adjacency list given we are going to implement the A star algorithm
def AStar(source, destination,Graph,Edges):
    if(source==destination):
        print("Already reached the destination")
        return
    src_flag=False
    dest_flag=False
    for node in Graph:
        if node==source:
            src_flag=True
        if node==destination:
            dest_flag=True
    if(src_flag==False):
        print(f"{source}")
        print("Source node is not present the given graph")
        return
    if(dest_flag==False):
        print("Destination node is not present the given graph")
        return
    open_list=set()
    closed_list=set()
    open_list.add(source)
    g={}
    parents={}
    g[source]=0
    parents[source]=source
    while len(open_list)>0:
        curr_node=None
        for V in open_list:
            if curr_node==None or g[curr_node]+Graph[curr_node]>Graph[V]+g[V]:
                curr_node=V
        if curr_node==destination or len(Edges[curr_node])==0:
            pass
        for neibhour in Edges[curr_node]:
            if (neibhour[0] not in open_list and neibhour[0] not in closed_list):
                open_list.add(neibhour[0])
                parents[neibhour[0]]=curr_node
                g[neibhour[0]]=g[curr_node]+neibhour[1]
            else:
                if g[neibhour[0]]>g[curr_node]+neibhour[1]:
                    g[neibhour[0]]=g[curr_node]+neibhour[1]
                    parents[neibhour[0]]=curr_node
                    if neibhour[0] in closed_list:
                        closed_list.remove(neibhour[0])
                        open_list.add(neibhour[0])
        if curr_node==None:
            print("Path does not exist")
            return None
        if curr_node==destination:
            path=[]
            while parents[curr_node]!=curr_node:
                path.append(curr_node)
                curr_node=parents[curr_node]
            path.append(source)
            path.reverse()
            return path
        open_list.remove(curr_node)
        closed_list.add(curr_node)
def main():
        file_name=input("Enter the txt file name:");
        fp=open(file_name,"r");
        num_nodes=int(fp.readline());
        Graph={}
        for i in range(num_nodes):
            string=fp.readline()
            string=string.split()
            node_name=string[0]
            heuristic_value=int(string[1])
            Graph[node_name]=heuristic_value
        Edges={}
        for node in Graph:
            Edges[node]=[]
            num_adj_nodes=fp.readline();
            num_adj_nodes=int(num_adj_nodes);
            for i in range(num_adj_nodes):
                string=fp.readline()
                string=string.split()
                adj_node=string[0]
                edge_weight=int(string[1])
                neib_list=Edges[node]
                new_tuple=(adj_node,edge_weight)
                neib_list.append(new_tuple)
                Edges[node]=neib_list
        string=fp.readline();
        string=string.split();
        source=string[0];
        destination=string[1];
        path=AStar(source,destination,Graph,Edges)
        if path==None:
            print("Path does not Exist")
            return
        else:
            print("Required path is:")
        for i in path:
            print(f'{i}->',end='')
    #Now the input is absolutely ready to use 
if __name__ == "__main__":
    main()
