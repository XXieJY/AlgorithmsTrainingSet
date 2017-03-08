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
 * +  API public class DynamicArray<T>                                       +
 * -----------------------------------------------------------------------------
 *              
 *        private  void    grow()                    grow the dynamic array by default GROWTH_RATE = 1.5
 *        private  void    deallocate(int position)  deallocate the dynamic array by default DEALLOCATE_RATE = 0.6; caution: DEALLOCATE RATE must less than GROWTH RATE
 *        private  boolean isOutbound()         examine the position is outbound or not
 *        public   void    DynamicArray()            initialize a dynamic array with DEFAULT_LENGTH = 10
 *        public   void    DynamicArray(int length)  initialize a dynamic array with length of l
 *        public   void    add(T element)            add a new element with type of T into dynamic array
 *        public   T       remove()                  return and remove the last element from dynamic array
 *        public   T       remove(int position)      return and remove the element at appointed position of dynamic array
 *        public   void    removeAll()               remove all elements of dynamic array
 *        public   void set(int position, T element) set the element at appointed position into given element e of type T
 *        public   T       getFirst()                get the first element of dynamic array
 *        public   T       get(int position)         get the element at the appointed position of dynamic array
 *        public   T       getLast()                 get the last element from dynamic array
 *        public   int     size()                    return the size of dynamic array
 *             
 */

public class DynamicArray<T> {
    private static final int DEFAULT_LENGTH = 10;
    private static final double GROWTH_RATE = 1.5;
    private static final double DEALLOCATE_RATE = 0.6;
    private int arrayLength;
    private int maxSize;
    private T[] array;
    
    
    public DynamicArray() {     //arrayLength start from 0 to n, when arrayLength == 1 means that array has one element at array[0];
        arrayLength = 0;
        maxSize = DEFAULT_LENGTH;
        array = (T[]) new Object[DEFAULT_LENGTH];
    }
    
    public DynamicArray(int length) {
        arrayLength = 0;
        maxSize = length;
        array = (T[]) new Object[maxSize];
    }
    
    public void add(T element) {
        if (arrayLength == maxSize) grow();     //arrayLength equals maxSize means the array is full, dynamic array will grow;
        array[arrayLength++] = element;
    }
    
    public T remove() {
        if (arrayLength == 0) return null;
        if (arrayLength <= (int)(0.5 * maxSize)) deallocate();  //deallocate dynamic array when it uses less than half of entire spaces;
        T temp = array[--arrayLength];
        array[arrayLength] = null;
        return temp;
    }
    
    public T remove(int position) {
        if (!isOutbound(position)) {
            T temp = array[position];
            for (int i = position + 1; i < arrayLength; i++) {
                array[i - 1] = array[i];
            }
            array[arrayLength - 1] = null;  // clean the reference of the last element which before the arrayLength;
            return temp;
        }
        else throw new ArrayIndexOutOfBoundsException();
    }
    
    public void removeAll() {
        if (arrayLength == 0) ;
        else {
            int newLength = (int) (maxSize * DEALLOCATE_RATE);
            T[] temp = (T[]) new Object[newLength];      // just create a new dynamic array with sixty percent length of origin one;
            array = temp;
            temp = null;
        }
    }
    
    public void set(int position, T value) {
        if (!isOutbound(position)) {
            array[position] = value;
        }
        else throw new ArrayIndexOutOfBoundsException();
    }
    
    public T getFirst() {
        if (arrayLength == 0) return null;
        else return array[0];
    }
    
    public T getLast() {
        if (arrayLength == 0) return null;
        else return array[arrayLength - 1];
    }
    
    public T get(int position) {
        if (!isOutbound(position)) {
            return array[position];
        }
        else throw new ArrayIndexOutOfBoundsException();
    }
    
    public int size() {
        return arrayLength;
    }
    
    
    private void grow() {
        int newLength = (int) (maxSize * GROWTH_RATE);
        T[] temp = (T[]) new Object[newLength];
        for (int i = 0; i < maxSize; i++) {
            temp[i] = array[i];
        }
        array = temp;
        temp = null;
        maxSize = newLength;
    }
    
    private void deallocate() {     //take care to deallocate function, because it probably invoke OutOfBoundsException of temp array when newLength less than arrayLength;
        int newLength = (int) (maxSize * DEALLOCATE_RATE);
        T[] temp = (T[]) new Object[newLength];
        for (int i = 0; i < arrayLength; i++) {
            temp[i] = array[i];
        }
        array = temp;
        temp = null;
        maxSize = newLength;
    }
    
    private boolean isOutbound(int position) {
        if (position >= maxSize) return true;  // array bounds start from 0 to maxiSize;
        else return false;
    }
    
    public static void main(String[] args) {
        DynamicArray<Integer> test = new DynamicArray<Integer>();
        DynamicArray<String> test2 = new DynamicArray<String>(100);
        System.out.println("test should has size 0: " + test.size());
        System.out.println("test2 should has size 100" + test2.size());
        test.add(1);
        test.add(2);
        test.add(3);
        test.remove();
        System.out.println("This should be one: " + test.getFirst() + " And should be two: " + test.getLast());
        test.removeAll();
        System.out.println("This shoule be null:" + test.getFirst() + " And should be null: " + test.getLast());
    }
    
    
}
