class LRUCache {
public:
    class Node{
    public:
        int key;
        int val;
        Node* next_node;
        Node* prev_node;
        Node(int k, int v)
        {
            key = k;
            val = v;
        }
    };
    Node* head = new Node(-1,-1);
    Node* tail = new Node(-1,-1);
    int cap; 
    unordered_map <int,Node*> mpp;

    LRUCache(int capacity) 
    {
        cap = capacity;
        head->next_node = tail;
        tail->prev_node = head;
    }
    
    void delete_node(Node* del)
    {
        Node* del_prev = del->prev_node;
        Node* del_next = del->next_node;
        del_prev -> next_node = del_next;
        del_next -> prev_node = del_prev;
    }

    void add_node(Node* add)
    {
        Node* temp = head->next_node;
        add->next_node = temp;
        add->prev_node = head;
        head->next_node = add;
        temp->prev_node = add;
    }

    int get(int key_) 
    {
        if(mpp.find(key_)!=mpp.end())
        {
            Node* get_node = mpp[key_];
            int ans = get_node->val;
            mpp.erase(key_);
            delete_node(get_node);
            add_node(get_node);
            mpp[key_] = head->next_node;
            return ans;
        }
        return -1;
    }
    
    void put(int key_, int value) 
    {
        if(mpp.find(key_)!=mpp.end())
        {
            Node* put_node = mpp[key_];
            mpp.erase(key_);
            delete_node(put_node);
        }
        else if(mpp.size()==cap)
        {
            mpp.erase(tail->prev_node->key);
            delete_node(tail->prev_node); 
        }
        add_node(new Node(key_,value));
        mpp[key_] = head->next_node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
