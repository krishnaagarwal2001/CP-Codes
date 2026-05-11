class Node {
	public:
		char ch;
		bool isTerminal;
		unordered_map<char, Node*> children;
		Node(char ch) {
			this->ch = ch;
			this->isTerminal = false;
		}
};
 
class Trie {
	public:
	Node *root;
 
	Trie() {
		this->root = new Node('\0');
	}
 
	void insert(string str) {
		Node *curNode = root;
		for(int i = 0; i < str.size(); i++) {
			char ch = str[i];
			if(curNode->children.find(ch) == curNode->children.end()) {
				curNode->children[ch] = new Node(ch);
			} 
			curNode = curNode->children[ch];
		}
		curNode->isTerminal = true;
	}

	bool search(string str)
	{
		Node *curNode = root;

		for(int i = 0; i < str.size(); i++) {
			char ch = str[i];

			if(curNode->children.find(ch) == curNode->children.end()) {
				return false;
			}

			curNode = curNode->children[ch];
		}

		return curNode->isTerminal;
	}

	void dfs(Node *root,string pre,string op)
	{
		if(root==NULL) return;
		if(root->isTerminal)cout<<pre+op<<endl;

		for(auto c:root->children)
			dfs(c.second,pre,op+c.first);

	}

	void print_strings_with_prefix(string pre)
	{
		Node *temp=this->root;
		for(int i = 0; i < str.size(); i++) {
			char ch = str[i];
			if(temp->children.count(ch)) {
				
				temp = temp->children[ch];
			} else {
				return;
			}
		}
		dfs(temp,pre,"");
	}
};
 
