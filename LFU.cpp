// least frequently used
class Node{
public:
    int key;
    int val;
    int count;
    Node* next;
    Node* prev;
    Node(int k, int v)
    {
        key = k;
        val = v;
        count =1;
    }
};

class List{
public:
    Node* head;
    Node* tail;
    int list_length;
    List()
    {
    head = new Node(-1,-1);
    tail = new Node(-1,-1);
    list_length = 0;
    head->next = tail;
    tail->prev = head;
    }

    void addfront(Node* node)
    {
        Node* temp = head->next;
        node->next = temp;
        node->prev = head;
        head->next = node;
        temp->prev = node;
        list_length++;
    }

    void deletenode(Node* node)
    {
        Node* node_prev = node->prev;
        Node* node_next = node->next;
        node_prev->next = node_next;
        node_next->prev = node_prev;
        list_length--;
    }
};

class LFUCache {
public:

    map<int,Node*> keynode;
    map<int,List*> freqlist;
    int minimum_frequency;
    int maximum_cache_size;
    int current_cache_size;

    LFUCache(int capacity) 
    {
        minimum_frequency = 0;
        maximum_cache_size = capacity;
        current_cache_size = 0;
    }

    void updatefreqlistmap(Node* node)
    {
        keynode.erase(node->key);
        freqlist[node->count]->deletenode(node);
        if(minimum_frequency == node->count && freqlist[node->count]->list_length == 0)
        {
            minimum_frequency++;
        }

        List* nextHigherFreqlist = new List();
        if(freqlist.find(node->count+1) != freqlist.end())
        {
            nextHigherFreqlist = freqlist[node->count+1];
        }
        node->count += 1;
        nextHigherFreqlist->addfront(node);
        freqlist[node->count] = nextHigherFreqlist;
        // keynode[node->key] = nextHigherFreqlist->head->next;
        keynode[node->key] = node;
    }
    
    int get(int key) 
    {
        if(keynode.find(key)!=keynode.end())
        {
            Node* node = keynode[key];
            int ans = node->val;
            updatefreqlistmap(node);
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) 
    {
        if(maximum_cache_size==0) return;
        if(keynode.find(key)!= keynode.end())
        {
            Node* node= keynode[key];
            node->val = value;
            updatefreqlistmap(node);
        }  
        else{
            if(current_cache_size==maximum_cache_size)
            {
                List* removal = freqlist[minimum_frequency];
                keynode.erase(removal->tail->prev->key);
                removal->deletenode(removal->tail->prev);
                current_cache_size--;
            }
            current_cache_size++;
            minimum_frequency = 1;
            List* adding = new List();
            if(freqlist.find(1)!=freqlist.end())
            {
                adding = freqlist[minimum_frequency];
            }
            Node* node = new Node(key,value);
            adding->addfront(node);
            freqlist[minimum_frequency] = adding;
            keynode[key] = node;
        }  
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
