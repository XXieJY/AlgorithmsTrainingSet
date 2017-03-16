/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jxie
 * @description
 * Lookup table is an application specified array type data structure
 * which is more efficient because indexing operation is more faster than 
 * computation operation.
 * For example: we can uses lookup table for checking which month has no more 
 * dates than 30.
 * Obviously, we can write down with switch-case clause like:
 * 
 * switch(month) {
 *  case 2: 
 *  return true;
 *  break;
 *  case 4:
 *  return true;
 *  break;
 *  case 6:
 *  return true;
 *  break;
 *  case 9:
 *  return true;
 *  break;
 *  case 11:
 *  return true;
 *  break;
 * }
 * 
 * but what if we use lookup table which contains 
 * the temporary results in an array, and we just 
 * check it for what we need;
 * 
 */
import java.util.*;

public class LookupTable {
    
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            System.out.println(smallMonth(sc.nextInt()));
        }
    }
    
    public static boolean smallMonth(int month) {
        int[] table = new int[]{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0};
        try {
            if (table[month] == 1) {
                return true;
            }   else return false;
        } catch (Exception e) {
            System.out.println("please enter a number between 1 ~ 12");
        }
        return false;
    }
}
