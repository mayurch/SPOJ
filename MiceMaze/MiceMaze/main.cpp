//
//  main.cpp
//  MiceMaze
//
//  Created by Mayur Cherukuri on 10/4/15.
//  Copyright © 2015 Mayur Cherukuri. All rights reserved.
//

#include <iostream>
#include <climits>

struct Node {
    Node* next;
    int val;
    int time;
};

struct heapNode {
    int val;
    int dist;
};

struct minHeap {
    heapNode* v;
    int size;
    int* pos;
};

void swap(minHeap*,int,int);
heapNode extractMin(minHeap*);
void minHeapify(minHeap*,int);
void updateDist(minHeap*,int,int,int);

using namespace std;
int main(int argc, const char * argv[]) {
    
    std::ios_base::sync_with_stdio(false);
    int N,E,T,M,count = 0;
    cin>>N>>E>>T>>M;
    E-=1;
    Node** conns = new Node*[N];
    bool* pathFound = new bool[N];
    for(int i=0;i<N;i++)
        conns[i] = NULL;
    for(int i=0;i<M;i++) {
        int a,b,time;
        cin>>a>>b>>time;
        a-=1;
        b-=1;
        if(!conns[a]){
            conns[a] = new Node;
            conns[a]->val = b;
            conns[a]->time = time;
            conns[a]->next = NULL;
        }
        else {
            Node* curr = new Node;
            curr->val = b;
            curr->time = time;
            curr->next = conns[a]->next;
            conns[a]->next = curr;
        }
    }
    
    for(int i=0;i<N;i++) {
        
        if(i==E)
            count++;
        else {
            minHeap* heap = new minHeap;
            heap->v = new heapNode[N];
            heap->size = N;
            heap->pos = new int[N];
        
            for(int j=0;j<N;j++) {
            
                heap->v[j].val = j;
                heap->v[j].dist = INT_MAX;
                pathFound[j] = false;
                heap->pos[j]=j;
            }
        
            heap->v[i].dist = 0;
            swap(heap,0,i);
    
            heapNode min = extractMin(heap);
            while(min.dist<=T && min.val!=E)
            {
                pathFound[min.val] = true;
                Node* curr = conns[min.val];
                while(curr && !pathFound[curr->val]) {
                    updateDist(heap, curr->val, min.dist, curr->time);
                    curr = curr->next;
                }
                if(heap->size>0)
                    min = extractMin(heap);
            }
            if(min.val==E && (min.dist)<=T){
                count++;
            }
            
        }
    }
    cout<<count;
}

void swap(minHeap* heap, int a, int b) {
    
    heapNode temp = heap->v[a];
    heap->pos[heap->v[a].val] = b;
    heap->pos[heap->v[b].val] = a;
    heap->v[a] = heap->v[b];
    heap->v[b] = temp;
}

heapNode extractMin(minHeap* heap) {
    
    heapNode temp = heap->v[0];
    swap(heap,0,heap->size-1);
    heap->size = heap->size - 1;
    minHeapify(heap,0);
    return temp;
}

void minHeapify(minHeap* heap, int i) {
    
    int smallest = i;
    
    int l = 2*i+1;
    int r = 2*i+2;
    
    if(l<(heap->size) && (heap->v[i].dist>heap->v[l].dist)) {
        
        swap(heap,i,l);
        smallest = l;
    }
    if(r<(heap->size) && (heap->v[smallest].dist>heap->v[r].dist)) {
        
        swap(heap, smallest, r);
        smallest = r;
    }
    
    if(smallest != i)
        minHeapify(heap, smallest);
}

void updateDist(minHeap* heap, int val, int dist, int time) {
    
    int ind = heap->pos[val];
    if(heap->v[ind].dist>(dist+time)) {
        heap->v[ind].dist = (dist+time);
    
        int i= ind;
    
        while(i && (heap->v[i].dist<heap->v[(i-1)/2].dist)) {
        
            swap(heap,i,(i-1)/2);
            i = (i-1)/2;
        }
    }
}