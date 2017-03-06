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
 * +  API public class CircularBuffer<T>                                       +
 * -----------------------------------------------------------------------------
 *             void    CircularBuffer(int l)     initialize a circular buffer with length of l
 *             void    push(T e)                 push a new element with type of T into circular buffer
 *             T       pop()                     get and remove the first element from circular buffer
 *             T       peekFirst()               get but don't remove the first element from circular buffer
 *             T       peekLast()                get but don't remove the last element from circular buffer
 *             boolean clean()                   remove all the elements in circular buffer
 *             int     size()                    return the size of circular buffer
 */

import java.nio.BufferOverflowException;
import java.nio.BufferUnderflowException;        
        
public class CircularBuffer<T> {
    private int front;
    private int rear;
    private int currentSize;
    private int maxSize;
    private T[] buffer;
    
    public CircularBuffer(int n) {
        buffer = (T[]) new Object[n];
        front = 0;
        rear = 0;
        currentSize = 0;
        maxSize = n;
    }
    
    public void push(T e) {
        if (!isFull()) {
            buffer[rear] = e;
            currentSize++;
            rear = (rear + 1) % maxSize;
        } else throw new BufferOverflowException();
    }
    
    public T pop() {
        if (!isEmpty()) {
            T temp = buffer[front];
            buffer[front] = null;
            front = (front + 1) % maxSize;
            currentSize--;
            return temp;
        } else throw new BufferUnderflowException();
    }
    
    public T peekFirst() {
        if (!isEmpty()) {
            return buffer[front];
        } else  return null;
    }
    
    public T peekLast() {
        if (!isEmpty()) {
            return buffer[rear - 1];
        } else return null;
    }
    
    public int size() {
        return currentSize;
    }
    
    public boolean isEmpty() {
        if (currentSize == 0) {
            return true;
        } else return false;
    }
    
    public boolean isFull() {
        if (currentSize == maxSize) {
            return true;
        } else return false;
    }
    
    public boolean clean() { //How could this clean option to be failse?
        front = 0;           //set all old references to null and call the JVM collection mechanism
        rear = 0;
        while (rear != 0) {
            buffer[rear] = null;
            rear = (rear + 1) % maxSize;
        }   
        return true;
    }
    
    public static void main(String[] args) {
        CircularBuffer<Integer> buff = new CircularBuffer<>(7);
        buff.push(0);
        buff.push(1);
        buff.push(2);
        System.out.println(buff.size());
        System.out.println("The head element is: " + buff.pop());
        System.out.println("Size should be twoo: " + buff.size());
        System.out.println("The last element is: " + buff.peekLast());
        System.out.println("Size should be two: " + buff.size());
        buff.clean();
        System.out.println("Size should be zero: " + buff.size());
        
    }
}
