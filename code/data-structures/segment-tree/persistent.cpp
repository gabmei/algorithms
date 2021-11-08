struct Node{
    int v = 0;
    Node *l = this, *r = this;
};
const int ms = 1e5;	
Node buffer[20 * ms]; // memory allocation for the nodes;
Node* root[ms + 1]; // root[i] - pointer to the root of version i
int cnt = 0;
Node* update(Node* on, int tl, int tr, int x, int val){
    Node* node = &buffer[cnt++];
    *node = *on;
    if(tl + 1 == tr){
        node->v = val;
        return node;
    }else{
        int mid = (tl + tr)/2;
        if(x<mid) node->l = update(on->l, tl, mid, x,val);
        else node->r = update(on->r, mid, tr, x, val);

        node->v = node->l->v + node->r->v;
        return node;
    }
}

int query(Node* on,int tl, int tr, int l, int r){
    if(tl>=r || tr<=l){
        return 0;
    }else if(tl>=l && tr<=r){
        return on->v;
    }else{
        int mid = (tl + tr)/2;
        return query(on->l, tl, mid, l, r) + query(on->r, mid, tr, l, r);
    }
}