
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
using namespace std;
int n, p, depth1, vt, counter=0;
float time1;

struct node{
    int **x,v,depth, alpha, beta, value,yc,xc, vc;
    bool flag,flag1;
    struct node * pback;
    struct node * next;
    struct node * bback;
};

struct node1{
    int x,y;
    struct node1 * next;
};

typedef struct node *nodeptr;
typedef struct node1 *nodeptr1;

nodeptr child=NULL;
nodeptr keep,finall,ans=NULL;

struct node *getnode(void){
    struct node *root;
    root=(struct node *)malloc(sizeof(struct node));
    return root;
}
struct node1 *getnode1(void){
    struct node1 *root;
    root=(struct node1 *)malloc(sizeof(struct node1));
    return root;
}

void gravity(int **temp2){
    int k=0;
    for(int j=n-1;j>=0;j--){
        for(int i=n-1;i>=0;i--){
            if(temp2[i][j]==-1){
                k=i-1;
                while(k>0&&temp2[k][j]==-1){
                    k--;
                }
                if(k>=0){
                    int vt=temp2[k][j];
                    temp2[i][j]=vt;
                    temp2[k][j]=-1;
                }
            }
        }
    }
}

void eval(int **board){

    int **temp=new int*[n];
    for(int i=0;i<n;i++)
        temp[i]=new int[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            temp[i][j]=board[i][j];
        }
    }
    nodeptr parent=child;
    nodeptr pparent=child;
    nodeptr sort1;
    int vvv=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp[i][j]!=-1){
                    vvv++;
                nodeptr nchild=getnode();
                nchild->x=new int*[n];
                for(int k=0;k<n;k++)
                    nchild->x[k]=new int[n];
                for(int k=0;k<n;k++){
                    for(int m=0;m<n;m++){
                        nchild->x[k][m]=board[k][m];
                    }
                }

                nchild->v=1;
                nchild->xc=i;
                nchild->yc=j;
                if(parent!=NULL)
                    nchild->depth=parent->depth+1;
                else
                    nchild->depth=1;
                if(nchild->depth%2==0)
                    nchild->value=-32768;
                else
                    nchild->value=32767;
                nchild->alpha=-32768;
                nchild->beta=32767;
                if(nchild->depth==depth1)
                    nchild->flag=true;
                else
                    nchild->flag=false;
                nchild->next=NULL;
                nchild->pback=parent;

                if(child==NULL&&vvv==1){
                    child=nchild;
                    keep=child;
                }
                else if(vvv==1){
                    while(child->next!=NULL){
                        child=child->next;
                    }
                    child->next=nchild;
                }

                //nchild->bback=child;
                nchild->x[i][j]=-1;
                nodeptr1 child1=getnode1();
                child1->x=i;
                child1->y=j;
                child1->next=NULL;
                int v1=temp[i][j];//cout<<v1<<endl;
                temp[i][j]=-1;
                do{
                nodeptr1 tt=child1;
                if(child1->y-1>=0&&temp[child1->x][child1->y-1]==v1){//cout<<"here1"<<" "<<child1->x<<" "<<child1->y<<endl;
                    //cout<<"hey1"<<" ";
                    nodeptr1 child11=getnode1();
                    child11->x=child1->x;
                    child11->y=child1->y-1;
                    child11->next=NULL;
                    while(tt->next!=NULL){
                        tt=tt->next;
                    }
                    tt->next=child11;
                    temp[child11->x][child11->y]=-1;
                    nchild->v=nchild->v+1;
                nchild->x[child11->x][child11->y]=-1;

                }
                if(child1->y+1<n&&temp[child1->x][child1->y+1]==v1){//cout<<"here2"<<" "<<child1->x<<" "<<child1->y<<endl;
                    //cout<<"hey1"<<" ";
                    nodeptr1 child11=getnode1();
                    child11->x=child1->x;
                    child11->y=child1->y+1;
                    child11->next=NULL;
                    while(tt->next!=NULL){
                        tt=tt->next;
                    }
                    tt->next=child11;
                    temp[child11->x][child11->y]=-1;
                    nchild->v=nchild->v+1;
                nchild->x[child11->x][child11->y]=-1;

                }
                if(child1->x-1>=0&&temp[child1->x-1][child1->y]==v1){//cout<<"here3"<<" "<<child1->x<<" "<<child1->y<<endl;
                    //cout<<"hey2"<<" ";
                    nodeptr1 child11=getnode1();
                    child11->x=child1->x-1;
                    child11->y=child1->y;
                    child11->next=NULL;
                    while(tt->next!=NULL){
                        tt=tt->next;
                    }
                    tt->next=child11;
                    temp[child11->x][child11->y]=-1;
                    nchild->v=nchild->v+1;
                nchild->x[child11->x][child11->y]=-1;

                }
                if(child1->x+1<n&&temp[child1->x+1][child1->y]==v1){//cout<<"here4"<<" "<<child1->x<<" "<<child1->y<<endl;
                    //cout<<"hey2"<<" ";
                    nodeptr1 child11=getnode1();
                    child11->x=child1->x+1;
                    child11->y=child1->y;
                    child11->next=NULL;
                    while(tt->next!=NULL){
                        tt=tt->next;
                    }
                    tt->next=child11;
                    temp[child11->x][child11->y]=-1;
                    nchild->v=nchild->v+1;
                nchild->x[child11->x][child11->y]=-1;

                }
                //cout<<child1->x<<" "<<child1->y<<endl;
                //temp[child1->x][child1->y]=-1;
                //nchild->v=nchild->v+1;
                //nchild->x[child1->x][child1->y]=-1;
                child1=child1->next;
                /*for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        if(child->x[i][j]!=-1)
                            cout<<child->x[i][j]<<"  ";
                        else
                            cout<<child->x[i][j]<<" ";
                    }cout<<endl;
                }*/
                //nchild->v=nchild->v+1;


                }while(child1!=NULL);
              /*  for(int i1=0;i1<n;i1++){
        for(int j1=0;j1<n;j1++){
            if(nchild->x[i1][j1]!=-1)
                cout<<nchild->x[i1][j1]<<"  ";
            else
                cout<<nchild->x[i1][j1]<<" ";
        }cout<<endl;
    }cout<<endl;
    sleep(4);*/
                if(nchild->depth%2!=0){
                    nchild->vc=parent->vc+nchild->v;
                    if(nchild->vc>=vt/2){
                        nchild->flag=true;//cout<<"prune"<<endl;
                        //counter++;
                    }
                }
                else{
                    nchild->vc=parent->vc;
                }
                int t=0;
                if(vvv==1){
                    pparent=pparent->next;
                    sort1=pparent;
                    pparent->bback=child;
                }
                else{
                    do{
                        if(pparent->v*pparent->v>=nchild->v*nchild->v){//cout<<"hello"<<" "<<vvv<<endl;
                            pparent->bback->next=nchild;
                            nchild->bback=pparent->bback;
                            nchild->next=pparent;
                            pparent->bback=nchild;
                            t=1;
                            break;
                        }
                        if(t==1)
                            break;
                        if(pparent->next!=NULL)
                            pparent=pparent->next;
                        //cout<<"fvk"<<vvv;
                    }while(pparent->next!=NULL);
                    if(t==0){
                        pparent->next=nchild;
                        nchild->bback=pparent;
                    }
                }
                gravity(nchild->x);
                pparent=sort1;
                //child=child->next;
            }
        }
    }
    /*cout<<"bye";
    while(child->next!=NULL){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
            }cout<<endl;
        }cout<<endl;
        sleep(2);
        child=child->next;
    }
    while(child->bback!=NULL){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
            }cout<<endl;
        }cout<<endl;
        sleep(2);
        child=child->bback;
    }*/
    while(child->next!=NULL){
        /*for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
            }cout<<endl;
        }cout<<endl;
        sleep(2);*/
        child=child->next;
    }
    //cout<<"bye";
}

void create(){
    do{//cout<<"start";
    int **temp1=new int*[n];//cout<<"v1";
    for(int i=0;i<n;i++)
        temp1[i]=new int[n];
    //cout<<"v";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            temp1[i][j]=child->x[i][j];
        }
    }//cout<<"regre";
    int c=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                c++;
        }
    }//cout<<"wvd";
    if(child->depth<depth1&&c!=0&&child->flag==false){//cout<<"here";
            eval(temp1);
           /* for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
        }cout<<endl;
    }cout<<endl<<"fbs"<<endl;*/
    }

    c=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                c++;
        }
    }
    if(c==0)
        child->flag=true;
    if(child->flag==true&&(child->value==-32768||child->value==32767)){//cout<<"here";
        child->value=child->v*child->v;
        if(child->depth%2==0)
            child->alpha=child->value;
        else
            child->beta=child->value;
        //child->flag1=false;
        //cout<<endl<<child->alpha<<" "<<child->beta<<endl;
    }

    if(child->pback!=NULL&&(child->pback->alpha!=-32768||child->pback->beta!=32767)&&child->flag==false){//cout<<"endsnjd";
        child->alpha=child->pback->alpha;
        child->beta=child->pback->beta;
        /*if(child->alpha>=child->beta&&child->pback!=NULL){
            child->pback->next=NULL;
            child->pback->flag=true;
            child=child->next;
        }*/ //remove dis comment
    }
    /*if(child->pback!=NULL){
        if(child->depth%2==0){
            if(child->pback->beta>child->alpha&&child->flag==true){//cout<<"max"<<endl;
                child->pback->beta=child->alpha;
                child->pback->value=child->value;
                child->flag1=true;
                if(child->depth==1&&child->flag1==true){
                    ans=child;
                    }
            }
            if(child->pback->pback!=NULL&&child->pback->beta<=child->alpha&&child->flag==true){//cout<<"prune1"<<endl;
                //child->pback->pback->next=NULL;
                child->pback->pback->flag=true;
                child=child->pback->pback;//do multiline comment
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
            }
            cout<<"parent value"<<child->pback->alpha<<" "<<child->pback->beta<<endl;
        }
        else{
            if(child->pback->alpha<=child->beta&&child->flag==true){//cout<<"min"<<endl;
                child->pback->alpha=child->beta;
                child->pback->value=child->value;
                child->flag1=true;


            }
            if(child->pback->pback!=NULL&&child->pback->alpha>=child->beta&&child->flag==true){//cout<<"prune2"<<endl;
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
            }
            cout<<"parent value"<<child->pback->alpha<<" "<<child->pback->beta<<endl;
        }
    }*/

    if(child->pback!=NULL){
        if(child->depth%2==0){
            /*if(child->pback!=NULL&&child->pback->value<child->alpha&&child->flag==true){//cout<<"prune1"<<endl;
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
            }*/

            if(child->flag==true&&child->pback!=NULL){//cout<<"max"<<endl;
                int vv=child->alpha+(child->pback->v*child->pback->v);
                if(child->pback->value>vv){
                    child->pback->value=vv;
                    child->pback->beta=vv;
                    child->alpha=vv;
                }
            //}
             if(child->pback!=NULL&&child->pback->beta<=child->pback->alpha&&child->flag==true){//cout<<"prune1"<<endl;
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
                //counter++;
                /*child->next=NULL;
                child->flag=true;
                child=child->bback;*/
            }}
            //cout<<"parent value1"<<child->pback->alpha<<" "<<child->pback->beta<<" "<<child->pback->value<<endl;
        }
        else{
             /*if(child->pback!=NULL&&child->pback->value>child->beta&&child->flag==true){//cout<<"prune2"<<" "<<child->pback->value<<endl;
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
                }*/

            if(child->flag==true&&child->pback!=NULL){//cout<<"min"<<endl;

                int vv=child->beta-(child->pback->v*child->pback->v);
                if(child->pback->value<vv){//cout<<vv;
                    child->pback->value=vv;
                    child->pback->alpha=vv;
                    child->beta=vv;
                    if(child->depth==1){
                        ans=child;
                    }
                }
            //}

            if(child->pback!=NULL&&child->pback->alpha>=child->pback->beta&&child->flag==true){//cout<<"prune2"<<endl;
                child->pback->next=NULL;
                child->pback->flag=true;
                child=child->pback;
                //counter++;
                /*child->next=NULL;
                child->flag=true;
                child=child->bback;*/
                }}
            //cout<<"parent value2"<<child->pback->alpha<<" "<<child->pback->beta<<" "<<child->pback->value<<endl;
        }
    }

    if(child->pback==NULL){
        child=NULL;
    }
    //cout<<"nsrwn";
    if(child!=NULL&&child->pback==child->bback&&child->bback!=NULL&&child->flag==true){//cout<<"sbsn";
        child->pback->flag=true;
        if(child->pback->depth%2==0)
            child->pback->alpha=child->pback->value;
        else
            child->pback->beta=child->pback->value;
        child=child->bback;
        child->next=NULL;//cout<<"back"<<endl;
        if(child->pback!=NULL&&(child->pback->alpha!=-32768||child->pback->beta!=32767)&&child->flag==false){//cout<<"endsnjd1";
        child->beta=child->pback->beta;
        child->alpha=child->pback->alpha;
        /*if(child->alpha>=child->beta&&child->pback!=NULL){
            child->pback->next=NULL;
            child->pback->flag=true;
            child=child->next;
        }*/
    }
    }
    else if(child!=NULL&&child->bback!=NULL&&child->flag==true){//cout<<"back11"<<endl;
        child=child->bback;//cout<<"bfsn";//<<" "<<child->next;
        child->next=NULL;//cout<<"back1"<<endl;
        if(child->pback!=NULL&&(child->pback->alpha!=-32768||child->pback->beta!=32767)&&child->flag==false){//cout<<"endsnjd2";
        child->beta=child->pback->beta;
        child->alpha=child->pback->alpha;
        /*if(child->alpha>=child->beta&&child->pback!=NULL){
            child->pback->next=NULL;
            child->pback->flag=true;
            child=child->next;
        }*/
    }
    }//cout<<"ukg";
   /* if(child!=NULL&&child->pback!=NULL&&(child->pback->alpha!=-32768||child->pback->beta!=32767)&&child->flag==false){//cout<<"endsnjd"<<endl;
        child->alpha=child->pback->alpha;
        child->beta=child->pback->beta;
    }*/

   /*if(child!=NULL){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    cout<<child->alpha<<" "<<child->beta<<" "<<child->value<<endl;
    sleep(2);
    }//cout<<"New child"<<endl<<endl;*/
    //counter++;
    }while(child!=NULL);//child!=NULL;

}

int main()
{
    time_t now,now1;
    ifstream inFile;
    ofstream outFile;
    //inFile.open("input.txt");
    outFile.open("calibration.txt");
    /*if(!inFile){
        cerr<<"Unable to open input file";
        exit(1);
    }*/
    for(int l=0;l<26;l++){//cout<<l;
    //n=l+1;
    //counter=0;
    struct timeval start, stop;
    //gettimeofday(&start,NULL);
    time(&now);
    inFile.open("input.txt");
    //outFile.open("calibration.txt");
    if(!inFile){
        cerr<<"Unable to open input file";
        exit(1);
    }
    int x,temp=0;float y;
    while(temp<3){
            if(temp==0){inFile>>x;n=x;}
            if(temp==1){inFile>>x;p=x;}
            if(temp==2){inFile>>y;time1=y;}
            temp++;
    }
    n=l+1;
    inFile.clear();
    inFile.seekg(0,ios::beg);
    int *board[n];
    for(int i=0;i<n;i++)
        board[i]=new int[n];
    vt=0;
    temp=0;string s;
    while(temp<4){
        if(temp>2){
            for(int i=0;i<n;i++){
                inFile>>s;
                for(int j=0;j<n;j++){
                    if(s.at(j)!='*'){
                        board[i][j]=s.at(j)-48;
                        vt++;
                    }
                    else
                        board[i][j]=-1;
                }
            }
            temp++;
        }
        else{
            inFile>>s;
            temp++;
        }
    }
    inFile.close();
   /* finall=getnode();
    child=finall;
    finall->alpha=-32768;
    finall->beta=32767;
    finall->pback=NULL;
    finall->bback=NULL;
    finall->next=NULL;
    finall->value=-32767;
    finall->depth=0;
    finall->flag=false;
    finall->v=0;
    finall->x=new int*[n];
    for(int k=0;k<n;k++)
        finall->x[k]=new int[n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            finall->x[i][j]=board[i][j];
        }
    }*/

    //eval(board);
   /* for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
        }cout<<endl;
    }*/
   /* gravity(child->x);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(child->x[i][j]!=-1)
                cout<<child->x[i][j]<<"  ";
            else
                cout<<child->x[i][j]<<" ";
        }cout<<endl;
    }*/
    //ans=child;
    //for(int ll=0;ll<2;ll++){//cout<<ll<<"gw";
     finall=getnode();
    child=finall;
    finall->alpha=-32768;
    finall->beta=32767;
    finall->pback=NULL;
    finall->bback=NULL;
    finall->next=NULL;
    finall->value=-32767;
    finall->depth=0;
    finall->flag=false;
    finall->v=0;
    finall->x=new int*[n];
    for(int k=0;k<n;k++)
        finall->x[k]=new int[n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            finall->x[i][j]=board[i][j];
        }
    }
     child=finall;ans=child;keep=NULL;
     gettimeofday(&start,NULL);
     depth1=1;
    create();
    time(&now1);
    gettimeofday(&stop,NULL);
    outFile<<(double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    //outFile<<stop.tv_usec-start.tv_usec;
    //outFile<<(float)difftime(now1,now);
     //cout<<l<<ll;
    outFile<<endl;//}
     //outFile.close();    //cout<<counter<<endl;
    /*while(keep!=NULL){
        cout<<keep->x<<" "<<keep->y<<" "<<keep->v<<endl;

        keep=keep->next;
    }*/
    /*char cc=ans->yc+65;
    //cout<<ans->xc<<cc;
    outFile<<cc<<ans->xc+1<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(ans->x[i][j]==-1)
                outFile<<"*";
            else
                outFile<<ans->x[i][j];
        }outFile<<endl;
    }
    cout<<counter;*/
    }
 outFile.close();
 return 0;
}
