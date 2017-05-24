package dataStructures;

import java.util.Map;
import java.util.Hashtable;

// Trie树核心是Trie树结构如何定义，以及Trie树如何构造。
// 具体怎么在Trie树中Search要根据题目判断
// 时间复杂度和字符串长度相关 O(m), m = string.leng();

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
        Hashtable<Character, TrieNode> children = root.children; //这里children相当于指针。
 
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
 
        if(t != null && t.isLeaf()) //这里 t != null 和 t.isLeaf 分别保证两种word不可能存在于trie中的情况
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
            return true; 		//这里 t != null 时 就可以保证 Trie树中有word有给定的prefix
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

