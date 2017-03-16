/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jxie
 * @param <T> the type held in this collection 
 * @version 1.0
 * @description 
 * -----------------------------------------------------------------------------
 * +  API public class SinglelyLinkedList<T>                                       +
 * -----------------------------------------------------------------------------
 *              
 *        public            SinglelyLinkedList()     initialize the default SinglelyLinkedList
 *        public            SinglelyLinkedList(Collection<? extends T> c)    initialize the SinglelyLinkedList with given collection's elements
 *        public boolean    addFirst(T element)                              add the element into the head of SinglelyLinkedList
 *        public boolean    addLast(T element)                               add the element into the tail of SinglelyLinkedList
 *        public void       add(int index, T element)                        add the element into the specified position of SinglelyLinkedList
 *        public boolean    addAll(Collection<? extends T> c)                add collection of elements into the SinglelyLinkedList
 *        public boolean    addAll(int index, Collection<? extends T> c)     add collection of elements into the specified position of SinglelyLinkedList
 *        public void       delete(int index)                                delete the element of SinglelyLinkedList which at specified position
 *        public T          getFirst()                                       get the first element of SinglelyLinkedList
 *        public T          getLast()                                        get the last element of SinglelyLinkedList
 *        public T          get(int index)                                   get the element of SinglelyLinkedList which at specified postion
 *        public void       set(int index, T element)                        update the value of element of SinglelyLinkedList which at specified position
 *        public void       setAll(int index, Collection<? extends T> c)     update the value of collections of elements of SinglelyLinkedList which start from specified position
 *        public T[]        toArray()                                        return the array type of SinglelyLinkedList
 *        public int        size()                                           return the size of SinglelyLinkedList
 *        private boolean   outOfRange(int index)                            return true if index is out of the range of SinglelyLinkedList
 *        private Node      getNode(int position)                            return the instances of Node which at the specified position at SinglelyLinkedList
 */
import java.util.*;



public class SinglelyLinkedList<T> {
    private class Node<T> {
        T value;
        Node next;
        public Node() {
            value = null;
            next = null;
        }
        
    }
    private Node head;
    private Node tail;
    private int size = 0;
    
    public SinglelyLinkedList() {
        Node node = new Node();
        head = node;
        tail = node;
        size  = 1;
    }
    
    public SinglelyLinkedList(Collection<? extends T> c) {
        Node node = new Node();
        head = node;
        tail = node;
        size = 1;
        addAll(c);
    }
    
    public <T> void add(int index, T element) {
        if (index == 0) {
            addFirst(element);
        }   else if (index == size) {
                addLast(element);
            }   else if (!outOfRange(index)) {
                    Node indexingNode = getNode(index);
                    Node tempNode = new Node();
                    tempNode.value = element;
                    tempNode.next = indexingNode.next;
                    indexingNode.next = tempNode;
                    size += 1;
                }   else throw new IndexOutOfBoundsException();
    }
    
    public <T> boolean addFirst(T element) {
        Node tempNode = new Node();
        tempNode.value = element;
        tempNode.next = head;
        head = tempNode;
        size += 1;
        return true;
    }
    
    public <T> boolean addLast(T element) {
        Node tempNode = new Node();
        tempNode.value = element;
        tail.next = tempNode;
        tail = tempNode;
        size += 1;
        return true;
    }
    
    public boolean addAll(Collection<? extends T> c) {
        for (T element : c) {
            addLast(element);
        }
        return true;
    }
    
    public void delete(int index) {
        if (index == 0) {
            Node tempNode = head;
            head = head.next;
            tempNode.next = null;
            tempNode = null;
        } else if(index == size - 1) {
            Node indexingNode = getNode(size - 2);
            tail = indexingNode;
            tail.next = null;
        } else if (!outOfRange(index)) {             // set useless node's next to null for memory saving
            Node indexingNode = getNode(index - 1);
            Node tempNode = indexingNode.next.next;
            indexingNode.next.next = null; 
            indexingNode.next = tempNode;
            tempNode = null;
        } else throw new IndexOutOfBoundsException();
    }
    
    public Node getFirst() {
        return head;
    }
    
    public Node getLast() {
        return tail;
    }
    
    public Node get(int index) {
        if (index == 0) {
            return getFirst();
        } else if (index == size - 1) {
            return getLast();
        } else if (!outOfRange(index)) {
            return getNode(index);
        } else throw new IndexOutOfBoundsException();
    }
    
    public <t> void set(int index, T element) {
        if (index == 0) {
            head.value = element;
        } else if (index == size - 1) {
            tail.value = element;
        } else if (!outOfRange(index)) {
            getNode(index).value = element;
        } else throw new IndexOutOfBoundsException();
    }
    
    public void setAll(int index, Collection<? extends T> c) {
        for (T element : c) {                    // invoke set function, but it is low efficient with lot of branchs;
            set(index, element);
            index++;
        }
    }
    
    public T[] toArray() {
        T[] tempArray =(T[]) new Object[size];
        Node traveller = head;
        for (int i = 0; i < size; i++) {
            tempArray[i] = (T) traveller.value;
            traveller = traveller.next;
        }
        return tempArray;
    }
    
    public int size() {
        return size;
    }
    
    
    private Node getNode(int index) {
        Node tempNode = head;
        for (int i = 1; i <= index; i++) {
            tempNode = tempNode.next;
        }
        return tempNode;
    }
    
    private boolean outOfRange(int index) {
        if (index < 0 || index >= size) {
            return true;
        }   else return false;
    }
    

}
