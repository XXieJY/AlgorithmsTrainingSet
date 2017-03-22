/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jxie
 */
import java.util.*;


public class SkipList<T> {
    private SkipNode<T> head, tail;
    private int totalNodes = 0, listLevels = 0;
    private Random random;
    private static final double CONS_PROBABILITY = 0.5;
    
    public SkipList() {
        random = new Random();
        clear();
    }
    
    public boolean isEmpty() {
        return totalNodes == 0;
    }
    
    public int size() {
        return totalNodes;
    }
    
    public SkipNode<T> findNode(int key) {
        SkipNode<T> result = findInsertPos(key);
        if (key == result.getKey()) {
            return result;
        } else {
            return null;
        }
    }
    
    public void put(T value, int key) {
        SkipNode<T> preNode = findInsertPos(key);
        if (key == preNode.getKey()) {
            preNode.setValue(value);
            return;
        }
        SkipNode<T> newNode = new SkipNode(key, value);
        insertIntoLink(preNode, newNode);
        int currentLevel = 0;
        while (random.nextDouble() < SkipList.CONS_PROBABILITY) {
            if (currentLevel >= listLevels) {
                listLevels++;
                SkipNode<T> headTemp = new SkipNode<T>(SkipNode.HEAD_IDENTIFIER, null);
                SkipNode<T> tailTemp = new SkipNode<T>(SkipNode.TAIL_IDENTIFIER, null);
                horizontalLink(headTemp, tailTemp);
                verticalLink(headTemp, head);
                verticalLink(tailTemp, tail);
                head = headTemp;
                tail = tailTemp;
                headTemp = null;
                tailTemp = null;
            }
            while (preNode.up == null) {  // do not need to verify the left is null or not ?
                preNode = preNode.left;
            }
            preNode = preNode.up;
            SkipNode<T> fillNode = new SkipNode<T>(key, null);
            insertIntoLink(preNode, fillNode);
            verticalLink(fillNode, newNode);
            newNode = fillNode;
            fillNode = null;
            currentLevel++;
        }
        totalNodes++;
    }
    
    private SkipNode<T> findInsertPos(int key) {
        SkipNode<T> pointer = head;
        while (true) {
            while (pointer.right.key != SkipNode.TAIL_IDENTIFIER && pointer.key <= key) {
                pointer = pointer.right;
            }
            if (pointer.down != null) {
                pointer = pointer.down;
            } else {
                break;
            }
        }
        return pointer;
    }
    
    private void clear() {
        head = new SkipNode<T>(SkipNode.HEAD_IDENTIFIER, null);
        tail = new SkipNode<T>(SkipNode.TAIL_IDENTIFIER, null);
        horizontalLink(head, tail);
        listLevels = 0;
        totalNodes = 0;
    }
    
    
    
    private <T> void horizontalLink(SkipNode<T> leftNode, SkipNode<T> rightNode) {
        leftNode.right = rightNode;
        rightNode.left = leftNode;
    }
    
    private <T> void verticalLink(SkipNode<T> upNode, SkipNode<T> downNode) {
        upNode.down = downNode;
        downNode.up = upNode;
    }
    
    private <T> void insertIntoLink(SkipNode<T> preNode, SkipNode<T> newNode) {
        newNode.right = preNode.right;
        preNode.right.left = newNode;
        newNode.left = preNode;
        preNode.right = newNode;
    }
    
    
    
    class SkipNode <T> {
        private int key;
        private T value;
        private SkipNode<T> up, down, left, right;
        private static final int HEAD_IDENTIFIER = Integer.MIN_VALUE;
        private static final int TAIL_IDENTIFIER = Integer.MAX_VALUE;
        
        public SkipNode() {};
        
        public SkipNode(int key, T value) {
            this.key = key;
            this.value = value;
        }
        
        public int getKey() {
            return this.key;
        }
        
        public T getValue() {
            return this.value;
        }
        
        public void setKey(int key) {
            // needs to resize whole skip List
        }
        
        public void setValue(T value) {
            this.value = value;
        }
        
        public boolean equals(Object o) {
            if (this == o) {
                return true;
            } else if (o == null) {
                return false;
            } else if (!(o instanceof SkipNode)) {
                return false;
            } else {
                SkipNode<T> ent;
                try {
                    ent = (SkipNode<T>) o;
                } catch (ClassCastException ex) {
                    return false;
                }
                return (ent.getKey() == this.key) && (ent.getValue() == this.value);
            }
        }
        
        @Override
        public String toString() {
            return " key-value " + this.key + " - " + this.value;
        }
    }
}
