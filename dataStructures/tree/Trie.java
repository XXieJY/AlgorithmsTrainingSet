package dataStructures;

import java.util.Map;
import java.util.Hashtable;

// Trie��������Trie���ṹ��ζ��壬�Լ�Trie����ι��졣
// ������ô��Trie����SearchҪ������Ŀ�ж�
// ʱ�临�ӶȺ��ַ���������� O(m), m = string.leng();

class TrieNode {
    Hashtable<Character, TrieNode> children = new Hashtable<Character, TrieNode>();
    private boolean isLeaf;
 
    public TrieNode(){
        isLeaf = false;
    }
    public boolean isLeaf() {
    	return isLeaf;
    }
    public void setLeaf() {
    	isLeaf = true;
    }
}

public class Trie {
    private TrieNode root;
 
    public Trie() {
        root = new TrieNode();
    }
    // Inserts a word into the trie.
    public void insert(String word) {
        Hashtable<Character, TrieNode> children = root.children; //����children�൱��ָ�롣
 
        for(int i=0; i<word.length(); i++){
            char c = word.charAt(i);
 
            TrieNode t;
            if(children.containsKey(c)){
                    t = children.get(c);
            }else{
                t = new TrieNode();
                children.put(c, t);
            }
 
            children = t.children;
 
            //set leaf node
            if(i==word.length()-1)
                t.setLeaf();    
        }
    }
    // Returns if the word is in the trie.
    public boolean search(String word) {
        TrieNode t = searchNode(word);
 
        if(t != null && t.isLeaf()) //���� t != null �� t.isLeaf �ֱ�֤����word�����ܴ�����trie�е����
            return true;
        else
            return false;
    }
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    public boolean startsWith(String prefix) {
        if(searchNode(prefix) == null)  
            return false;
        else
            return true; 		//���� t != null ʱ �Ϳ��Ա�֤ Trie������word�и�����prefix
    }
    public TrieNode searchNode(String str){
        Map<Character, TrieNode> children = root.children; 
        TrieNode t = null;
        for(int i=0; i<str.length(); i++){
            char c = str.charAt(i);
            if(children.containsKey(c)){
                t = children.get(c);
                children = t.children;
            }else{
                return null;
            }
        }
 
        return t;
    }
}

