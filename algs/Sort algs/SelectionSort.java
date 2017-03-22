/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sortingAlgs;

/**
 *
 * @author jxie
 * @description
 * ----------------------------------------------------------------------------
 * This is implementations for selection sorting algorithms depends on major 
 * java data structures: LinkedList, arrayList;
 * ----------------------------------------------------------------------------
 * There are two version of implementations of selection sorting:
 * 1.directly selection sorting:
 *      The time complexity for directly selection sorting is O(n^2);
 *      The space complexity for directly selection sorting is O(1);
 *      It is an unstable sorting algorithm;
 * 2.selection sorting based on heap
 *      The time complexity for selection sorting based on heap is O(nlogn);
 *      The space complexity for selection sorting based on heap is O(1);
 *      It is an unstable sorting algorithm;
 */
import java.util.*;

public class SelectionSort {
    private static AbstractList<Integer> list;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String str = sc.nextLine();
            sortArrayList(str);
            show();
        }
    }
      
    public static void show() {
        for (Integer i : list) {
            System.out.print(i + " ");
        }
    }
    
    private static void sortArrayList(String str) {
        list = new ArrayList();
        String[] tempList = str.split(",");
        int length = tempList.length;
        for (int i = 0; i < length; i++) {
            list.add(Integer.parseInt(tempList[i]));
        }
        int listSize = list.size();
        for (int i = 0; i < listSize; i++) {
            int indexOfMinimumNumber = i;
            for (int j = i + 1; j < listSize; j++) {
                if (list.get(j) < list.get(indexOfMinimumNumber)) {
                    indexOfMinimumNumber = j;
                }
            }
            int temp = list.get(i);
            int minimumNumber = list.get(indexOfMinimumNumber);
            list.set(i, minimumNumber);
            list.set(indexOfMinimumNumber, temp);
        }
    }
}
    
    

