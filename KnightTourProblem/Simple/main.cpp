#include <iostream>
#include <fstream>

using namespace std;

struct knightPosition {
   
    char x;
    char y;
    int level;
};

struct qNode {
    qNode* next;
    knightPosition* position;
    int level;
};

struct Queue {
    qNode* head;
    qNode* tail;
};

void enQueue(Queue*, qNode*);
qNode* deQueue(Queue*);
void buildQueue(Queue**);
void makeQNode(qNode**, knightPosition*, int level);
bool matchQnodes(qNode*, qNode*);

int main(int argc, const char * argv[]) {
    
    std::ios_base::sync_with_stdio(false);
    int xPos[8] = {-2,2,-1,1,-2,2,-1,1};
    int yPos[8] = {-1,-1,-2,-2,1,1,2,2};
    int T;
    cin>>T;
    while(T--) {
        bool visited[8][8];
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                visited[i][j] = false;
        char temp[2];
        cin>>temp;
        knightPosition* start = new knightPosition;
        start->x = temp[0];
        start->y = temp[1]-'0';
        cin>>temp;
        knightPosition* dest = new knightPosition;
        dest->x = temp[0];
        dest->y = temp[1]-'0';
        
        Queue* q;
        buildQueue(&q);
        
        qNode* first;
        makeQNode(&first, start, 0);
        qNode* last;
        makeQNode(&last, dest, 100);
        enQueue(q, first);
        visited[(int)first->position->x-97][(int)first->position->y-1] = true;
        if(matchQnodes(first, last))
            cout<<0<<"\n";
        else
        while(q->head) {
            qNode* curr = deQueue(q);
            for(int i=0;i<8;i++) {
                int hor = (int)curr->position->x + xPos[i];
                int ver = (int)curr->position->y + yPos[i];
                qNode* childNode;
                
                if(((hor-97)>=0) && ((ver-1)>=0) && ((hor-97)<8) && ((ver-1)<8) && !visited[hor-97][ver-1]){
                    if((hor>=(int)'a') && (hor<=(int)'h') && (ver>=1) && (ver<=8)) {
                        knightPosition* child = new knightPosition;
                        child->x = (char)hor;
                        child->y = (char)ver;
                    
                        makeQNode(&childNode, child, (curr->level+1));
                    
                        if(matchQnodes(childNode, last)) {
                        
                            cout<<childNode->level<<"\n";
                            q->head = NULL;
                            i=10;
                        }
                        else {
                            enQueue(q, childNode);
                            visited[hor-97][ver-1] = true;
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

bool matchQnodes(qNode* q1, qNode* q2) {
    
    if((q1->position->x == q2->position->x) && (q1->position->y == q2->position->y))
        return true;
    return false;
}

void enQueue(Queue* q, qNode* node) {
    
    if(!q->head) {
        
        q->head = node;
        q->tail = node;
    }
    
    else {
        q->tail->next = node;
        q->tail = node;
    }
    
    
}

qNode* deQueue(Queue* q) {
    
    if(!q->head) {
        return NULL;
    }
    
    qNode* link = q->head;
    q->head = q->head->next;
    link->next = NULL;
    if(!q->head) {
        q->tail = NULL;
    }
    return link;
}

void buildQueue(Queue** q) {
    
    (*q) = new Queue;
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

void makeQNode(qNode** q, knightPosition* start, int level) {
    
    (*q) = new qNode;
    (*q)->position = start;
    (*q)->next = NULL;
    (*q)->level = level;
}
